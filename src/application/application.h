#ifndef _APPLICATION_H_
#define _APPLICATION_H_

namespace application {
    /**
     * @brief ApplicationState is enum representing all application states
     * @note add state here when adding new state to application
    */
    enum ApplicationState {
        NullState = -1,
        MainMenu = 0,
        ManualControlMenu = 1,
        CalibrationMenu = 2,
        SettingsMenu = 3,
        CalibrationMode = 4,
        CalibrationSettings = 5
    };

    /**
     * @brief represents state information which can be used for transitions and navigation
    */
    struct StateData {
        ApplicationState state;
        uint8_t inFocus;

        /**
         * @brief reset to null state
        */
        void reset() {
            state = NullState;
            inFocus = 0;
        }
    };
}

#endif