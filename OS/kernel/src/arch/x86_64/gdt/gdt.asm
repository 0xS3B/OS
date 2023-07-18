[bits 64]

global loadGDT

loadGDT:
    ; get rip from call to put in rbx 
    ; the call instruction pushes rip so we can get the rip with pop
    pop rbx
    
    lgdt [rdi]

    ; reload data segment
    mov ax, 0x10    ; data segment offset
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov es, ax

    ; reload code segment 
    mov rax, 0x8
    push rax
    push rbx ; = rip
    retfq