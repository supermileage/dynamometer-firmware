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

    void configureMainWindow(std::shared_ptr<Container> window);
    void configureHeader(std::shared_ptr<TextElement> header, const String& displayString);
    void configureMenuContainer(std::shared_ptr<Container> container);
    void configureMenuButton(std::shared_ptr<UIButton> button, const String& displayString);
    void configureNavButtonContainer(std::shared_ptr<Container> container);
    void configureNavButton(std::shared_ptr<UIButton> button);
    void configureBackButton(std::shared_ptr<UIButton> button);
    void configureSelectButton(std::shared_ptr<UIButton> button);

    /**
     * @brief get string name for state
    */
    const String stateToString(ApplicationState state);
}

#endif