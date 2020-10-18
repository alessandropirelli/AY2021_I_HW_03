/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "GlobalVar.h"
#include "Interrupt_UART.h"
#include "stdio.h"
#include "Time_ISR.h"

#define OFF 0


int state;
int time;
int flag; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
     
    state=0;           //state=IDLE
    time=0;
    
    
    Timer_Start();
    PWM_RedGreen_Start();
    PWM_Blue_Start();
    UART_Start();
    UART_isr_StartEx(RGBSetting);
    Timer_isr_StartEx(TimeOut);
    
    PWM_RedGreen_WriteCompare1(OFF);          //
    PWM_RedGreen_WriteCompare2(OFF);          //
    PWM_Blue_WriteCompare(OFF);               //RGB LED starts OFF
    
    
    
    for(;;)
    {
                      //check state variable
    }
}

/* [] END OF FILE */
