#include "SessionView.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "app_util.h"

using namespace application;

SessionView::SessionView(TFT_eSPI& display) : ViewBase(display) {
    _sessionContainer = std::make_unique<Container>(_display);
}

SessionView::~SessionView() {
    DEBUG_SERIAL_LN("~SessionView");
}

// Following MenuView's example
void SessionView::init(){
    _window->addVisualElement(_header)
        .addVisualElement(_sessionContainer);
    _sessionContainer->addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack)
        .addVisualElement(_navButtonSelect);

    app_util::configureSelectButton(_navButtonSelect.get());
    app_util::configureBackButton(_navButtonBack.get());

    app_util::configureMainWindow(_window.get());
    app_util::configureMenuContainer(_sessionContainer.get());
    app_util::configureNavButtonContainer(_navButtonContainer.get());

    _window->align();

    // call to principal container draws all elements
    DEBUG_SERIAL_LN("Drawing window");
    _window->draw();
}

void SessionView::generateValueDisplay(std::vector<::application::ValueId>& ids) {
    for (application::ValueId id : ids) {

    }
}

void SessionView::updateValueElement(::application::ValueId id, String& value) {

}

// try valueElement.redraw();
void SessionView::drawValues() {
    _window->draw();
}

void SessionView::startRecording() {

}

void SessionView::stopRecording() {

}
