#include "UIButton.h"

UIButton::UIButton(Adafruit_ILI9341& display) : UIElement(display) {
    _textComponent.setOwner(this);
}

UIButton::~UIButton() { }

void UIButton::draw() {
    // draw background
    VisualElement::draw();
    // draw text
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