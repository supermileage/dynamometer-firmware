#ifndef _APP_UTIL_H_
#define _APP_UTIL_H_

#include "Arduino.h"
#include "ui/UIButton.h"
#include "ui/Container.h"
#include "ui/TextElement.h"

namespace app_util {
    void configureMainWindow(Container* window);
    void configureHeader(TextElement* header, const String& displayString);
    void configureMenuContainer(Container* container);
    void configureMenuButton(UIButton* button, const String& displayString);
    void configureNavButtonContainer(Container* container);
    void configureNavButton(UIButton* button, const String& displayString);
    void configureBackButton(UIButton* button);
    void configureSelectButton(UIButton* button);
}

#endif