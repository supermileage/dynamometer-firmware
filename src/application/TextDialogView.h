#ifndef _TEXT_DIALOG_VIEW_H_
#define _TEXT_DIALOG_VIEW_H_

#include "Adafruit_GFX.h"
#include "ViewBase.h"

class TextDialogView : public ViewBase {
    public:
        TextDialogView(Adafruit_GFX& display);
        ~TextDialogView();
        void init();
        void addCharacterElement(UIButton* element);

    private:
        Container* _textContainer;

        void _configureCharacterElement(UIButton* element);

};

#endif