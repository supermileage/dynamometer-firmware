#include "UIButton.h"

UIButton::UIButton(Adafruit_GFX& display) : UIElement(display) {
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
    UIElement::focus();
    uint16_t temp = _textComponent.getFontColour();
    _textComponent.setFontColour(_fontFocusColour);
    _textComponent.draw(_display);
    _textComponent.setFontColour(temp);
}

void UIButton::unfocus() {
    draw();
}

void UIButton::select() {
    // TODO: select effect
}

UIButton& UIButton::setFontFocusColour(uint16_t colour) {
    _fontFocusColour = colour;
    return *this;
}


void UIButton::_onResize() {
    // TODO: resize text element
}