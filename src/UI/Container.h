#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include "Adafruit_ILI9341.h"

#include "VisualElement.h"

/**
 * @brief Container class provides border and background for set of visual elements
 * 
*/
class Container : public VisualElement {
    public:
        enum Alignment { Left, Center, Right };
        
        /**
         * @brief initialize container class with background colour
        */
        Container(Adafruit_ILI9341& display);

        ~Container();

        /**
         * @brief sets padding for this container
        */
        void setPadding(int16_t padding);

        /**
         * @brief add set of visual elements contained within window display
        */
        void addVisualElements(std::vector<VisualElement*>& elements);

        /**
         * @brief draws header, optional border and all visual elements in window
        */
        void draw() override;

        /**
         * @brief clears header, optional border and all visual elements in window
        */
        void clear() override;

        /**
         * @brief aligns elements (best effort) -- Center by default
        */
       void alignElements(Alignment alignment = Center);

    private:
        const Adafruit_ILI9341& _display;
        std::vector<VisualElement*> _elements;
        int16_t _padding = 0;

};

#endif