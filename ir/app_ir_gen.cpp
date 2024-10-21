#include "../sim.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/MCJIT.h"
using namespace llvm;

int main() {
  LLVMContext context;
  // ; ModuleID = 'app.c'
  // source_filename = "app.c"
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);

  // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
  // local_unnamed_addr #1
  Type *voidType = Type::getVoidTy(context);
  ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                            Type::getInt32Ty(context),
                                            Type::getInt32Ty(context)};
  FunctionType *simPutPixelType =
      FunctionType::get(voidType, simPutPixelParamTypes, false);
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", simPutPixelType);

  // declare void @simFlush(...) local_unnamed_addr #1
  FunctionType *simFlushType = FunctionType::get(voidType, {voidType}, false);
  FunctionCallee simFlushFunc =
      module->getOrInsertFunction("simFlush", simFlushType);

  FunctionType *simRandType = FunctionType::get(Type::getInt32Ty(context), {voidType}, false);
  FunctionCallee simRandFunc =
      module->getOrInsertFunction("simRand", simRandType);

  // define void @app() local_unnamed_addr #0 {
  FunctionType *appFuncType = FunctionType::get(builder.getInt32Ty(), false);
  Function *appFunc =
      Function::Create(appFuncType, Function::ExternalLinkage, "app", module);

  BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB2 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB5 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB8 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB17 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB22 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB27 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB30 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB33 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB43 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB63 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB65 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB68 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB139 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB141 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB143 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB148 = BasicBlock::Create(context, "", appFunc);

  // 0:
  builder.SetInsertPoint(BB0);
//   %1 = alloca [262144 x i8], align 1

  Value* val1 = builder.CreateAlloca(ArrayType::get(builder.getInt8Ty(), 262144));
  // TODO: examine
//   call void @llvm.lifetime.start.p0(i64 262144, ptr nonnull %1) #3
  builder.CreateLifetimeStart(val1, builder.getInt64(262144));
//   br label %2
  builder.CreateBr(BB2);

// 2:                                                ; preds = %0, %5
  builder.SetInsertPoint(BB2);
//   %3 = phi i64 [ 0, %0 ], [ %6, %5 ]
  PHINode *val3 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %4 = shl nuw nsw i64 %3, 9
  Value* val4 = builder.CreateShl(val3, builder.getInt64(9), "", true, true);
//   br label %8
  builder.CreateBr(BB8);

// 5:                                                ; preds = %8
  builder.SetInsertPoint(BB5);
//   %6 = add nuw nsw i64 %3, 1
  Value* val6 = builder.CreateAdd(val3, builder.getInt64(1), "", true, true);
//   %7 = icmp eq i64 %6, 256
  Value *val7 = builder.CreateICmpEQ(val6, builder.getInt64(256));
//   br i1 %7, label %17, label %2, !llvm.loop !5
  builder.CreateCondBr(val7, BB17, BB2);

// 8:                                                ; preds = %2, %8
  builder.SetInsertPoint(BB8);
//   %9 = phi i64 [ 0, %2 ], [ %15, %8 ]
  PHINode* val9 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %10 = tail call i32 @simRand() #3
  Value* val10 = builder.CreateCall(simRandFunc);
//   %11 = srem i32 %10, 2
  Value* val11 = builder.CreateSRem(val10, builder.getInt32(2));
//   %12 = trunc nsw i32 %11 to i8
  Value* val12 = builder.CreateTrunc(
      val11, builder.getInt8Ty(), "", false, true);
//   %13 = add nuw nsw i64 %9, %4
  Value* val13 = builder.CreateAdd(val9, val4, "", true, true);
//   %14 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %13
  Value* val14 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val13});
//   store i8 %12, ptr %14, align 1, !tbaa !7
  builder.CreateStore(val12, val14);
//   %15 = add nuw nsw i64 %9, 1
  Value* val15 = builder.CreateAdd(val9, builder.getInt64(1), "", true, true);
//   %16 = icmp eq i64 %15, 512
  Value* val16 = builder.CreateICmpEQ(val15, builder.getInt64(512));
//   br i1 %16, label %5, label %8, !llvm.loop !10
  builder.CreateCondBr(val16, BB5, BB8);

// 17:                                               ; preds = %5, %63
  builder.SetInsertPoint(BB17);
//   %18 = phi i8 [ %64, %63 ], [ 0, %5 ]
  PHINode* val18 = builder.CreatePHI(builder.getInt8Ty(), 2);
//   %19 = zext nneg i8 %18 to i32
  Value* val19 = builder.CreateZExt(val18, builder.getInt32Ty(), "", true);
//   %20 = shl nuw nsw i32 %19, 17
  Value* val20 = builder.CreateShl(val19, builder.getInt32(17), "", true, true);
//   %21 = zext nneg i32 %20 to i64
  Value* val21 = builder.CreateZExt(val20, builder.getInt64Ty(), "", true);
//   br label %22
  builder.CreateBr(BB22);

// 22:                                               ; preds = %17, %30
  builder.SetInsertPoint(BB22);
//   %23 = phi i64 [ 0, %17 ], [ %31, %30 ]
  PHINode* val23 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %24 = shl nuw nsw i64 %23, 9
  Value* val24 = builder.CreateShl(val23, builder.getInt64(9), "", true, true);
//   %25 = add nuw nsw i64 %24, %21
  Value* val25 = builder.CreateAdd(val24, val21, "", true, true);
//   %26 = trunc nuw nsw i64 %23 to i32
  Value* val26 = builder.CreateTrunc(
      val23, builder.getInt32Ty(), "", true, true);
//   br label %33
  builder.CreateBr(BB33);

// 27:                                               ; preds = %30
  builder.SetInsertPoint(BB27);
//   tail call void @simFlush() #3
  builder.CreateCall(simFlushFunc);
//   %28 = icmp eq i8 %18, 0
  Value* val28 = builder.CreateICmpEQ(val18, builder.getInt8(0));
//   %29 = select i1 %28, i64 131072, i64 0
  Value* val29 = builder.CreateSelect(val28, builder.getInt64(131072), builder.getInt64(0));
//   br label %43
  builder.CreateBr(BB43);

// 30:                                               ; preds = %33
  builder.SetInsertPoint(BB30);
//   %31 = add nuw nsw i64 %23, 1
  Value* val31 = builder.CreateAdd(val23, builder.getInt64(1), "", true, true);
//   %32 = icmp eq i64 %31, 256
  Value* val32 = builder.CreateICmpEQ(val31, builder.getInt64(256));
//   br i1 %32, label %27, label %22, !llvm.loop !11
  builder.CreateCondBr(val32, BB27, BB22);


// 33:                                               ; preds = %22, %33
  builder.SetInsertPoint(BB33);
//   %34 = phi i64 [ 0, %22 ], [ %41, %33 ]
  PHINode* val34 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %35 = add nuw nsw i64 %34, %25
  Value* val35 = builder.CreateAdd(val34, val25, "", true, true);
//   %36 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %35
  Value* val36 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val35});
//   %37 = load i8, ptr %36, align 1, !tbaa !7
  Value* val37 = builder.CreateLoad(builder.getInt8Ty(), val36);
//   %38 = icmp eq i8 %37, 0
  Value* val38 = builder.CreateICmpEQ(val37, builder.getInt8(0));
//   %39 = select i1 %38, i32 -16777216, i32 -1
  Value* val39 = builder.CreateSelect(val38, builder.getInt32(-16777216), builder.getInt32(-1));
//   %40 = trunc nuw nsw i64 %34 to i32
  Value* val40 = builder.CreateTrunc(val34, builder.getInt32Ty(), "", true, true);
//   tail call void @simPutPixel(i32 noundef %40, i32 noundef %26, i32 noundef %39) #3
  Value *args[] = {val40, val26, val39};
  builder.CreateCall(simPutPixelFunc, args);
//   %41 = add nuw nsw i64 %34 
  Value* val41 = builder.CreateAdd(val34, builder.getInt64(1), "", true, true);
//   %42 = icmp eq i64 %41, 512
  Value* val42 = builder.CreateICmpEQ(val41, builder.getInt64(512));
//   br i1 %42, label %30, label %33, !llvm.loop !12
  builder.CreateCondBr(val42, BB30, BB33);

// 43:                                               ; preds = %27, %65
  builder.SetInsertPoint(BB43);
//   %44 = phi i64 [ 0, %27 ], [ %66, %65 ]
  PHINode* val44 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %45 = shl nuw nsw i64 %44, 9
  Value* val45 = builder.CreateShl(val44, builder.getInt64(9), "", true, true);
//   %46 = add nuw nsw i64 %45, %21
  Value* val46 = builder.CreateAdd(val45, val21, "", true, true);
//   %47 = or disjoint i64 %45, %29
  Value* val47 = builder.CreateOr(val45, val29);  // TODO: disjoint, logical
//   %48 = add nuw nsw i64 %45, %29
  Value* val48 = builder.CreateAdd(val45, val29, "", true, true);
//   %49 = trunc i64 %44 to i32
  Value* val49 = builder.CreateTrunc(val44, builder.getInt32Ty());
//   %50 = shl i32 %49, 9
  Value* val50 = builder.CreateShl(val49, builder.getInt32(9));
//   %51 = add i32 %50, 130560
  Value* val51 = builder.CreateAdd(val50, builder.getInt32(130560));
//   %52 = and i32 %51, 130560
  Value* val52 = builder.CreateAnd(val51, builder.getInt32(130560));
//   %53 = or disjoint i32 %52, %20
  Value* val53 = builder.CreateOr(val52, val20);  // TODO: disjoint, logical
//   %54 = trunc i64 %44 to i32
  Value* val54 = builder.CreateTrunc(val44, builder.getInt32Ty());
//   %55 = shl i32 %54, 9
  Value* val55 = builder.CreateShl(val54, builder.getInt32(9));
//   %56 = and i32 %55, 130560
  Value* val56 = builder.CreateAnd(val55, builder.getInt32(130560));
//   %57 = or disjoint i32 %56, %20
  Value* val57 = builder.CreateOr(val56, val20);
//   %58 = trunc i64 %44 to i32
  Value* val58 = builder.CreateTrunc(val44, builder.getInt32Ty());
//   %59 = shl i32 %58, 9
  Value* val59 = builder.CreateShl(val58, builder.getInt32(9));
//   %60 = add i32 %59, 512
  Value* val60 = builder.CreateAdd(val59, builder.getInt32(512));
//   %61 = and i32 %60, 130560
  Value* val61 = builder.CreateAnd(val60, builder.getInt32(130560));
//   %62 = or disjoint i32 %61, %20
  Value* val62 = builder.CreateOr(val61, val20);
//   br label %68
  builder.CreateBr(BB68);

// 63:                                               ; preds = %65
  builder.SetInsertPoint(BB63);
//   %64 = xor i8 %18, 1
  Value* val64 = builder.CreateXor(val18, builder.getInt8(1));
//   br label %17
  builder.CreateBr(BB17);

// 65:                                               ; preds = %148
  builder.SetInsertPoint(BB65);
//   %66 = add nuw nsw i64 %44 
  Value* val66 = builder.CreateAdd(val44, builder.getInt64(1), "", true, true);
//   %67 = icmp eq i64 %66, 256
  Value* val67 = builder.CreateICmpEQ(val66, builder.getInt64(256));
//   br i1 %67, label %63, label %43, !llvm.loop !13
  builder.CreateCondBr(val67, BB63, BB43);

// 68:                                               ; preds = %148, %43
  builder.SetInsertPoint(BB68);
//   %69 = phi i64 [ 0, %43 ], [ %152, %148 ]
  PHINode* val69 = builder.CreatePHI(builder.getInt64Ty(), 2);
//   %70 = trunc i64 %69 to i32
  Value* val70 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %71 = add i32 %70, 511
  Value* val71 = builder.CreateAdd(val70, builder.getInt32(511));
//   %72 = and i32 %71, 511
  Value* val72 = builder.CreateAnd(val71, builder.getInt32(511));
//   %73 = or disjoint i32 %53, %72
  Value* val73 = builder.CreateOr(val53, val72);
//   %74 = zext nneg i32 %73 to i64
  Value* val74 = builder.CreateZExt(val73, builder.getInt64Ty(), "", true);
//   %75 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %74
  Value* val75 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val74});
//   %76 = load i8, ptr %75, align 1, !tbaa !7
  Value* val76 = builder.CreateLoad(builder.getInt8Ty(), val75);
//   %77 = sext i8 %76 to i32
  Value* val77 = builder.CreateSExt(val76, builder.getInt32Ty());
//   %78 = trunc i64 %69 to i32
  Value* val78 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %79 = and i32 %78, 511
  Value* val79 = builder.CreateAnd(val78, builder.getInt32(511));
//   %80 = or disjoint i32 %53, %79
  Value* val80 = builder.CreateOr(val53, val79);
//   %81 = zext nneg i32 %80 to i64
  Value* val81 = builder.CreateZExt(val80, builder.getInt64Ty(), "", true);
//   %82 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %81
  Value* val82 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val81});
//   %83 = load i8, ptr %82, align 1, !tbaa !7
  Value* val83 = builder.CreateLoad(builder.getInt8Ty(), val82);
//   %84 = sext i8 %83 to i32
  Value* val84 = builder.CreateSExt(val83, builder.getInt32Ty());
//   %85 = add nsw i32 %77, %84
  Value* val85 = builder.CreateNSWAdd(val77, val84);
//   %86 = trunc i64 %69 to i32
  Value* val86 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %87 = add i32 %86, 1
  Value* val87 = builder.CreateAdd(val86, builder.getInt32(1));
//   %88 = and i32 %87, 511
  Value* val88 = builder.CreateAnd(val87, builder.getInt32(511));
//   %89 = or disjoint i32 %53, %88
  Value* val89 = builder.CreateOr(val53, val88);
//   %90 = zext nneg i32 %89 to i64
  Value* val90 = builder.CreateZExt(val89, builder.getInt64Ty(), "", true);
//   %91 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %90
  Value* val91 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val90});
//   %92 = load i8, ptr %91, align 1, !tbaa !7
  Value* val92 = builder.CreateLoad(builder.getInt8Ty(), val91);
//   %93 = sext i8 %92 to i32
  Value* val93 = builder.CreateSExt(val92, builder.getInt32Ty());
//   %94 = add nsw i32 %85, %93
  Value* val94 = builder.CreateNSWAdd(val85, val93);
//   %95 = trunc i64 %69 to i32
  Value* val95 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %96 = add i32 %95, 511
  Value* val96 = builder.CreateAdd(val95, builder.getInt32(511));
//   %97 = and i32 %96, 511
  Value* val97 = builder.CreateAnd(val96, builder.getInt32(511));
//   %98 = or disjoint i32 %57, %97
  Value* val98 = builder.CreateOr(val57, val97);
//   %99 = zext nneg i32 %98 to i64
  Value* val99 = builder.CreateZExt(val98, builder.getInt64Ty(), "", true);
//   %100 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %99
  Value* val100 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val99});
//   %101 = load i8, ptr %100, align 1, !tbaa !7
  Value* val101 = builder.CreateLoad(builder.getInt8Ty(), val100);
//   %102 = sext i8 %101 to i32
  Value* val102 = builder.CreateSExt(val101, builder.getInt32Ty());
//   %103 = add nsw i32 %94, %102
  Value* val103 = builder.CreateNSWAdd(val94, val102);
//   %104 = trunc i64 %69 to i32
  Value* val104 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %105 = add i32 %104, 1
  Value* val105 = builder.CreateAdd(val104, builder.getInt32(1));
//   %106 = and i32 %105, 511
  Value* val106 = builder.CreateAnd(val105, builder.getInt32(511));
//   %107 = or disjoint i32 %57, %106
  Value* val107 = builder.CreateOr(val57, val106);
//   %108 = zext nneg i32 %107 to i64
  Value* val108 = builder.CreateZExt(val107, builder.getInt64Ty(), "", true);
//   %109 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %108
  Value* val109 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val108});
//   %110 = load i8, ptr %109, align 1, !tbaa !7
  Value* val110 = builder.CreateLoad(builder.getInt8Ty(), val109);
//   %111 = sext i8 %110 to i32
  Value* val111 = builder.CreateSExt(val110, builder.getInt32Ty());
//   %112 = add nsw i32 %103, %111
  Value* val112 = builder.CreateNSWAdd(val103, val111);
//   %113 = trunc i64 %69 to i32
  Value* val113 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %114 = add i32 %113, 511
  Value* val114 = builder.CreateAdd(val113, builder.getInt32(511));
//   %115 = and i32 %114, 511
  Value* val115 = builder.CreateAnd(val114, builder.getInt32(511));
//   %116 = or disjoint i32 %62, %115
  Value* val116 = builder.CreateOr(val62, val115);
//   %117 = zext nneg i32 %116 to i64
  Value* val117 = builder.CreateZExt(val116, builder.getInt64Ty(), "", true);
//   %118 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %117
  Value* val118 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val117});
//   %119 = load i8, ptr %118, align 1, !tbaa !7
  Value* val119 = builder.CreateLoad(builder.getInt8Ty(), val118);
//   %120 = sext i8 %119 to i32
  Value* val120 = builder.CreateSExt(val119, builder.getInt32Ty());
//   %121 = add nsw i32 %112, %120
  Value* val121 = builder.CreateNSWAdd(val112, val120);
//   %122 = trunc i64 %69 to i32
  Value* val122 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %123 = and i32 %122, 511
  Value* val123 = builder.CreateAnd(val122, builder.getInt32(511));
//   %124 = or disjoint i32 %62, %123
  Value* val124 = builder.CreateOr(val62, val123);
//   %125 = zext nneg i32 %124 to i64
  Value* val125 = builder.CreateZExt(val124, builder.getInt64Ty(), "", true);
//   %126 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %125
  Value* val126 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val125});
//   %127 = load i8, ptr %126, align 1, !tbaa !7
  Value* val127 = builder.CreateLoad(builder.getInt8Ty(), val126);
//   %128 = sext i8 %127 to i32
  Value* val128 = builder.CreateSExt(val127, builder.getInt32Ty());
//   %129 = add nsw i32 %121, %128
  Value* val129 = builder.CreateNSWAdd(val121, val128);
//   %130 = trunc i64 %69 to i32
  Value* val130 = builder.CreateTrunc(val69, builder.getInt32Ty());
//   %131 = add i32 %130, 1
  Value* val131 = builder.CreateAdd(val130, builder.getInt32(1));
//   %132 = and i32 %131, 511
  Value* val132 = builder.CreateAnd(val131, builder.getInt32(511));
//   %133 = or disjoint i32 %62, %132
  Value* val133 = builder.CreateOr(val62, val132);
//   %134 = zext nneg i32 %133 to i64
  Value* val134 = builder.CreateZExt(val133, builder.getInt64Ty(), "", true);
//   %135 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %134
  Value* val135 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val134});
//   %136 = load i8, ptr %135, align 1, !tbaa !7
  Value* val136 = builder.CreateLoad(builder.getInt8Ty(), val135);
//   %137 = sext i8 %136 to i32
  Value* val137 = builder.CreateSExt(val136, builder.getInt32Ty());
//   %138 = add nsw i32 %129, %137
  Value* val138 = builder.CreateNSWAdd(val129, val137);
//   switch i32 %138, label %141 [
//     i32 3, label %139
//     i32 2, label %143
//   ]
  SwitchInst* sw = builder.CreateSwitch(val138, BB141, 2);
  sw->addCase(builder.getInt32(3), BB139);
  sw->addCase(builder.getInt32(2), BB143);

// 139:                                              ; preds = %68
  builder.SetInsertPoint(BB139);
//   %140 = add nuw nsw i64 %69, %48
  Value* val140 = builder.CreateAdd(val69, val48, "", true, true);
//   br label %148
  builder.CreateBr(BB148);

// 141:                                              ; preds = %68
  builder.SetInsertPoint(BB141);
//   %142 = add nuw nsw i64 %69, %48
  Value* val142 = builder.CreateAdd(val69, val48, "", true, true);
//   br label %148
  builder.CreateBr(BB148);

// 143:                                              ; preds = %68
  builder.SetInsertPoint(BB143);
//   %144 = add nuw nsw i64 %69, %46
  Value* val144 = builder.CreateAdd(val69, val46, "", true, true);
//   %145 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %144
  Value* val145 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val144});
//   %146 = load i8, ptr %145, align 1, !tbaa !7
  Value* val146 = builder.CreateLoad(builder.getInt8Ty(), val145);
//   %147 = or disjoint i64 %47, %69
  Value* val147 = builder.CreateOr(val47, val69);
//   br label %148
  builder.CreateBr(BB148);

// 148:                                              ; preds = %141, %143, %139
  builder.SetInsertPoint(BB148);
//   %149 = phi i64 [ %142, %141 ], [ %147, %143 ], [ %140, %139 ]
  PHINode* val149 = builder.CreatePHI(builder.getInt64Ty(), 3);
//   %150 = phi i8 [ 0, %141 ], [ %146, %143 ], [ 1, %139 ]
  PHINode* val150 = builder.CreatePHI(builder.getInt8Ty(), 3);
//   %151 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %149
  Value* val151 = builder.CreateInBoundsGEP(ArrayType::get(builder.getInt8Ty(), 262144), val1, {builder.getInt64(0), val149});
//   store i8 %150, ptr %151, align 1, !tbaa !7
  builder.CreateStore(val150, val151);
//   %152 = add nuw nsw i64 %69, 
  Value* val152 = builder.CreateAdd(val69, builder.getInt64(1), "", true, true);
//   %153 = icmp eq i64 %152, 512
  Value* val153 = builder.CreateICmpEQ(val152, builder.getInt64(512));
//   br i1 %153, label %65, label %68, !llvm.loop !14
  builder.CreateCondBr(val153, BB65, BB68);
// }

  // Link PHI nodes
  // %3 = phi i64 [ 0, %0 ], [ %6, %5 ]
  val3->addIncoming(builder.getInt64(0), BB0);
  val3->addIncoming(val6, BB5);
  // %9 = phi i64 [ 0, %2 ], [ %15, %8 ]
  val9->addIncoming(builder.getInt64(0), BB2);
  val9->addIncoming(val15, BB8);
  // %18 = phi i8 [ %64, %63 ], [ 0, %5 ]
  val18->addIncoming(val64, BB63);
  val18->addIncoming(builder.getInt8(0), BB5);
  // %23 = phi i64 [ 0, %17 ], [ %31, %30 ]
  val23->addIncoming(builder.getInt64(0), BB17);
  val23->addIncoming(val31, BB30);
  // %34 = phi i64 [ 0, %22 ], [ %41, %33 ]
  val34->addIncoming(builder.getInt64(0), BB22);
  val34->addIncoming(val41, BB33);
  // %44 = phi i64 [ 0, %27 ], [ %66, %65 ]
  val44->addIncoming(builder.getInt64(0), BB27);
  val44->addIncoming(val66, BB65);
  // %69 = phi i64 [ 0, %43 ], [ %152, %148 ]
  val69->addIncoming(builder.getInt64(0), BB43);
  val69->addIncoming(val152, BB148);
  // %149 = phi i64 [ %142, %141 ], [ %147, %143 ], [ %140, %139 ]
  val149->addIncoming(val142, BB141);
  val149->addIncoming(val147, BB143);
  val149->addIncoming(val140, BB139);
  // %150 = phi i8 [ 0, %141 ], [ %146, %143 ], [ 1, %139 ]
  val150->addIncoming(builder.getInt8(0), BB141);
  val150->addIncoming(val146, BB143);
  val150->addIncoming(builder.getInt8(1), BB139);

  // Dump LLVM IR
  module->print(outs(), nullptr);

  // /*
  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMLinkInMCJIT();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == "_simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "_simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "_simRand") {
      return reinterpret_cast<void *>(simRand);
    }
    outs() << fnName << "\n";
    return nullptr;
  });
  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> noargs;
  outs() << "[EE] Run function\n";
  GenericValue v = ee->runFunction(appFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << "\n";

  simExit();
  return EXIT_SUCCESS;
}
