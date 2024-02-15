#pragma once
#include <Adafruit_SSD1306.h>

class Menu
{
public:
    void show_page();

    void show_main_page();

    void show_play_page();

    void show_settings_page();

    void show_calculate_page();
    void next_item();

    void prev_item();

    int select_item();

    void show_wifi_page();

    void update_status(bool wifi, bool ogs, int battery);

    void init();

private:
    int _current_item;
    int _prev_item;
    int _next_item;

    int _current_menu_level = 0;

    int _main_page_icons[3];
    char _main_page_names[3][20];

    // play page
    int _play_page_icons[3];
    char _play_page_names[3][20];

    // play page
    int _settings_page_icons[4];
    char _settings_page_names[4][20];

    void _calculate_items();

    void _page_display(int icons[], char names[][20]);

    void _show_status();
};

extern Adafruit_SSD1306 display;

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
