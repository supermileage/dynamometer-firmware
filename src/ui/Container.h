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
        enum Alignment { Left, Center, Right, Top, Bottom };
        
        /**
         * @brief initialize container class with background colour
        */
        Container(Adafruit_ILI9341& display);

        ~Container();

        /**
         * @brief sets padding for this container
        */
        Container& setPadding(int16_t padding);

        /**
         * @brief add set of visual elements contained within window display
        */
        Container& addVisualElements(std::vector<VisualElement*>& elements);

        /**
         * @brief add set of visual elements contained within window display
        */
        Container& addVisualElement(VisualElement* element);

        /**
         * @brief draws header, optional border and all visual elements in window
        */
        void draw() override;

        /**
         * @brief aligns elements (best effort)
        */
       void alignElements(Alignment horizontal = Center, Alignment vertical = Center);

    private:
        std::vector<VisualElement*> _elements;
        int16_t _padding = 0;

        void _onResize() override;
        void _alignHorizontal(Alignment horizontal);
        void _alignVertical(Alignment vertical);

};

#endif