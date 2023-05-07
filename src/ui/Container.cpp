#include "Container.h"

Container::Container(Adafruit_GFX& display) : VisualElement(display) { }

Container::~Container() { }

Container& Container::setPadding(int16_t padding) {
    _padding = padding;
    return *this;
}

Container& Container::addVisualElements(std::vector<VisualElement*>& elements) {
    for (VisualElement* element : elements) {
        element->setParent(this);
        _elements.push_back(element);
    }
    return *this;
}

Container& Container::addVisualElement(VisualElement* element) {
    element->setParent(this);
    _elements.push_back(element);
    return *this;
}

void Container::draw() {
    // draw background and border
    VisualElement::draw();
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void Container::alignElements(Alignment horizontal, Alignment vertical) {
    _alignHorizontal(horizontal);
    _alignVertical(vertical);
}

void Container::_onResize() {
    // resize event
}

void Container::_alignHorizontal(Alignment horizontal) {
    // ignore alignment and only do center
    // TODO: implement alignment for other configurations
    for (VisualElement* element : _elements) {
        int16_t elementX = _position.x + (_width - element->getWidth()) / 2;
        element->setPosition(Point { elementX, element->getPosition().y });
    }
}

void Container::_alignVertical(Alignment vertical) {
    int16_t totalHeight = 0;
    for (VisualElement* element : _elements) {
        totalHeight += element->getHeight();
    }

    // equal vertical space between all elements
    int16_t padding = (_height - totalHeight) / (_elements.size() + 1);
    int16_t cur = padding + _position.y;
    for (VisualElement* element : _elements) {
        element->setPosition(Point { element->getPosition().x, cur });
        cur += (padding + element->getHeight());
    }
}


