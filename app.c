/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "Mc32DriverLcd.h"
#include "peripheral/ports/plib_ports.h"
#include "framework/driver/tmr/drv_tmr_static.h"
#include "Mc32DriverAdc.h"
#include "Mc32DriverLcd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define LED0        PORTS_BIT_POS_0
#define LED1        PORTS_BIT_POS_1
#define LED2        PORTS_BIT_POS_4
#define LED3        PORTS_BIT_POS_5
#define LED4        PORTS_BIT_POS_6
#define LED5        PORTS_BIT_POS_7
#define LED6        PORTS_BIT_POS_15
#define LED7        PORTS_BIT_POS_10

const uint8_t tbLED[7] = {LED1,LED2,LED3,LED4,LED5,LED6,LED7}; 
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    lcd_init();
    BSP_InitADC10();
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

void APP_UpdateState(APP_STATES newState)
{
    // mise à jour de l'etat de state
    appData.state = newState;
}
/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    
    
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            
            // ligne pour allumer le backlight su LCD
            lcd_bl_on();
            // affichage du text voulu sur le LCD
            printf_lcd("Tp0 Led+AD 2025");
            lcd_gotoxy(1, 2);
            printf_lcd("Diego Alec Savary");
            // initialisation devariable pour svoir si c'est la 
            //premiere fois que nous l'allomons
            appData.ST_New = 1;
            appData.ST_Old = 0;
            // allumer les LED's
            LEDs();           
            // demarer le timer 1
            DRV_TMR0_Start();
            
            appData.state = APP_STATE_WAIT;
            
            break;
        }
        case APP_STATE_WAIT:
        {
        
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            //static bool Chenillard_Bool = false;
            static int8_t i; 
            // apelle de la fonction d'adc
            appData.adcRes = BSP_ReadAllADC();
            // affichage des resultats
            lcd_gotoxy(1, 3);
            printf_lcd("CH0 %4d CH1 %4d",appData.adcRes.Chan0, appData.adcRes.Chan1 );
            // eteinte des LED's
            if (appData.ST_New != appData.ST_Old)
            {
               
                for (i = 0; i < 7; i++) 
                {    
                    PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, tbLED[i]); 
                }
                
                PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_B, LED7);
                appData.ST_New = 0;
            }
            // fonction de chenillard
            Chenillard();
            // remise dans l'etat WAIT
            appData.state = APP_STATE_WAIT;
            break;
        }
        
        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


void Chenillard(void)
{
    static int timer_C;
    // incrementation de la variable timer counter
    timer_C ++;
    // si plus grand que 17 il est remis à 0
    if (timer_C >= 17)
    {
        timer_C = 0;
    }
    // bloc utiliser pour allumer les leds en chenillard
    else if(timer_C <= 2)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED0);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_B, LED7);
    }
    else if(timer_C <= 4)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED1);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED0);
    }
    else if(timer_C <= 6)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED2);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED1);
    }
    else if(timer_C <= 8)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED3);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED2);
    }
    else if(timer_C <= 10)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED4);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED3);
    }
    else if(timer_C <= 12)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED5);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED4);
    }
    else if(timer_C <= 14)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED6);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED5);
    }
    else if(timer_C <= 16)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_B, LED7);
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, LED6);
    }
    
}

 void LEDs(void)
{
     // allume toute les LED's si c'est la premiee utilisation
     if (appData.ST_New != appData.ST_Old)
     {
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED1);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED2);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED3);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED4);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED5);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, LED6);
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_B, LED7);
     }
 }

/*******************************************************************************
 End of File
 */
