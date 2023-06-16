#include "CircularGauge.h"
#include "settings.h"

CircularGauge::CircularGauge(Adafruit_GFX& display, int32_t min, int32_t max) :
    CircularElement(display), _min(min), _max(max) { }

CircularGauge::~CircularGauge() { }

void CircularGauge::setDisplayValue(int32_t val) {
    _displayValue = val;
}

int32_t CircularGauge::getDisplayValue() {
    return _displayValue;
}

void CircularGauge::draw() {
    // draw circle background
    CircularElement::_drawInternal(_backgroundColour);
    
    // TODO: draw gauge
}