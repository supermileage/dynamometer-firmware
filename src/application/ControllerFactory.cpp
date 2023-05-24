#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"

const std::vector<ControllerMenu::MenuButtonData> mainMenuConfig = {
    { ControllerMenu::MenuButtonData { .text = "Run Calibration", .state = CalibrationMenu } },
    { ControllerMenu::MenuButtonData { .text = "Manual Control", .state = ManualControlMenu } },
    { ControllerMenu::MenuButtonData { .text = "Settings", .state = SettingsMenu } }
};

ControllerFactory::ControllerFactory(Adafruit_GFX& display, InputManager& manager) :
    _display(display), _inputManager(manager) { }

ControllerBase* ControllerFactory::create(ApplicationState state) {
    StateData data { .state = state, .inFocus = 0 };
    return _createInternal(data);
}

ControllerBase* ControllerFactory::create(StateData data) {
    return _createInternal(data);
}

void ControllerFactory::setContext(ApplicationContext* context) {
    _context = context;
}

ControllerBase* ControllerFactory::_createInternal(StateData data) {
    ControllerBase* ret;
    switch (data.state) {
        case MainMenu:
            ret = new ControllerMenu(*_context, _display, data.inFocus);
            static_cast<ControllerMenu*>(ret)->init(_inputManager, mainMenuConfig);
            break;
        case ManualControlMenu:
            // TODO: add ManualControlMenu implementation
            break;
        case CalibrationMenu:
            // TODO: add CalibrationMenu implementation
            break;
        case SettingsMenu:
            // TODO: add SettingsMenu implementation
            break;
        default:
            // do nothing
            break;
    }
    return ret;
}