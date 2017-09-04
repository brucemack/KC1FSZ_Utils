/**
Copyright (c) 2017 Bruce MacKinnon, KC1FSZ
*/
#ifndef _Switch_h
#define _Switch_h

class Switch {
public:
  virtual boolean getState() = 0;
  virtual boolean isEdge() = 0;
};

#endif
