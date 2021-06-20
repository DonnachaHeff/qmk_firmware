#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _POG    1
#define _FN     2
#define _NUMPAD 3
#define _MEDIA  4

// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

#define MOD_CSHF MOD_LCTL | MOD_LSFT

enum custom_keycodes {
    S_TRUE = SAFE_RANGE,
    S_FALSE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // TODO: Can I be holding down shift and check if that's what I'm pressing right now as well...
    switch (keycode) {
    case S_TRUE:
        if (record->event.pressed) {
            SEND_STRING("true");
        }
        break;
    case S_FALSE:
        if (record->event.pressed) {
            SEND_STRING("false");
        }
        break;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /*
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | TAB    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | DEL    |   Q  |   W  |   E  |   R  |   T  |  [   |           | ]    |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ESC    |   A  |   S  |   D  | F/FN |   G  |------|           |------|   H  | J/Alt| K/POG|   L  |; / L2|   '    |
 * |--------+------+------+------+------+------| RESET|           |  FN  |------+------+------+------+------+--------|
 * | LShift | Ctrl |x:M_CS|   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//LGUI| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CAPS |AltShf| Left | Right|                                       |      |  Up  | Down |  POG   |
 *   `---------------------------'                                       `-----------------------------'
 *
 *                                .--------------------.         .---------------.------.
 *                                | Ctrl |      |      |         |        |      | Ctrl |
 *                                |------|AltShf|  SPC |         |  UP    | Tab  |------|
 *                                | BS   |      |      |         |        |      | SPC  |
 *                                '------|-------------|         |---------------'------'
 *                                       | LEFT | RGHT |         |   Down | Enter|
 *                                       '------'------'         '--------'------'
 *
 *
 */

[_QWERTY] = LAYOUT_5x7(
   // left hand
   KC_TAB,          KC_1,                  KC_2,                  KC_3,   KC_4,           KC_5,   XXXXXXX,
   KC_DEL,          KC_Q,                  KC_W,                  KC_E,   KC_R,           KC_T,   KC_LBRC,
   KC_ESC,          KC_A,                  KC_S,                  KC_D,   LT(_FN, KC_F),  KC_G,   RESET,
   OSM(MOD_LSFT),   MT(MOD_LCTL, KC_Z),    MT(MOD_CSHF, KC_X),    KC_C,   KC_V,           KC_B,
   KC_CAPS,         KC_LGUI,               KC_LEFT,               KC_RGHT,
                               // 1btm ,  1tp
                               KC_BSPC, KC_LCTL,
                               // 2btm , 2tp
                               KC_LEFT, KC_LALT,
                               // 3btm , 3tp
                               KC_RGHT, KC_SPC,

    // right hand
                     XXXXXXX, KC_6,    KC_7,                        KC_8,               KC_9,               KC_0,                   KC_MINS,
                     KC_RBRC, KC_Y,    KC_U,                        KC_I,               KC_O,               KC_P,                   KC_BSLS,
                     TT(_FN), KC_H,    LT(_MEDIA, KC_J),            LT(_POG, KC_K),     KC_L,               KC_SCLN,                KC_QUOT,
                              KC_N,    KC_M,                        KC_COMM,            KC_DOT,             MT(MOD_LGUI, KC_SLSH),  OSM(MOD_RSFT),
                                       XXXXXXX,                     KC_UP,              KC_DOWN,            MO(_POG),
        // 1tp , 1btm
        KC_LCTL, KC_SPC, 
        // 2tp , 2btm
        KC_TAB,  KC_ENT, 
        // 3tp , 3btm
        KC_UP,   KC_DOWN), 

/* Keymap 1: Symbol Layer
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |false |      |   {  |   }  |      |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |true  |   =  |   (  |   )  |      |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   _  |   [  |   ]  |      |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_POG] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,     KC_F3,    KC_F4,     KC_F5,    _______,
   _______,   S_FALSE,   _______,   KC_LCBR,  KC_RCBR,   _______,  _______,
   _______,   S_TRUE ,   KC_EQL ,   KC_LPRN,  KC_RPRN,   _______,  RESET,
   _______,   KC_GRV,    KC_UNDS,   KC_LBRC,  KC_RBRC,   _______,
   KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                _______,   _______,   _______,   _______,   _______,   _______,
                                                      _______,   _______,   _______,   _______,
        KC_DEL, _______,
        _______, _______,
        _______, _______),

[_FN] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   KC_F5,     _______,   _______,   _______,  RESET,
   _______,   _______,   _______,   _______,   _______,   _______,
   KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
                     _______,   _______,   _______,   KC_F11,    KC_F10,    _______,   KC_F12,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                _______,   _______,   _______,   _______,   _______,   _______,
                                                      _______,   _______,   _______,   _______,
        KC_DEL, _______,
        _______, _______,
        _______, _______),

[_NUMPAD] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
   _______,   _______,   _______,   _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                                _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                      KC_P0,     KC_PDOT,   _______,   _______,
        _______, KC_PENT,
        _______, _______,
        _______, _______),


[_MEDIA] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
   _______,   _______,   _______,   _______,

                               // 1btm , 1tp
                               KC_VOLD, KC_VOLU,
                               // 2btm , 2tp
                               KC_MNXT, KC_MUTE,
                               // 3btm , 3tp
                               KC_MPRV, KC_MPLY,
        // right hand
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                _______,   _______,   _______,   _______,   _______,   _______,
                                                      _______,   _______,   _______,   _______,
        // 1tp , 1btm
        _______, _______,
        // 2tp , 2btm
        _______, _______,
        // 3tp , 3btm
        _______, _______),

};
