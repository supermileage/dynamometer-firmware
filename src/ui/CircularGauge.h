#ifndef _CIRCULAR_GAUGE_H_
#define _CIRCULAR_GAUGE_H_

#include "CircularElement.h"

class CircularGauge : public CircularElement {
    public:
        /**
         * @brief contruct circular gauge object with display and min / max values
        */
        CircularGauge(TFT_eSPI& display, int32_t min, int32_t max);
        ~CircularGauge();

        /**
         * @brief set display value for gauge: min <= val <= max
        */
        void setDisplayValue(int32_t val);

        /**
         * @brief returns current gauge display value
        */
        int32_t getDisplayValue();

        /**
         * @brief draw gauge to screen
        */
        void draw() override;

    private:
        int32_t _displayValue = 0;
        int32_t _min = 0;
        int32_t _max = 0;

};

#endif