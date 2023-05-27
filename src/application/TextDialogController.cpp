#include "TextDialogController.h"
#include "ui/UIEventHandler.h"

TextDialogController::TextDialogController(ApplicationContext context, Adafruit_GFX& display, uint8_t inFocus)
    : ControllerBase(context, display, inFocus) {
    _view = new TextDialogView(display);
}

TextDialogController::~TextDialogController() {
    UIEventHandler::instance().clearAnimations();
    UIEventHandler::instance().clearEventQueue();

    delete _view;
    for (UIButton* element : _characterElements) {
        delete element;
    }
}


void TextDialogController::init(InputManager& manager, const String& start) {
    ControllerBase::init(manager);

    int i = 0;
    for (; i < start.length(); i++) {
        char cur = start[i];
        UIButton* button = new UIButton(_display);
        button->getTextComponent().setDisplayString(String(cur));
        _view->addCharacterElement(button);
        _characterElements.push_back(button);
    }
    for (; i < _maxTextLength; i++) {
        UIButton* button = new UIButton(_display);
        button->getTextComponent().setDisplayString(" ");
        _view->addCharacterElement(button);
        _characterElements.push_back(button);
    }

    DEBUG_STATE_TRANSITION_LN("Initializing view");
    UIButton* cur = _characterElements[_inFocus];
    UIEventHandler::instance().addEvent( [this]() { _view->init(); } );
    UIEventHandler::instance().addAnimation(new TextFocusAnimation(cur));
}

TextDialogView& TextDialogController::getView() {
    return *_view;
}

void TextDialogController::_handleInputSerial(input_data_t d) {

}

void TextDialogController::_handleInputEncoder(input_data_t d) {
    if (_selectHeld) {

    } else {
        uint8_t next = static_cast<uint8_t>(_computeIndexOffset(_inFocus, d, _characterElements.size()));

        if (next != _inFocus) {
            UIElement* cur = _characterElements[_inFocus];
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
    if (d) {
        _selectHeld = true;
        UIEventHandler::instance().removeAnimation(_currentAnimation);
        _currentAnimation = nullptr;
        UIButton* cur = _characterElements[_inFocus];
        UIEventHandler::instance().addEvent([cur]() { cur->select(); });
    } else {
        _selectHeld = false;
        UIButton* cur = _characterElements[_inFocus];
        UIEventHandler::instance().removeAnimation(_currentAnimation);
        _currentAnimation = new TextFocusAnimation(cur);
        UIEventHandler::instance().addAnimation(_currentAnimation);
    }
}

void TextDialogController::_handleInputBack(input_data_t d) {

}

void TextDialogController::_handleInputSelect(input_data_t d) {
    // pop-up confirmation dialog
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
