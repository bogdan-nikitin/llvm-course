#include "include/extIR.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void ExtIR::buildIR(Binary &Bin) {
  module = new Module("top", context);
  IRBuilder<> builder(context);
  Type *voidType = Type::getVoidTy(context);
  Type *int64Type = Type::getInt64Ty(context);

  //[16 x i64] regFile = {0, 0, 0, 0}
  ArrayType *regFileType = ArrayType::get(int64Type, CPU::RegSize);
  module->getOrInsertGlobal("regFile", regFileType);
  regFile = module->getNamedGlobal("regFile");

  // declare void @main()
  FunctionType *funcType = FunctionType::get(voidType, false);
  mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);
  // Funcions types
  FunctionType *voidFuncType = FunctionType::get(voidType, false);
  ArrayRef<Type *> int64x4Types = {int64Type, int64Type, int64Type, int64Type};
  FunctionType *int64x4FuncType =
      FunctionType::get(voidType, int64x4Types, false);

  // Functions
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  FunctionCallee Callee##_Name =                                               \
      module->getOrInsertFunction("do_" #_Name, int64x4FuncType);
#include "include/ISA.h"
#undef _ISA

  std::unordered_map<uint64_t, BasicBlock *> BBMap;
  for (auto &BB : Bin.PC2BBName) {
    BBMap[BB.first] = BasicBlock::Create(context, BB.second, mainFunc);
  }

  uint64_t PC = 0;
  builder.SetInsertPoint(BBMap[0]);
  for (Instr &I : Bin.Instrs) {
    Value *arg1 = builder.getInt64(I.A1);
    Value *arg2 = builder.getInt64(I.A2);
    Value *arg3 = builder.getInt64(I.A3);
    Value *arg4 = builder.getInt64(I.A4);
    Value *args[] = {arg1, arg2, arg3, arg4};
    switch (I.Op) {
    default:
      break;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    builder.CreateCall(Callee##_Name, args);                                   \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    PC++;
    if (I.Op == Instr::BR) {
      builder.CreateBr(BBMap[I.A1]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    } else if (I.Op == Instr::BREQ) {
      builder.CreateCondBr(builder.CreateICmpEQ(LOAD_REG(I.A2), GEN_IMM(I.A3)),
                           BBMap[I.A1], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    } else if (I.Op == Instr::BRZ) {
      builder.CreateCondBr(
          builder.CreateICmpEQ(builder.CreateOr(LOAD_REG(I.A2), LOAD_REG(I.A3)),
                               GEN_IMM(0)),
          BBMap[I.A1], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    } else if (I.Op == Instr::LOOP) {
      builder.CreateCondBr(builder.CreateICmpEQ(LOAD_REG(I.A2), GEN_IMM(I.A3)),
                           BBMap[PC], BBMap[I.A1]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    }
    auto BB = BBMap.find(PC);
    if (I.Op == Instr::EXIT) {
      builder.CreateRetVoid();
      if (BB != BBMap.end())
        builder.SetInsertPoint(BB->second);
      continue;
    }
    if (BB != BBMap.end()) {
      builder.CreateBr(BB->second);
      builder.SetInsertPoint(BB->second);
    }
  }
}

void ExtIR::dumpIR() {
  outs() << "\n[LLVM IR]:\n";
  module->print(outs(), nullptr);
  outs() << "\n";
}
bool ExtIR::verifyIR() {
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
  return verif;
}

void ExtIR::executeIR(CPU &Cpu) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  if (fnName == "_do_" #_Name)                                                 \
    return reinterpret_cast<void *>(CPU::do_##_Name);
#include "include/ISA.h"
#undef _ISA
    return nullptr;
  });

  ee->addGlobalMapping(regFile, (void *)Cpu.RegFile);
  ee->finalizeObject();

  simInit();
  CPU::setCPU(&Cpu);
  // Cpu.DumpInstrs = true;

  ArrayRef<GenericValue> noargs;
  outs() << "\n#[Running code]\n";
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  simExit();
}
