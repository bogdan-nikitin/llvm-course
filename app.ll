; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

; Function Attrs: noreturn nounwind ssp uwtable(sync)
define void @app() local_unnamed_addr #0 {
  %1 = alloca [2 x [256 x [512 x i8]]], align 1
  call void @llvm.lifetime.start.p0(i64 262144, ptr nonnull %1) #3
  br label %2

2:                                                ; preds = %0, %4
  %3 = phi i64 [ 0, %0 ], [ %5, %4 ]
  br label %7

4:                                                ; preds = %7
  %5 = add nuw nsw i64 %3, 1
  %6 = icmp eq i64 %5, 256
  br i1 %6, label %15, label %2, !llvm.loop !6

7:                                                ; preds = %2, %7
  %8 = phi i64 [ 0, %2 ], [ %13, %7 ]
  %9 = tail call i32 @simRand() #3
  %10 = srem i32 %9, 2
  %11 = trunc i32 %10 to i8
  %12 = getelementptr inbounds [256 x [512 x i8]], ptr %1, i64 0, i64 %3, i64 %8
  store i8 %11, ptr %12, align 1, !tbaa !8
  %13 = add nuw nsw i64 %8, 1
  %14 = icmp eq i64 %13, 512
  br i1 %14, label %4, label %7, !llvm.loop !11

15:                                               ; preds = %4, %43
  %16 = phi i8 [ %44, %43 ], [ 0, %4 ]
  %17 = zext i8 %16 to i64
  br label %18

18:                                               ; preds = %15, %24
  %19 = phi i64 [ 0, %15 ], [ %25, %24 ]
  %20 = trunc i64 %19 to i32
  br label %27

21:                                               ; preds = %24
  tail call void @simFlush() #3
  %22 = icmp eq i8 %16, 0
  %23 = zext i1 %22 to i64
  br label %36

24:                                               ; preds = %27
  %25 = add nuw nsw i64 %19, 1
  %26 = icmp eq i64 %25, 256
  br i1 %26, label %21, label %18, !llvm.loop !12

27:                                               ; preds = %18, %27
  %28 = phi i64 [ 0, %18 ], [ %34, %27 ]
  %29 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %19, i64 %28
  %30 = load i8, ptr %29, align 1, !tbaa !8
  %31 = icmp eq i8 %30, 0
  %32 = select i1 %31, i32 -16777216, i32 -1
  %33 = trunc i64 %28 to i32
  tail call void @simPutPixel(i32 noundef %33, i32 noundef %20, i32 noundef %32) #3
  %34 = add nuw nsw i64 %28, 1
  %35 = icmp eq i64 %34, 512
  br i1 %35, label %24, label %27, !llvm.loop !13

36:                                               ; preds = %21, %45
  %37 = phi i64 [ 0, %21 ], [ %41, %45 ]
  %38 = add nuw i64 %37, 255
  %39 = and i64 %38, 255
  %40 = and i64 %37, 255
  %41 = add nuw i64 %37, 1
  %42 = and i64 %41, 255
  br label %47

43:                                               ; preds = %45
  %44 = xor i8 %16, 1
  br label %15

45:                                               ; preds = %89
  %46 = icmp eq i64 %41, 256
  br i1 %46, label %43, label %36, !llvm.loop !14

47:                                               ; preds = %89, %36
  %48 = phi i64 [ 0, %36 ], [ %59, %89 ]
  %49 = add nuw i64 %48, 511
  %50 = and i64 %49, 511
  %51 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %39, i64 %50
  %52 = load i8, ptr %51, align 1, !tbaa !8
  %53 = sext i8 %52 to i32
  %54 = and i64 %48, 511
  %55 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %39, i64 %54
  %56 = load i8, ptr %55, align 1, !tbaa !8
  %57 = sext i8 %56 to i32
  %58 = add nsw i32 %53, %57
  %59 = add nuw i64 %48, 1
  %60 = and i64 %59, 511
  %61 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %39, i64 %60
  %62 = load i8, ptr %61, align 1, !tbaa !8
  %63 = sext i8 %62 to i32
  %64 = add nsw i32 %58, %63
  %65 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %40, i64 %50
  %66 = load i8, ptr %65, align 1, !tbaa !8
  %67 = sext i8 %66 to i32
  %68 = add nsw i32 %64, %67
  %69 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %40, i64 %60
  %70 = load i8, ptr %69, align 1, !tbaa !8
  %71 = sext i8 %70 to i32
  %72 = add nsw i32 %68, %71
  %73 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %42, i64 %50
  %74 = load i8, ptr %73, align 1, !tbaa !8
  %75 = sext i8 %74 to i32
  %76 = add nsw i32 %72, %75
  %77 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %42, i64 %54
  %78 = load i8, ptr %77, align 1, !tbaa !8
  %79 = sext i8 %78 to i32
  %80 = add nsw i32 %76, %79
  %81 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %42, i64 %60
  %82 = load i8, ptr %81, align 1, !tbaa !8
  %83 = sext i8 %82 to i32
  %84 = add nsw i32 %80, %83
  switch i32 %84, label %85 [
    i32 3, label %89
    i32 2, label %86
  ]

85:                                               ; preds = %47
  br label %89

86:                                               ; preds = %47
  %87 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %17, i64 %37, i64 %48
  %88 = load i8, ptr %87, align 1, !tbaa !8
  br label %89

89:                                               ; preds = %47, %85, %86
  %90 = phi i8 [ 0, %85 ], [ %88, %86 ], [ 1, %47 ]
  %91 = getelementptr inbounds [2 x [256 x [512 x i8]]], ptr %1, i64 0, i64 %23, i64 %37, i64 %48
  store i8 %90, ptr %91, align 1, !tbaa !8
  %92 = icmp eq i64 %59, 512
  br i1 %92, label %45, label %47, !llvm.loop !15
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

declare i32 @simRand(...) local_unnamed_addr #2

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

attributes #0 = { noreturn nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 16.0.0 (clang-1600.0.26.3)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = !{!9, !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
