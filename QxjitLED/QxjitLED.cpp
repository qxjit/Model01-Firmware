#include <QxjitLED.h>
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Ranges.h>
#include <kaleidoscope/hid.h>

namespace kaleidoscope {

QxjitLED::QxjitLED() {
}

void QxjitLED::update(void) {
  cRGB shiftColor = CRGB(0xff, 0x00, 0x00);
  cRGB guiColor = CRGB(0x00, 0xff, 0x00);
  cRGB controlColor = CRGB(0x00, 0x00, 0xff);
  cRGB altColor = CRGB(0xff, 0xff, 0x00);

  cRGB colors[5];

  uint8_t numColors = 1;
  uint8_t topLayer = Layer.top();

  switch (topLayer % 3) {
    case 2:
      colors[0] = CRGB(0xdd, 0xdd, 0x00);
      break;

    case 1:
      colors[0] = CRGB(0xdd, 0x00, 0xdd);
      break;

    default:
      colors[0] = CRGB(0x00, 0xdd, 0xdd);
  }

  if (qxjit::isModifierActive(Key_LeftShift) ||
      qxjit::isModifierActive(Key_RightShift)) {
    colors[numColors] = shiftColor;
    numColors += 1;
  }

  if (qxjit::isModifierActive(Key_LeftGui) ||
      qxjit::isModifierActive(Key_RightGui)) {
    colors[numColors] = guiColor;
    numColors += 1;
  }

  if (qxjit::isModifierActive(Key_LeftControl) ||
      qxjit::isModifierActive(Key_RightControl)) {
    colors[numColors] = controlColor;
    numColors += 1;
  }

  if (qxjit::isModifierActive(Key_LeftAlt) ||
      qxjit::isModifierActive(Key_RightAlt)) {
    colors[numColors] = altColor;
    numColors += 1;
  }

  for (uint8_t r = 0; r < ROWS; r++) {
    for (uint8_t c = 0; c < COLS; c++) {
      Key k = Layer.lookupOnActiveLayer(r, c);

      if (qxjit::isSameModifier(k, Key_LeftShift) ||
          qxjit::isSameModifier(k, Key_RightShift)) {
        ::LEDControl.setCrgbAt(r, c, shiftColor);

      } else if (qxjit::isSameModifier(k, Key_LeftGui) ||
                 qxjit::isSameModifier(k, Key_RightGui)) {
        ::LEDControl.setCrgbAt(r, c, guiColor);

      } else if (qxjit::isSameModifier(k, Key_LeftControl) ||
                 qxjit::isSameModifier(k, Key_RightControl)) {
        ::LEDControl.setCrgbAt(r, c, controlColor);

      } else if (qxjit::isSameModifier(k, Key_LeftAlt) ||
                 qxjit::isSameModifier(k, Key_RightAlt)) {
        ::LEDControl.setCrgbAt(r, c, altColor);

      } else {
        uint8_t idx = (r + c) % numColors;
        ::LEDControl.setCrgbAt(r, c, colors[idx]);
      }
    }
  }
}

namespace qxjit {
  bool isSameModifier(Key key, Key modifier) {
    if (key.raw >= Key_LeftControl.raw && key.raw <= Key_RightGui.raw) {
      return key.raw == modifier.raw;
    } else if (key.raw >= ranges::OSM_FIRST && key.raw <= ranges::OSM_LAST) {
      return (key.raw + Key_LeftControl.keyCode - ranges::OSM_FIRST) == modifier.raw;
    } else {
      return false;
    }
  }

  bool isModifierActive(Key key) {
    return ::kaleidoscope::hid::isModifierKeyActive(key) ||
           ::OneShot.isModifierActive(key);
  }
}
}

