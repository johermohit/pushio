/*
  pushio.h - Library for flashing pushio code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef pushio_h
#define pushio_h

#include "Arduino.h"

class pushio
{
  public:
    pushio(String deviceID, String key);
    void connect(int pin);
    int current_state();
    String sync();
    void toggle();

  private:
    String get();
    String put(String state);
    int _previousstate;
    int _pin;
    String _key;
    String _deviceID;
    int _state;
};

#endif