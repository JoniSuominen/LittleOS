extern interrupt_handler

% macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
    push dword 0    ; push 0 as error code for interrupt
    push dword %1   ; push the interrupt number
    jmp common_interrupt_handler ; jump to common handler
%endmacro

%macro error_code_interrupt_handler %1
global interrupt_handler_%1
    push dword %1   ; push the interrupt number
    jmp common_interrupt_handler  ; jump to common handler
%endmacro

common_interrupt_handler:
    ;save registers
    push eax
    push ebx
    push ecx
    push edx
    push esp
    push ebp
    push esi
    push edi

    ; call c function
    call interrupt_handler

    pop eax
    pop ebx
    pop ecx
    pop edx
    pop esp
    pop ebp
    pop esi
    pop edi
    
    add esp, 8
    iret


no_error_code_interrupt_handler 33 ; keyboard