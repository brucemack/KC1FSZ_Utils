/**
Copyright (c) 2017 Bruce MacKinnon, KC1FSZ
*/
#ifndef _RotaryEncoder_h
#define _RotaryEncoder_h

#include <Switch.h>

/**
  A class for implementing a rotary encoder behavior from two
  debounced switched.
*/
class RotaryEncoder {

public:

  RotaryEncoder(Switch* switchLeft,Switch* switchRight,unsigned long fastInterval) {
    _switchLeft = switchLeft;
    _switchRight = switchRight;
    _idle = true;
    _fastInterval = fastInterval;
    _lastChange = millis();
  }

  long getIncrement() {

    long result = 0;
    unsigned long now = millis();
    unsigned long d = now - _lastChange;

    if (_idle) {
      if (_switchLeft->getState() &&
          _switchLeft->isEdge() &&
          !_switchRight->getState()) {
        result = -getSlewMultiplier(d);
        _idle = false;
        _lastChange = now;
        //Serial.println(d);
      } else if (_switchRight->getState() &&
          _switchRight->isEdge() &&
          !_switchLeft->getState()) {
        result = getSlewMultiplier(d);
        _idle = false;
        _lastChange = now;
        //Serial.println(d);
      }
    }

    // If both are off then we are between notches and ready to collect a new sample
    if (!_switchLeft->getState() &&
        !_switchRight->getState()) {
        _idle = true;
    }

    return result;
  }

private:

  Switch* _switchLeft;
  Switch* _switchRight;
  boolean _idle;
  unsigned long _lastChange;
  unsigned long _fastInterval;

  long getSlewMultiplier(unsigned long msBetween) {
    if (msBetween < (_fastInterval / 2)) {
      return 4;
    } else if (msBetween < _fastInterval) {
      return 2;
    } else {
      return 1;
    }
  }
};

#endif
