#ifndef _APP_UTIL_H_
#define _APP_UTIL_H_

#include <memory>

#include "Arduino.h"
#include "ui/UIButton.h"
#include "ui/Container.h"
#include "ui/TextElement.h"
#include "System/ErrorHandler.h"
#include "application.h"

using namespace application;

#if DYNO_ASSERT_EN
#define dyno_assert(__expr) ((__expr) ? (void)0 : ErrorUtil.errorAssert(__FILE__, __LINE__, \
                                __PRETTY_FUNCTION__, #__expr))
#else
#define dyno_assert(__expr) { }
#endif

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