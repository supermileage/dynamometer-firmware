#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include <utility>
#include <memory>

#include "Adafruit_GFX.h"
#include "RectangularElement.h"

using namespace std;

/**
 * @brief Container class provides border and background for set of visual elements
 * 
 * @note note that default orientation is column
*/
class Container : public RectangularElement {
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
         * @brief add visual element child to container
        */
        Container& addVisualElement(std::shared_ptr<VisualElement> element, Alignment align = Center);

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
        */
       void alignElements();

    private:
        vector<pair<shared_ptr<VisualElement>, Alignment>> _elements;
        int16_t _padding = 0;
        Orientation _orientation = Column;
        
        /**
         * @brief aligns elements oriented in row
         * 
         * @note only Top, Center, Bottom are valid
        */
        void _alignElementsHorizontal(Alignment horizontal);
        
        /**
         * @brief aligns elements oriented in column
         * 
         * @note only Left, Center and Right are valid
        */
        void _alignElementsVertical(Alignment vertical);
        
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