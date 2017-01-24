#include <stdint.h>
#define GPIO_PORTF_AMSEL_R 0x40025528
#define GPIO_PORTF_PCTL_R 0x4002552C
#define GPIO_PORTF_DIR_R 0x40025400
#define GPIO_PORTF_AFSEL_R 0x40025420
#define GPIO_PORTF_DEN_R  0x4002551C
#define GPIO_PORTF_DATA_R 0x400253FC
#define SYSCTL_RCGC2_R 	0x400FE108

void PORTF_INIT(void)
{
volatile uint32_t delay;
*((volatile uint32_t*)SYSCTL_RCGC2_R) |= 0x00000020;	//set clock of PORTF (otherwise port wont work)
delay = SYSCTL_RCGC2_R;					//give time to start up the clock of port
*((volatile uint32_t*)GPIO_PORTF_AMSEL_R) = 0X00;	//disable analog functionality on whole of portf
*((volatile uint32_t*)GPIO_PORTF_PCTL_R) = 0X00;	//to select regular digital func
*((volatile uint32_t*)GPIO_PORTF_DIR_R) = 0X02;		//to set PF1 to o/p mode direction reg
*((volatile uint32_t*)GPIO_PORTF_AFSEL_R) = 0X00;	//clearing to disable alternate functions of port
*((volatile uint32_t*)GPIO_PORTF_DEN_R) = 0X1F;		//to enable digital func

}

int main(void)
{
PORTF_INIT();
    *((volatile uint32_t*)GPIO_PORTF_DATA_R) = 0x02;	//write HIGH to PF1
while(1);{
}
}
