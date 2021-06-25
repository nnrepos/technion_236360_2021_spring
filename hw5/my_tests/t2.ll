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
define void @main() {
%r0 = alloca i32, i32 200
%r1 = add i32 2000111222, 0
%r2 = getelementptr i32, i32* %r0, i32 4
store i32 %r1, i32* %r2
br label %label7_next  ; end of statement
br label %label7_next  ; end of statement
  label7_next:
%r3 = add i32 2000111223, 0
%r4 = getelementptr i32, i32* %r0, i32 8
store i32 %r3, i32* %r4
br label %label13_next  ; end of statement
br label %label13_next  ; end of statement
  label13_next:
%r6 = getelementptr i32, i32* %r0, i32 4
%r5 = load i32, i32* %r6
%r8 = getelementptr i32, i32* %r0, i32 8
%r7 = load i32, i32* %r8
%r9 = add i32 %r5, %r7
%r10 = add i32 %r9, 0
%r11 = getelementptr i32, i32* %r0, i32 12
store i32 %r10, i32* %r11
br label %label24_next  ; end of statement
br label %label24_next  ; end of statement
  label24_next:
br label %label57_switch_init  ; start of switch
br label %label27_case  ; start of case
  label27_case:
%r12 = add i32 5, 0
%r13 = getelementptr i32, i32* %r0, i32 12
store i32 %r12, i32* %r13
br label %label32_next  ; end of statement
  label32_next:
br label %label34_case  ; start of case
  label34_case:
%r15 = getelementptr i32, i32* %r0, i32 4
%r14 = load i32, i32* %r15
%r16 = add i32 %r14, 0
%r17 = getelementptr i32, i32* %r0, i32 12
store i32 %r16, i32* %r17
br label %label42_next  ; end of statement
br label %label42_next  ; end of statement
  label42_next:
br label %label69_next  ; break
br label %label45_next  ; end of statement
  label45_next:
br label %label47_case  ; start of case
  label47_case:
ret void
br label %label50_next  ; end of statement
  label50_next:
br label %label52_default  ; start of default
  label52_default:
%r19 = getelementptr i32, i32* %r0, i32 12
%r18 = load i32, i32* %r19
call void @printi(i32 %r18)
br label %label69_next  ; end of statement
  label57_switch_init:
%r21 = icmp eq i32 4, 2
br i1 %r21, label %label47_case, label %label60_switch_comparison
  label60_switch_comparison:
%r22 = icmp eq i32 4, 1
br i1 %r22, label %label34_case, label %label63_switch_comparison
  label63_switch_comparison:
%r23 = icmp eq i32 4, 3
br i1 %r23, label %label27_case, label %label66_switch_comparison_end
  label66_switch_comparison_end:
br label %label52_default
br label %label69_next  ; end of statement
  label69_next:
ret void
}
