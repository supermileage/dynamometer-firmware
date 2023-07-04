#ifndef _APP_UTIL_H_
#define _APP_UTIL_H_

#include <memory>

#include "Arduino.h"
#include "ui/UIButton.h"
#include "ui/Container.h"
#include "ui/TextElement.h"
#include "application.h"

using namespace application;

namespace app_util {
    /* configure different visual elements as defined by macros in style.h */

    void configureMainWindow(Container* window);
    void configureHeader(TextElement* header, const String& displayString);
    void configureMenuContainer(Container* container);
    void configureMenuButton(UIButton* button, const String& displayString);
    void configureNavButtonContainer(Container* container);
    void configureNavButton(UIButton* button);
    void configureBackButton(UIButton* button);
    void configureSelectButton(UIButton* button);

    /**
     * @brief get string name for state
    */
    const String stateToString(ApplicationState state);
}

#endif