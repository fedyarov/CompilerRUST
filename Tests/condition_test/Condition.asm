.586
.model flat, stdcall

include <C:\masm32\include\msvcrt.inc>
include <C:\masm32\include\kernel32.inc>
includelib <C:\masm32\lib\msvcrt.lib>
includelib <C:\masm32\lib\kernel32.lib>

data segment

   print_format db "%d ", 0

data ends

text segment

var1 = -8
var2 = -12
temp = -16

print PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset print_format, eax
   leave
   ret 4
print ENDP

__start:

   enter 16, 0
   push 2
   pop eax
   mov var1[ebp], eax
   push 10
   pop eax
   mov var2[ebp], eax
   push var2[ebp]
   pop ecx
   push var1[ebp]
   push 2
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop edx
   cmp ecx, edx
   jge COMPARE_FALSE2
   push 1
   jmp COMPARE_END2
COMPARE_FALSE2:
   push 0
COMPARE_END2:
   pop eax
   cmp eax, 0
   je ELSE_START1
   push var2[ebp]
   call print
   jmp IF_END1
ELSE_START1:
   push var2[ebp]
   pop eax
   mov temp[ebp], eax
   push var1[ebp]
   pop eax
   mov var2[ebp], eax
   push temp[ebp]
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print
   push var2[ebp]
   call print
IF_END1:

   leave

   ret

text ends

end __start

