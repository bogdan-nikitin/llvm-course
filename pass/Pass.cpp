#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct LogPass : public PassInfoMixin<LogPass> {

  static bool isFuncLogger(StringRef name) { return name == "useLogger"; }

  static bool isPhiInstruction(Instruction &I) {
    return I.getOpcode() == Instruction::PHI;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    for (auto &F : M) {
      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      LLVMContext &Ctx = F.getContext();
      IRBuilder<> builder(Ctx);
      Type *retType = Type::getVoidTy(Ctx);

      ArrayRef<Type *> useParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                        builder.getInt8Ty()->getPointerTo()};
      FunctionType *useLogFuncType =
          FunctionType::get(retType, useParamTypes, false);
      FunctionCallee useLogFunc =
          M.getOrInsertFunction("useLogger", useLogFuncType);

      for (auto &B : F) {
        for (auto &I : B) {
          if (isPhiInstruction(I)) {
            continue;
          }
          builder.SetInsertPoint(&I);
          Value *opcode = builder.CreateGlobalStringPtr(I.getOpcodeName());
          for (auto &U : I.operands()) {
            Value *use = U.get();
            if (auto operand = dyn_cast<Instruction>(use)) {
              if (isPhiInstruction(*operand)) {
                continue;
              }
              Value *operandOpcode =
                  builder.CreateGlobalStringPtr(operand->getOpcodeName());
              Value *args[] = {operandOpcode, opcode};
              builder.CreateCall(useLogFunc, args);
            }
          }
        }
      }
    }
    return PreservedAnalyses::all();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(LogPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "LogPlugin", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
