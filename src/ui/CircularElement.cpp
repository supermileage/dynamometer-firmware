#include "CircularElement.h"

CircularElement::CircularElement(TFT_eSPI& display) :
    VisualElement(display) {
        _typeId |= TYPE_ID_CIRCULAR_ELEMENT;
}

CircularElement::~CircularElement() { }

int16_t CircularElement::getWidth() {
    return _radius * 2;
}

int16_t CircularElement::getHeight() {
    return _radius * 2;
}


int16_t CircularElement::getRadius() {
    return _radius;
}

CircularElement& CircularElement::setRadius(int16_t radius) {
    _radius = radius;
    return *this;
}

void CircularElement::_drawInternal(uint16_t colour) {
    if (!_parent || (_parent && _parent->getBackgroundColour() != colour)) {
        _display.fillCircle(_position.x + _radius, _position.y  + _radius,
            _radius, colour);
    }

    if (_hasBorder) {
        _display.drawCircle(_position.x + _radius, _position.y + _radius,
            _radius, _borderColour);
    }
}

void CircularElement::clear() {
    uint16_t colour;
    if (_parent) {
        colour = _parent->getBackgroundColour();
    } else {
        colour = _backgroundColour;
    }
    _display.fillCircle(_position.x + _radius, _position.y + _radius, _radius, colour);
}