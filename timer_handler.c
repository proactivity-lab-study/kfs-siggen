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

void motor_pin_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_GPIO, true);

    // Init LED pins
    GPIO_PinModeSet(VIBROMOTOR_PORT, VIBROMOTOR_PIN, gpioModePushPull, 0);
}

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
uint32_t timer0_init_counter(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

    // Configure CC to compare mode, toggle action
    TIMER_InitCC_TypeDef ccInit = TIMER_INITCC_DEFAULT;
	ccInit.mode = timerCCModeCompare;
	ccInit.cmoa = timerOutputActionToggle;
		
	// Initilize a CC channels for toggling buzzer.
	TIMER_InitCC(TIMER0, 0, &ccInit);
	
	// Enable GPIO toggling by TIMER and set location of pins to be toggled.
	TIMER0->ROUTEPEN = TIMER_ROUTEPEN_CC0PEN;
	
	// Route timer output(action) to LED pin
	TIMER0->ROUTELOC0 = KFS_LED2_LOCATION;

	// Set same TIMER0 top value for all CC channels.
	TIMER_TopSet(TIMER0, 1000);

	// TIMER general init
    // https://docs.silabs.com/mcu/latest/efr32mg12/structTIMER-Init-TypeDef
	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = MOT_TIMER0_CLOCK_DIV;
	timerInit.enable = true; // Start timer after init.

	TIMER_Init(TIMER0, &timerInit);
	
	return (uint32_t)(CMU_ClockFreqGet(cmuClock_TIMER0) / (uint32_t)(0x1 << MOT_TIMER0_CLOCK_DIV));

}

void set_top_val(uint32_t topVal)
{
    TIMER_TopBufSet(TIMER0, topVal);
}

uint32_t timer0_init_pwm(void)
{
// Enable Timer and GPIO clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

	// Init CompareCapture for PWM. 
	// https://docs.silabs.com/mcu/latest/efr32mg12/structTIMER-InitCC-TypeDef
	TIMER_InitCC_TypeDef ccInit = TIMER_INITCC_DEFAULT;
	ccInit.mode = timerCCModePWM;
	ccInit.cmoa = timerOutputActionToggle;
	
	TIMER_InitCC(TIMER0, VIBROMOTOR_CC_CHANNEL, &ccInit);

	// Enable GPIO toggling by TIMER and set location of pins to be toggled.
	TIMER0->ROUTEPEN = (TIMER_ROUTEPEN_CC0PEN); //Definition at line 589 of file efr32mg12p_timer.h.
	TIMER0->ROUTELOC0 = (VIBROMOTOR_LOCATION);

	// Set TIMER0 top value and initial PWM duty cycle.
	TIMER_TopSet(TIMER0, MOT_TIMER0_TOP_VAL);
	TIMER_CompareBufSet(TIMER0, VIBROMOTOR_CC_CHANNEL, 0); // Initial duty cycle = 0

	// TIMER general init
	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = MOT_TIMER0_CLOCK_DIV;
	timerInit.enable = true; // Start timer after init.

	TIMER_Init(TIMER0, &timerInit);

    return (uint32_t)(CMU_ClockFreqGet(cmuClock_TIMER0) / (uint32_t)(0x1 << MOT_TIMER0_CLOCK_DIV));
}

void set_duty_cycle(uint32_t dc)
{
    TIMER_CompareBufSet(TIMER0, VIBROMOTOR_CC_CHANNEL, dc);
}

