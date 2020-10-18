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
#include "Time_ISR.h"
#include "Timer_isr.h"
#include "GlobalVar.h"
#include "UART.h"



CY_ISR(TimeOut)         
{
    Timer_ReadStatusRegister();
    if(state!=0){
    time++;                         
    
    if(time==5){                    //when in the same intermediate state for 5 seconds (timer has 1s period)
        
            //UART_PutString("Time Out\r\n");   //abilitate to check by terminal the correct functioning of the program
            
            flag=0;             //message ended
            state=0;            //return to IDLE state
            time=0;             //timer counter reset
            
        }
    }
               
    
       
        }
      
        

    

    
/* [] END OF FILE */
