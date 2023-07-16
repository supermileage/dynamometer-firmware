#include "UIButton.h"

UIButton::UIButton(TFT_eSPI& display) : UIElement(display) {
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
    _recolourText(_fontFocusColour);
}

void UIButton::revert() {
    draw();
}

void UIButton::select() {
    UIElement::focus();
    _recolourText(_fontSelectColour);
}

UIButton& UIButton::setFontFocusColour(uint16_t colour) {
    _fontFocusColour = colour;
    return *this;
}

UIButton& UIButton::setFontSelectColour(uint16_t colour) {
    _fontSelectColour = colour;
    return *this;
}

void UIButton::_recolourText(uint16_t colour) {
    uint16_t temp = _textComponent.getFontColour();
    _textComponent.setFontColour(_fontFocusColour);
    _textComponent.draw(_display);
    _textComponent.setFontColour(temp);
}