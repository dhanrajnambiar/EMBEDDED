#include <stdint.h>

#define GPIO_PORTA_AMSEL_R 0x40004528
#define GPIO_PORTA_PCTL_R 0x4000452C
#define GPIO_PORTA_DIR_R 0x40004400
#define GPIO_PORTA_AFSEL_R 0x40004420
#define GPIO_PORTA_DEN_R 0x4000451C
#define GPIO_PORTA_DATA_R 0x40004030
#define SYSCTL_RCGC2_R 0x400FE108	

void porta_init(void)
{
volatile uint32_t delay;
*((volatile uint32_t*)SYSCTL_RCGC2_R) |= 0x00000001;	//set clock of PORTA (otherwise port wont work)
delay = SYSCTL_RCGC2_R;					//give time to start up the clock of port
*((volatile uint32_t*)GPIO_PORTA_AMSEL_R) &= ~0x0C;	//disable analog functionality of PA2 & PA3 only
*((volatile uint32_t*)GPIO_PORTA_PCTL_R) &= ~0x0C;	//to select regular digital func to PA2 & PA3 ONLY
*((volatile uint32_t*)GPIO_PORTA_DIR_R) |= 0x08;	//to set PA2 to i/p mode and PA3 to o/p mode leave the rest as such
*((volatile uint32_t*)GPIO_PORTA_AFSEL_R) &= ~0x0C;	//clearing to disable alternate functions of PA2 & PA3
*((volatile uint32_t*)GPIO_PORTA_DEN_R) |= 0x0C;	//to enable digital function of PA2 and PA3 only
}

unsigned long int In;
unsigned long int Out;

uint32_t inputfn()
{
uint32_t In1;
In1 = *((volatile uint32_t*)GPIO_PORTA_DATA_R);
return(In1);
}

void outputfn()
{
*((volatile uint32_t*)GPIO_PORTA_DATA_R) = Out;
}


int main(void)
{
while(1){
    porta_init();
    In = inputfn();
    Out = In << 1;
    outputfn();
}
}
