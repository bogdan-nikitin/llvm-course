#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {

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
              Value *operandOpcode = builder.CreateGlobalStringPtr(
                  operand->getOpcodeName());
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
      MPM.addPass(MyModPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
