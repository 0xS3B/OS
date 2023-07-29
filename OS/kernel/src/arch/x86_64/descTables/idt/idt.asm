[bits 64]

global loadIDT

loadIDT:
    ; save rip (instruction pointer) from call to put in rbx 
    ; the call instruction pushes rip so we can get the rip with pop
    pop rbx
    
    lidt [rdi]

    push rbx ; = rip
    retn