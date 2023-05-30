#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"


const std::vector<ControllerMenu::MenuButtonData> mainMenuConfig = {
    { ControllerMenu::MenuButtonData { .state = CalibrationMenu, .text = "Run Calibration" } },
    { ControllerMenu::MenuButtonData { .state = ManualControlMenu, .text = "Manual Control" } },
    { ControllerMenu::MenuButtonData { .state = TextDialog, .text = "Text Dialog" } }
};

const std::vector<ControllerMenu::MenuButtonData> calibrationMenuConfig = {
    { ControllerMenu::MenuButtonData { .state = CalibrationMode, .text = "Begin Calibration" } },
    { ControllerMenu::MenuButtonData { .state = CalibrationSettings, .text = "Calibration Settings" } }
};

ControllerFactory::ControllerFactory(Adafruit_GFX& display, InputManager& manager) :
    _display(display), _inputManager(manager) { }

std::shared_ptr<ControllerBase> ControllerFactory::create(StateData& data) {
    return _createInternal(data);
}

void ControllerFactory::setContext(ApplicationContext* context) {
    _context = context;
}

std::shared_ptr<ControllerBase> ControllerFactory::_createInternal(StateData& data) {
    std::shared_ptr<ControllerBase> ret = nullptr;
    switch (data.state) {
        case MainMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, data, mainMenuConfig);
            break;
        case ManualControlMenu:
            // TODO: add ManualControlMenu implementation
            break;
        case CalibrationMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, data, calibrationMenuConfig);
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