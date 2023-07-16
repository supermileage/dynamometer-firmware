#ifndef _TEXT_DIALOG_VIEW_H_
#define _TEXT_DIALOG_VIEW_H_

#include "TFT_eSPI.h"
#include "ViewBase.h"

class TextDialogView : public ViewBase {
    public:
        TextDialogView(TFT_eSPI& display);
        ~TextDialogView();
        void init();
        void setTextDisplay(const String& str);
        void redrawTextDisplay();
        void addCharacterElement(std::shared_ptr<UIButton> element);

    private:
        std::shared_ptr<TextElement> _textDisplay;
        std::shared_ptr<Container> _textContainer;

        void _configureCharacterElement(std::shared_ptr<UIButton> element);

};

#endif