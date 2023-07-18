#ifndef _MENU_VIEW_H_
#define _MENU_VIEW_H_

#include "ViewBase.h"
#include "ui/Container.h"
#include "ui/UIButton.h"
#include "ui/TextElement.h"

/**
 * Example menu with button focus animation
*/
class MenuView : public ViewBase {
    public:
        MenuView(TFT_eSPI& display);
        ~MenuView();

        /**
         * @brief initializes and renders all visual elements
        */
        void init();

        /**
         * @brief adds menu button and styles it with app_util::configureMenuButton
        */
        void addMenuButton(std::shared_ptr<UIButton> button, const String& str);

    private:
        std::shared_ptr<Container> _menuContainer;

};

#endif