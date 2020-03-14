//*****************************************************************************
//
// timers.c - Timers example.
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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "grlib/grlib.h"
#include "drivers/frame.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/pinout.h"

#include "inc/hw_ints.h"
#include "inc/hw_timer.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
#include "driverlib/Timer.c"
#include "driverlib/Timer.h"
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

uint32_t g_ui32SysClock;

int main(void)
{

//1. set the clock to run off of crystal at 25Mhz
g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN \
| SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

//2. Enable the PWM Module in the System Control using
//enable peripheral (port F)
SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

//2b. secret level; unlock port F0 so that we can use it!!! >=O
while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)));
HWREG(GPIO_PORTF_AHB_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
HWREG(GPIO_PORTF_AHB_BASE+GPIO_O_CR) |= GPIO_PIN_2;

//configure pin as a PWM pin
GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
GPIOPinConfigure(GPIO_PF2_M0PWM2);

//3. Set the pwm clock to the system clock/64
PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);

//4. Configure the PWM generator
PWMGenConfigure(PWM0_BASE, PWM_GEN_1, (PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC));

//5. Set the period for the generator
//set pwm to run at 100hz . (N = (1 / f) * SysClk) ; (1 / 100Hz) * (120MHz/64) = 18750 cycles
unsigned long period = 18750;
PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period);

//6. Enable the PWM outputs
// Enable the PWM1 Bit 0 (PF1) and Bit 1 (PF2) output signals.
PWMOutputState(PWM0_BASE,  PWM_OUT_2_BIT, true);

//7. set the pulse width



//8. Enable the PWM Generator
PWMGenEnable(PWM0_BASE, PWM_GEN_1);
while(1)
{
    uint32_t ui32SysClock;

        //
        // Run from the PLL at 120 MHz.
        //
        ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                               SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                               SYSCTL_CFG_VCO_480), 120000000);
int i;
for(i=1;i<=period;i++)
{
PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, (period/i));
SysCtlDelay(ui32SysClock/100);
}
}
}

