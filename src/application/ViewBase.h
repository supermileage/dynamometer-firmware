#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

#include "ui/Container.h"
#include "ui/TextElement.h"
#include "ui/UIButton.h"

class ViewBase {
    public:
        ViewBase(Adafruit_GFX& display);
        virtual ~ViewBase();

        /**
         * @brief sets string header for this view
        */
        void setHeader(const String& str);

        /**
         * @brief triggers select on select nav button
        */
        virtual void select();

        /**
         * @brief triggers select on back nav button
        */
        virtual void back();

        /**
         * @brief reverts back/select buttons to default state
        */
        virtual void revert();
    
    protected:
        Adafruit_GFX& _display;
        Container* _window;
        TextElement* _header;
        Container* _navButtonContainer;
        UIButton* _navButtonSelect;
        UIButton* _navButtonBack;
};

#endif