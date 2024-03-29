#include <Arduino.h>

// 'lamp', 16x16px
const unsigned char epd_bitmap_lamp[] PROGMEM = {
    0x00, 0x00, 0x07, 0xe0, 0x08, 0x10, 0x10, 0x08, 0x10, 0x08, 0x15, 0xa8, 0x14, 0x28, 0x12, 0x48,
    0x0a, 0x50, 0x04, 0x20, 0x03, 0xc0, 0x02, 0x40, 0x03, 0xc0, 0x02, 0x40, 0x03, 0xc0, 0x00, 0x00};
// 'oneplayer', 16x16px
const unsigned char epd_bitmap_oneplayer[] PROGMEM = {
    0x00, 0x00, 0x07, 0xe0, 0x08, 0x10, 0x10, 0x08, 0x10, 0x08, 0x12, 0x48, 0x12, 0x48, 0x10, 0x08,
    0x08, 0x10, 0x07, 0xe0, 0x00, 0x00, 0x1f, 0xf8, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x00, 0x00};
// 'palette', 16x16px
const unsigned char epd_bitmap_palette[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x1e, 0xf8, 0x3f, 0xdc, 0x77, 0xfe, 0x63, 0xf6, 0x77, 0xfe,
    0x3e, 0x7e, 0x1c, 0x36, 0x00, 0x3c, 0x00, 0x78, 0x00, 0x70, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00};
// 'play', 16x16px
const unsigned char epd_bitmap_play[] PROGMEM = {
    0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08, 0x23, 0x04, 0x22, 0x84, 0x42, 0x42, 0x42, 0x22,
    0x42, 0x22, 0x42, 0x42, 0x22, 0x84, 0x23, 0x04, 0x10, 0x08, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00};
// 'robot', 16x16px
const unsigned char epd_bitmap_robot[] PROGMEM = {
    0x00, 0x00, 0x01, 0x80, 0x0f, 0xf0, 0x10, 0x08, 0x50, 0x0a, 0x72, 0x4e, 0x52, 0x4a, 0x10, 0x08,
    0x18, 0x18, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xf8, 0x20, 0x04, 0x20, 0x04, 0x2d, 0x54, 0x00, 0x00};
// 'rules', 16x16px
const unsigned char epd_bitmap_rules[] PROGMEM = {
    0x00, 0x00, 0x3f, 0xf0, 0x40, 0x08, 0x58, 0x04, 0x2b, 0xf4, 0x08, 0x04, 0x0b, 0xf4, 0x08, 0x04,
    0x0b, 0xf4, 0x08, 0x04, 0x08, 0x04, 0x08, 0xfc, 0x09, 0x02, 0x04, 0x02, 0x03, 0xfc, 0x00, 0x00};
// 'score', 16x16px
const unsigned char epd_bitmap_score[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x38, 0x1c, 0x48, 0x12, 0x48, 0x12, 0x28, 0x14, 0x18, 0x18,
    0x08, 0x10, 0x04, 0x20, 0x02, 0x40, 0x02, 0x40, 0x06, 0x60, 0x08, 0x10, 0x0f, 0xf0, 0x00, 0x00};
// 'settings', 16x16px
const unsigned char epd_bitmap_settings[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x14, 0x28, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x23, 0xc4,
    0x20, 0x04, 0x20, 0x04, 0x10, 0x08, 0x0c, 0x30, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20};
// 'twoplayers', 16x16px
const unsigned char epd_bitmap_twoplayers[] PROGMEM = {
    0x00, 0x00, 0x1e, 0xf0, 0x21, 0xf8, 0x40, 0xfc, 0x52, 0x6c, 0x52, 0x6c, 0x40, 0xfc, 0x21, 0xf8,
    0x1e, 0xf0, 0x00, 0x00, 0x3f, 0xbc, 0x40, 0x5e, 0x40, 0x5e, 0x40, 0x5e, 0x00, 0x00, 0x00, 0x00};
// 'wifi', 16x16px
const unsigned char epd_bitmap_wifi[] PROGMEM = {
    0x00, 0x00, 0x0f, 0xf0, 0x1f, 0xf8, 0x30, 0x0c, 0x60, 0x06, 0x47, 0xe2, 0x0f, 0xf0, 0x18, 0x18,
    0x10, 0x08, 0x03, 0xc0, 0x07, 0xe0, 0x04, 0x20, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00};

const unsigned char epd_bitmap_back[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x3f, 0xf8, 0x3f, 0xf8, 0x18, 0x18,
    0x0c, 0x18, 0x04, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x00};

const unsigned char epd_bitmap_OGS[] PROGMEM = {
    0x07, 0xe0, 0x1f, 0xf8, 0x38, 0x1c, 0x70, 0x0e, 0x60, 0x06, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x07, 0xe0};
const unsigned char epd_bitmap_time[] PROGMEM = {
    0x07, 0xf0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x10, 0x03, 0xe0, 0x01, 0xc0,
    0x01, 0xc0, 0x02, 0x20, 0x04, 0x90, 0x08, 0x08, 0x08, 0x88, 0x09, 0xc8, 0x0b, 0xe8, 0x07, 0xf0};
const unsigned char epd_bitmap_update[] PROGMEM = {
    0x00, 0x00, 0x27, 0xe0, 0x28, 0x10, 0x30, 0x08, 0x3c, 0x04, 0x00, 0x02, 0x00, 0x02, 0x40, 0x02,
    0x40, 0x02, 0x40, 0x00, 0x40, 0x00, 0x20, 0x3c, 0x10, 0x0c, 0x08, 0x14, 0x07, 0xe4, 0x00, 0x00};
const unsigned char epd_bitmap_size[] PROGMEM = {
    0xff, 0xff, 0x80, 0x01, 0x80, 0x3d, 0x80, 0x0d, 0x80, 0x15, 0x80, 0x25, 0x80, 0x41, 0x80, 0x01,
    0x80, 0x01, 0x82, 0x01, 0xa4, 0x01, 0xa8, 0x01, 0xb0, 0x01, 0xbc, 0x01, 0x80, 0x01, 0xff, 0xff};
const unsigned char epd_bitmap_end[] PROGMEM = {
    0x07, 0xe0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 0x40, 0x02, 0x87, 0xe1, 0x87, 0xe1, 0x87, 0xe1,
    0x87, 0xe1, 0x87, 0xe1, 0x87, 0xe1, 0x40, 0x02, 0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xe0};
const unsigned char epd_bitmap_confirm[] PROGMEM = {
    0x07, 0xe0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 0x40, 0x02, 0x80, 0x09, 0x80, 0x19, 0x80, 0x31,
    0x98, 0x61, 0x8c, 0xc1, 0x87, 0x81, 0x43, 0x02, 0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xe0};

// 'blitz', 16x16px
const unsigned char epd_bitmap_blitz[] PROGMEM = {
    0x00, 0x00, 0x00, 0x20, 0x00, 0x60, 0x00, 0xc0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0f, 0xf8,
    0x1f, 0xf0, 0x00, 0x60, 0x00, 0xc0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00};
// 'normal', 16x16px
const unsigned char epd_bitmap_normal[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x08, 0x88, 0x14, 0x14, 0x20, 0x02,
    0x50, 0x05, 0x44, 0x01, 0x42, 0x01, 0x41, 0x01, 0x40, 0x81, 0x3c, 0x1e, 0x00, 0x00, 0x00, 0x00};
// 'low', 16x16px
const unsigned char epd_bitmap_low[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x20, 0x46, 0x50, 0xa9, 0x8f, 0x11, 0x90, 0x91,
    0xa0, 0x46, 0x7f, 0xf8, 0x28, 0x50, 0x28, 0x50, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 480)
const unsigned char *bitmap_icons[20] = {
    epd_bitmap_play,
    epd_bitmap_score,
    epd_bitmap_settings,
    epd_bitmap_oneplayer,
    epd_bitmap_twoplayers,
    epd_bitmap_robot,
    epd_bitmap_wifi,
    epd_bitmap_lamp,
    epd_bitmap_rules,
    epd_bitmap_palette,
    epd_bitmap_back,
    epd_bitmap_OGS,
    epd_bitmap_time,
    epd_bitmap_update,
    epd_bitmap_size,
    epd_bitmap_end,
    epd_bitmap_confirm,
    epd_bitmap_blitz,
    epd_bitmap_normal,
    epd_bitmap_low,
};

// 'no-ogs', 8x8px
const unsigned char epd_bitmap_no_ogs[] PROGMEM = {
    0x3c, 0x42, 0xa5, 0x81, 0xbd, 0xa5, 0x42, 0x3c};
// 'no-wifi', 8x8px
const unsigned char epd_bitmap_no_wifi[] PROGMEM = {
    0x42, 0x24, 0x08, 0x10, 0x24, 0x42, 0x18, 0x18};
// 'ogs', 8x8px
const unsigned char epd_bitmap_ogs[] PROGMEM = {
    0x3c, 0x42, 0x81, 0x81, 0xff, 0xff, 0x7e, 0x3c};
// 'wifi', 8x8px
const unsigned char epd_bitmap_wifi_sm[] PROGMEM = {
    0x00, 0x7e, 0xc3, 0x81, 0x3c, 0x42, 0x18, 0x18};
// 'sprite_0', 8x8px
const unsigned char epd_bitmap_sprite_0[] PROGMEM = {
    0x00, 0x7f, 0x81, 0x81, 0x81, 0x7f, 0x00, 0x00};
// 'sprite_1', 8x8px
const unsigned char epd_bitmap_sprite_1[] PROGMEM = {
    0x00, 0x7f, 0x83, 0x83, 0x83, 0x7f, 0x00, 0x00};
// 'sprite_2', 8x8px
const unsigned char epd_bitmap_sprite_2[] PROGMEM = {
    0x00, 0x7f, 0x87, 0x87, 0x87, 0x7f, 0x00, 0x00};
// 'sprite_3', 8x8px
const unsigned char epd_bitmap_sprite_3[] PROGMEM = {
    0x00, 0x7f, 0x8f, 0x8f, 0x8f, 0x7f, 0x00, 0x00};
// 'sprite_4', 8x8px
const unsigned char epd_bitmap_sprite_4[] PROGMEM = {
    0x00, 0x7f, 0x9f, 0x9f, 0x9f, 0x7f, 0x00, 0x00};
// 'sprite_5', 8x8px
const unsigned char epd_bitmap_sprite_5[] PROGMEM = {
    0x00, 0x7f, 0xbf, 0xbf, 0xbf, 0x7f, 0x00, 0x00};
// 'sprite_6', 8x8px
const unsigned char epd_bitmap_sprite_6[] PROGMEM = {
    0x00, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 352)
const unsigned char *epd_bitmap_status[4] = {
    epd_bitmap_wifi_sm,
    epd_bitmap_no_wifi,
    epd_bitmap_ogs,
    epd_bitmap_no_ogs};

const unsigned char *epd_bitmap_battery[7] = {

    epd_bitmap_sprite_0,
    epd_bitmap_sprite_1,
    epd_bitmap_sprite_2,
    epd_bitmap_sprite_3,
    epd_bitmap_sprite_4,
    epd_bitmap_sprite_5,
    epd_bitmap_sprite_6};
