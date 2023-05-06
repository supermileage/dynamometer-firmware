#include "UIButton.h"

UIButton::UIButton(Adafruit_ILI9341& display) : _display(display) {
    _textComponent.setOwner(this);
}

UIButton::~UIButton() { }

void UIButton::draw() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // draw background
    }

    if (_hasBorder) {
        // draw border
    }

    _textComponent.draw(_display);
}

void UIButton::clear() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // draw background
    }

    if (_hasBorder) {
        // draw border
    }

    _textComponent.draw(_display);
}

TextComponent& UIButton::getTextComponent() {
    return _textComponent;
}

void UIButton::focus() {
    // focus effect
}

void UIButton::unfocus() {
    // unfocus effect
}

void UIButton::select() {
    // select effect
}


void UIButton::_onResize() {
    // resize text element
}