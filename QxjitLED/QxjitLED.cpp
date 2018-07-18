#include <QxjitLED.h>
#include <Kaleidoscope-OneShot.h>
#include <kaleidoscope/hid.h>

namespace kaleidoscope {

QxjitLED::QxjitLED() {
}

void QxjitLED::update(void) {
  cRGB baseColor;

  uint8_t topLayer = Layer.top();

  switch (topLayer % 3) {
    case 2:
      baseColor = CRGB(0xdd, 0xdd, 0x00);
      break;

    case 1:
      baseColor = CRGB(0xdd, 0x00, 0xdd);
      break;

    default:
      baseColor = CRGB(0x00, 0xdd, 0xdd);
  }

  cRGB modColor = baseColor;

  if (hid::isModifierKeyActive(Key_LeftShift) ||
      ::OneShot.isModifierActive(Key_LeftShift) ||
      hid::isModifierKeyActive(Key_RightShift) ||
      ::OneShot.isModifierActive(Key_RightShift)) {
    modColor = CRGB(0xff, 0x00, 0x00);
  }

  for (uint8_t r = 0; r < ROWS; r++) {
    for (uint8_t c = 0; c < COLS; c++) {
      cRGB color = baseColor;

      if ((r % 2) == (c % 2)) {
        color = modColor;
      }

      ::LEDControl.setCrgbAt(r, c, color);
    }
  }
}
}

