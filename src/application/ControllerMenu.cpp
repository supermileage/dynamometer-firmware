#include "ControllerMenu.h"

using namespace application;

ControllerMenu::ControllerMenu(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
    ControllerBase(context, display, inFocus) {
        _menu = new MenuView(display);
}

ControllerMenu::~ControllerMenu() {
    DEBUG_STATE_TRANSITION_LN("Clearing event queue");
    DEBUG_STATE_TRANSITION_LN("~ControllerMenu");
    delete _menu;

    // delete all UIButtons generated from call to init
    for (const auto& pair : _buttonCallbackMap) {
        delete pair.second.first;
    }
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
        UIButton* cur = new UIButton(_display);
        _menu->addMenuButton(cur, data.text);
        _buttonCallbackMap[i] = std::make_pair(cur, [this, data]() { _context.setNextState(data.state); });
    }

    DEBUG_STATE_TRANSITION_LN("Initializing view");
    UIEventHandler::instance().addEvent( [this]() { _menu->init(); } );
    UIEventHandler::instance().addEvent( [this]() { _buttonCallbackMap[_inFocus].first->focus(); } );
}

MenuView& ControllerMenu::getView() {
    return *_menu;
}

void ControllerMenu::_handleInputSerial(input_data_t d) {
    DEBUG_STATE_TRANSITION_LN("Serial input received: " + String(d));
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
            UIEventHandler::instance().addEvent(
                [this, cur]() {
                    DEBUG_STATE_TRANSITION_LN("Final state change render event invoked");
                    cur->revert();
                    _menu->revert();
                    _context.setStateTransitionFlag();
                    DEBUG_STATE_TRANSITION_LN("Final state change render event complete");
                });
            (_buttonCallbackMap[_inFocus].second)();
            break;
        case 13:
            cur = _buttonCallbackMap[_inFocus].first;
            UIEventHandler::instance().addEvent([this, cur]() {
                DEBUG_STATE_TRANSITION_LN("Prelim state change render event invoked");
                cur->select();
                _menu->select();
                DEBUG_STATE_TRANSITION_LN("Prelim state change render event complete");
            });
            break;
        case 8:
            _context.revertState();
            UIEventHandler::instance().addEvent([this, cur]() {
                _menu->back();
                _context.setStateTransitionFlag();
            });
            break;
        default:
            // do nothing
            break;
    }
}
