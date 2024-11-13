; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

; Function Attrs: noreturn nounwind optsize ssp uwtable(sync)
define void @app() local_unnamed_addr #0 {
  %1 = alloca [262144 x i8], align 1
  call void @llvm.lifetime.start.p0(i64 262144, ptr nonnull %1) #3
  br label %2

2:                                                ; preds = %0, %5
  %3 = phi i64 [ 0, %0 ], [ %6, %5 ]
  %4 = shl nuw nsw i64 %3, 9
  br label %8

5:                                                ; preds = %8
  %6 = add nuw nsw i64 %3, 1
  %7 = icmp eq i64 %6, 256
  br i1 %7, label %17, label %2, !llvm.loop !5

8:                                                ; preds = %2, %8
  %9 = phi i64 [ 0, %2 ], [ %15, %8 ]
  %10 = tail call i32 @simRand() #4
  %11 = srem i32 %10, 2
  %12 = trunc nsw i32 %11 to i8
  %13 = add nuw nsw i64 %9, %4
  %14 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %13
  store i8 %12, ptr %14, align 1, !tbaa !7
  %15 = add nuw nsw i64 %9, 1
  %16 = icmp eq i64 %15, 512
  br i1 %16, label %5, label %8, !llvm.loop !10

17:                                               ; preds = %5, %50
  %18 = phi i8 [ %51, %50 ], [ 0, %5 ]
  %19 = zext nneg i8 %18 to i32
  %20 = shl nuw nsw i32 %19, 17
  %21 = zext nneg i32 %20 to i64
  br label %22

22:                                               ; preds = %17, %30
  %23 = phi i64 [ 0, %17 ], [ %31, %30 ]
  %24 = shl nuw nsw i64 %23, 9
  %25 = add nuw nsw i64 %24, %21
  %26 = trunc nuw nsw i64 %23 to i32
  br label %33

27:                                               ; preds = %30
  tail call void @simFlush() #4
  %28 = icmp eq i8 %18, 0
  %29 = select i1 %28, i64 131072, i64 0
  br label %43

30:                                               ; preds = %33
  %31 = add nuw nsw i64 %23, 1
  %32 = icmp eq i64 %31, 256
  br i1 %32, label %27, label %22, !llvm.loop !11

33:                                               ; preds = %22, %33
  %34 = phi i64 [ 0, %22 ], [ %41, %33 ]
  %35 = add nuw nsw i64 %34, %25
  %36 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %35
  %37 = load i8, ptr %36, align 1, !tbaa !7
  %38 = icmp eq i8 %37, 0
  %39 = select i1 %38, i32 -16777216, i32 -1
  %40 = trunc nuw nsw i64 %34 to i32
  tail call void @simPutPixel(i32 noundef %40, i32 noundef %26, i32 noundef %39) #4
  %41 = add nuw nsw i64 %34, 1
  %42 = icmp eq i64 %41, 512
  br i1 %42, label %30, label %33, !llvm.loop !12

43:                                               ; preds = %27, %55
  %44 = phi i64 [ 0, %27 ], [ %56, %55 ]
  %45 = shl nuw nsw i64 %44, 9
  %46 = add nuw nsw i64 %45, %21
  %47 = or disjoint i64 %45, %29
  %48 = add nuw nsw i64 %45, %29
  %49 = trunc i64 %44 to i32
  br label %52

50:                                               ; preds = %55
  %51 = xor i8 %18, 1
  br label %17

52:                                               ; preds = %43, %96
  %53 = phi i64 [ 0, %43 ], [ %100, %96 ]
  %54 = trunc i64 %53 to i32
  br label %58

55:                                               ; preds = %96
  %56 = add nuw nsw i64 %44, 1
  %57 = icmp eq i64 %56, 256
  br i1 %57, label %50, label %43, !llvm.loop !13

58:                                               ; preds = %52, %65
  %59 = phi i32 [ -1, %52 ], [ %66, %65 ]
  %60 = phi i32 [ 0, %52 ], [ %84, %65 ]
  %61 = add i32 %59, %49
  %62 = shl i32 %61, 9
  %63 = and i32 %62, 130560
  br label %68

64:                                               ; preds = %65
  switch i32 %84, label %89 [
    i32 3, label %87
    i32 2, label %91
  ]

65:                                               ; preds = %83
  %66 = add nsw i32 %59, 1
  %67 = icmp eq i32 %66, 2
  br i1 %67, label %64, label %58, !llvm.loop !14

68:                                               ; preds = %58, %83
  %69 = phi i32 [ -1, %58 ], [ %85, %83 ]
  %70 = phi i32 [ %60, %58 ], [ %84, %83 ]
  %71 = or i32 %69, %59
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %83, label %73

73:                                               ; preds = %68
  %74 = add i32 %69, %54
  %75 = and i32 %74, 511
  %76 = or disjoint i32 %63, %75
  %77 = or disjoint i32 %76, %20
  %78 = zext nneg i32 %77 to i64
  %79 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %78
  %80 = load i8, ptr %79, align 1, !tbaa !7
  %81 = sext i8 %80 to i32
  %82 = add nsw i32 %70, %81
  br label %83

83:                                               ; preds = %68, %73
  %84 = phi i32 [ %70, %68 ], [ %82, %73 ]
  %85 = add nsw i32 %69, 1
  %86 = icmp eq i32 %85, 2
  br i1 %86, label %65, label %68, !llvm.loop !15

87:                                               ; preds = %64
  %88 = add nuw nsw i64 %53, %48
  br label %96

89:                                               ; preds = %64
  %90 = add nuw nsw i64 %53, %48
  br label %96

91:                                               ; preds = %64
  %92 = add nuw nsw i64 %53, %46
  %93 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %92
  %94 = load i8, ptr %93, align 1, !tbaa !7
  %95 = or disjoint i64 %47, %53
  br label %96

96:                                               ; preds = %89, %91, %87
  %97 = phi i64 [ %90, %89 ], [ %95, %91 ], [ %88, %87 ]
  %98 = phi i8 [ 0, %89 ], [ %94, %91 ], [ 1, %87 ]
  %99 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %97
  store i8 %98, ptr %99, align 1, !tbaa !7
  %100 = add nuw nsw i64 %53, 1
  %101 = icmp eq i64 %100, 512
  br i1 %101, label %55, label %52, !llvm.loop !16
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: optsize
declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: optsize
declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: optsize
declare void @simFlush(...) local_unnamed_addr #2

attributes #0 = { noreturn nounwind optsize ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { optsize "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { nounwind }
attributes #4 = { nounwind optsize }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 1}
!3 = !{i32 7, !"frame-pointer", i32 1}
!4 = !{!"Homebrew clang version 19.1.1"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C/C++ TBAA"}
!10 = distinct !{!10, !6}
!11 = distinct !{!11, !6}
!12 = distinct !{!12, !6}
!13 = distinct !{!13, !6}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
!16 = distinct !{!16, !6}
