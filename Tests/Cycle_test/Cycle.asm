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
i = -12
j = -16

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
   push 0
   pop eax
   mov i[ebp], eax
   push 0
   pop eax
   mov j[ebp], eax
   push 1
   pop eax
   mov i[ebp], eax
START_FOR1:
   push i[ebp]
   pop ecx
   push 5
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
   je END_FOR1
   push var1[ebp]
   push 2
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print
   push 0
   pop eax
   mov j[ebp], eax
START_FOR3:
   push j[ebp]
   pop ecx
   push 2
   pop edx
   cmp ecx, edx
   jge COMPARE_FALSE4
   push 1
   jmp COMPARE_END4
COMPARE_FALSE4:
   push 0
COMPARE_END4:
   pop eax
   cmp eax, 0
   je END_FOR3
   push var1[ebp]
   push 1
   pop eax
   pop ebx
   add eax, ebx
   push eax
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print
   push j[ebp]
   pop eax
   add eax, 1
   mov j[ebp], eax
   jmp START_FOR3
END_FOR3:
   push i[ebp]
   pop eax
   add eax, 1
   mov i[ebp], eax
   jmp START_FOR1
END_FOR1:

   leave

   ret

text ends

end __start

