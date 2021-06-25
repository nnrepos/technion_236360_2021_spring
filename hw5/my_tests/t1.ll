declare i32 @printf(i8*, ...)
declare void @exit(i32)
@.str_specifier = constant [4 x i8] c"%s\0A\00"
define void @print(i8*) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)
    ret void
}
@.int_specifier = constant [4 x i8] c"%d\0A\00"
define void @printi(i32) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)
    ret void
}
@err_zero = constant [23 x i8] c"Error division by zero\00"
@r14 = constant [4 x i8] c"why\00"
@r17 = constant [3 x i8] c"hi\00"
@r20 = constant [4 x i8] c"bye\00"
define void @main() {
%r0 = alloca i32, i32 200
%r1 = add i32 4, 0
%r2 = getelementptr i32, i32* %r0, i32 4
store i32 %r1, i32* %r2
br label %label7_next  ; end of statement
br label %label7_next  ; end of statement
  label7_next:
br label %label9_while_head  ; start/end of while
  label9_while_head:
%r4 = getelementptr i32, i32* %r0, i32 4
%r3 = load i32, i32* %r4
%r5 = icmp sgt i32 %r3, 3
br i1 %r5, label %label14_while_body, label %label95_next
  label14_while_body:
%r7 = getelementptr i32, i32* %r0, i32 4
%r6 = load i32, i32* %r7
br label %label57_switch_init  ; start of switch
br label %label19_case  ; start of case
  label19_case:
%r8 = add i32 3, 0
%r9 = getelementptr i32, i32* %r0, i32 8
store i32 %r8, i32* %r9
br label %label25_next  ; end of statement
br label %label25_next  ; end of statement
  label25_next:
br label %label27_while_head  ; start/end of while
  label27_while_head:
%r11 = getelementptr i32, i32* %r0, i32 8
%r10 = load i32, i32* %r11
%r12 = icmp sgt i32 %r10, 0
br i1 %r12, label %label32_while_body, label %label37_next
  label32_while_body:
br label %label37_next  ; break
br label %label27_while_head  ; start/end of while
br label %label37_next  ; end of statement
br label %label37_next  ; end of statement
  label37_next:
%r13 = getelementptr [4 x i8], [4 x i8]* @r14, i32 0, i32 0
call void @print(i8* %r13)
br label %label41_next  ; end of statement
  label41_next:
br label %label43_case  ; start of case
  label43_case:
%r16 = getelementptr [3 x i8], [3 x i8]* @r17, i32 0, i32 0
call void @print(i8* %r16)
br label %label48_next  ; end of statement
br label %label48_next  ; end of statement
  label48_next:
br label %label67_next  ; break
br label %label51_next  ; end of statement
  label51_next:
br label %label53_default  ; start of default
  label53_default:
%r19 = getelementptr [4 x i8], [4 x i8]* @r20, i32 0, i32 0
call void @print(i8* %r19)
br label %label67_next  ; end of statement
  label57_switch_init:
%r22 = icmp eq i32 %r6, 5
br i1 %r22, label %label43_case, label %label60_switch_comparison
  label60_switch_comparison:
%r23 = icmp eq i32 %r6, 4
br i1 %r23, label %label19_case, label %label63_switch_comparison_end
  label63_switch_comparison_end:
br label %label53_default
br label %label67_next  ; end of statement
br label %label67_next  ; end of statement
  label67_next:
%r25 = getelementptr i32, i32* %r0, i32 4
%r24 = load i32, i32* %r25
%r26 = icmp sgt i32 %r24, 6
br i1 %r26, label %label72_if, label %label78_next
  label72_if:
br label %label95_next  ; break
br label %label78_next  ; end of statement
br label %label78_next  ; end of if
br label %label78_next  ; end of statement
br label %label78_next  ; end of statement
  label78_next:
%r28 = getelementptr i32, i32* %r0, i32 4
%r27 = load i32, i32* %r28
%r29 = add i32 %r27, 1
%r30 = and i32 %r29, 255
%r31 = add i32 %r30, 0
%r32 = getelementptr i32, i32* %r0, i32 4
store i32 %r31, i32* %r32
br label %label88_next  ; end of statement
br label %label88_next  ; end of statement
  label88_next:
%r34 = getelementptr i32, i32* %r0, i32 4
%r33 = load i32, i32* %r34
call void @printi(i32 %r33)
br label %label9_while_head  ; end of statement
br label %label9_while_head  ; start/end of while
br label %label95_next  ; end of statement
  label95_next:
ret void
}
