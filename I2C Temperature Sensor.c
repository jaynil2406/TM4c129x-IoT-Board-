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
#include "utils/ustdlib.h"
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
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#define SLAVE_ADDRESS 0x4A
#define GREEN_LED  GPIO_PIN_7
#define BLUE_LED  GPIO_PIN_4
#define RED_LED  GPIO_PIN_5
#define NEW_LED GPIO_PIN_4

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

    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    //
    // Draw the application frame.
    //
   // int32_t i32Val, i32Vol, i32VolStep;
       // uint32_t ui32Key,ui32Key1,ui32Key2;// ui32NewStep;

        //
        // See if one of the push buttons is pressed.
        //
int countq=0;
        uint32_t ui32ClockMS;


               //
               // Determine the number of system clock cycles in 1mS
               //
               ui32ClockMS = CYCLES_FROM_TIME_US(ui32SysClock, 1000);

               //
               // Divide by 3 to get the number of SysCtlDelay loops in 1mS.
               //
               ui32ClockMS /= 3;

               char pcBuf[8];
                   uint16_t data_low, data_high;
                   uint32_t sys_clock;
                   sys_clock = SysCtlClockFreqSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ, 25000000);

                   //ConfigureUART();

                   SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C6);
                   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
                   SysCtlDelay(10);

                   GPIOPinConfigure(GPIO_PB6_I2C6SCL);
                   GPIOPinConfigure(GPIO_PB7_I2C6SDA);
                   GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_6);
                   GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_7);
                   I2CMasterInitExpClk(I2C6_BASE, sys_clock, false);

                   //UARTprintf("Initialized I2C-6 peripheral.\n");

                   /*  Configuration Register */
                   I2CMasterSlaveAddrSet(I2C6_BASE, SLAVE_ADDRESS, false);
                   I2CMasterDataPut(I2C6_BASE, 0x01);
                   I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_SEND_START);
                   while(!(I2CMasterBusy(I2C6_BASE)));
                   while(I2CMasterBusy(I2C6_BASE));
                   I2CMasterDataPut(I2C6_BASE, 0xA0);
                   I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
                   while(!(I2CMasterBusy(I2C6_BASE)));
                   while(I2CMasterBusy(I2C6_BASE));
                   I2CMasterSlaveAddrSet(I2C6_BASE, SLAVE_ADDRESS, true);
                   I2CMasterDataPut(I2C6_BASE, 0x01);
                   I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_SEND_START);
                   while(!(I2CMasterBusy(I2C6_BASE)));
                   while(I2CMasterBusy(I2C6_BASE));
                   I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
                   while(!(I2CMasterBusy(I2C6_BASE)));
                   while(I2CMasterBusy(I2C6_BASE));

                   FrameDraw(&sContext, "Temperature I2C");

while(1)
{

    I2CMasterSlaveAddrSet(I2C6_BASE, SLAVE_ADDRESS, false);
           I2CMasterDataPut(I2C6_BASE, 0x00);
           I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_SEND_START);
           while(!(I2CMasterBusy(I2C6_BASE)));
           while(I2CMasterBusy(I2C6_BASE));
           I2CMasterSlaveAddrSet(I2C6_BASE, SLAVE_ADDRESS, true);
           I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
           while(!(I2CMasterBusy(I2C6_BASE)));
           while(I2CMasterBusy(I2C6_BASE));
           data_high = I2CMasterDataGet(I2C6_BASE);
           I2CMasterControl(I2C6_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
           while(!(I2CMasterBusy(I2C6_BASE)));
           while(I2CMasterBusy(I2C6_BASE));

           GrContextFontSet(&sContext, g_psFontCmss20);
                      usprintf(pcBuf, " %d ", data_high);
                      GrStringDraw(&sContext, "CURRENT TEMPERATURE", -1, 60, 100, 0);
                      GrStringDrawCentered(&sContext, pcBuf, -1, 150, 150, 1);


                                                             /*  GrContextFontSet(&sContext, g_psFontCm32);
                                                 GrStringDraw(&sContext, "NEW LED", -1, 100, 108, 0);*/


}
}
