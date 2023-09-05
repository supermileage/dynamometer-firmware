#include "RectangularElement.h"

RectangularElement::RectangularElement(TFT_eSPI& display) :
    VisualElement(display) {
        _typeId |= TYPE_ID_RECTANGULAR_ELEMENT;
}

RectangularElement::~RectangularElement() { }

int16_t RectangularElement::getWidth() {
    return _width;
}

int16_t RectangularElement::getHeight() {
    return _height;
}

RectangularElement& RectangularElement::setWidth(int16_t width) {
    _width = width;
    return *this;
}

RectangularElement& RectangularElement::setHeight(int16_t height) {
    _height = height;
    return *this;
}

void RectangularElement::_drawInternal(uint16_t colour) {
    if (!_parent || (_parent && _parent->getBackgroundColour() != colour)) {
        _display.fillRect(_position.x, _position.y, _width, _height, colour);
    }

    if (_hasBorder) {
        _display.drawRect(_position.x, _position.y, _width, _height, _borderColour);
    }
}

void RectangularElement::clear() {
    uint16_t colour;
    if (_parent) {
        colour = _parent->getBackgroundColour();
    } else {
        colour = _backgroundColour;
    }
    _display.fillRect(_position.x, _position.y, _width, _height, colour);
}