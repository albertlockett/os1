#ifndef INCLUDE_INTERRUPT_H
#define INCLUDE_INTERRUPT_H

void load_idt(unsigned short addr);

void no_error_code_interrupt_handler0();
void no_error_code_interrupt_handler1();

#endif /* INCLUDE_INTERRUPT_H */
