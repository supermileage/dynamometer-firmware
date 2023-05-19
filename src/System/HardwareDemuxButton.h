#ifndef _HARDWARE_BUTTON_H_
#define _HARDWARE_BUTTON_H_

#include "HardwareInput.h"
#include "HardwareDemuxer.h"

#define LED_NULL 255 // LED_NULL is max unsigned 8-bit value

class HardwareDemuxButton : public HardwareInput {
    public:
        HardwareDemuxButton(HardwareDemuxer& demuxer, uint8_t selectId, pin_size_t ledPin, bool normalLow);
        ~HardwareDemuxButton();
		void init() override;
		void run() override;

    private:
        HardwareDemuxer& _demuxer;
		uint8_t _selectId;
		pin_size_t _ledPin;
		PinStatus _lastReadVal;
		uint32_t _lastReadMillis = 0;
		bool _normalLow;

		inline PinStatus _read() {
			PinStatus read = digitalRead(_demuxer.getOutputPin());
			return static_cast<PinStatus>(_normalLow ? read : !read);
		}
};

#endif