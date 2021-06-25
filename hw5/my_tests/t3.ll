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
define i32 @retFromSwitch(i32) {
%r0 = alloca i32, i32 200
%r1 = add i32 0, %0
br label %label22_switch_init  ; start of switch
br label %label5_case  ; start of case
  label5_case:
call void @printi(i32 4)
br label %label8_next  ; end of statement
  label8_next:
br label %label10_case  ; start of case
  label10_case:
ret i32 5
br label %label13_next  ; end of statement
  label13_next:
br label %label15_default  ; start of default
  label15_default:
ret i32 6
br label %label19_next  ; end of statement
br label %label19_next  ; end of statement
  label19_next:
br label %label31_next  ; break
br label %label31_next  ; end of statement
  label22_switch_init:
%r3 = icmp eq i32 %r1, 5
br i1 %r3, label %label10_case, label %label25_switch_comparison
  label25_switch_comparison:
%r4 = icmp eq i32 %r1, 4
br i1 %r4, label %label5_case, label %label28_switch_comparison_end
  label28_switch_comparison_end:
br label %label15_default
br label %label31_next  ; end of statement
  label31_next:
ret i32 0
}
define void @main() {
%r5 = alloca i32, i32 200
%r6 = call i32 @retFromSwitch(i32 4)
call void @printi(i32 %r6)
br label %label40_next  ; end of statement
br label %label40_next  ; end of statement
  label40_next:
%r8 = call i32 @retFromSwitch(i32 5)
call void @printi(i32 %r8)
br label %label45_next  ; end of statement
br label %label45_next  ; end of statement
  label45_next:
%r10 = call i32 @retFromSwitch(i32 6)
call void @printi(i32 %r10)
br label %label49_next  ; end of statement
  label49_next:
ret void
}
