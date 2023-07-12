#ifndef _VALUE_ELEMENT_H_
#define _VALUE_ELEMENT_H_

#include "Container.h"
#include "TextElement.h"

class ValueElement : public Container {
    public:
        ValueElement(Adafruit_GFX& display) : Container(display) {

        }

        ValueElement& setLabel(String& label, Alignment alignment = Container::) {
            
            return *this;
        }
    private:
        TextElement _valueText;
        String (*_valueHandler())
};

#endif