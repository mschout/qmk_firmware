#include QMK_KEYBOARD_H
#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"

// Max time allowed for second keypress to register double-tap
#define TAPPING_TERM 200

#define ________ KC_TRNS

enum anne_pro_layers {
  _BASE_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
};


enum td_keycodes {
    TD_ALT_LP,
    TD_ALT_RP,
    TD_ESC_CAPS
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// tapdance functions
uint8_t cur_dance(qk_tap_dance_state_t *state);
void altlp_finished(qk_tap_dance_state_t *state, void *user_data);
void altlp_reset(qk_tap_dance_state_t *state, void *user_data);
void altrp_finished(qk_tap_dance_state_t *state, void *user_data);
void altrp_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset),
  [TD_ALT_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altrp_finished, altrp_reset),
  [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};

/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |  `~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |       UP       |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_GRV         , KC_1   , KC_2         , KC_3  , KC_4         , KC_5         , KC_6    , KC_7         , KC_8    , KC_9           , KC_0   , KC_MINS      , KC_EQL , KC_BSPC,
    KC_TAB         , KC_Q   , KC_W         , KC_E  , KC_R         , KC_T         , KC_Y    , KC_U         , KC_I    , KC_O           , KC_P   , KC_LBRC      , KC_RBRC, KC_BSLS,
    TD(TD_ESC_CAPS), KC_A   , KC_S         , KC_D  , KC_F         , KC_G         , KC_H    , KC_J         , KC_K    , KC_L           , KC_SCLN, KC_QUOT      , KC_ENT ,
    KC_LSFT        , KC_Z   , KC_X         , KC_C  , KC_V         , KC_B         , KC_N    , KC_M         , KC_COMM , KC_DOT         , KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL        , KC_LGUI, TD(TD_ALT_LP), KC_SPC, TD(TD_ALT_RP), LT(_FN1_LAYER, KC_LEFT), LT(_FN2_LAYER, KC_DOWN), RCTL_T(KC_RGHT)
),
  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_GRV  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6         , KC_F7   , KC_F8   , KC_F9   , KC_F10 , KC_F11  , KC_F12  , KC_DEL  ,
    ________, ________, KC_UP   , ________, ________, ________, ________      , ________, ________, ________, KC_PSCR, KC_HOME , KC_END  , ________,
    ________, KC_LEFT , KC_DOWN , KC_RGHT , ________, ________, ________      , ________, ________, ________, KC_PGUP, KC_PGDN , ________,
    ________, KC_VOLU , KC_VOLD , KC_MUTE , ________, ________, ________      , ________, ________, KC_INS  , KC_DEL , ________,
    ________, ________, ________, ________, ________, ________, MO(_FN2_LAYER), ________
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| F10 | F11 | F12 |    Bksp   |r
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    ________      , KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, ________      , ________      , ________, KC_AP_LED_OFF, KC_AP_LED_ON, ________, ________   , ________ , ________,
    MO(_FN2_LAYER), ________  , KC_UP     , ________  , ________  , ________      , ________      , ________, ________     , ________    , KC_PSCR , KC__VOLDOWN, KC__VOLUP, ________,
    ________      , KC_LEFT   , KC_DOWN   , KC_RGHT   , ________  , ________      , ________      , ________, ________     , ________    , KC_PGUP , KC_PGDN    , ________ ,
    ________      , ________  , ________  , ________  , ________  , ________      , ________      , ________, ________     , KC_INS      , KC_DEL  , ________   ,
    ________      , ________  , ________  , ________  , ________  , MO(_FN1_LAYER), MO(_FN2_LAYER), ________
 ),
};

const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  }

  if (state->count == 2)
    return DOUBLE_SINGLE_TAP;
  else
    return 3;
}

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);

  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LEFT_PAREN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LEFT_PAREN);
      register_code16(KC_LEFT_PAREN);
  }
}

void altlp_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LEFT_PAREN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LEFT_PAREN);
  }
}

void altrp_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);

  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RIGHT_PAREN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RIGHT_PAREN);
      register_code16(KC_RIGHT_PAREN);
  }
}

void altrp_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RIGHT_PAREN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RIGHT_PAREN);
  }
}
