/**
 * @brief Example usage of Timer peripheral.
 *
 * EFR32 Application Note on Timers
 * https://www.silabs.com/documents/public/application-notes/AN0014.pdf
 *
 * EFR32MG12 Wireless Gecko Reference Manual (Timer p672)
 * https://www.silabs.com/documents/public/reference-manuals/efr32xg12-rm.pdf
 *
 * Timer API documentation 
 * https://docs.silabs.com/mcu/latest/efr32mg12/group-TIMER
 * 
 * ARM RTOS API
 * https://arm-software.github.io/CMSIS_5/RTOS2/html/group__CMSIS__RTOS.html
 * 
 * Copyright Thinnect Inc. 2019
 * Copyright ProLab TTÜ 2022
 * @license MIT
 * @author Johannes Ehala
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "retargetserial.h"
#include "cmsis_os2.h"
#include "platform.h"

#include "SignatureArea.h"
#include "DeviceSignature.h"

#include "loggers_ext.h"
#include "logger_fwrite.h"

#include "timer_handler.h"
#include "em_timer.h"
#include "em_gpio.h"

#include "loglevels.h"
#define __MODUUL__ "main"
#define __LOG_LEVEL__ (LOG_LEVEL_main & BASE_LOG_LEVEL)
#include "log.h"

// Include the information header binary
#include "incbin.h"
INCBIN(Header, "header.bin");

void LED_control();
void motor_control();

// Heartbeat thread, initialize Timer and print heartbeat messages.
void hp_loop ()
{
    #define HB_DELAY 10 // Heartbeat message delay, seconds
    uint32_t clock_freq;
    
    // Configure LED pin.
    led_pin_init();
    
    // Configure vibro-motor pin.
    motor_pin_init();
    
    // Initialize Timer.
    clock_freq = timer0_init_pwm();
    //clock_freq = timer0_init_counter();
    
    info1("Timer 0 clock %lu", clock_freq);
    
    // Create thread to control LEDs.
    const osThreadAttr_t led_thread_attr = { .name = "LED" };
    osThreadNew(LED_control, NULL, &led_thread_attr);
    
    // Create thread to control vibromotor.
    const osThreadAttr_t motor_thread_attr = { .name = "motor" };
    osThreadNew(motor_control, NULL, &motor_thread_attr);
    
    for (;;)
    {
        osDelay(HB_DELAY*osKernelGetTickFreq());
        info1("Heartbeat");
    }
}

void LED_control()
{
    for(;;)
    {
        // turn LED on
        // GPIO_PinOutSet(KFS_LED2_PORT, 5);
        //set_top_val(10000);
        // wait 1 sec
        osDelay(1000);
        // 
        //set_top_val(1);
        // wait 1 sec
        osDelay(1000);
    }
}

void motor_control()
{
    for(;;)
    {
        set_duty_cycle(95);
        osDelay(1000);
        set_duty_cycle(0);
        osDelay(1000);
    }
}

int logger_fwrite_boot (const char *ptr, int len)
{
    fwrite(ptr, len, 1, stdout);
    fflush(stdout);
    return len;
}

int main ()
{
    PLATFORM_Init();

    // Configure log message output
    RETARGET_SerialInit();
    log_init(BASE_LOG_LEVEL, &logger_fwrite_boot, NULL);

    info1("KFS-Signal-Generator "VERSION_STR" (%d.%d.%d)", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

    // Initialize OS kernel.
    osKernelInitialize();

    // Create a thread.
    const osThreadAttr_t hp_thread_attr = { .name = "hp" };
    osThreadNew(hp_loop, NULL, &hp_thread_attr);

    if (osKernelReady == osKernelGetState())
    {
        // Switch to a thread-safe logger
        logger_fwrite_init();
        log_init(BASE_LOG_LEVEL, &logger_fwrite, NULL);

        // Start the kernel
        osKernelStart();
    }
    else
    {
        err1("!osKernelReady");
    }

    for(;;);
}
