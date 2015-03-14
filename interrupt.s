global load_idt
; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
;        [esp    ] the return address
load_idt:
    mov     eax, [esp+4]    ; load the address of the IDT into register eax
    lidt    eax             ; load the IDT
    ret                     ; return to the calling function



%macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword 0					; push 0 as error code
	push dword %1					; push interrupt number
	jmp common_interrupt_handler	; jmp to interrupt handler
%endmacro	

%macro error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword %1					; push interrupt number
	jmp common_interrupt_handler	; jmp to interrupt handler
%endmacro	


 common_interrupt_handler:               ; the common parts of the generic interrupt handler
        ; save the registers
        push    eax
        push    ebx
        push	ecx
		push	edx
        push    ebp

        ; call the C function
        call    interrupt_handler

        ; restore the registers
        pop     ebp
		pop		edx
		pop		ecx
        pop     ebx
        pop     eax

        ; restore the esp
        add     esp, 8

        ; return to the code that got interrupted
        iret


no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
