#include "Container.h"

Container::Container(Adafruit_GFX& display) : RectangularElement(display) { }

Container::~Container() { }

Container& Container::setPadding(int16_t padding) {
    _padding = padding;
    return *this;
}

Container& Container::addVisualElements(std::vector<std::shared_ptr<VisualElement>>& elements) {
    for (auto element : elements) {
        element->setParent(this);
        _elements.push_back(element);
    }
    return *this;
}

Container& Container::addVisualElement(std::shared_ptr<VisualElement> element) {
    element->setParent(this);
    _elements.push_back(element);
    return *this;
}

void Container::draw() {
    // draw background and border
    VisualElement::draw();
    
    for (auto element : _elements) {
        element->draw();
    }
}

Container& Container::setOrientation(Orientation o) {
    _orientation = o;
    return *this;
}

void Container::align(Alignment a) {
    switch (_orientation) {
        case Column:
            _alignHorizontal(a);
            _applyVerticalSpacing();
            break;
        case Row:
            _alignVertical(a);
            _applyHorizontalSpacing();
            break;
        default:
            break;
    }
}

void Container::_alignHorizontal(Alignment horizontal) {
    // TODO: implement top/bottom alignment
    for (auto element : _elements) {
        int16_t elementX = _position.x + (_width - element->getWidth()) / 2;
        element->setPosition(Point { elementX, element->getPosition().y });
    }
}

void Container::_alignVertical(Alignment vertical) {
    // TODO: implement left/right alignment
    for (auto element : _elements) {
        int16_t elementY = _position.y + (_height - element->getHeight()) / 2;
        element->setPosition(Point { element->getPosition().x, elementY });
    }
}

void Container::_applyVerticalSpacing() {
    int16_t totalHeight = 0;
    for (auto element : _elements) {
        totalHeight += element->getHeight();
    }

    // equal vertical space between all elements
    int16_t padding = (_height - totalHeight) / (_elements.size() + 1);
    int16_t cur = padding + _position.y;
    for (auto element : _elements) {
        element->setPosition(Point { element->getPosition().x, cur });
        cur += (padding + element->getHeight());
    }
}

void Container::_applyHorizontalSpacing() {
    int16_t total = 0;
    for (auto element : _elements) {
        total += element->getWidth();
    }

    int16_t padding = (_width - total) / (_elements.size() + 1);
    int16_t cur = padding + _position.x;
    for (auto element : _elements) {
        element->setPosition(Point { cur, element->getPosition().y });
        cur += (padding + element->getWidth());
    }
}



