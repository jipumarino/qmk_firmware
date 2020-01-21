#include QMK_KEYBOARD_H

enum preonic_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPECIAL MO(_NUMPAD)

#define NUM_GRV LT(_NUMPAD, KC_GRV)
#define CTR_ESC CTL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)

enum td_keycodes {
  ATAB_DANCE,
  CTAB_DANCE
};

#define ATAB TD(ATAB_DANCE)
#define CTAB TD(CTAB_DANCE)

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD
} td_state_t;

static td_state_t td_state;
int cur_dance (qk_tap_dance_state_t *state);

void atab_finished (qk_tap_dance_state_t *state, void *user_data);
void atab_reset (qk_tap_dance_state_t *state, void *user_data);
void ctab_finished (qk_tap_dance_state_t *state, void *user_data);
void ctab_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_preonic_grid(
    NUM_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
    CTR_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SFT_ENT,
    KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, RAISE  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
  ),

  [_LOWER] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),


  [_RAISE] = LAYOUT_preonic_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_EQL , KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_UNDS, KC_LCBR, KC_RCBR, KC_DQUO,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_preonic_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_NUMPAD] = LAYOUT_preonic_grid(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_BSPC,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4  , KC_P5  , KC_P6  , KC_PMNS, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1  , KC_P2  , KC_P3  , KC_PAST, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0  , KC_PDOT, KC_PEQL, KC_PSLS, KC_PENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _NUMPAD, _RAISE, _ADJUST);
}


int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else {
    return 2;
  }
}

void atab_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_mods(MOD_BIT(KC_RALT));
      register_code16(KC_TAB);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RALT));
  }
}

void atab_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_TAB);
      unregister_mods(MOD_BIT(KC_RALT));
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RALT));
  }
}

void ctab_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_mods(MOD_BIT(KC_RCTL));
      register_code16(KC_TAB);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
  }
}

void ctab_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_TAB);
      unregister_mods(MOD_BIT(KC_RCTL));
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RCTL));
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [ATAB_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, atab_finished, atab_reset),
  [CTAB_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctab_finished, ctab_reset),
};

