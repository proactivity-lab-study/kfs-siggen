# Timer example
A software project base to demonstrate Timer peripheral usage.
 * Use Timer to fade LED brightness and generate PWM signals.

# Platforms
The application has been tested and should work with the following platforms:
 * Thinnect TestSystemBoard tsb0

# Build
 * Add project as submodule to the https://github.com/thinnect/node-apps.git project. Put it under 'node-apps/apps' directory. 
 * Open terminal and navigate to 'node-apps/apps/kfs-siggen' directory and type 'make tsb0' to build project.

# Resources
 * EFR32 Application Note on Timers
   https://www.silabs.com/documents/public/application-notes/AN0014.pdf
 * EFR32MG12 Wireless Gecko Reference Manual (Timer p672)
   https://www.silabs.com/documents/public/reference-manuals/efr32xg12-rm.pdf
 * Timer API documentation 
   https://docs.silabs.com/mcu/latest/efr32mg12/group-TIMER
 * ARM RTOS API
   https://arm-software.github.io/CMSIS_5/RTOS2/html/group__CMSIS__RTOS.html
