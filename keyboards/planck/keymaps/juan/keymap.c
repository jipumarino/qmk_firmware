#include QMK_KEYBOARD_H

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define CTR_ESC CTL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)
#define RSE_QUO LT(_RAISE, KC_QUOT)
#define LWR_TAB LT(_LOWER, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    LWR_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    CTR_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, RSE_QUO,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SFT_ENT,
    KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, KC_P7  , KC_P8  , KC_P9  , _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PMNS, KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_P1  , KC_P2  , KC_P3  , KC_PENT,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_P0  , KC_P0  , KC_PDOT, KC_PEQL
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    KC_GRV , KC_UNDS, KC_MINS, KC_PLUS, KC_EQL , KC_PIPE, KC_PIPE, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

};

static uint8_t hyper_state = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Custom media keys with Hyper/Function key
  switch (keycode) {
    case KC_HYPR:
      if (record->event.pressed) {
        hyper_state = 1;
      } else {
        hyper_state = 0;
      }
      break;
    case KC_SPC:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_MPLY);
        } else {
          unregister_code(KC_MPLY);
        }
        return false;
      }
      break;
    case KC_LCTL:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_MUTE);
        } else {
          unregister_code(KC_MUTE);
        }
        return false;
      }
      break;
    case KC_LALT:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_VOLD);
        } else {
          unregister_code(KC_VOLD);
        }
        return false;
      }
      break;
    case KC_LGUI:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_VOLU);
        } else {
          unregister_code(KC_VOLU);
        }
        return false;
      }
      break;
    case LOWER:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_MPRV);
        } else {
          unregister_code(KC_MPRV);
        }
        return false;
      }
      break;
    case RAISE:
      if (hyper_state == 1) {
        if (record->event.pressed) {
          register_code(KC_MNXT);
        } else {
          unregister_code(KC_MNXT);
        }
        return false;
      }
      break;
  }
  return true;
}


uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
