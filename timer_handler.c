/**
 * @file timer_handler.c
 *
 * @brief Init TIMER0 to control buzzer with PWM signal.
 * 
 * @author Johannes Ehala, ProLab.
 * @license MIT
 *
 * Copyright ProLab, TTÜ. 15 January 2022
 */

#include "em_cmu.h"
#include "em_timer.h"

#include "timer_handler.h"

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
void timer0_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

    // TODO Init
}
