#include "UIElement.h"

UIElement::UIElement(Adafruit_GFX& display) : VisualElement(display) { }

void UIElement::focus() {
    _drawInternal(_focusColour);
}

void UIElement::unfocus() {
    draw();
}

UIElement& UIElement::setFocusColour(uint16_t colour) {
    _focusColour = colour;
    return *this;
}