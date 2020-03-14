//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the DK-TM4C129X Firmware Package.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
//#include "grlib/widget.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "drivers/frame.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/pinout.h"
#define GREEN_LED  GPIO_PIN_7
#define BLUE_LED  GPIO_PIN_4
#define RED_LED  GPIO_PIN_5

#define GPIO_O_DATA   0x00000000
#define CYCLES_FROM_TIME_US(ui32ClockFreq, ui32Time_uS)                       \
    (((ui32Time_uS) == 0) ? 0 :                                               \
    (((ui32ClockFreq) / 1000000) * ((((ui32Time_uS) * 1000) - 1) / 1000)) + 1)

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``Hello World!''
//! on the display and is a starting point for more complicated applications.
//! This example uses calls to the TivaWare Graphics Library graphics
//! primitives functions to update the display.  For a similar example using
//! widgets, please see ``hello_widget''.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Print "Hello World!" to the display on the Intelligent Display Module.
//
//*****************************************************************************
int
main(void)
{

    tContext sContext;
    uint32_t ui32SysClock;

    //
    // Run from the PLL at 120 MHz.
    //
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 120000000);

    //
    // Configure the device pins.
    //
    PinoutSet();

    //
    // Initialize the display driver.
    //
    Kentec320x240x16_SSD2119Init(ui32SysClock);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
   // extern void GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_3);
    // Initialize the graphics context.GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_7);
    //
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    //
    // Draw the application frame.
    //
   // int32_t i32Val, i32Vol, i32VolStep;
        uint32_t ui32Key,ui32Key1,ui32Key2;// ui32NewStep;

        //
        // See if one of the push buttons is pressed.
        //
int count=0,countq=0;
        uint32_t ui32ClockMS;


               //
               // Determine the number of system clock cycles in 1mS
               //
               ui32ClockMS = CYCLES_FROM_TIME_US(ui32SysClock, 1000);

               //
               // Divide by 3 to get the number of SysCtlDelay loops in 1mS.
               //
               ui32ClockMS /= 3;
               GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GREEN_LED);//|USER_LED2));
                 GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, BLUE_LED);
               GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, RED_LED);
while(1)
{

    ui32Key = (ROM_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_3));
if(ui32Key==0)
{
    SysCtlDelay(ui32SysClock/10);
    countq++;
    if(countq>3)
    {
        countq=0;
    }

}
ui32Key1 = (ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5));
if(ui32Key1==0)
{
SysCtlDelay(ui32SysClock/10);

countq--;
if(countq==0)
{
    countq=3;
}
}
switch(countq)
{
case 1:
           GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
           GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
           GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, RED_LED);
          SysCtlDelay(ui32SysClock/100);
          GPIOPinWrite(GPIO_PORTN_BASE, RED_LED,0);


                                        break ;
case 2:
                                        GPIOPinWrite(GPIO_PORTN_BASE, RED_LED,0);
                                        GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
                                        GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,GREEN_LED);
                                        SysCtlDelay(ui32SysClock/100);


                                        break ;

case 3:
    ui32Key = (ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5));

                                        GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                        GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, 0x0);
                                        GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,BLUE_LED);
                                        SysCtlDelay(ui32SysClock/100);


                                        break;



default:
    break;

}

/*ui32Key1 = (ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5));
if(ui32Key1==0)
{
SysCtlDelay(ui32SysClock/10);

count++;
countq =0;
}
switch(count)
{
case 2:
                                     GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
                                     GPIOPinWrite(GPIO_PORTQ_BASE, RED_LED,0);
                                    GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,GREEN_LED);
                                    SysCtlDelay(ui32SysClock/100);
                                    GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                    break ;

case 1:
                                    GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, 0x0);
                                    GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                    GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,BLUE_LED);
                                    SysCtlDelay(ui32SysClock/100);
                                    GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);

                                    break;
case 3:
    GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
    GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                   GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, RED_LED);
                                   SysCtlDelay(ui32SysClock/100);

                                   count =0;
                                   break ;


default:
break;

}

            }*/
}
}
   /* ui32Key=(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5)) ;
    if(ui32Key != GPIO_PIN_5)
        {
        GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED, BLUE_LED);
               // Delay for a bit
               //
                   SysCtlDelay(ui32SysClock/100);
                   GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED, 0x0);

    //    SysCtlDelay(3000 * ui32ClockMS);
       // if(ui32Key == GPIO_PIN_3)
        //{
        FrameDraw(&sContext, "DOWN");

        //
        // Say hello using the Computer Modern 40 point font.
        //

        GrContextFontSet(&sContext, g_psFontCm32);
        GrStringDrawCentered(&sContext, "~~Down Button~~", -1,
                             GrContextDpyWidthGet(&sContext) / 2,
                             ((GrContextDpyHeightGet(&sContext) - 32) / 2) + 24,
                             0);
        SysCtlDelay(999 * ui32ClockMS);
            Kentec320x240x16_SSD2119Init(ui32SysClock);


       // GrFlush(&sContext);

        //
        // We are finished. Hang around doing nothing.


       // }
       }
    ui32Key = ((ROM_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_3)));
   if(ui32Key != GPIO_PIN_3)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, RED_LED);

                          //
                          // Delay for a bit
                          //
                  SysCtlDelay(ui32SysClock/100);
                    GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, 0x0);
    }


}
}
*/
