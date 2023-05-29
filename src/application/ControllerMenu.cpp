#include "ControllerMenu.h"

using namespace application;

ControllerMenu::ControllerMenu(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
    ControllerBase(context, display, inFocus) {
        _menu = std::make_shared<MenuView>(display);
}

ControllerMenu::~ControllerMenu() {
    DEBUG_STATE_TRANSITION_LN("~ControllerMenu");
}

void ControllerMenu::init(InputManager& manager, const std::vector<MenuButtonData>& buttonConfigs) {
    // register all input callbacks with input manager
    ControllerBase::init(manager);

    DEBUG_STATE_TRANSITION_LN("Initializing new ControllerMenu");
    DEBUG_STATE_TRANSITION_LN("buttonConfigs.size() = " + String(buttonConfigs.size()));
    for (uint8_t i = 0; i < buttonConfigs.size(); i++) {
        const MenuButtonData& data = buttonConfigs[i];

        DEBUG_STATE_TRANSITION_LN("ButtonData:");
        DEBUG_STATE_TRANSITION_LN("state: " + app_util::stateToString(data.state) + " -- text: " + data.text);
        std::shared_ptr<UIButton> cur = std::make_shared<UIButton>(_display);
        _menu->addMenuButton(cur, data.text);
        _buttonCallbackMap[i] = std::make_pair(cur, [this, data]() { _context.setNextState(data.state); });
    }

    auto self = shared_from_this();
    auto cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent( [this, self]() { _menu->init(); } );
    UIEventHandler::instance().addEvent( [cur]() { cur->focus(); } );
}

MenuView& ControllerMenu::getView() {
    return *_menu;
}

void ControllerMenu::_handleInputSerial(input_data_t d) {
    DEBUG_STATE_TRANSITION_LN("Serial input received: " + String(d));
    switch (d) {
        case 65:    // up
            _shiftFocus(-1);
            break;
        case 66:    // down 
            _shiftFocus(1);
            break;
        case 8:     // backspace
            _navigateBack();
            break;
        case 10:    // enter '\n'
            _triggerStateChange();
            break;
        case 13:    // enter '\r'
            _selectCurrent();
            break;
        default:    // do nothing
            break;
    }
}

void ControllerMenu::_handleInputEncoder(input_data_t d) {
    _shiftFocus(d);
}

void ControllerMenu::_handleInputEncoderSelect(input_data_t d) {
    if (d && !_buttonHeld) {
        DEBUG_STATE_TRANSITION_LN("Encoder Select High");
        _buttonHeld = true;
        _selectCurrent();
    } else {
        DEBUG_STATE_TRANSITION_LN("Encoder Select Low");
        if (_buttonHeld) {
            _buttonHeld = false;
            _triggerStateChange();
        }
    }
}

void ControllerMenu::_handleInputBack(input_data_t d) {
    // if (d) {
    //     UIElement* cur = _buttonCallbackMap[_inFocus].first;
    //     UIEventHandler::instance().addEvent([this,cur]() { cur->focus(); _menu->back(); });
    // } else {
    //     _navigateBack();
    // }
}

void ControllerMenu::_handleInputSelect(input_data_t d) {
    // if (d) {
    //     _selectCurrent();
    // } else {
    //     _triggerStateChange();
    // }
}

void ControllerMenu::_navigateBack() {
    if (!_context.tryRevertState()) {
        return;
    }

    DEBUG_STATE_TRANSITION_LN("Navigate Back");
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, self]() {
        _menu->back();
        _context.setStateTransitionFlag();
    });
}

void ControllerMenu::_shiftFocus(int32_t offset) {
    DEBUG_SERIAL_LN("Shift Focus");
    auto cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent( [cur]() { cur->revert(); } );

    // compute index of new focussed element
    int32_t modVal = _buttonCallbackMap.size();
    input_data_t val = ((_inFocus + offset) % modVal + modVal) % modVal;
    _inFocus = static_cast<uint8_t>(val);

    // focus new element
    cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent([cur]() { cur->focus(); });
}

void ControllerMenu::_selectCurrent() {
    DEBUG_STATE_TRANSITION_LN("Select Current");
    auto cur = _buttonCallbackMap[_inFocus].first;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, cur, self]() {
            cur->select();
            _menu->select();
        });
}

void ControllerMenu::_triggerStateChange() {
    DEBUG_STATE_TRANSITION_LN("Trigger State Changed");
    auto cur = _buttonCallbackMap[_inFocus].first;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent(
        [this, cur, self]() {
            cur->revert();
            _menu->revert();
            _context.setStateTransitionFlag(); // set flag after render actions are complete
        });
    (_buttonCallbackMap[_inFocus].second)();
}


