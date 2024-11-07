#include "SessionView.h"

SessionView::SessionView(TFT_eSPI& display) : ViewBase(display) {

}

SessionView::~SessionView() {

}

void SessionView::generateValueDisplay(std::vector<::application::ValueId>& ids) {
    for (application::ValueId id : ids) {
        
    }
}

void SessionView::updateValueElement(::application::ValueId id, String& value) {

}

void SessionView::drawValues() {

}

void SessionView::startRecording() {

}

void SessionView::stopRecording() {

}
