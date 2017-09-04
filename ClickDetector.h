/**
Copyright (c) 2017 Bruce MacKinnon, KC1FSZ
*/
#ifndef _ClickDetector_h
#define _ClickDetector_h

#include <Switch.h>

class ClickDetector {
public:

  ClickDetector(Switch* sw) {
    _switch = sw;
    _downStamp = millis();
  }

  /**
      Returns the duration of the button click.  Please note that this call
      "consumes" the click, so calling this more than once in a sample
      interval will give unexpected results.
  */
  long getClickDuration() {
    long result = 0;
    boolean state = _switch->getState();
    // If the switch is up then do some processing
    if (!state) {
      // If the switch was down before then we've captured a click
      if (lastState) {
        result = millis() - _downStamp;
      }
    } else {
      // If the switch was up then we are capturing the transition, start the
      // timer here.
      if (!lastState) {
        _downStamp = millis();
      }
    }
    lastState = state;
    return result;
  }

private:

  Switch* _switch;
  boolean lastState;
  long _downStamp;
};

#endif
