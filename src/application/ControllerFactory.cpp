#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"
#include "TextDialogController.h"

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
            static_cast<ControllerMenu*>(ret)->getView().setHeader("main menu");
            static_cast<ControllerMenu*>(ret)->init(_inputManager, mainMenuConfig);
            break;
        case ManualControlMenu:
            // TODO: add ManualControlMenu implementation
            break;
        case CalibrationMenu:
            ret = new ControllerMenu(*_context, _display, data.inFocus);
            static_cast<ControllerMenu*>(ret)->getView().setHeader("calibration setup");
            static_cast<ControllerMenu*>(ret)->init(_inputManager, calibrationMenuConfig);
            break;
        case SettingsMenu:
            // TODO: add SettingsMenu implementation
            break;
        case TextDialog:
            ret = new TextDialogController(*_context, _display, data.inFocus);
            static_cast<TextDialogController*>(ret)->getView().setHeader("text dialog");
            static_cast<TextDialogController*>(ret)->init(_inputManager, String("file.csv"));
        default:
            // do nothing
            break;
    }
    return ret;
}