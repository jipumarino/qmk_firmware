#include QMK_KEYBOARD_H

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define SFT_PIP LSFT_T(KC_PIPE)
#define SFT_ENT RSFT_T(KC_ENT)

#define RSE_SPC LT(_RAISE, KC_SPC)
#define LWR_ESC LT(_LOWER, KC_ESC)

enum td_keycodes {
  ALT_LBC,
  ALT_RBC,
  GUI_LBR,
  GUI_RBR,
  CTL_LPR,
  CTL_RPR
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;
int cur_dance (qk_tap_dance_state_t *state);

void altlbc_finished (qk_tap_dance_state_t *state, void *user_data);
void altlbc_reset (qk_tap_dance_state_t *state, void *user_data);
void altrbc_finished (qk_tap_dance_state_t *state, void *user_data);
void altrbc_reset (qk_tap_dance_state_t *state, void *user_data);
void guilbr_finished (qk_tap_dance_state_t *state, void *user_data);
void guilbr_reset (qk_tap_dance_state_t *state, void *user_data);
void guirbr_finished (qk_tap_dance_state_t *state, void *user_data);
void guirbr_reset (qk_tap_dance_state_t *state, void *user_data);
void ctllpr_finished (qk_tap_dance_state_t *state, void *user_data);
void ctllpr_reset (qk_tap_dance_state_t *state, void *user_data);
void ctlrpr_finished (qk_tap_dance_state_t *state, void *user_data);
void ctlrpr_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB , KC_Q       , KC_W       , KC_E       , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I       , KC_O       , KC_P       , KC_BSPC,
    LWR_ESC, KC_A       , KC_S       , KC_D       , KC_F   , KC_G   , KC_H   , KC_J   , KC_K       , KC_L       , KC_SCLN    , KC_QUOT,
    SFT_PIP, KC_Z       , KC_X       , KC_C       , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM    , KC_DOT     , KC_SLSH    , SFT_ENT,
    XXXXXXX, TD(CTL_LPR), TD(ALT_LBC), TD(GUI_LBR), XXXXXXX, RSE_SPC, RSE_SPC, XXXXXXX, TD(GUI_RBR), TD(ALT_RBC), TD(CTL_RPR), XXXXXXX
  ),

  [_LOWER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_P7  , KC_P8  , KC_P9  ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DQUO, KC_MINS, KC_PLUS, KC_P4  , KC_P5  , KC_P6  ,
    KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, KC_UNDS, KC_EQL , KC_P1  , KC_P2  , KC_P3  ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0  , KC_PDOT, XXXXXXX
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET  , DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  if (state->count == 2) return DOUBLE_SINGLE_TAP;
  else return 3;
}

void altlbc_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LBRC);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LBRC);
      register_code16(KC_LBRC);
  }
}

void altlbc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LBRC);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LBRC);
  }
}

void altrbc_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RBRC);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RBRC);
      register_code16(KC_RBRC);
  }
}

void altrbc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RBRC);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RBRC);
  }
}

/////////////////////////////////////////////////////////


void guilbr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LPRN);
      register_code16(KC_LPRN);
  }
}

void guilbr_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LPRN);
  }
}

void guirbr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RPRN);
      register_code16(KC_RPRN);
  }
}

void guirbr_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RPRN);
  }
}

//////////////////////////////////////////////////

void ctllpr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LCBR);
      register_code16(KC_LCBR);
  }
}

void ctllpr_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LCBR);
  }
}

void ctlrpr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RCBR);
      register_code16(KC_RCBR);
  }
}

void ctlrpr_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RCBR);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT_LBC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlbc_finished, altlbc_reset),
  [ALT_RBC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altrbc_finished, altrbc_reset),
  [GUI_LBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guilbr_finished, guilbr_reset),
  [GUI_RBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guirbr_finished, guirbr_reset),
  [CTL_LPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctllpr_finished, ctllpr_reset),
  [CTL_RPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrpr_finished, ctlrpr_reset)
};
