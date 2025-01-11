#ifndef _SESSION_VIEW_H_
#define _SESSION_VIEW_H_
// #define VALUES_PER_COL 5

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
        void init(std::vector<::application::ValueId>& ids);
        void generateValueDisplay(std::vector<application::ValueId>& ids);
        void updateValueElement(application::ValueId id, String& value);
        void drawValues();
        void startRecording();
        void stopRecording();
    private:
        std::shared_ptr<Container> _sessionContainer;
        std::shared_ptr<ValueElement> _sessionElement;
        std::unordered_map<application::ValueId, std::shared_ptr<ValueElement>> _idToElement;
};

#endif