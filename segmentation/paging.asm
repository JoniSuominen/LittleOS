bits 32

global enable_paging


enable_paging:
    mov cr3, eax    ;eax contains the register of page directory
    
    mov ebx, cr4    ;read cr4
    or ebx, 0x00000010 ; set PSE
    mov cr4, ebx

    mov ebx, cr0
    or ebx, 0x80000000 ; set PG
    mov cr0, ebx    ;;update ebx