/*
Copyright 2021 @Yowkees

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "oledkit.h"
#include "stdlib.h"
#include "../../pmw/pmw.h"
#include "../../optical_sensor/optical_sensor.h"

enum keymap_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _BALL,
};

/////////////////////////////////////////////////////////////////////////////
// Special key codes for shorthand

// clang-format off

// layer
#define KC_L_SPC    LT(_LOWER, KC_SPC)
#define KC_R_ENT    LT(_RAISE, KC_ENT)

// shift_t
#define KC_S_EN     LSFT_T(KC_LANG2)

// original
#define KC_A_JA     LT(_BALL, KC_LANG1)     // cmd or adjust
#define KC_AL_CP    MT(MOD_LALT, KC_CAPS)   // alt or caps lock
#define KC_G_BS     MT(MOD_LGUI, KC_BSPC)   // command or back space
#define KC_G_DEL    MT(MOD_LGUI, KC_DEL)    // command or delete
#define KC_A_BS     LT(_BALL, KC_BSPC)      // adjust or back space
#define KC_A_DEL    LT(_BALL, KC_DEL)       // adjust or delete

enum custom_keycodes {
    KC_CPI_DEF = SAFE_RANGE,
    KC_CPI_UP,
    KC_CPI_DOWN
};

// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_left_ball(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_LBRC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_SCLN,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_RBRC,    KC_H,    KC_J,    KC_K,    KC_L, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      KC_BSLS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PSCR,KC_AL_CP,        KC_G_BS,  KC_SPC,                KC_A_JA, KC_S_EN,  KC_R_ENT,   KC_G_DEL,    KC_EXLM,  KC_TAB
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_RAISE] = LAYOUT_left_ball(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_BSLS,    KC_7,    KC_8,    KC_9, KC_PLUS,                      KC_LPRN,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_ASTR,    KC_4,    KC_5,    KC_6,  KC_DOT,                      KC_RPRN, KC_LEFT,   KC_UP, KC_RGHT, _______,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      _______, KC_SLSH,    KC_1,    KC_2,    KC_3,  KC_EQL,                               _______, KC_DOWN, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      _______, _______,    KC_0,         KC_ENT,KC_A_DEL,                 KC_SPC, _______,   _______,    _______,    _______, _______
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_LOWER] = LAYOUT_left_ball(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_LPRN,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HASH, KC_EXLM, KC_AMPR, KC_PIPE,   KC_AT,                      KC_RPRN, KC_BTN1, KC_PGUP, KC_BTN2, KC_BTN3,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      _______,  KC_GRV,  KC_DQT, KC_QUOT, KC_CIRC, KC_TILD,                               _______, KC_PGDN, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      _______, _______,    KC_0,        _______, _______,                _______, _______,   KC_A_BS,    _______,    _______, _______
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_BALL] = LAYOUT_left_ball(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CPI_DEF, KC_CPI_UP, KC_CPI_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BALL:
            keyball_set_scroll_mode(true);
            break;
        default:
            keyball_set_scroll_mode(false);
            break;
    }
    return state;
}

#ifdef OLED_DRIVER_ENABLE

void oledkit_render_info_user(void) {
    const char *n;
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            n = PSTR("Default");
            break;
        case _RAISE:
            n = PSTR("Raise");
            break;
        case _LOWER:
            n = PSTR("Lower");
            break;
        case _BALL:
            n = PSTR("Adjust");
            break;
        default:
            n = PSTR("Undefined");
            break;
    }
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln_P(n, false);

    keyball_oled_render_ballinfo();
    keyball_oled_render_keyinfo();
}

#endif

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) { return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v; }

int8_t keyball_process_trackball_acceleration(const int16_t val) {
    int step1 = 3;
    float step1_acc = 3;

    int step2 = 10;
    float step2_acc = 13;

    int abs_val = abs(val);

    int8_t result = 0;

    if (abs_val > step2) {
        result = clip2int8(val * step2_acc);
    } else if (abs_val > step1){
        result = clip2int8(val * step1_acc);
    } else {
        result = clip2int8(val);
    }

    return result;
}

void keyball_process_trackball_user(const trackball_delta_t *primary, const trackball_delta_t *secondary) {
    bool is_scroll_mode = keyball_get_scroll_mode();
    report_mouse_t r = pointing_device_get_report();
    if (primary) {
        if (!is_scroll_mode) {
            r.x = keyball_process_trackball_acceleration(primary->x);
            r.y = keyball_process_trackball_acceleration(primary->y);
        } else {
            r.h += clip2int8(primary->x);
            r.v -= clip2int8(primary->y);
        }
    }
    if (secondary) {
        r.h += clip2int8(secondary->x);
        r.v -= clip2int8(secondary->y);
    }

    pointing_device_set_report(r);
    pointing_device_send();
}

void keyboard_post_init_user(void) {
    eeconfig_t kb_config;
    kb_config.raw = eeconfig_read_user();

    if (!kb_config.cpi) {
        kb_config.cpi = DEFAULT_CPI;
        eeconfig_update_user(kb_config.raw);
    }

    pmw_set_config((config_pmw_t){kb_config.cpi});
}

static void on_cpi_button(int cpi, keyrecord_t *record, bool absolute) {
    if (!record->event.pressed) return;

    eeconfig_t kb_config;

    if (absolute) {
        kb_config.cpi = (uint16_t)CLAMP_CPI(cpi);
    } else {
        kb_config.raw = eeconfig_read_user();
        int config_1;

        if (cpi < 0 && kb_config.cpi < abs(cpi)) {
            config_1 = MIN_CPI;
        } else {
            config_1 = (int)kb_config.cpi + cpi;
        }

        kb_config.cpi = (uint16_t)CLAMP_CPI(config_1);
    }

    eeconfig_update_user(kb_config.raw);
    pmw_set_config((config_pmw_t){kb_config.cpi});
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case KC_CPI_DEF:
            on_cpi_button(DEFAULT_CPI, record, true);
            return false;

        case KC_CPI_UP:
            on_cpi_button(4 * CPI_STEP, record, false);
            return false;

        case KC_CPI_DOWN:
            on_cpi_button(-4 * CPI_STEP, record, false);
            return false;

        default:
            return true;
    }
}
