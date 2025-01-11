#include "SessionView.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "app_util.h"
#include "SessionController.h"

using namespace application;

SessionView::SessionView(TFT_eSPI& display) : ViewBase(display) {
    _sessionContainer = std::make_unique<Container>(_display);
}

SessionView::~SessionView() {
    DEBUG_SERIAL_LN("~SessionView");
}

// Following MenuView's example
void SessionView::init(std::vector<::application::ValueId>& ids){
    _window->addVisualElement(_header).addVisualElement(_sessionContainer);
        //_sessionContainer->addVisualElement(_sessionElement); // freezes
    /*
    _sessionContainer->addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack)
        .addVisualElement(_navButtonSelect);
    
    app_util::configureSelectButton(_navButtonSelect.get());
    app_util::configureBackButton(_navButtonBack.get());

    app_util::configureNavButtonContainer(_navButtonContainer.get());
    */

    app_util::configureMainWindow(_window.get());
    app_util::configureMenuContainer(_sessionContainer.get());

    SessionView::generateValueDisplay(ids);
    // call to principal container draws all elements
    _window->align();
    _window->draw();
}

void SessionView::generateValueDisplay(std::vector<::application::ValueId>& ids) {
    String test = "";
    const GFXfont* testFont = FREE_MONO_BOLD_9PT7B;
     String testVal = "";

    for (application::ValueId id : ids) {
        _idToElement.try_emplace(id,std::make_shared<ValueElement>(_display));
        _idToElement.at(id)->configureLabel(test,testFont,COLOUR_BLUE,1,1);
        _idToElement.at(id)->configureValue(testVal,testFont,COLOUR_BLACK,1,1);

        _sessionContainer->addVisualElement(_idToElement.at(id), Container::TopMiddle);
    }
}

void SessionView::updateValueElement(::application::ValueId id, String& value) {
    _idToElement.at(id)->updateValue(value);
}


// try valueElement.redraw() (?)
void SessionView::drawValues() {
    _window->draw();
}

void SessionView::startRecording() {

}

void SessionView::stopRecording() {

}
