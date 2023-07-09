#include "MenuView.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "app_util.h"

MenuView::MenuView(Adafruit_GFX& display) : ViewBase(display) {
    _menuContainer = std::make_unique<Container>(_display);
}

MenuView::~MenuView() {
    DEBUG_SERIAL_LN("~MenuView");
}

void MenuView::init() {
    _window->addVisualElement(_header)
        .addVisualElement(_menuContainer);
    _menuContainer->addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack)
        .addVisualElement(_navButtonSelect);

    app_util::configureSelectButton(_navButtonSelect.get());
    app_util::configureBackButton(_navButtonBack.get());
    
    app_util::configureMainWindow(_window.get());
    app_util::configureMenuContainer(_menuContainer.get());
    app_util::configureNavButtonContainer(_navButtonContainer.get());
    
    // order matters for alignment: align top-level container first, then down
    _window->alignElements();
    _menuContainer->alignElements();
    _navButtonContainer->alignElements();

    // call to principal container draws all elements
    DEBUG_SERIAL_LN("Drawing window");
    _window->draw();
}

void MenuView::addMenuButton(std::shared_ptr<UIButton> button, const String& str) {
    app_util::configureMenuButton(button.get(), str);
    _menuContainer->addVisualElement(button);
}
