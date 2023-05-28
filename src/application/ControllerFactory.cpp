#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"

const std::vector<ControllerMenu::MenuButtonData> mainMenuConfig = {
    { ControllerMenu::MenuButtonData { .state = CalibrationMenu, .text = "Run Calibration" } },
    { ControllerMenu::MenuButtonData { .state = ManualControlMenu, .text = "Manual Control" } },
    { ControllerMenu::MenuButtonData { .state = SettingsMenu, .text = "Settings" } }
};

const std::vector<ControllerMenu::MenuButtonData> calibrationMenuConfig = {
    { ControllerMenu::MenuButtonData { .state = CalibrationMode, .text = "Begin Calibration" } },
    { ControllerMenu::MenuButtonData { .state = CalibrationSettings, .text = "Calibration Settings" } }
};

ControllerFactory::ControllerFactory(Adafruit_GFX& display, InputManager& manager) :
    _display(display), _inputManager(manager) { }

std::shared_ptr<ControllerBase> ControllerFactory::create(ApplicationState state) {
    StateData data { .state = state, .inFocus = 0 };
    return _createInternal(data);
}

std::shared_ptr<ControllerBase> ControllerFactory::create(StateData data) {
    return _createInternal(data);
}

void ControllerFactory::setContext(ApplicationContext* context) {
    _context = context;
}

std::shared_ptr<ControllerBase> ControllerFactory::_createInternal(StateData data) {
    std::shared_ptr<ControllerBase> ret = nullptr;
    switch (data.state) {
        case MainMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display, data.inFocus);
            static_cast<ControllerMenu*>(ret.get())->getView().setHeader("main menu");
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, mainMenuConfig);
            break;
        case ManualControlMenu:
            // TODO: add ManualControlMenu implementation
            break;
        case CalibrationMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display, data.inFocus);
            static_cast<ControllerMenu*>(ret.get())->getView().setHeader("calibration setup");
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, calibrationMenuConfig);
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