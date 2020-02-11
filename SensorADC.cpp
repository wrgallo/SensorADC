#include "SensorADC.h"

SensorADC::SensorADC(uint8_t PIN , uint8_t bufferLength) : _PIN(PIN),
                                                           _bufferLength{
                                                                            (bufferLength == (uint8_t)0) ? (uint8_t)1 : 
                                                                            (bufferLength > (uint8_t)64) ? (uint8_t)64 : bufferLength
                                                                        }
{
    this->_busy = 0;
    this->_getNewValue = 1;
    pinMode( PIN, INPUT );
    this->_bufferIndex  = 1;
    this->_buffer       = new uint16_t[bufferLength + 1];
    this->clearBuffer();
}

SensorADC::~SensorADC(){
    delete []this->_buffer;
    this->_buffer = NULL;
}

void SensorADC::read(){
    this->_busy  = 1;
    this->_getNewValue = 1;
    uint16_t aux = analogRead( _PIN );
    this->_buffer[ 0 ] -= this->_buffer[ _bufferIndex ];
    this->_buffer[ 0 ] += aux;
    this->_buffer[ this->_bufferIndex ] = aux;
    this->_bufferIndex = this->_bufferIndex + 1;
    this->_bufferIndex = (this->_bufferIndex == this->_bufferLength + 1 ) ? 1 : this->_bufferIndex;
    this->_busy  = 0;
}

uint16_t SensorADC::getValue(){
    while( this->_busy ){}
    if( this->_getNewValue )
    {
        this->_getNewValue = 0;
        this->_value = this->_buffer[0] / this->_bufferLength;
    }
    return this->_value;
}

void SensorADC::clearBuffer(){
    while( this->_busy ){}
    this->_busy = 1;
    for(uint8_t i=0; i<this->_bufferLength + 1; i++){
        this->_buffer[i] = 0;
    }
    this->_bufferIndex = 1;
    this->_value = 0;
    this->_busy = 0;
}