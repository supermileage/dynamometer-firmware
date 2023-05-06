#include "Container.h"

Container::Container(Adafruit_ILI9341& display) : _display(display) { }

Container::~Container() { }

void Container::setPadding(int16_t padding) {
    _padding = padding;
}

void Container::addVisualElements(std::vector<VisualElement*>& elements) {
    _elements = elements;
}

void Container::draw() {
    if (_hasBorder) {
        // TODO: draw border
    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void Container::clear() {
    if (_hasBorder) {
        // TODO: erase border
    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void Container::alignElements(Alignment alignment) {
    // TODO: align elements left, right or center
}
