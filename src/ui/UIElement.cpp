#include "UIElement.h"

UIElement::UIElement(Adafruit_GFX& display) : VisualElement(display) { }

void UIElement::focus() {
    _drawInternal(_focusColour);
}

void UIElement::revert() {
    draw();
}

void UIElement::select() {
    _drawInternal(_selectColour);
}

UIElement& UIElement::setFocusColour(uint16_t colour) {
    _focusColour = colour;
    return *this;
}

UIElement& UIElement::setSelectColour(uint16_t colour) {
    _selectColour = colour;
    return *this;
}