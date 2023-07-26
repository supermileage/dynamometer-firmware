#ifndef _SESSION_VIEW_H_
#define _SESSION_VIEW_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <Arduino.h>

#include "application.h"
#include "ui/ValueElement.h"
#include "ui/Container.h"
#include "ViewBase.h"

class SessionView : public ViewBase {
    public:
        SessionView(TFT_eSPI& display);
        ~SessionView();
        void generateValueDisplay(std::vector<ValueId>& ids);
        void updateValueElement(ValueId id, String& value);
        void drawValues();
        void startRecording();
        void stopRecording();
    private:
        std::shared_ptr<Container> _valueContainer;
        std::unordered_map<ValueId, ValueElement> _idToElement;
};

#endif