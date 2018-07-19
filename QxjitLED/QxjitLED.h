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

namespace qxjit {
  bool isSameModifier(Key, Key);
  bool isModifierActive(Key);
}
}

