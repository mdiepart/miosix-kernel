/***************************************************************************
 *   Copyright (C) 2021 by Terraneo Federico                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

/*
 * This file implements the functions for the IRQ timer on the NXP MK22F51212 series of MCU.
 * The timer used is the FlexTimer 0 (FTM0). This timer is clocked by the Bus Clock. 
 * The timer is a 16 bits timer. A prescaler of 4 was selected for a clocking frequency
 * of 59.904 MHz / 4 = 14.976 MHz. This makes it possible to have an integer number of clock
 * cycles in 1ms. This also provokes a timer overflow every 65536/14976000 = 4.38 ms.
 * 
 * In order to keep an integer number of cycles in a millisecond, the prescaler can go up to
 * the maximum value but at that point, the resolution of the timer will of course degrade.
 */

#include "kernel/kernel.h"
#include "interfaces/os_timer.h"
#include "interfaces/arch_registers.h"

namespace miosix {

class NXPFlexTimer0
{
public:
    static inline FTM_Type *get() { return FTM0; }
    static inline IRQn_Type getIRQn() { return FTM0_IRQn; }
    static inline void enableClock() { SIM->SCGC6 |= SIM_SCGC6_FTM0(1); }
};
#define IRQ_HANDLER_NAME FTM0_IRQHandler
#define TIMER_HW_CLASS NXPFlexTimer0

template<class T>
class MK22FlexTimer : public TimerAdapter<MK22FlexTimer<T>, 16>
{
public:   
    static inline unsigned int IRQgetTimerCounter() { return T::get()->CNT; }
    static inline void IRQsetTimerCounter(unsigned int v)
    {
        T::get()->CNTIN = v;
        __NOP();
        T::get()->CNT = v; // When CNT is written to, it gets updated with CNTIN value
        T::get()->CNTIN = 0;
    }

    static inline unsigned int IRQgetTimerMatchReg() { return T::get()->CONTROLS[0].CnV; }
    static inline void IRQsetTimerMatchReg(unsigned int v) { T::get()->CONTROLS[0].CnV=v; }

    static inline bool IRQgetOverflowFlag() { return T::get()->SC & FTM_SC_TOF_MASK; }
    static inline void IRQclearOverflowFlag() { T::get()->SC &= ~FTM_SC_TOF(1); } // This will only work if SC was read while TOF was set and setting the bit to 0.
    
    static inline bool IRQgetMatchFlag() { return T::get()->CONTROLS[0].CnSC & FTM_CnSC_CHF(1); }
    static inline void IRQclearMatchFlag() { T::get()->CONTROLS[0].CnSC &= ~FTM_CnSC_CHF(1); }
    
    static inline void IRQforcePendingIrq() { NVIC_SetPendingIRQ(T::getIRQn()); }

    static inline void IRQstopTimer() { T::get()->SC &= ~FTM_SC_CLKS(3); }
    static inline void IRQstartTimer() { T::get()->SC |= FTM_SC_CLKS(1); }
    
    static unsigned int IRQTimerFrequency()
    {
        /* The global variable SystemCoreClock from ARM's CMSIS allows to know
         * the CPU frequency. From there we get the common clock source to both system clock and 
         * bus clock. Then divide by the clock divider for the bus clock. 
         * Finally we take the prescaler into account.
         */
        
        uint32_t mcgoutClock = SystemCoreClock * (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
        uint32_t busClock = mcgoutClock / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1);
        uint32_t freq = busClock >> (T::get()->SC & FTM_SC_PS_MASK);
        return freq;
    }
    
    static void IRQinitTimer()
    {
        // Enable clock to FTM
        SIM->SCGC6 |= SIM_SCGC6_FTM0(1);

        // Set counter to count up to maximum value, counter initializes at 0
        T::get()->CNTIN = 0x0000;
        T::get()->MOD = 0xFFFF;

        // Set output compare mode without gpio output but with
        // interrupt enabled
        T::get()->CONTROLS[0].CnSC = FTM_CnSC_CHF(0) | FTM_CnSC_CHIE(1) |
                                 FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | 
                                 FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(0) |
                                 FTM_CnSC_ICRST(0) | FTM_CnSC_DMA(0);
        
        // Enable interrupts, keep timer disabled, set prescaler to 4
        T::get()->SC = FTM_SC_TOF(0) | FTM_SC_TOIE(1) | FTM_SC_CPWMS(0) |
                   FTM_SC_CLKS(0) | FTM_SC_PS(2);

        // Enable interrupts for FTM0
        NVIC_SetPriority(T::getIRQn(), 3); //High priority for FTM0 (Max=0, min=15)
        NVIC_EnableIRQ(T::getIRQn());
     
        // FTMEN set to 0, when writing to registers, their value 
        // is updated:
        //  - next system clock cycle for CNTIN
        //  - when FTM counter changes from MOD to CNTIN for MOD
        //  - when the FTM counter updates for CnV
        T::get()->MODE = FTM_MODE_FAULTIE(0) | FTM_MODE_FAULTM(0) |
                     FTM_MODE_CAPTEST(0) | FTM_MODE_PWMSYNC(0) |
                     FTM_MODE_WPDIS(0) | FTM_MODE_INIT(0) |
                     FTM_MODE_FTMEN(0);
    }
};

static MK22FlexTimer<TIMER_HW_CLASS> timer;
DEFAULT_OS_TIMER_INTERFACE_IMPLMENTATION(timer);
} //namespace miosix

void __attribute__((naked)) IRQ_HANDLER_NAME()
{
    saveContext();
    asm volatile ("bl _Z11osTimerImplv");
    restoreContext();
}

void __attribute__((used)) osTimerImpl()
{
    miosix::timer.IRQhandler();
}