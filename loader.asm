bits 32
MAGIC_NUMBER        equ 0x1BADB002
ALIGN_MODULES       equ 0x00000001

CHECKSUM            equ -(MAGIC_NUMBER + ALIGN_MODULES)

section .text
align 4
  dd MAGIC_NUMBER           ;magic
  dd ALIGN_MODULES           ; align_modules
  dd CHECKSUM ;checksum. m+f+c should be 
  
global loader
extern kmain

loader:  
    ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; point esp to the start of the stack (end of memory area )
    push ebx
    call kmain



.loop:
  jmp .loop

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

section .bss  
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
    