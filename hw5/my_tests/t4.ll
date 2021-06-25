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
@r6 = constant [27 x i8] c"nothing to see here, folks\00"
define void @main() {
%r0 = alloca i32, i32 200
%r1 = sub i32 3, 5
br label %label13_switch_init  ; start of switch
br label %label5_case  ; start of case
  label5_case:
br label %label22_next  ; break
br label %label8_next  ; end of statement
  label8_next:
br label %label10_case  ; start of case
  label10_case:
call void @printi(i32 35)
br label %label22_next  ; end of statement
  label13_switch_init:
%r3 = icmp eq i32 %r1, 5
br i1 %r3, label %label10_case, label %label16_switch_comparison
  label16_switch_comparison:
%r4 = icmp eq i32 %r1, 3
br i1 %r4, label %label5_case, label %label19_switch_comparison_end
  label19_switch_comparison_end:
br label %label22_next  ; end of statement
br label %label22_next  ; end of statement
  label22_next:
%r5 = getelementptr [27 x i8], [27 x i8]* @r6, i32 0, i32 0
call void @print(i8* %r5)
br label %label26_next  ; end of statement
  label26_next:
ret void
}
