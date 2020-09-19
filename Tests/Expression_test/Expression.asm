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

print PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset print_format, eax
   leave
   ret 4
print ENDP

__start:

   enter 12, 0
   push 0
   pop eax
   mov var1[ebp], eax
   push 98
   pop eax
   mov var2[ebp], eax
   push 25
   push 5
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   push 5
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push 2
   mov ecx, 0
   pop ebx
   cdq
   pop eax
   idiv ebx
   push eax
   push 50
   pop eax
   pop ebx
   add eax, ebx
   push eax
   push var2[ebp]
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print

   leave

   ret

text ends

end __start

