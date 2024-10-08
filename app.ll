; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx14.0.0"

; Function Attrs: noreturn nounwind ssp uwtable(sync)
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
  %10 = tail call i32 @simRand() #3
  %11 = srem i32 %10, 2
  %12 = trunc nsw i32 %11 to i8
  %13 = add nuw nsw i64 %9, %4
  %14 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %13
  store i8 %12, ptr %14, align 1, !tbaa !7
  %15 = add nuw nsw i64 %9, 1
  %16 = icmp eq i64 %15, 512
  br i1 %16, label %5, label %8, !llvm.loop !10

17:                                               ; preds = %5, %63
  %18 = phi i8 [ %64, %63 ], [ 0, %5 ]
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
  tail call void @simFlush() #3
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
  tail call void @simPutPixel(i32 noundef %40, i32 noundef %26, i32 noundef %39) #3
  %41 = add nuw nsw i64 %34, 1
  %42 = icmp eq i64 %41, 512
  br i1 %42, label %30, label %33, !llvm.loop !12

43:                                               ; preds = %27, %65
  %44 = phi i64 [ 0, %27 ], [ %66, %65 ]
  %45 = shl nuw nsw i64 %44, 9
  %46 = add nuw nsw i64 %45, %21
  %47 = or disjoint i64 %45, %29
  %48 = add nuw nsw i64 %45, %29
  %49 = trunc i64 %44 to i32
  %50 = shl i32 %49, 9
  %51 = add i32 %50, 130560
  %52 = and i32 %51, 130560
  %53 = or disjoint i32 %52, %20
  %54 = trunc i64 %44 to i32
  %55 = shl i32 %54, 9
  %56 = and i32 %55, 130560
  %57 = or disjoint i32 %56, %20
  %58 = trunc i64 %44 to i32
  %59 = shl i32 %58, 9
  %60 = add i32 %59, 512
  %61 = and i32 %60, 130560
  %62 = or disjoint i32 %61, %20
  br label %68

63:                                               ; preds = %65
  %64 = xor i8 %18, 1
  br label %17

65:                                               ; preds = %148
  %66 = add nuw nsw i64 %44, 1
  %67 = icmp eq i64 %66, 256
  br i1 %67, label %63, label %43, !llvm.loop !13

68:                                               ; preds = %148, %43
  %69 = phi i64 [ 0, %43 ], [ %152, %148 ]
  %70 = trunc i64 %69 to i32
  %71 = add i32 %70, 511
  %72 = and i32 %71, 511
  %73 = or disjoint i32 %53, %72
  %74 = zext nneg i32 %73 to i64
  %75 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %74
  %76 = load i8, ptr %75, align 1, !tbaa !7
  %77 = sext i8 %76 to i32
  %78 = trunc i64 %69 to i32
  %79 = and i32 %78, 511
  %80 = or disjoint i32 %53, %79
  %81 = zext nneg i32 %80 to i64
  %82 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %81
  %83 = load i8, ptr %82, align 1, !tbaa !7
  %84 = sext i8 %83 to i32
  %85 = add nsw i32 %77, %84
  %86 = trunc i64 %69 to i32
  %87 = add i32 %86, 1
  %88 = and i32 %87, 511
  %89 = or disjoint i32 %53, %88
  %90 = zext nneg i32 %89 to i64
  %91 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %90
  %92 = load i8, ptr %91, align 1, !tbaa !7
  %93 = sext i8 %92 to i32
  %94 = add nsw i32 %85, %93
  %95 = trunc i64 %69 to i32
  %96 = add i32 %95, 511
  %97 = and i32 %96, 511
  %98 = or disjoint i32 %57, %97
  %99 = zext nneg i32 %98 to i64
  %100 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %99
  %101 = load i8, ptr %100, align 1, !tbaa !7
  %102 = sext i8 %101 to i32
  %103 = add nsw i32 %94, %102
  %104 = trunc i64 %69 to i32
  %105 = add i32 %104, 1
  %106 = and i32 %105, 511
  %107 = or disjoint i32 %57, %106
  %108 = zext nneg i32 %107 to i64
  %109 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %108
  %110 = load i8, ptr %109, align 1, !tbaa !7
  %111 = sext i8 %110 to i32
  %112 = add nsw i32 %103, %111
  %113 = trunc i64 %69 to i32
  %114 = add i32 %113, 511
  %115 = and i32 %114, 511
  %116 = or disjoint i32 %62, %115
  %117 = zext nneg i32 %116 to i64
  %118 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %117
  %119 = load i8, ptr %118, align 1, !tbaa !7
  %120 = sext i8 %119 to i32
  %121 = add nsw i32 %112, %120
  %122 = trunc i64 %69 to i32
  %123 = and i32 %122, 511
  %124 = or disjoint i32 %62, %123
  %125 = zext nneg i32 %124 to i64
  %126 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %125
  %127 = load i8, ptr %126, align 1, !tbaa !7
  %128 = sext i8 %127 to i32
  %129 = add nsw i32 %121, %128
  %130 = trunc i64 %69 to i32
  %131 = add i32 %130, 1
  %132 = and i32 %131, 511
  %133 = or disjoint i32 %62, %132
  %134 = zext nneg i32 %133 to i64
  %135 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %134
  %136 = load i8, ptr %135, align 1, !tbaa !7
  %137 = sext i8 %136 to i32
  %138 = add nsw i32 %129, %137
  switch i32 %138, label %141 [
    i32 3, label %139
    i32 2, label %143
  ]

139:                                              ; preds = %68
  %140 = add nuw nsw i64 %69, %48
  br label %148

141:                                              ; preds = %68
  %142 = add nuw nsw i64 %69, %48
  br label %148

143:                                              ; preds = %68
  %144 = add nuw nsw i64 %69, %46
  %145 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %144
  %146 = load i8, ptr %145, align 1, !tbaa !7
  %147 = or disjoint i64 %47, %69
  br label %148

148:                                              ; preds = %141, %143, %139
  %149 = phi i64 [ %142, %141 ], [ %147, %143 ], [ %140, %139 ]
  %150 = phi i8 [ 0, %141 ], [ %146, %143 ], [ 1, %139 ]
  %151 = getelementptr inbounds [262144 x i8], ptr %1, i64 0, i64 %149
  store i8 %150, ptr %151, align 1, !tbaa !7
  %152 = add nuw nsw i64 %69, 1
  %153 = icmp eq i64 %152, 512
  br i1 %153, label %65, label %68, !llvm.loop !14
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

declare i32 @simRand(...) local_unnamed_addr #2

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

attributes #0 = { noreturn nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { nounwind }

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
