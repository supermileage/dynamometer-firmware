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
    int enumIterator = 0;
    for (application::ValueId id : ids) {
        //std::shared_ptr<ValueElement> valueElementPtr = std::make_shared<ValueElement>(_idToElement.at(id)); //warning: hangs
        _idToElement.try_emplace(id,ValueElement(_display));
        _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::CentreMiddle);
    //    std::make_shared<ValueElement>(_idToElement.at(id))->configureLabel("Force",FREE_MONO_12PT7B,COLOUR_BLACK,__SIZE_WIDTH__);

    //     switch(enumIterator){
    //         case 0:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::CentreMiddle);
    //         //std::make_shared<ValueElement>(_idToElement.at(id))->Container::setPadding(10);
    //         //_sessionContainer->Container::setPadding(10);
    //         break;
    //         case 1:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::TopRight);
    //         break;
    //         case 2:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::TopRight);
    //         break;
    //         case 3:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::CentreLeft);
    //         break;
    //         case 4:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::CentreMiddle);
    //         break;
    //         case 5:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::CentreRight);
    //         break;
    //         case 6:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::BottomLeft);
    //         break;
    //         case 7:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::BottomMiddle);
    //         break;
    //         case 8:
    //         _sessionContainer->addVisualElement(std::make_shared<ValueElement>(_idToElement.at(id)), Container::BottomRight);
    //         break;
    //         default:
    //         DEBUG_SERIAL_LN("Too many values to add.");
    //         break;
    //     }
    //     enumIterator++;
    }
}

void SessionView::updateValueElement(::application::ValueId id, String& value) {
    _idToElement.at(id).updateValue(value);
}


// try valueElement.redraw() (?)
void SessionView::drawValues() {
    _window->draw();
}

void SessionView::startRecording() {

}

void SessionView::stopRecording() {

}
