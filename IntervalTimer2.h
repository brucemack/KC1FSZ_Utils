/**
Copyright (c) 2019 Bruce MacKinnon, KC1FSZ
*/
#ifndef _IntervalTimer2_h
#define _IntervalTimer2_h

class IntervalTimer2 {

    const unsigned long interval;
    unsigned long lastResetStamp = 0;
    bool everReset = false;

public:

  IntervalTimer2(unsigned long interval);

  void start(unsigned long now);
  bool isExpired(unsigned long now) const;
};

IntervalTimer2::IntervalTimer2(unsigned long interval) :
  interval(interval) {
}

void IntervalTimer2::start(unsigned long now) {
  lastResetStamp = now;
  everReset = true;
}

bool IntervalTimer2::isExpired(unsigned long now) const {
  return everReset && now > lastResetStamp + interval;
}

#endif
