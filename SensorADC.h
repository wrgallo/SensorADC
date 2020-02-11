#ifndef __SensorADC__
#define __SensorADC__

#include <Arduino.h>

class SensorADC{

protected:
    const uint8_t _PIN;
    const uint8_t _bufferLength;
    uint8_t       _bufferIndex;
    uint16_t     *_buffer;
    uint16_t      _value;
    bool          _busy;
    bool          _getNewValue;

public:
    SensorADC(uint8_t PIN , uint8_t bufferLength = 5);
    ~SensorADC();

    void read();
    uint16_t getValue();
    void clearBuffer();
};

#endif