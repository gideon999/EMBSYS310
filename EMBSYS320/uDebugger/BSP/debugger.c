#include <stdint.h>
#include "print.h"

/*
 *
 * Part of a fault exception handler. Prints the given register values.
 * pc: the value of the program counter when the fault occurred.
 * lr: the value of the link register when the fault occurred.
 *
 */
void FaultPrint(uint32_t pc, uint32_t lr)
{
    // TODO: Print an error message specifying the PC and LR values when the fault occurred
    // <Your code here>
    char tempMessage[80];
    sprintf(tempMessage, "\nFault Print: PC: %X8\tLR: %X8\n", pc, lr);
    PrintString(tempMessage);
}
