[bits 64]

%define SEGDESC_OFFSET      0x8

global gdt_load
global tss_load

gdt_load:
    ; save rip (instruction pointer) from call to put in rbx 
    ; the call instruction pushes rip so we can get the rip with pop
    pop rbx
    
    lgdt [rdi]

    ; load data segment
    mov ax, SEGDESC_OFFSET * 2
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    mov ss, ax

    ; load code segment and get old instruction pointer to return (cs:ip)
    mov rax, SEGDESC_OFFSET
    push rax
    push rbx ; = rip
    retfq

tss_load:
    mov ax, SEGDESC_OFFSET * 5 ; the sixth entry in GDT (TSS)
    ltr ax
    ret