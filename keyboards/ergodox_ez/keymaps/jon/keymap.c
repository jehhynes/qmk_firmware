#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"



enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ergodox(KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,LCTL(KC_F5),KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_PGUP,LT(1,KC_GRAVE),KC_A,KC_S,KC_D,KC_F,KC_G,SFT_T(KC_BSLASH),CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,KC_PGDOWN,LM(2,MOD_LCTL),KC_LGUI,ALT_T(KC_NO),LCTL(KC_C),LCTL(KC_V),KC_F5,KC_F10,KC_INSERT,KC_SPACE,KC_ENTER,KC_DELETE,KC_PAUSE,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_HOME,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_EQUAL,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,KC_END,KC_N,KC_M,KC_COMMA,KC_DOT,KC_UP,RSFT_T(KC_SLASH),KC_LBRACKET,KC_RBRACKET,KC_LEFT,KC_DOWN,KC_RIGHT,KC_F11,KC_F12,KC_DELETE,KC_ENTER,KC_BSPACE,KC_SPACE),

  [1] = LAYOUT_ergodox(KC_ESCAPE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_TRANSPARENT,KC_7,KC_8,KC_9,KC_ASTR,KC_F12,KC_TRANSPARENT,KC_4,KC_5,KC_6,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_AMPR,KC_1,KC_2,KC_3,KC_BSLASH,KC_TRANSPARENT,KC_TRANSPARENT,KC_DOT,KC_0,KC_EQUAL,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [2] = LAYOUT_ergodox(LCTL(KC_ESCAPE),LCTL(KC_F1),LCTL(KC_F2),LCTL(KC_F3),LCTL(KC_F4),LCTL(KC_F5),LCTL(KC_PSCREEN),LCTL(KC_TAB),LCTL(KC_Q),LCTL(KC_W),LCTL(KC_E),LCTL(KC_R),LCTL(KC_T),LCTL(KC_PGUP),KC_TRANSPARENT,LCTL(KC_A),LCTL(KC_S),LCTL(KC_D),LCTL(KC_F),LCTL(KC_G),KC_LSHIFT,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),LCTL(KC_PGDOWN),KC_TRANSPARENT,KC_TRANSPARENT,KC_LALT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_INSERT),LCTL(KC_SPACE),LCTL(KC_ENTER),LCTL(KC_DELETE),LCTL(KC_PAUSE),LCTL(KC_F6),LCTL(KC_F7),LCTL(KC_F8),LCTL(KC_F9),LCTL(KC_F10),LCTL(KC_F11),LCTL(KC_HOME),LCTL(KC_Y),LCTL(KC_U),LCTL(KC_I),LCTL(KC_O),LCTL(KC_P),LCTL(KC_F12),LCTL(KC_H),LCTL(KC_J),LCTL(KC_K),LCTL(KC_L),KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_END),LCTL(KC_N),LCTL(KC_M),LCTL(KC_COMMA),LCTL(KC_DOT),LCTL(KC_UP),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_LEFT),LCTL(KC_DOWN),LCTL(KC_RIGHT),KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_DELETE),LCTL(KC_ENTER),LCTL(KC_BSPACE),LCTL(KC_SPACE)),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }
    return state;

};
