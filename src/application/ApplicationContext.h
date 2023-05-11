#ifndef _APPLICATION_CONTEXT_H_
#define _APPLICATION_CONTEXT_H_

#include <stack>

#include "Adafruit_GFX.h"
#include "System/Handleable.h"
#include "System/InputManager.h"
#include "application/MenuControllerExample.h"

class MenuControllerExample;

class ApplicationContext : public Handleable {
    public:
        enum ApplicationState { MainMenu, ManualControlMenu, CalibrationMenu, SettingsMenu };

        ApplicationContext(InputManager& manager, Adafruit_GFX& display, ApplicationState state = MainMenu);

        ~ApplicationContext() { }
        void begin() override;
        void handle() override { }
        void changeState(ApplicationState state);
        void navigateBack();
    
    private:
        MenuControllerExample* _controller;
        InputManager& _inputManager;
        Adafruit_GFX& _display;
        ApplicationState _currentState;
        std::stack<ApplicationState> _previousStates;

        void _changeStateInternal(ApplicationState state);
        static const String stateToString(ApplicationState state);
};

#endif