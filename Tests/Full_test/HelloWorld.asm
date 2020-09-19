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
var3 = -16
i = -20
temp = -24

print PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset print_format, eax
   leave
   ret 4
print ENDP

__start:

   enter 24, 0
   push 0
   pop eax
   mov var1[ebp], eax
   push 10
   pop eax
   mov var2[ebp], eax
   push 98
   pop eax
   mov var3[ebp], eax
   push 0
   pop eax
   mov i[ebp], eax
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
   push var3[ebp]
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print
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
   push i[ebp]
   pop eax
   add eax, 1
   mov i[ebp], eax
   jmp START_FOR1
END_FOR1:
   push var1[ebp]
   pop ecx
   push 32
   pop edx
   cmp ecx, edx
   jne COMPARE_FALSE4
   push 1
   jmp COMPARE_END4
COMPARE_FALSE4:
   push 0
COMPARE_END4:
   pop eax
   cmp eax, 0
   je IF_END3
   push 0
   pop eax
   mov i[ebp], eax
START_FOR5:
   push i[ebp]
   pop ecx
   push 3
   pop edx
   cmp ecx, edx
   jge COMPARE_FALSE6
   push 1
   jmp COMPARE_END6
COMPARE_FALSE6:
   push 0
COMPARE_END6:
   pop eax
   cmp eax, 0
   je END_FOR5
   push var1[ebp]
   push 2
   mov ecx, 0
   pop ebx
   cdq
   pop eax
   idiv ebx
   push eax
   pop eax
   mov var1[ebp], eax
   push var1[ebp]
   call print
   push i[ebp]
   pop eax
   add eax, 1
   mov i[ebp], eax
   jmp START_FOR5
END_FOR5:
IF_END3:
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
   jge COMPARE_FALSE8
   push 1
   jmp COMPARE_END8
COMPARE_FALSE8:
   push 0
COMPARE_END8:
   pop eax
   cmp eax, 0
   je ELSE_START7
   push var2[ebp]
   call print
   jmp IF_END7
ELSE_START7:
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
IF_END7:

   leave

   ret

text ends

end __start

