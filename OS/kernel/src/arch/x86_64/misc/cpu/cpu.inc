; save/restore general registers
%macro PUSHA64 0
    push rax
    push rbx
    push rcx
    push rdx
    ;push rsp
    push rbp
    push rsi
    push rdi
%endmacro

%macro POPA64 0
    pop rdi
    pop rsi
    pop rbp
    ;pop rsp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro