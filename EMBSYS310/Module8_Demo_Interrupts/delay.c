#include "delay.h"

extern int counter;

void delay(unsigned int iteration)
{
    counter = iteration;
    while (counter > 0)
    {
    }
}