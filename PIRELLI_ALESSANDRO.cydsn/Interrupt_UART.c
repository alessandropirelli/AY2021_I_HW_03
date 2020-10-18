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
#include "Interrupt_UART.h"
#include "GlobalVar.h"
#include "UART.h"
#include "stdio.h"
#include "PWM_RedGreen.h"
#include "PWM_Blue.h"


#define IDLE 0
#define HEAD 1
#define R 2
#define G 3
#define B 4
#define TAIL 5
#define P 6


CY_ISR(RGBSetting)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)    //when there's data sent
    {
        int setting = UART_ReadRxData();                    //read data and save it as setting
                                                            
        time=0;                                             //reset timer counter as state is about to change
        
        switch (setting){
            case 'v':                                           
                state=P;                                    
                break;
            case 0xA0:
                if(state != TAIL){                          //only when not waiting for the tail character go to the next state
                    flag=1;                                 //doesn't matter that it gets set to 1 even if the header has already been received during the same message
                    state++;                                
                }
                break;
            default:
                if(flag==1){                                //only when the start of a message has been already received
                    state++;                                //go to the next state
                };
                break;
            }
        
    switch(state){                                          //strings printed may be used to facilitate access to the program by terminal
            case IDLE:
                //UART_PutString("Waiting\r\n");
                break;
            case HEAD:
                //UART_PutString("Insert R value: \r\n");
                break;
            case R:
                
                PWM_RedGreen_WriteCompare1(setting);        //update RED PWM
                //UART_PutString("Insert G value\r\n");
                break;
            case G:
                
                PWM_RedGreen_WriteCompare2(setting);        //update GREEN PWM
                //UART_PutString("Insert B value\r\n");
                break;
            case B:
                
                PWM_Blue_WriteCompare(setting);             //update BLUE PWM
                //UART_PutString("Insert TAIL value\r\n");
                break;
            case TAIL:
                if(setting == 0XC0)
                {
                    //UART_PutString("End\r\n");            
                    state=IDLE;                             //if TAIL character correct, return to IDLE
                    
                    
                }else{
                    //UART_PutString("Error\r\n");
                    state=TAIL;                             //if TAIL character wrong, stay in TAIL until the correct character is sent
                    
                };
                flag=0;                                     //flag set to 0 means that the message has ended and also assures for the TAIL!=0XC0 case the state doesn't get updated when reading a new character
                break;
            case P:
                UART_PutString("RGB LED Program $$$\r\n");
                state=0;
                break;
            default:
                break;
            } 
    }
}
        


/* [] END OF FILE */
