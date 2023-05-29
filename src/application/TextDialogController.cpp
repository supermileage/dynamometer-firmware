#include "TextDialogController.h"
#include "ui/UIEventHandler.h"

#define FIRST_CHAR  '0' // 48
#define LAST_CHAR   'z' // 122
#define CHAR_RANGE  (LAST_CHAR - FIRST_CHAR)

TextDialogController::TextDialogController(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus)
    : ControllerBase(context, display, inFocus) {
    _view = std::make_shared<TextDialogView>(_display);
}

TextDialogController::~TextDialogController() {
    DEBUG_SERIAL_LN("~TextDialogController");
}

void TextDialogController::init(InputManager& manager, const String& start) {
    ControllerBase::init(manager);

    _text = start;
    int i = _text.lastIndexOf('.');
    if (i != -1) {
        _extension = _text.substring(i);
        for (; i < _text.length(); i++) {
            _text[i] = ' ';
        }
        for (; i < MAX_TEXT_LENGTH; i++) {
            _text += ' ';
        }
    }

    for (i = 0; i < MAX_TEXT_LENGTH; i++) {
        char cur = _text[i];
        std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
        button->getTextComponent().setDisplayString(String(cur));
        _view->addCharacterElement(button);
        _characterElements.push_back(button);
    }

    // initialize view and animation
    String displayText = _removeWhitespace(_text) + _extension;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent( [this, displayText]() { _view->setTextDisplay(displayText); _view->init(); } );

    _currentAnimation = new TextFocusAnimation(_characterElements[_inFocus]);
    UIEventHandler::instance().addAnimation(_currentAnimation);
}

TextDialogView& TextDialogController::getView() {
    return *_view;
}

void TextDialogController::_handleInputSerial(input_data_t d) {
    DEBUG_STATE_TRANSITION_LN("Serial input received: " + String(d));
    switch (d) {
        case 65:    // up
            // _shiftFocus(-1);
            break;
        case 66:    // down 
            // _shiftFocus(1);
            break;
        case 8:     // backspace
            _navigateBack();
            break;
        case 10:    // enter '\n'
            // _triggerStateChange();
            break;
        case 13:    // enter '\r'
            // _selectCurrent();
            break;
        default:    // do nothing
            break;
    }
}

void TextDialogController::_navigateBack() {
    if (!_context.tryRevertState()) {
        return;
    }

    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, self]() {
        _view->back();
        _context.setStateTransitionFlag();
    });
    UIEventHandler::instance().removeAnimation(_currentAnimation);
}

void TextDialogController::_handleInputEncoder(input_data_t d) {
    if (_buttonHeld) {
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        char c = _text[_inFocus];
        if (c == ' ') {
            c = FIRST_CHAR;
        }
        c = static_cast<char>(_computeIndexOffset(c - FIRST_CHAR, d, CHAR_RANGE) + FIRST_CHAR);
        TextComponent& text = cur->getTextComponent().setDisplayString(String(c));
        text.setDisplayString(String(c));
        _text[_inFocus] = c;

        String displayText = _removeWhitespace(_text) + _extension;
        _view->setTextDisplay(displayText);
        auto self = shared_from_this();
        UIEventHandler::instance().addEvent([cur, this]() { cur->draw(); _view->redrawTextDisplay(); });
    } else {
        uint8_t next = static_cast<uint8_t>(_computeIndexOffset(_inFocus, d, _characterElements.size()));

        if (next != _inFocus) {
            std::shared_ptr<UIElement> cur = _characterElements[_inFocus];
            auto self = shared_from_this();
            UIEventHandler::instance().addEvent([cur]() { cur->revert(); });
            UIEventHandler::instance().removeAnimation(_currentAnimation);

            _inFocus = next;
            cur = _characterElements[_inFocus];
            _currentAnimation = new TextFocusAnimation(cur);
            UIEventHandler::instance().addAnimation(_currentAnimation);
        }
    }
}

void TextDialogController::_handleInputEncoderSelect(input_data_t d) {

}

void TextDialogController::_handleInputBack(input_data_t d) {

}

void TextDialogController::_handleInputSelect(input_data_t d) {
    // pop-up confirmation dialog
}

void TextDialogController::_handleInputBrakeButton(input_data_t d) {
    if (d) {
        _buttonHeld = true;
        UIEventHandler::instance().removeAnimation(_currentAnimation);
        _currentAnimation = nullptr;
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        // auto self = shared_from_this();
        UIEventHandler::instance().addEvent([cur]() { cur->select(); });
    } else {
        _buttonHeld = false;
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        _currentAnimation = new TextFocusAnimation(cur);
        UIEventHandler::instance().addAnimation(_currentAnimation);
    }
}

void TextDialogController::TextFocusAnimation::run(uint32_t time) {
    if (time >= _interval + _lastTime) {
        if (_focussed) {
            _element->revert();
        } else {
            _element->focus();
        }
        _focussed = !_focussed;
        _lastTime = time;
    }
}

String TextDialogController::_removeWhitespace(const String& str) {
    String ret = "";
    for (char c : str) {
        if (c != ' ') {
            ret += c;
        }
    }
    return ret;
}
