#include <QxjitLED.h>

namespace kaleidoscope {

QxjitLED::QxjitLED() {
}

void QxjitLED::update(void) {
  cRGB color;

  uint8_t topLayer = Layer.top();

  switch (topLayer % 3) {
    case 2:
      color = CRGB(0xdd, 0xdd, 0x00);
      break;

    case 1:
      color = CRGB(0xdd, 0x00, 0xdd);
      break;

    default:
      color = CRGB(0x00, 0xdd, 0xdd);
  }

  for (uint8_t r = 0; r < ROWS; r++) {
    for (uint8_t c = 0; c < COLS; c++) {
      ::LEDControl.setCrgbAt(r, c, color);
    }
  }
}
}

