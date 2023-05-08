#ifndef _MENU_EXAMPLE_H_
#define _MENU_EXAMPLE_H_

#include <vector>
#include "System/Handleable.h"
#include "ui/Container.h"
#include "ui/UIButton.h"
#include "ui/TextElement.h"

/**
 * Example menu with button focus animation
*/
class MenuViewExample {
    public:
        MenuViewExample(Adafruit_GFX& display);
        ~MenuViewExample();
        void init();
        void run();

    private:
        Adafruit_GFX& _display;
        Container* _window;
        TextElement* _header;
        Container* _menuContainer;
        Container* _navButtonContainer;
        UIButton* _menuButton1;
        UIButton* _menuButton2;
        UIButton* _menuButton3;
        UIButton* _navButton1;
        UIButton* _navButton2;

        // for focus/selection animation
        std::vector<UIElement*> _interactives;
        unsigned int _cur = 0;
        unsigned int _lastTime = 0;

};

#endif