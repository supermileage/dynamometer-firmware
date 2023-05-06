#include "UIButton.h"

UIButton::UIButton(Adafruit_ILI9341& display) : _display(display) {
    _textComponent.setOwner(this);
}

UIButton::~UIButton() { }

void UIButton::draw() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // TODO: draw background
    }

    if (_hasBorder) {
        // TODO: draw border
    }

    _textComponent.draw(_display);
}

void UIButton::clear() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // TODO: draw background
    }

    if (_hasBorder) {
        // TODO: draw border
    }

    _textComponent.draw(_display);
}

TextComponent& UIButton::getTextComponent() {
    return _textComponent;
}

void UIButton::focus() {
    // TODO: focus effect
}

void UIButton::unfocus() {
    // TODO: unfocus effect
}

void UIButton::select() {
    // TODO: select effect
}


void UIButton::_onResize() {
    // TODO: resize text element
}