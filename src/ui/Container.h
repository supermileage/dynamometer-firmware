#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include <utility>
#include <memory>

#include "TFT_eSPI.h"
#include "RectangularElement.h"

#define CONTAINER_ALIGNMENT_RIGHT   0x1
#define CONTAINER_ALIGNMENT_MIDDLE  0x2
#define CONTAINER_ALIGNMENT_LEFT    0x4
#define CONTAINER_ALIGNMENT_TOP     0x10
#define CONTAINER_ALIGNMENT_CENTRE  0x20
#define CONTAINER_ALIGNMENT_BOTTOM  0x40

using namespace std;

/**
 * @brief Container class provides border and background for set of visual elements
 * 
 * @note note that default orientation is column
*/
class Container : public RectangularElement {
    public:
        enum Alignment {
            TopRight = (CONTAINER_ALIGNMENT_TOP | CONTAINER_ALIGNMENT_RIGHT),
            TopMiddle = (CONTAINER_ALIGNMENT_TOP | CONTAINER_ALIGNMENT_MIDDLE),
            TopLeft = (CONTAINER_ALIGNMENT_TOP | CONTAINER_ALIGNMENT_LEFT),
            CentreRight = (CONTAINER_ALIGNMENT_CENTRE | CONTAINER_ALIGNMENT_RIGHT),
            CentreMiddle = (CONTAINER_ALIGNMENT_CENTRE | CONTAINER_ALIGNMENT_MIDDLE),
            CentreLeft = (CONTAINER_ALIGNMENT_CENTRE | CONTAINER_ALIGNMENT_LEFT),
            BottomRight = (CONTAINER_ALIGNMENT_BOTTOM | CONTAINER_ALIGNMENT_RIGHT),
            BottomMiddle = (CONTAINER_ALIGNMENT_BOTTOM | CONTAINER_ALIGNMENT_MIDDLE),
            BottomLeft = (CONTAINER_ALIGNMENT_BOTTOM | CONTAINER_ALIGNMENT_LEFT)
        };
        enum Orientation { Column, Row };
        
        /**
         * @brief initialize container class with background colour
        */
        Container(TFT_eSPI& display);

        ~Container();

        /**
         * @brief sets padding for this container
        */
        Container& setPadding(int16_t padding);

        /**
         * @brief returns this container's padding property
        */
        int16_t getPadding();

        /**
         * @brief add visual element child to container
         * @param element element to be added
         * @param alignment alignment value for element
        */
        Container& addVisualElement(std::shared_ptr<VisualElement> element, Alignment alignment = CentreMiddle);

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
         * @brief align elements in this container according to their associated Alignment value
        */
       virtual void align();

    protected:
        int16_t _padding = 0;
        Orientation _orientation = Column;

    private:
        vector<std::pair<std::shared_ptr<VisualElement>, Alignment>> _children;
        
        /**
         * @brief aligns elements oriented in row
         * 
         * @note only Top, Center, Bottom are valid
        */
        void _alignElementsHorizontal();
        
        /**
         * @brief aligns elements oriented in column
         * 
         * @note only Left, Center and Right are valid
        */
        void _alignElementsVertical();
        
        /**
         * @brief applies equal vertical space between all elements oriented in column
        */
        void _applyVerticalSpacing();

        /**
         * @brief applies equal horizontal space between all elements oriented in row
        */
        void _applyHorizontalSpacing();

        /**
         * @brief computes and returns horizontal offset for VisualElement in pair
        */
        int16_t _getHorizontalOffset(pair<shared_ptr<VisualElement>, Alignment> pair, int16_t width);

        /**
         * @brief computes and returns vertical offset for VisualElement in pair
        */
        int16_t _getVerticalOffset(pair<shared_ptr<VisualElement>, Alignment> pair, int16_t height);
};

#endif