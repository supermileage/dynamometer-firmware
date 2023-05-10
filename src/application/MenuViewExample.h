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
        void setHeader(const String& str)
        void addMenuButton(UIElement* btn);
        void addSelectButton(UIElement* btn);
        void addBackButton(UIElement* btn);

    private:
        Adafruit_GFX& _display;
        Container* _window;
        TextElement* _header;
        Container* _menuContainer;
        Container* _navButtonContainer;
        
        // for demo purposes
        std::vector<UIElement*> _interactives;
        unsigned int _cur = 0;
        unsigned int _lastTime = 0;

};

#endif