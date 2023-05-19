#include "MenuControllerExample.h"

#define BUTTON_ID_CALIBRATE 0
#define BUTTON_ID_CONTROL   1
#define BUTTON_ID_SETTINGS  2

MenuControllerExample::MenuControllerExample(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
	_context(context), _inFocus(inFocus) {
    	_menu = new MenuViewExample(display);
    	_menuButtonCalibrate = new UIButton(display);
    	_menuButtonCtrl = new UIButton(display);
    	_menuButtonSettings = new UIButton(display);
}

MenuControllerExample::~MenuControllerExample() {
    // delete each UIElement stored in map
    for (const auto& pair : _buttonCallbackMap) {
        delete pair.second.first;
    }

	delete _menu;
}

void MenuControllerExample::init(InputManager& manager) {
    manager.registerAction( ID_SERIAL, [this](int32_t arg) { _handleInputSerial(arg); } );

    _menu->addMenuButton(_menuButtonCalibrate, "Run Calibration");
    _buttonCallbackMap[BUTTON_ID_CALIBRATE] =
        std::make_pair(_menuButtonCalibrate, [this]() { _context.changeState(ApplicationContext::CalibrationMenu); });
    
    _menu->addMenuButton(_menuButtonCtrl, "Manual Control");
    _buttonCallbackMap[BUTTON_ID_CONTROL] =
        std::make_pair(_menuButtonCtrl, [this]() { _context.changeState(ApplicationContext::ManualControlMenu); });
    
    _menu->addMenuButton(_menuButtonSettings, "Settings");
    _buttonCallbackMap[BUTTON_ID_SETTINGS] =
        std::make_pair(_menuButtonSettings, [this]() { _context.changeState(ApplicationContext::SettingsMenu); });

    UIEventHandler::instance().addEvent( [this]() { _menu->init(); } );
    UIEventHandler::instance().addEvent( [this]() { _buttonCallbackMap[_inFocus].first->focus(); } );
}

uint8_t MenuControllerExample::getInFocus() {
	return _inFocus;
}

void MenuControllerExample::_handleInputSerial(int32_t arg) {
    DEBUG_SERIAL_LN("Serial input received: " + String(arg));
    UIElement* cur;

    switch (arg) {
        case 65:
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent( [cur]() { cur->revert(); } );
            _inFocus = _inFocus == 0 ? _buttonCallbackMap.size() - 1 : _inFocus - 1;
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent([cur]() { cur->focus(); });
            break;
        case 66:
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent( [cur]() { cur->revert(); } );
            _inFocus = (_inFocus + 1) % _buttonCallbackMap.size();
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent([cur]() { cur->focus(); });
            break;
        case 10:
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent( [this, cur]() { cur->select(); _menu->select(); } );
            (_buttonCallbackMap[_inFocus].second)();
            break;
        default:
            // do nothing
            break;
    }
}

void MenuControllerExample::_handleInputSelect(int32_t arg) {

}

void MenuControllerExample::_handleInputBack(int32_t arg) {

}

void MenuControllerExample::_handleInputBrakeButton(int32_t arg) {

}

void MenuControllerExample::_handleInputBrakePot(int32_t arg) {

}
