#ifndef _MENU_EXAMPLE_H_
#define _MENU_EXAMPLE_H_

#include <vector>
#include "System/Handleable.h"
#include "ui/Container.h"
#include "ui/UIButton.h"
#include "ui/TextElement.h"

#include "settings.h"

/**
 * Example menu with button focus animation
*/
class MenuView {
    public:
        MenuView(Adafruit_GFX& display);
        ~MenuView();
        void init();

        /**
         * @brief sets string header for this view
        */
        void setHeader(const String& str);

        /**
         * @brief adds menu button and styles it with app_util::configureMenuButton
        */
        void addMenuButton(UIButton* button, const String& str);

        /**
         * @brief triggers select nav button
        */
        void select();

        /**
         * @brief triggers back nav button
        */
        void back();

    private:
        Adafruit_GFX& _display;
        Container* _window;
        TextElement* _header;
        Container* _menuContainer;
        Container* _navButtonContainer;
        UIButton* _navButtonSelect;
        UIButton* _navButtonBack;

};

#endif