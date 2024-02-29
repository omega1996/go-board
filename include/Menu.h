#pragma once
#include <vector>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "MenuIcons.h"

#define MAX_MENU_ITEMS 8

// Define structure for menu item
struct MenuItem
{
    const char *label;
    bool hasSubMenu;
    bool (*callback)(void *);
    void *data;
    const unsigned char *icon;
    std::vector<MenuItem> subItems; 
};

class Menu
{

private:
    MenuItem _current_item;
    MenuItem _prev_item;
    MenuItem _next_item;

    const char *_title;
    MenuItem _items[MAX_MENU_ITEMS];

public:
    Menu(const char *title);
    void init();

    MenuItem addItem(const char *label, const uint8_t *icon, bool (*callback)(void *), void *data);
    MenuItem addItem(const char *label, const uint8_t *icon, MenuItem *submenu);

    void showPage();

    void nextItem();

    void prevItem();

    bool selectItem();

    void update_status(bool wifi, bool ogs, int battery);
};

extern Adafruit_SSD1306 display;

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
