#pragma once
#include <vector>
#include <tuple>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "MenuIcons.h"

#define MAX_MENU_DEPTH 8

// Define structure for menu item
struct MenuItem
{
    const char *label;
    bool (*callback)(Adafruit_SSD1306 *display);
    const unsigned char *icon;
    std::vector<MenuItem> subItems;
    bool isBackButton;
};

class Menu
{

private:
    struct MenuState
    {
        MenuItem *parent;
        int selectedIndex;
    };
    MenuItem _rootMenu;

    std::vector<MenuState> _menuStack;

public:
    void init(MenuItem *root);

    MenuItem addItem(const char *label, const uint8_t *icon, bool (*callback)(Adafruit_SSD1306 *display));
    MenuItem addItem(const char *label, const uint8_t *icon, std::vector<MenuItem> *submenu);
    MenuItem addItem(bool isBackButton);

    void showPage();

    void nextItem();

    void prevItem();

    bool selectItem();

    void update_status(bool wifi, bool ogs, int battery);
};

extern Adafruit_SSD1306 display;

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
