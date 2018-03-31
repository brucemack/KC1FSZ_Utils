/**
Copyright (c) 2018 Bruce MacKinnon, KC1FSZ
*/
#ifndef _DebouncedSwitch2_h
#define _DebouncedSwitch2_h

#include <Switch.h>

/**
A class for implementing a debounce of a potentially noisy switch.

Bruce MacKinnon KC1FSZ
*/
class DebouncedSwitch2 : public Switch {

  public:

    DebouncedSwitch2(long dur) {
      _windowDuration = dur;
      _settleStartStamp = 0;
      _stateChangeStamp = 0;
      _state = false;
      _transition = false;
    }

    void loadSample(boolean sample) {

      long now = millis();
      bool isSettled = ((now - _settleStartStamp) > _windowDuration);
      _transition = false;

      if (isSettled) {
        if (_state != sample) {
          _state = sample;
          _settleStartStamp = now;
          _stateChangeStamp = now;
          _transition = true;
        }
      }
    }

    long getStateDuration() {
      return millis() - _stateChangeStamp;
    }

    boolean getState() {
      return _state;
    }

    boolean isEdge() {
      return _transition;
    }

  private:

    unsigned long _windowDuration;
    unsigned long _settleStartStamp;
    unsigned long _stateChangeStamp;
    boolean _state;
    boolean _transition;
};

#endif
