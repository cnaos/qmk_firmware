/* Copyright 2018 Eucalyn
 * Copyright 2019 cnaos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "keymap_jp.h"
#include "../../../../tmk_core/common/action.h"
#include "../../../../tmk_core/common/keycode.h"
#include "../../../../quantum/keymap_extras/keymap_jp.h"
#include "../../../../quantum/quantum.h"
#include "../../../../quantum/quantum_keycodes.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  JP_ANSI_KC_2_AT,
  JP_ANSI_KC_6_CIRC,
  JP_ANSI_KC_7_AMPR,
  JP_ANSI_KC_8_ASTR,
  JP_ANSI_KC_9_LPRN,
  JP_ANSI_KC_0_RPRN,
  JP_ANSI_KC_MINS_UNDS,
  JP_ANSI_KC_EQL_PLUS,
  JP_ANSI_KC_SCLN_COLN,
  JP_ANSI_KC_QUOT_DQT,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( \
    KC_GRV,  KC_1,    JP_ANSI_KC_2_AT,    KC_3,    KC_4,    KC_5,      JP_ANSI_KC_6_CIRC,    JP_ANSI_KC_7_AMPR,    JP_ANSI_KC_8_ASTR,    JP_ANSI_KC_9_LPRN,    JP_ANSI_KC_0_RPRN,    JP_ANSI_KC_MINS_UNDS, JP_ANSI_KC_EQL_PLUS,    KC_BSPC,  \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_LBRC, JP_RBRC, JP_YEN,  \
    KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    JP_ANSI_KC_SCLN_COLN, JP_ANSI_KC_QUOT_DQT,        KC_ENT,   \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,   KC_UP,  MO(1),   \
    KC_ESC,    KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,        KC_BSPC, KC_ENT,  LALT(KC_GRV),               KC_LEFT,KC_DOWN,KC_RGHT \
  ),
  [1] = LAYOUT( \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL, \
    RGB_TOG,   RGBRST,  RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_PGUP, _______, \
    XXXXXXX,   _______,    _______,    _______,    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HOME, KC_PGDN, KC_END \
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

bool shift_held = false;

void remapShiftedKeyCode(const keyrecord_t *record, enum quantum_keycodes originalKeyCode,
                           enum quantum_keycodes replacedKeyCode);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSFT:
      shift_held = record->event.pressed;
      return true;
      break;
    case KC_RSFT:
      shift_held = record->event.pressed;
      return true;
      break;
    case RGBRST:
#ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
#endif
      break;
    case JP_ANSI_KC_2_AT:
      remapShiftedKeyCode(record, KC_2, JP_AT);
      return false;
      break;

    case JP_ANSI_KC_6_CIRC:
      remapShiftedKeyCode(record, KC_6, JP_CIRC);
      return false;
      break;

    case JP_ANSI_KC_7_AMPR:
      remapShiftedKeyCode(record, KC_7, JP_AMPR);
      return false;
      break;

    case JP_ANSI_KC_8_ASTR:
      remapShiftedKeyCode(record, KC_8, JP_ASTR);
      return false;
      break;

    case JP_ANSI_KC_9_LPRN:
      remapShiftedKeyCode(record, KC_9, JP_LPRN);
      return false;
      break;

    case JP_ANSI_KC_0_RPRN:
      remapShiftedKeyCode(record, KC_0, JP_RPRN);
      return false;
      break;

    case JP_ANSI_KC_MINS_UNDS:
      remapShiftedKeyCode(record, KC_MINUS, JP_UNDS);
      return false;
      break;

    case JP_ANSI_KC_EQL_PLUS:
      remapShiftedKeyCode(record, JP_EQL, JP_PLUS);
      return false;
      break;

    case JP_ANSI_KC_SCLN_COLN:
      remapShiftedKeyCode(record, KC_SCLN, JP_COLN);
      return false;
      break;

    case JP_ANSI_KC_QUOT_DQT:
      remapShiftedKeyCode(record, JP_QUOT, JP_DQT);
      return false;
      break;

  }
  return true;
}

void remapShiftedKeyCode(
        const keyrecord_t *record,
        enum quantum_keycodes originalKeyCode,
        enum quantum_keycodes replacedKeyCode) {
  if (record->event.pressed) {
    if (shift_held) {
      unregister_code16(originalKeyCode);
      unregister_code(KC_RSFT);
      unregister_code(KC_LSFT);
      register_code16(replacedKeyCode);
    } else {
      unregister_code16(replacedKeyCode);
      register_code16(originalKeyCode);
    }
  } else { // Release the key
    unregister_code(KC_LSFT);
    unregister_code(KC_RSFT);
    unregister_code16(originalKeyCode);
    unregister_code16(replacedKeyCode);
  }
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
