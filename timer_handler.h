/**
 * @file timer_handler.h
 *
 * @author Johannes Ehala, ProLab.
 * @license MIT
 *
 * Copyright ProLab, TTÜ. 15 January 2022
 */

#ifndef TIMER_HANDLER_H_
#define TIMER_HANDLER_H_

// LED ports and pins. Timer counter routing to LEDs.
#define KFS_LED0_PORT       gpioPortB
#define KFS_LED1_PORT       gpioPortB
#define KFS_LED2_PORT       gpioPortA

#define KFS_LED0_PIN        12 // Red
#define KFS_LED1_PIN        11 // Green
#define KFS_LED2_PIN        5 // Blue

#define KFS_LED0_LOCATION   TIMER_ROUTELOC0_CC0LOC_LOC7 // PB12 route location for CC channel 7
#define KFS_LED1_LOCATION   TIMER_ROUTELOC0_CC0LOC_LOC6 // PB11 route location for CC channel 6
#define KFS_LED2_LOCATION   TIMER_ROUTELOC0_CC0LOC_LOC5 // PA5 route location for CC channel 5

#define LED_COUNTER_IF      0x01

// Buzzer port and pin is PA0, timer compare-capture interface routing to PA0
#define BUZZER_PORT             gpioPortA
#define BUZZER_PIN              0
#define BUZZER_CC_CHANNEL       0
#define BUZZER_LOCATION         TIMER_ROUTELOC0_CC0LOC_LOC0 // PA0 route location for CC channel 0

// PWM configuration parameters
#define BUZ_TIMER0_CLOCK_DIV        timerPrescale1024 // Timer0 clock divider
#define BUZ_TIMER0_TOP_VAL      100
#define BUZ_PWM_DUTY_CYCLE      50

// Public functions
void led_pin_init();
void buzzer_pin_init();

uint32_t timer0_init_counter();
uint32_t timer0_init_pwm();

void start_timer(uint32_t topVal);
void stop_timer();
void set_top_val(uint32_t topVal);

void set_duty_cycle(uint32_t dc);

#endif // TIMER_HANDLER_H_ */
