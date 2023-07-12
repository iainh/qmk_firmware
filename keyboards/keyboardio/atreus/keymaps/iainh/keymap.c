/* Copyright 2023 iainh <iain@spiralpoint.org>
 *
 *  This program is free software: you can redistribute it and/or modify
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

enum my_layers {
  _COLEMAK,
  _SYMB,
  _FUNC
};

enum my_tds {
  TdH,
  TdL
};

#define FUNC LT(_FUNC, KC_SPC)
#define SYMBOL OSL(_SYMB)

#define OSMCMD OSM(MOD_LGUI)
#define OSMOPT OSM(MOD_LALT)
#define OSMCTL OSM(MOD_LCTL)
#define OSMSFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
         KC_Q,         KC_W,    KC_F,    KC_P,   KC_B,                     KC_J,  KC_L,    KC_U,    KC_Y, KC_SCLN,
         KC_A, KC_R,    KC_S, LSFT_T(KC_T),   LALT_T(KC_G),                     RALT_T(KC_M),  RSFT_T(KC_N),    KC_E,    KC_I,   KC_O,
         LCTL_T(KC_Z), KC_X,   KC_C,    KC_D,   KC_V,  KC_LSFT, KC_ESC,  KC_K,  KC_H, KC_COMM,  KC_DOT, RCTL_T(KC_SLSH),
    MO(_SYMB), KC_SCLN, KC_LEFT, KC_RGHT, KC_SPC, KC_BSPC, KC_TAB, KC_ENT,  KC_UP, KC_DOWN, KC_QUOT, MO(_SYMB)
  ),

  [_SYMB] = LAYOUT(
      KC_EXLM, KC_LCBR, KC_RCBR, KC_PIPE, _______,                     KC_UP,    KC_8,   KC_9, KC_ASTR, _______,
      KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                    KC_DOWN,    KC_4,   KC_5,    KC_6, KC_PLUS,
      KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, KC_AMPR,    KC_1,   KC_2,    KC_3, KC_BSLS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOT,    KC_0, _______
  ),

  [_FUNC] = LAYOUT(
      KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD, KC_MPLY,                   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_CAPS,
      KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_BRIU,                   KC_F12,  KC_F4,   KC_F5,   KC_F6,   TD(TdL),
      KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_BRID, _______, _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,
      _______, _______, _______, CW_TOGG, _______, _______, _______, _______, _______, _______, _______, _______
      ),
};

void dance_hex(tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
			SEND_STRING("0x");
      break;
    case 2:
			SEND_STRING("\\x");
      break;
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [TdH] = ACTION_TAP_DANCE_FN(dance_hex),
};
