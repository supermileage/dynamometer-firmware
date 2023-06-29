#include <vector>

#include "ControllerFactory.h"
#include "ControllerMenu.h"
#include "TextDialogController.h"

// menu configs

typedef std::vector<ControllerMenu::MenuButtonInfo> NavMenuConfig;
typedef ControllerMenu::MenuButtonInfo ButtonInfo;

extern const NavMenuConfig MainMenuConfig;
extern const NavMenuConfig CalibrationMenuConfig;
extern const NavMenuConfig AutoControlMenuConfig;
extern const NavMenuConfig ManualControlMenuConfig;

// controller factory

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
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, MainMenuConfig);
            break;
        case GlobalSettingsMenu:
            // TODO: add SettingsMenu implementation
            break;
        case CalibrationMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, CalibrationMenuConfig);
            break;
        case CalibrationMode:
            // TODO: add calibration mode state
            break;
        case CalibrationSettings:
            // TODO: add calibration settings state
            break;
        case AutoControlMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, AutoControlMenuConfig);
            break;
        case AutoControlMode:
            // TODO: add auto control mode state
            break;
        case AutoControlSettings:
            // TODO: add auto control settings state
            break;
        case ManualControlMenu:
            ret = std::make_shared<ControllerMenu>(*_context, _display);
            static_cast<ControllerMenu*>(ret.get())->init(_inputManager, info, ManualControlMenuConfig);
            break;
        case ManualControlMode:
            // TODO: add manual control mode state
            break;
        case ManualControlSettings:
            // TODO: add manual control settings state
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

// menu configs

const NavMenuConfig MainMenuConfig = {
    { ButtonInfo {
        .text = "Manual Control",
        .info = { .state = ManualControlMenu } } },
    { ButtonInfo {
        .text = "Automated Control",
        .info = { .state = AutoControlMenu } } },
    { ButtonInfo {
        .text = "Calibration",
        .info = { .state = CalibrationMenu } } },
    { ButtonInfo {
        .text = "Settings",
        .info = { .state = GlobalSettingsMenu } } }
};

const NavMenuConfig CalibrationMenuConfig = {
    { ButtonInfo { .text = "Begin Calibration", .info { .state = CalibrationMode } } },
    { ButtonInfo { .text = "Calibration Settings", .info { .state = CalibrationSettings } } }
};

const NavMenuConfig AutoControlMenuConfig = {
    { ButtonInfo { .text = "Start Session", .info { .state = AutoControlMode } } },
    { ButtonInfo { .text = "Automation Settings", .info { .state = AutoControlSettings } } }
};

const NavMenuConfig ManualControlMenuConfig = {
    { ButtonInfo { .text = "Start Session", .info { .state = ManualControlMode } } },
    { ButtonInfo { .text = "Manual Settings", .info { .state = ManualControlSettings } } }
};