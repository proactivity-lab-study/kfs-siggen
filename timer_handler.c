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

    // Init LED pins
    GPIO_PinModeSet(KFS_LED2_PORT, 5, gpioModePushPull, 0);
}

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
uint32_t timer0_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

    // Configure CC to compare mode, toggle action
    TIMER_InitCC_TypeDef ccInit = TIMER_INITCC_DEFAULT;
	ccInit.mode = timerCCModeCompare;
	ccInit.cmoa = timerOutputActionToggle;
		
	// Initilize a CC channels for toggling buzzer.
	TIMER_InitCC(TIMER0, 0, &ccInit);
	
	
    // TODO Route timer output(action) to LED pin
    // TODO Configure Timer
    
    return 0;
}


