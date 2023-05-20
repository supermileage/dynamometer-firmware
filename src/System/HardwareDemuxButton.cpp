#include "HardwareDemuxButton.h"

#include "settings.h"

/* Hardware Button */
HardwareDemuxButton::HardwareDemuxButton(HardwareDemuxer& demuxer, uint8_t selectId, pin_size_t ledPin, bool normalHigh)
	: _demuxer(demuxer), _selectId(selectId), _ledPin(ledPin), _normalHigh(normalHigh) { }

HardwareDemuxButton::~HardwareDemuxButton() { }

void HardwareDemuxButton::init() {
	if (_ledPin != LED_NULL) {
		pinMode(_ledPin, OUTPUT);
		PinStatus initReadVal = _read();
		digitalWrite(_ledPin, static_cast<PinStatus>(!initReadVal));
	}
}

void HardwareDemuxButton::run() {
	_demuxer.setSelect(_selectId);
	PinStatus readVal = _read();
	
	if (readVal != _lastReadVal && millis() > _lastReadMillis + BUTTON_DEBOUNCE_MILLIS) {
		(_action)(static_cast<input_data_t>(readVal));
		_lastReadMillis = millis();
		_lastReadVal = readVal;

		if (_ledPin != LED_NULL) {
			// Low = 0, High = 1 
			digitalWrite(_ledPin, static_cast<PinStatus>(!readVal));
		}
	}
}
