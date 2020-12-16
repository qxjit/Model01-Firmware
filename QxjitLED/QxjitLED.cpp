#include <QxjitLED.h>
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Ranges.h>
#include <kaleidoscope/hid.h>

namespace kaleidoscope {
namespace plugin {

QxjitLED::QxjitLED() {
}

void QxjitLED::setStatusBarColor(cRGB statusBarColor) {
  this->statusBarColor = statusBarColor;
  this->statusBarIsActive = true;
}

void QxjitLED::clearStatusBarColor() {
  this->statusBarIsActive = false;
}

void QxjitLED::update(void) {
  cRGB shiftColor = CRGB(0xff, 0x00, 0x00);
  cRGB guiColor = CRGB(0x00, 0xff, 0x00);
  cRGB controlColor = CRGB(0x00, 0x00, 0xff);
  cRGB altColor = CRGB(0xff, 0xbb, 0x55);

  cRGB colors[5];

  uint8_t numColors = 1;
  uint8_t topLayer = Layer.top();

  switch (topLayer % 4) {
    case 3:
      colors[0] = CRGB(0xdd, 0xdd, 0x00);
      break;

    case 2:
      colors[0] = CRGB(0xee, 0x99, 0xcc);
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

  for (auto addr : KeyAddr::all()) {
    if (addr.isValid()) {
      Key k = Layer.lookupOnActiveLayer(addr);

      if (qxjit::isSameModifier(k, Key_LeftShift) ||
          qxjit::isSameModifier(k, Key_RightShift)) {
        ::LEDControl.setCrgbAt(addr, shiftColor);

      } else if (qxjit::isSameModifier(k, Key_LeftGui) ||
                 qxjit::isSameModifier(k, Key_RightGui)) {
        ::LEDControl.setCrgbAt(addr, guiColor);

      } else if (qxjit::isSameModifier(k, Key_LeftControl) ||
                 qxjit::isSameModifier(k, Key_RightControl)) {
        ::LEDControl.setCrgbAt(addr, controlColor);

      } else if (qxjit::isSameModifier(k, Key_LeftAlt) ||
                 qxjit::isSameModifier(k, Key_RightAlt)) {
        ::LEDControl.setCrgbAt(addr, altColor);

      } else if ((addr.row() == 0) && statusBarIsActive) {
        ::LEDControl.setCrgbAt(addr, this->statusBarColor);

      } else {
        uint8_t idx = (addr.row() + addr.col()) % numColors;
        ::LEDControl.setCrgbAt(addr, colors[idx]);
      }
    }
  }
}
}

namespace qxjit {
  bool isSameModifier(Key key, Key modifier) {
    if (key.getRaw() >= Key_LeftControl.getRaw() && key.getRaw() <= Key_RightGui.getRaw()) {
      return key.getRaw() == modifier.getRaw();
    } else if (key.getRaw() >= ranges::OSM_FIRST && key.getRaw() <= ranges::OSM_LAST) {
      return (key.getRaw() + Key_LeftControl.getKeyCode() - ranges::OSM_FIRST) == modifier.getRaw();
    } else {
      return false;
    }
  }

  bool isModifierActive(Key key) {
    return ::kaleidoscope::Runtime.hid().keyboard().isModifierKeyActive(key) ||
           ::OneShot.isModifierActive(key);
  }
}
}

