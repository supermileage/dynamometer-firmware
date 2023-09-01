#ifndef _CALIBRATION_VIEW_H_
#define _CALIBRATION_VIEW_H_

#include "ViewBase.h"

class CalibrationView : public ViewBase {
    public:
        CalibrationView(TFT_eSPI& display);
        ~CalibrationView();
        void updateVescRpm(String& rpm);
        
    private:

};

#endif