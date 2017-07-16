#ifndef _COMPORTAMIENTO_H_INCLUDED_
#define _COMPORTAMIENTO_H_INCLUDED_

#define ROUND 10

#include <gtkmm.h>
#include <math.h>

class Comportamiento {
public:
  virtual bool on_button_press_event (GdkEventButton* event ) = 0;
  virtual bool on_button_release_event (GdkEventButton* event ) = 0;
  virtual bool on_motion_notify_event (GdkEventMotion* event ) = 0;
  virtual bool on_key_press_event ( GdkEventKey* event ) {
    return true;
  }
  static bool cercano( int x1, int y1, int x2, int y2 ) {
    float d = sqrt( pow(x1-x2,2) + pow(y1-y2,2) ); 
    return (d < ROUND);
  }
};

#endif
