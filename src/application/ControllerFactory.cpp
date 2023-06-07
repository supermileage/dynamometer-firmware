#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"
#include "TextDialogController.h"

const std::vector<ControllerMenu::MenuButtonInfo> mainMenuConfig = {
    { ControllerMenu::MenuButtonInfo {
        .text = "Run Calibration",
        .info = { .state = CalibrationMenu } } },
    { ControllerMenu::MenuButtonInfo {
        .text = "Manual Control",
        .info = { .state = ManualControlMenu } } },
    { ControllerMenu::MenuButtonInfo {
            .text = "Text Dialog",
            .info = { .state = TextDialog, .config = {
                { CONFIG_ID_EDIT_STRING_ID, String(CONFIG_ID_DEFAULT_OUTPUT_FILENAME) }, } } } }
};

const std::vector<ControllerMenu::MenuButtonInfo> calibrationMenuConfig = {
    { ControllerMenu::MenuButtonInfo { .text = "Begin Calibration", .info { .state = CalibrationMode } } },
    { ControllerMenu::MenuButtonInfo { .text = "Calibration Settings", .info { .state = CalibrationSettings } } },
};

ControllerFactory::ControllerFactory(Adafruit_GFX& display, InputManager& manager) :
    _display(display), _inputManager(manager) { }

std::shared_ptr<ControllerBase> ControllerFactory::create(StateInfo& info) {
    return _createInternal(info);
}

void ControllerFactory::setContext(ApplicationContext* context) {
    _context = context;
}

std::shared_ptr<ControllerBase> ControllerFactory::_createInternal(StateInfo& info) {
    std::shared_ptr<ControllerBase> ret = nullptr;
    switch (info.state) {
        case MainMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, mainMenuConfig);
            break;
        case ManualControlMenu:
            // TODO: add ManualControlMenu implementation
            break;
        case CalibrationMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, calibrationMenuConfig);
            break;
        case SettingsMenu:
            // TODO: add SettingsMenu implementation
            break;
        case TextDialog:
            ret = std::make_shared<TextDialogController>(*_context, _display);
            static_cast<TextDialogController*>(ret.get())->init(_inputManager, info);
            break;
        default:
            // do nothing
            break;
    }
    return ret;
}