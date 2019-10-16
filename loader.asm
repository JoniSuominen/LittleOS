

MAGIC_NUMBER        equ 0x1BADB002
ALIGN_MODULES       equ 0x00000001
KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER  equ (KERNEL_VIRTUAL_BASE >> 22)
CHECKSUM            equ -(MAGIC_NUMBER + ALIGN_MODULES)

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes
loader equ (_loader - 0xC0000000)
global loader
extern kmain
extern init_paging

section .text
align 4
  dd MAGIC_NUMBER           ;magic
  dd ALIGN_MODULES           ; align_modules
  dd CHECKSUM ;checksum. m+f+c should be 
  
_loader: 
    mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)  
    mov cr3, ecx

    mov ecx, cr4    ;read cr4
    or ecx, 0x00000010 ; set PSE
    mov cr4, ecx

    mov ecx, cr0
    or ecx, 0x80000000 ; set PG
    mov cr0, ecx    ;;update ebx
    lea ecx, [higherHalf]
    jmp ecx

higherHalf:
  mov dword [BootPageDirectory], 0
  invlpg [0]
  mov esp, kernel_stack + KERNEL_STACK_SIZE ; point esp to the start of the stack (end of memory area )
  push ebx
  call kmain

.loop:
  jmp .loop



section .bss  
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel

section .data
align 0x1000 ; 4kb
BootPageDirectory:
  dd 0x00000083 ;map first 4mb of virtual memory
  times (KERNEL_PAGE_NUMBER - 1) dd 0
  dd 0x00000083
  times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0
    