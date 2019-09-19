section .text
  ;multiboot spec
  align 4
  dd 0x1BADB002            ;magic
  dd 0x00                  ;flags
  dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be 
  
global loader
extern kmain

loader:  
    ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; point esp to the start of the stack (end of memory area )
    call kmain

.loop:
  jmp .loop

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

section .bss
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
    