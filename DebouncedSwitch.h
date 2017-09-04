/**
Copyright (c) 2017 Bruce MacKinnon, KC1FSZ
*/
#ifndef _DebouncedSwitch_h
#define _DebouncedSwitch_h

#include <Switch.h>

/**
A class for implementing a debounce of a potentially noisy switch.

Bruce MacKinnon KC1FSZ
*/
class DebouncedSwitch : public Switch {

  public:

    DebouncedSwitch(long dur) {
      _windowDuration = dur;
      _transitionStartStamp = 0;
      _stateChangeStamp = 0;
      _lastSample = false;
      _state = false;
      _transition = false;
    }

    void loadSample(boolean sample) {

      long now = millis();
      _transition = false;

      // Look for an attempt at a changed transition
      if (sample != _state) {
        // On the edge of the transition we reset the timer
        if (sample != _lastSample) {
           _transitionStartStamp = now;
        }
        // If this is in the middle of the transition we check to see if
        // the transition has lasted long enough to be valid.
        else {
          if (now - _transitionStartStamp > _windowDuration &&
            _stateChangeStamp < _transitionStartStamp) {
            _stateChangeStamp = now;
            _state = !_state;
            _transition = true;
          }
        }
      }

      _lastSample = sample;
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

    long _windowDuration;
    long _transitionStartStamp;
    long _stateChangeStamp;
    boolean _state;
    boolean _lastSample;
    boolean _transition;
};

#endif
