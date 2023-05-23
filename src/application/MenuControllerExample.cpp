#include "MenuControllerExample.h"

#define BUTTON_ID_CALIBRATE 0
#define BUTTON_ID_CONTROL   1
#define BUTTON_ID_SETTINGS  2

MenuControllerExample::MenuControllerExample(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
    _context(context) {
        _inFocus = inFocus;
        _menu = new MenuViewExample(display);
    	_menuButtonCalibrate = new UIButton(display);
    	_menuButtonCtrl = new UIButton(display);
    	_menuButtonSettings = new UIButton(display);
}

MenuControllerExample::~MenuControllerExample() {
    delete _menu;
    delete _menuButtonCalibrate;
	delete _menuButtonCtrl;
    delete _menuButtonSettings;
}

void MenuControllerExample::init(InputManager& manager) {
    // register all input callbacks with input manager
    ControllerBase::init(manager);

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

void MenuControllerExample::_handleInputSerial(input_data_t d) {
    DEBUG_SERIAL_LN("Serial input received: " + String(d));
    UIElement* cur;

    switch (d) {
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
