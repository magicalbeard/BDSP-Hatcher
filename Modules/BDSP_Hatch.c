//
// Created by user on 1/8/22.
//

#include "../Joystick.h"
#include "Modules.h"

#define SECOND 125

typedef enum {
    FLY_TO_RESET,
    WALK_TO_MAN,
    TALK_TO_MAN,
    GET_EGG,
    BIKE_SETUP,
    HATCH_EGG,
} State_t;

static State_t state = FLY_TO_RESET;
static uint16_t duration_count;
const int state_counter = 0;
static uint16_t egg_hatch_duration = 21;
static uint16_t hatch_counter = 0;

static uint8_t FlyToReset(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
    switch (count) {
        case 0 ... 249:
            // Wait 2 seconds before starting
            /* Open menu */
            break;
        case 250 ... 299:
            // Open Menu
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_X;
            break;
        case 300 ... 549:
            // Wait 2 seconds to open menu
            break;
        case 550 ... 599:
            // Select Map
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_START; // might need to change
            break;
        case 600 ... 849:
            // Wait 2 seconds to open map
            break;
        case 850 ... 1549:
            // Align at bottom of map
            if (count % 50 < 25)
                ReportData->HAT = HAT_BOTTOM;
            break;
        case 1550 ... 1999:
            // move up to town
            if (count % 50 < 25)
                ReportData->HAT = HAT_TOP;
            break;
        case 2000 ... 2049:
            // move right 1 space
            if (count % 50 < 25)
                ReportData->HAT = HAT_RIGHT;
            break;
        case 2050 ... 2099:
            // select town
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 2100 ... 2249:
            // wait for box to load
            break;
        case 2250 ... 2299:
            // "yes" to fly
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 2300 ... 3750:
            // wait 10s
            break;
        case 3800:
            return 1;
    }
    return 0;
}

static uint8_t WalkToMan(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
    switch (count) {
        case 0 ... 80:
            // walk left 0.8s
            ReportData->LX = STICK_MIN;
            break;
        case 125 ... 284:
            // Walk Up 2 sec
            ReportData->LX = STICK_CENTER;
            ReportData->LY = STICK_MIN;
            break;
        case 285 ... 384:
            // Walk left 1 sec
            ReportData->LY = STICK_CENTER;
            ReportData->LX = STICK_MIN;
            break;
        case 400:
            return 1;
    }
    return 0;
}

static uint8_t TalkToMan(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
    switch (count) {
        case 0 ... 49:
            // first talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 50 ... 374:
            // wait 2.5s
            break;
        case 375 ... 424:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 425 ... 674:
            // wait 2s
            break;
        case 675 ... 724:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 725 ... 974:
            // wait 2s
            break;
        case 975 ... 1024:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 1025 ... 1274:
            // wait 2s
            break;
        case 1275 ... 1324:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 1325 ... 1574:
            // wait 2s
            break;
        case 1575 ... 1624:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 1625 ... 2099:
            // wait 3.5s
            break;
        case 2100 ... 2149:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 2150 ... 2649:
            // wait 4s
            break;
        case 2650 ... 2699:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 2700 ... 3199:
            // wait 4s
            break;
        case 3200 ... 3249:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 3250 ... 3749:
            // wait 4s
            break;
        case 3750 ... 3799:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 3800 ... 4174:
            // wait 3s
            break;
        case 4175 ... 4224:
            // Select 2nd slot pokemon to replace
            if (count % 50 < 25)
                ReportData->HAT = HAT_BOTTOM;
            break;
        case 4225 ... 4349:
            // wait 1s
            break;
        case 4350 ... 4399:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 4400 ... 4649:
            // wait 2s
            break;
        case 4650 ... 4699:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 4700 ... 5199:
            // wait 4s
            break;
        case 5200 ... 5249:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 5250 ... 5699:
            // wait 4s
            break;
        case 5700 ... 5749:
            // talk to man
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            break;
        case 5850:
            return 1;
    }
    return 0;
}

static uint8_t BikeSetup(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
    switch (count) {
        case 0 ... 106:
            // walk right
            ReportData->LX = STICK_MAX;
            break;
        case 125 ... 174:
            // Walk Up 2 sec
            ReportData->LX = STICK_CENTER;
            // Select Bike
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_START; // might need to change
            break;
        case 175 ... 224:
            // Wait a smidge
            break;
        case 225 ... 974:
            ReportData->LY = STICK_MIN;
            break;
        case 1025:
            return 1;
    }
    return 0;
}

static uint8_t HatchEgg(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
    switch (count) {
        case 0 ... 1299:
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            ReportData->LY = STICK_MAX;
            break;
        case 1300 ... 2599:
            if (count % 50 < 25)
                ReportData->Button |= SWITCH_A;
            ReportData->LY = STICK_MIN;
            break;
        case 2625:
            return 1;
    }
    return 0;
}

void BDSP_Hatch_Module(USB_JoystickReport_Input_t* const ReportData)
{
    switch (state) {
        case FLY_TO_RESET:
            if (FlyToReset(ReportData, duration_count)) {
                state = WALK_TO_MAN;
                duration_count = 0;
            }
            break;
        case WALK_TO_MAN:
            if (WalkToMan(ReportData, duration_count)) {
                state = TALK_TO_MAN;
                duration_count = 0;
            }
            break;
        case TALK_TO_MAN:
            if (TalkToMan(ReportData, duration_count)) {
                state = BIKE_SETUP;
                duration_count = 0;
            }
            break;
        case BIKE_SETUP:
            if (BikeSetup(ReportData, duration_count)) {
                state = HATCH_EGG;
                duration_count = 0;
            }
            break;
        case HATCH_EGG:
            if (HatchEgg(ReportData, duration_count)) {
                if (hatch_counter == egg_hatch_duration) {
                    state = FLY_TO_RESET;
                    hatch_counter = 0;
                    duration_count = 0;
                    break;
                }
                duration_count=0;
                state = HATCH_EGG;
                hatch_counter++;
            }
            break;
            /*
        case SELECT_OTHER_POKEMON:
            if (release_count == MAX_EGG_COUNT || release_count == LIMIT_EGG_COUNT) {
                state = DONE;
            } else if (SelectOtherPokemon(ReportData, duration_count, release_count)) {
                state = RELEASE_POKEMON;
                duration_count = 0;
            }
            break;
        case DONE:
            break;
             */
    }
    duration_count++;
}
