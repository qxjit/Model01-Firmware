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

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for Heatmap LED Effect
#include "Kaleidoscope-Heatmap.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for Active modifier LEDs
//   (particularly useful with one shot modifiers, see above)
//   (https://github.com/keyboardio/Kaleidoscope-LED-ActiveModColor)
#include "Kaleidoscope-LED-ActiveModColor.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VIM_ALT_BUFFER
     };



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
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { DVORAK, SYMBOL, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

#define Key_Colon       LSHIFT(Key_Semicolon)
#define Key_LessThan    LSHIFT(Key_Comma)
#define Key_GreaterThan LSHIFT(Key_Period)
#define Key_Plus        LSHIFT(Key_Equals)
#define Key_Bang        LSHIFT(Key_1)
#define Key_Octothorpe  LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Asterisk    LSHIFT(Key_8)
#define Key_Tmux_Leader LCTRL(Key_A)

KEYMAPS(

  [DVORAK] = KEYMAP_STACKED
  (___,             Key_1,          Key_2,      Key_3,        Key_4,    Key_5, Key_LEDEffectNext,
   Key_Backtick,    Key_Quote,      Key_Comma,  Key_Period,   Key_P,    Key_Y, Key_LeftControl,
   Key_PageUp,      Key_A,          Key_O,      Key_E,        Key_U,    Key_I,
   Key_PageDown,    Key_Semicolon,  Key_Q,      Key_J,        Key_K,    Key_X, Key_Escape,
   ShiftToLayer(SYMBOL), Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   Key_RightAlt,      Key_6, Key_7,    Key_8,        Key_9,    Key_0,    ___,
   Key_RightControl,  Key_F, Key_G,    Key_C,        Key_R,    Key_L,    Key_Slash,
                      Key_D, Key_H,    Key_T,        Key_N,    Key_S,    Key_Minus,
   ___,               Key_B, Key_M,    Key_W,        Key_V,    Key_Z,    Key_Equals,
   Key_RightShift, Key_Enter, Key_Spacebar, ShiftToLayer(SYMBOL),
   ShiftToLayer(FUNCTION)),

  [SYMBOL] =  KEYMAP_STACKED
  (___, ___,              ___,                ___,                   ___,                   ___, ___,
   ___, Key_Bang,         Key_LessThan,       Key_GreaterThan,       ___,                   ___, ___,
   ___, Key_LeftParen,    Key_RightParen,     Key_LeftCurlyBracket,  Key_RightCurlyBracket, ___,
   ___, ___,              ___,                ___,                   ___,                   ___, ___,
   ___, ___,              ___,                ___,
   ___,

   ___, ___, ___,             ___,              ___,            ___,           ___,
   ___, ___, Key_Plus,        Key_Minus,        Key_Asterisk,   Key_Backslash, ___,
        ___, Key_LeftBracket, Key_RightBracket, Key_Equals,     Key_Slash,     Key_Pipe,
   ___, ___, Key_Dollar,      Key_Octothorpe,   ___,            ___,           ___,
   ___, ___, ___,             ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,          Key_F2,           Key_F3,       Key_F4,                   Key_F5,   XXX,
   Key_Tab,  Key_1,           Key_2,            Key_3,        Key_4,                    Key_5,    ___,
   Key_Home, Key_Tmux_Leader, Key_Backslash,    Key_Escape,   Key_Colon,                Key_Tab,
   Key_End,  Key_PrintScreen, Key_Insert,       ___,          M(MACRO_VIM_ALT_BUFFER),  ___,      ___,
   ___, ___, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,        Key_F7,                   Key_F8,                   Key_F9,          Key_F10, Key_F11,
   Consumer_PlaySlashPause,    Key_6,         Key_7,                    Key_8,                    Key_9,           Key_0,   Key_F12,
                               Key_LeftArrow, Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,     ___,
   Key_PcApplication,          Consumer_Mute, Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             ___,     ___,
   ___, ___, Key_Tab, ___,
   ___)

	) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

#define MODDED(mod, key) D(mod), T(key), U(mod)
#define SHIFT(key) MACRODOWN(MODDED(LeftShift, key))

static const macro_t *vimAltBufferMacro(uint8_t keyState) {
  return MACRODOWN(
    MODDED(LeftShift, Semicolon),
    T(B), T(U), T(F), T(Space),
    MODDED(LeftShift, 3),
    T(Enter));
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_VIM_ALT_BUFFER:
    return vimAltBufferMacro(keyState);
  }
  return MACRO_NONE;
}

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

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  BootGreetingEffect,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The HeatmapEffect shows how much each key has been pressed using the
  // LEDS
  HeatmapEffect,

  // The ActiveModColorEffect indicates which keyboard modifiers are active
  // by lighting up the LEDs for the modifier keys.
  ActiveModColorEffect,

  // The macros plugin adds support for macros
  Macros,

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

  ActiveModColorEffect.highlight_color = CRGB(0xB0, 0xCC, 0x55);
  ActiveModColorEffect.sticky_color = CRGB(0xBF, 0xAD, 0xEB);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
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
