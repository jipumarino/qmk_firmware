#include QMK_KEYBOARD_H

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define CTR_ESC CTL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)
#define NUM_TAB LT(_NUMPAD, KC_TAB)
#define LWR_QUO LT(_LOWER, KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    NUM_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    CTR_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, LWR_QUO,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SFT_ENT,
    KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_PIPE,
    KC_GRV , KC_UNDS, KC_MINS, KC_PLUS, KC_EQL , _______, _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    KC_GRV , KC_UNDS, KC_MINS, KC_PLUS, KC_EQL , _______, _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_NUMPAD] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, KC_P7  , KC_P8  , KC_P9  , KC_PPLS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_P4  , KC_P5  , KC_P6  , KC_PMNS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1  , KC_P2  , KC_P3  , KC_PENT,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0  , KC_PDOT, KC_PEQL, KC_PEQL
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
