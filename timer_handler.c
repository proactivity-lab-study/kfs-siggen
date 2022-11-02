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
 * @brief Init GPIO and configure LED pins. 
 */
void led_pin_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_GPIO, true);

    // TODO Init LED pins
}

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
uint32_t timer0_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

    // TODO Configure CC to compare mode, toggle action
    // TODO Route timer output(action) to LED pin
    // TODO Configure Timer
    
    return 0;
}


