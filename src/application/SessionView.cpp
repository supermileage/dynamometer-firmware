#include "SessionView.h"

SessionView::SessionView(TFT_eSPI& display) : ViewBase(display) {

}

SessionView::~SessionView() {

}

void SessionView::generateValueDisplay(std::vector<ValueId>& ids) {
    for (ValueId id : ids) {
        
    }
}

void SessionView::updateValueElement(ValueId id, String& value) {

}

void SessionView::drawValues() {

}

void SessionView::startRecording() {

}

void SessionView::stopRecording() {

}
