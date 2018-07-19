// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// The Kaleidoscope core
#include "Kaleidoscope-MouseKeys.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for One-Shot keys
#include "Kaleidoscope-OneShot.h"
#include "kaleidoscope/hid.h"

// Support for tapdance keys
#include "Kaleidoscope-TapDance.h"

// Support for tapdance keys
#include "Kaleidoscope-LEDEffect-SolidColor.h"

#include "QxjitEffect.h"

/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

// Layers
enum { DVORAK, FUNCTION, MOUSE };

// Tapdances
enum { DanceParens, DanceCurlies, DanceSquares, DanceAngles, DanceSlash, DanceQuotes };

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

#define Key_Colon       LSHIFT(Key_Semicolon)
#define Key_LessThan    LSHIFT(Key_Comma)
#define Key_GreaterThan LSHIFT(Key_Period)
#define Key_Plus        LSHIFT(Key_Equals)
#define Key_DoubleQuote LSHIFT(Key_Quote)
#define Key_Bang        LSHIFT(Key_1)
#define Key_Asperand    LSHIFT(Key_2)
#define Key_Octothorpe  LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_Ampersand   LSHIFT(Key_7)
#define Key_Asterisk    LSHIFT(Key_8)

KEYMAPS(

  [DVORAK] = KEYMAP_STACKED
  (___,              Key_1,          Key_2,      Key_3,        Key_4,    Key_5, Key_LEDEffectNext,
   Key_Backtick,     Key_Quote,      Key_Comma,  Key_Period,   Key_P,    Key_Y, ___,
   Key_PageUp,       Key_A,          Key_O,      Key_E,        Key_U,    Key_I,
   Key_PageDown,     Key_Semicolon,  Key_Q,      Key_J,        Key_K,    Key_X, Key_Escape,
   OSM(LeftControl), Key_Backspace, OSM(LeftGui), OSM(LeftShift),
   OSL(FUNCTION),

   Consumer_Mute,             Key_6, Key_7,    Key_8,        Key_9,    Key_0,    LockLayer(MOUSE),
   Consumer_VolumeIncrement,  Key_F, Key_G,    Key_C,        Key_R,    Key_L,    Key_Slash,
                              Key_D, Key_H,    Key_T,        Key_N,    Key_S,    Key_Minus,
   Consumer_VolumeDecrement,  Key_B, Key_M,    Key_W,        Key_V,    Key_Z,    Key_Equals,
   OSM(RightShift), Key_Enter, Key_Spacebar, OSM(RightAlt),
   OSL(FUNCTION)),

  [FUNCTION] = KEYMAP_STACKED
  (___,      Key_F1,            Key_F2,           Key_F3,           Key_F4,       Key_F5,     XXX,
   ___,      TD(DanceSquares),  TD(DanceAngles),  Key_Dollar,       Key_Asterisk, Key_Minus,  ___,
   Key_Home, TD(DanceCurlies),  TD(DanceParens),  Key_Escape,       Key_Colon,    Key_Equals,
   Key_End,  ___,               ___,              TD(DanceQuotes),  Key_Caret,    Key_Plus,   ___,
   ___, ___, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,        Key_F7,         Key_F8,       Key_F9,         Key_F10,        Key_F11,
   Consumer_PlaySlashPause,    Key_Bang,      TD(DanceSlash), Key_Percent,  Key_Pipe,       Key_Octothorpe, Key_F12,
                               Key_LeftArrow, Key_DownArrow,  Key_UpArrow,  Key_RightArrow, Key_Ampersand,  Key_Asperand,
   Key_PcApplication,          ___,           ___,            ___,          ___,            ___,            ___,
   ___, ___, Key_Tab, ___,
   ___),

  [MOUSE] = KEYMAP_STACKED
  (XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX,              Key_mouseL,      Key_mouseDn,      Key_mouseUp,      Key_mouseR,       XXX, XXX,
   Key_mouseWarpEnd, Key_mouseWarpNW, Key_mouseWarpSW,  Key_mouseWarpSE,  Key_mouseWarpNE,  XXX,
   XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX,
   XXX,

   XXX, XXX, XXX, XXX, XXX, XXX, ___,
   XXX, XXX,           Key_mouseScrollL,  Key_mouseScrollR,   XXX,            XXX,            XXX,
        Key_mouseBtnL, Key_mouseScrollUp, Key_mouseScrollDn,  Key_mouseBtnR,  Key_mouseBtnM,  XXX,
   XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX,
   XXX)

	) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** tapDanceAction defines the behavior of tapdance keys for each number of
 * key presses
 */
void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count,
    kaleidoscope::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case DanceParens:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_LeftParen, Key_RightParen);

    case DanceCurlies:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_LeftCurlyBracket, Key_RightCurlyBracket);

    case DanceSquares:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_LeftBracket, Key_RightBracket);

    case DanceAngles:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_LessThan, Key_GreaterThan);

    case DanceSlash:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_Slash, Key_Backslash);

    case DanceQuotes:
      return tapDanceActionKeys(tap_count, tap_dance_action,
          Key_DoubleQuote, Key_Quote);
  }
}

// Solid white colors for testing purposes
static kaleidoscope::LEDSolidColor solidWhite1(0x77, 0x77, 0x77);
static kaleidoscope::LEDSolidColor solidWhite2(0x99, 0x99, 0x99);
static kaleidoscope::LEDSolidColor solidWhite3(0xbb, 0xbb, 0xbb);
static kaleidoscope::LEDSolidColor solidWhite4(0xdd, 0xdd, 0xdd);
static kaleidoscope::LEDSolidColor solidWhite5(0xff, 0xff, 0xff);

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // Default to the Qxjit Effect
  QxjitEffect,

  solidWhite1,
  solidWhite2,
  solidWhite3,
  solidWhite4,
  solidWhite5,

  // Provides support for OneShot keys
  OneShot,

  // Provides support for TapDance keys
  TapDance,

  // Provides support for MouseKeys
  MouseKeys,

  // The HostPowerManagement plugin enables waking up the host from suspend,
  // and allows us to turn LEDs off when it goes to sleep.
  HostPowerManagement
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // Disable sticky oneshots. I often turn them on by accident :(
  OneShot.double_tap_sticky = false;
  OneShot.double_tap_sticky_layers = false;

  MouseKeys.accelSpeed = 4;
  MouseKeys.accelDelay = 25;
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
