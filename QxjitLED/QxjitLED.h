#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>

namespace kaleidoscope {
namespace plugin {
class QxjitLED : public LEDMode {
 public:
  QxjitLED();
  void setStatusBarColor(cRGB);
  void clearStatusBarColor();

 protected:
  void update(void) final;

 private:
  cRGB statusBarColor;
  bool statusBarIsActive;
};
}

namespace qxjit {
  bool isSameModifier(Key, Key);
  bool isModifierActive(Key);
}
}

