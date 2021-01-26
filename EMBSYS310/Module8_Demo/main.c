#include <stdint.h>
#include "delay.h"
#include "stm32l475xx.h"

// LD1 --> PA5 -- Homework
// LD2 --> PB14 -- In Class

//typedef __packed struct {
typedef struct {
    uint8_t y;
    uint16_t x;
} Point;

typedef struct {
    Point bottom_left;
    Point top_right;    
} Rectangle;

typedef struct {
    Point corners[3];
} Triangle;


#if 1 // ****************** Uninitialized ****************** 
int16_t x;
uint32_t y;
int16_t myArray1[8];
Point p1;
Rectangle r1;
Triangle t1;
#endif // ****************** Uninitialized ****************** 

#if 0 // ****************** Initialized ******************
int16_t x = -1;
uint32_t y = 0x5A5A5A5A;
int16_t myArray1[8] = {1, 2, 3, 4}; // Missing elements will be initialized to zero.

Point p1 = {
    0x12,
    0x1234
};

Rectangle r1 = {
    {1, 1},
    {5, 5}
};

Triangle t1 = {
    { {1, 1}, {2, 2}, {3, 3}}
};
#endif // ****************** Iniialized ******************



#if 1 // ****************** Uninitialized ****************** 
Point* p2;
int16_t myArray2[5];
Rectangle r2;
Triangle t2;
#endif // ****************** Uninitialized ****************** 

#if 0  // ****************** Iniialized ******************
Point* p2 = &p1;
int16_t myArray2[] = {1, 2, 3, 4, 5}; // Missing elements will be initialized to zero.
Rectangle r2 = {
    {7, 7},
    {9, 9}
};

Triangle t2 = {
    { {4, 4}, {5, 5}, {6, 6}}
};
#endif // ****************** Iniialized ******************


void main(void)
{
    p1.x = sizeof(Point);
    p1.y = 'C';
       
    r1.bottom_left.x = 1;
    r1.bottom_left.y = 1;
    r1.top_right.x = 5;
    r1.top_right.x = 5;
    
    t1.corners[0].x = 1;
    t1.corners[0].y = 1;
    
    t1.corners[1].x = 3;
    t1.corners[1].y = 4;
    
    t1.corners[2].x = 5;
    t1.corners[2].y = 1;

    for(int i= 0; i < sizeof(myArray1)/sizeof(myArray1[0]); i++)
    {
        myArray1[i] = 'a' + i;
    }

    // ***********************
    p2 = &p1;    
    p2->x = sizeof(p1);
    (*p2).y = 34;

    r2.bottom_left.x = 1;
    r2.bottom_left.y = 1;
    r2.top_right.x = 5;
    r2.top_right.x = 5;
    
    t2.corners[0].x = 1;
    t2.corners[0].y = 1;
    
    t2.corners[1].x = 3;
    t2.corners[1].y = 4;
    
    t2.corners[2].x = 5;
    t2.corners[2].y = 1;
        
    for(int i= 0; i < sizeof(myArray2)/sizeof(myArray2[0]); i++)
    {
        myArray2[i] = 'a' + i;
    }
    // ***********************
   
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    // RCC Base Address: 0x40021000
    // Address offset: 0x4C
    // Set bit[1] to 1
    // 1. Enable clock to Peripheral  
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
   
    
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // GPIOB Base Address: 0x48000400
    // Address offset: 0x00
    // Set bit[29:28] to 0x01  so --> 0x400 // To enable PB14 as output
    GPIOB->MODER &= ~GPIO_MODER_MODE14_1;
    GPIOB->MODER |= GPIO_MODER_MODE14_0;
    
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // GPIOB Base Address: 0x48000400
    // Address offset: 0x14
    // Set bit[14] to 1 --> 0x4000; // Turn LED ON
    // Set bit[14] to 0 --> 0x0; // Turn LED OFF
    while(1)
    {
        GPIOB->ODR |= GPIO_ODR_OD14;
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        delay(100000);

        GPIOB->ODR &= ~GPIO_ODR_OD14;
        GPIOA->ODR |= GPIO_ODR_OD5;
        delay(100000);
    }    
}
