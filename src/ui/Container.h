#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include "Adafruit_GFX.h"
#include "VisualElement.h"

/**
 * @brief Container class provides border and background for set of visual elements
 * 
 * @note note that default orientation is column
*/
class Container : public VisualElement {
    public:
        enum Alignment { Left, Center, Right, Top, Bottom };
        enum Orientation { Column, Row };
        
        /**
         * @brief initialize container class with background colour
        */
        Container(Adafruit_GFX& display);

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
         * @brief sets this container's orientation to one of Column/Row
         * 
         * @param o column means elements will be stacked; row means laid out side to side
        */
        Container& setOrientation(Orientation o);

        /**
         * @brief align elements in this container
         * 
         * @note interpretation of alignment changes depending on orientation
        */
       void align(Alignment a = Center);

    private:
        std::vector<VisualElement*> _elements;
        int16_t _padding = 0;
        Orientation _orientation = Column;
        
        /**
         * @brief aligns elements oriented in row
         * 
         * @note only Top, Center, Bottom are valid
        */
        void _alignHorizontal(Alignment horizontal);
        
        /**
         * @brief aligns elements oriented in column
         * 
         * @note only Left, Center and Right are valid
        */
        void _alignVertical(Alignment vertical);
        
        /**
         * @brief applies equal vertical space between all elements oriented in column
        */
        void _applyVerticalSpacing();

        /**
         * @brief applies equal horizontal space between all elements oriented in row
        */
        void _applyHorizontalSpacing();

};

#endif