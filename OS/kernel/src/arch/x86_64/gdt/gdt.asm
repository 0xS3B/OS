[bits 64]

%define SEGDESC_OFFSET      0x8

global loadGDT
global loadTSS

loadGDT:
    ; get rip (instruction pointer) from call to put in rbx 
    ; the call instruction pushes rip so we can get the rip with pop
    pop rbx
    
    lgdt [rdi]

    ; reload data segment
    mov ax, SEGDESC_OFFSET * 2 ; data segment descriptor offset
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov es, ax

    ; reload code segment
    mov rax, SEGDESC_OFFSET * 1
    push rax
    push rbx ; = rip
    retfq

loadTSS:
    mov ax, SEGDESC_OFFSET * 5 ; the sixth entry in GDT (TSS segment descriptor)
    ltr ax
    ret