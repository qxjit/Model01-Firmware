#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>

namespace kaleidoscope {
class QxjitLED : public LEDMode {
 public:
  QxjitLED();

 protected:
  void update(void) final;
};
}

