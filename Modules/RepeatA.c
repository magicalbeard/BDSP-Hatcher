#include "Joystick.h"
#include "Modules.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "util/delay.h"		// include timer function library

#define SECOND 125
#ifdef SECOND
#define RET_COUNT SECOND * 125
#else
// 一番時間がかかるドラメシヤがこれ
#define RET_COUNT 18500
#endif


static uint16_t duration_count = 0;
int count = 0;
uint16_t i = 0;

void delay(unsigned long seconds_to_delay) {
    unsigned long delay_stop = 0;
    unsigned long currentMillis = millis();
    delay_stop = currentMillis + (seconds_to_delay * 1000);
    while(delay_stop > millis()) {  // loop adds some overhead
        asm("nop");
    }
}

void delay_1s(void) {
    for (uint16_t delay_count = 0; delay_count < 125; delay_count++) {
        switch (delay_count) {
            case 0 ... 125:
                asm("nop");
                break;
        }
    }
}

void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData)
{
    _delay_ms(2000);
    ReportData->LX = STICK_MAX;
    _delay_ms(1000);
    ReportData->LX = STICK_MIN;
    _delay_ms(1000);
    ReportData->LY = STICK_MIN;
    ReportData->Button |= SWITCH_X;
    _delay_ms(1000);
    ReportData->Button |= SWITCH_B;
    /*
    switch (count) {
        case 0 ... 125:
            // Move Right
            //if (count % 50 < 10)
            ReportData->LX = STICK_MAX;
            break;
        case 126 ... 250:
            // Turn around
            //if (count % 50 < 10)
            ReportData->LX = STICK_MIN;
            ReportData->RX = STICK_MAX;
            break;
        case 251 ... 300:
            ReportData->RX = STICK_MIN;
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_X;
            break;
        case 301 ... 350:
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_B;
        case 1000:
            count = 0;
    }
     */

    count++;
}