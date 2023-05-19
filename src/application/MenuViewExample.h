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
class MenuViewExample {
    public:
        MenuViewExample(Adafruit_GFX& display);
        ~MenuViewExample();
        void init();
        void setHeader(const String& str);
        void addMenuButton(UIButton* button, const String& str);
        void select();
        void back();
        void revert();

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