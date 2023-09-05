#include "UIElement.h"

UIElement::UIElement(TFT_eSPI& display) : RectangularElement(display) {
    _typeId |= TYPE_ID_UI_ELEMENT;
}

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