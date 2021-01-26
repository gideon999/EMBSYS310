#if 0

void main()
{
    int mem_value;
    mem_value = *((unsigned int *)(0x20000000));
    
    for (int i = 0 ; i < 32; i ++)
    {
        *((unsigned int *)(0x22000000 + (0x0 * 32) + (i * 4))) = 0x1;
        mem_value = *((unsigned int *)(0x20000000));
    }
}

#endif

#if 1

#define RCC_BASE 0x40021000
#define GPIOB_BASE 0x48000400
#define GPIOA_BASE 0x48000000

#define RCC_AHB2EBR (*((unsigned int *) (RCC_BASE + 0x4c)))

#define GPIOA_MODER (*((unsigned int *) (GPIOA_BASE + 0x00)))
#define GPIOA_ODR (*((unsigned int *) (GPIOA_BASE + 0x14)))

#define GPIOB_MODER (*((unsigned int *) (GPIOB_BASE + 0x00)))
#define GPIOB_ODR (*((unsigned int *) (GPIOB_BASE + 0x14)))

#define ORD14 (1 <<14)
#define ORD05 (1 <<5)

volatile int counter = 0;

void delay(int value)
{
    counter = 0;
    while (counter < value)
    {
        counter++;
    }
}

int main()
{
    // RCC_AHB2EBR = RCC_AHB2EBR | 0x3;    // Turn on GPIOA and GPIOB ports
    *((unsigned int *)((0x42000000)+ (0x2104C * 32) + (0 * 4))) = 0x1;
    *((unsigned int *)((0x42000000)+ (0x2104C * 32) + (1 * 4))) = 0x1;
    GPIOA_MODER &= 0xFFFFF7FF;          // Turn on PA5 port
    GPIOB_MODER &= 0xDFFFFFFF;          // Turn on PB14 port
    
    while (1)
    {
        delay(100000);
        GPIOB_ODR |= ORD14;
        GPIOA_ODR &= ~ORD05;
        
        delay(300000);
        
        GPIOA_ODR |= ORD05;
        GPIOB_ODR &= ~ORD14;
    }
}
#endif
