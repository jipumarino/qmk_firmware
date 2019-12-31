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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB , KC_Q       , KC_W       , KC_E       , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I       , KC_O       , KC_P       , KC_BSPC,
    CTR_ESC, KC_A       , KC_S       , KC_D       , KC_F   , KC_G   , KC_H   , KC_J   , KC_K       , KC_L       , KC_SCLN    , KC_QUOT,
    KC_LSFT, KC_Z       , KC_X       , KC_C       , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM    , KC_DOT     , KC_SLSH    , SFT_ENT,
    KC_HYPR, XXXXXXX    , KC_LALT    , KC_LGUI    , LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT    , KC_DOWN    , KC_UP      , KC_RGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7  , KC_P8  , KC_P9  ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4  , KC_P5  , KC_P6  ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P0  , KC_PDOT, _______
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, ?????  , ?????  , ?????  ,
    KC_PIPE, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL , ?????  , ?????  , ?????  ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, ?????  , ?????  , _______
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
