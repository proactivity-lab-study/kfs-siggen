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

void buzzer_pin_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_GPIO, true);

    // Init LED pins
    GPIO_PinModeSet(BUZZER_PORT, BUZZER_PIN, gpioModePushPull, 0);
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
	TIMER0->ROUTELOC0 = TIMER_ROUTELOC0_CC0LOC_LOC0;

	// Set same TIMER0 top value for all CC channels.
	TIMER_TopSet(TIMER0, 0);

	// TIMER general init
    // https://docs.silabs.com/mcu/latest/efr32mg12/structTIMER-Init-TypeDef
	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = BUZ_TIMER0_CLOCK_DIV;
	timerInit.enable = false; // Start timer after init.

	TIMER_Init(TIMER0, &timerInit);
	
	return (uint32_t)(CMU_ClockFreqGet(cmuClock_TIMER0) / (uint32_t)(0x1 << BUZ_TIMER0_CLOCK_DIV));

}

void set_top_val(uint32_t topVal)
{
    TIMER_TopBufSet(TIMER0, topVal);
    TIMER_Enable(TIMER0, true);
}

void timer_stop()
{
    TIMER_Enable(TIMER0, false);
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
	
	TIMER_InitCC(TIMER0, BUZZER_CC_CHANNEL, &ccInit);

	// Enable GPIO toggling by TIMER and set location of pins to be toggled.
	TIMER0->ROUTEPEN = (TIMER_ROUTEPEN_CC0PEN); //Definition at line 589 of file efr32mg12p_timer.h.
	TIMER0->ROUTELOC0 = (BUZZER_LOCATION);

	// Set TIMER0 top value and initial PWM duty cycle.
	TIMER_TopSet(TIMER0, BUZ_TIMER0_TOP_VAL);
	TIMER_CompareBufSet(TIMER0, BUZZER_CC_CHANNEL, 0); // Initial duty cycle = 0

	// TIMER general init
	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = BUZ_TIMER0_CLOCK_DIV;
	timerInit.enable = true; // Start timer after init.

	TIMER_Init(TIMER0, &timerInit);

    return (uint32_t)(CMU_ClockFreqGet(cmuClock_TIMER0) / (uint32_t)(0x1 << BUZ_TIMER0_CLOCK_DIV));
}

void set_duty_cycle(uint32_t dc)
{
    TIMER_CompareBufSet(TIMER0, BUZZER_CC_CHANNEL, dc);
}

