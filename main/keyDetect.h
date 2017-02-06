#ifndef KEYDETECT_H_INCLUDED
#define KEYDETECT_H_INCLUDED

#include "keyMap.h"
#include "config.h"
#include <stdint.h>

class keyDetect
{
public:
    keyDetect();
    keyDetect(void (*[])());
    void setCallback(keyMap,void (*)());
    void detect();

protected:
    void (*callbackFunction[NUMBER_OF_KEY])();

    #ifdef NUMBER_GRATER_THAN_16
    uint32_t flag;
    #elif defined NUMBER_GRATER_THAN_8
    uint16_t flag;
    #else
    uint8_t flag;
    #endif // NUMBER_GRATER_THAN_16

    #ifdef COUNTDOWN_BY_KEYDETECT
    uint32_t timer;
    #endif // COUNTDOWN_BY_KEYDETECT

private:
    void init();

    #if defined(USE_ENCODER)
    uint8_t encoder_motion;
    inline void checkEncoder ();
    #endif // USE ENCODER
};

#endif // KEYDETECT_H_INCLUDED
