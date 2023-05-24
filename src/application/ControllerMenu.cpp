#include "ControllerMenu.h"

using namespace application;

ControllerMenu::ControllerMenu(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
    ControllerBase(context, display, inFocus) {
        _menu = new MenuView(display);
}

ControllerMenu::~ControllerMenu() {
    delete _menu;

    // delete all UIButtons generated from call to init
    for (const auto& pair : _buttonCallbackMap) {
        delete pair.second.first;
    }
}

void ControllerMenu::init(InputManager& manager, const std::vector<MenuButtonData>& buttonConfigs) {
    // register all input callbacks with input manager
    ControllerBase::init(manager);

    for (uint8_t i = 0; i < buttonConfigs.size(); i++) {
        const MenuButtonData& data = buttonConfigs[i];
        UIButton* cur = new UIButton(_display);
        _menu->addMenuButton(cur, data.text);
        _buttonCallbackMap[i] = std::make_pair(cur, [this, data]() { _context.changeState(data.state); });
    }

    UIEventHandler::instance().addEvent( [this]() { _menu->init(); } );
    UIEventHandler::instance().addEvent( [this]() { _buttonCallbackMap[_inFocus].first->focus(); } );
}

void ControllerMenu::_handleInputSerial(input_data_t d) {
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
