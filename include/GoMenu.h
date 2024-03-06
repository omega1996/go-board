
#pragma once

#include "Menu.h"
#include "CallbackManager.h"
#include "WiFiManager.h"

int timer_base_seconds = 600;
int timer_add_seconds = 30;
int periods = 5;
unsigned int timeout = 120; // seconds to run for
unsigned int startTime = millis();
bool portalRunning = false;
bool wifi_connected = false;

Menu menu = Menu();
CallbackManager manager;
WiFiManager wm;

bool show_timer(Adafruit_SSD1306 *display);
MenuItem createGameMenu();

bool reconnect_wifi(Adafruit_SSD1306 *display)
{

    // wm.resetSettings();
    Serial.println(F("Button Pressed, Starting Config Portal"));
    wm.setConfigPortalBlocking(false);
    wm.startConfigPortal("GoBoard");
    startTime = millis();
    portalRunning = true;
    display->clearDisplay();

    display->setTextSize(1);
    display->setCursor(0, 20);
    display->print(F("Connect to GoBoard wifi hostpot"));
    display->display();
    return true;
}

void connectWiFi()
{

    wifi_connected = wm.getWiFiIsSaved();
    if (portalRunning)
    {
        wm.process(); // do processing

        // check for timeout
        if ((millis() - startTime) > (timeout * 1000))
        {
            Serial.println("portaltimeout");
            wm.stopConfigPortal();
            portalRunning = false;
        }
    }
}

bool callback2(Adafruit_SSD1306 *display)
{

    // Serial.println(data);
    display->clearDisplay();
    display->display();
    return true;
}

bool start_game(Adafruit_SSD1306 *display)
{

    show_timer(display);

    MenuItem gameMenu = createGameMenu();
    menu.init(&gameMenu);

    // set up, down and select callback
    // callbacks call menu
    // back button shows timer again

    return false;
}

bool start_blitz_game(Adafruit_SSD1306 *display)
{
    timer_base_seconds = 30;
    timer_base_seconds = 5;
    return start_game(display);
}
bool start_live_game(Adafruit_SSD1306 *display)
{
    timer_base_seconds = 600;
    timer_base_seconds = 30;
    return start_game(display);
}
bool start_long_game(Adafruit_SSD1306 *display)
{
    timer_base_seconds = 86400;
    timer_base_seconds = 3600;
    return start_game(display);
}

bool show_timer(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    display->setTextSize(1);

    display->setCursor(0, 20);

    auto displayCallback = [display]() {

    };
    manager.setDisplayCallback(displayCallback);

    display->print(timer_base_seconds);

    display->display();
    return false;
}

MenuItem createRootMenu()
{
    MenuItem back = menu.addItem(true);

    // pair menu
    MenuItem blitz_start = menu.addItem("blitz", bitmap_icons[17], start_blitz_game);
    MenuItem live_start = menu.addItem("live", bitmap_icons[18], start_live_game);
    MenuItem long_start = menu.addItem("long", bitmap_icons[19], start_long_game);

    std::vector<MenuItem> start_submenu = {blitz_start, live_start, long_start, back};
    // play menu
    MenuItem pair = menu.addItem("pair", bitmap_icons[4], &start_submenu);
    MenuItem practice = menu.addItem("practice", bitmap_icons[5], callback2);
    MenuItem online = menu.addItem("online", bitmap_icons[11], callback2);
    std::vector<MenuItem> play_submenu = {pair, practice, online, back};

    // settings menu
    MenuItem wifi = menu.addItem("wifi", bitmap_icons[6], reconnect_wifi);
    MenuItem ogs = menu.addItem("ogs", bitmap_icons[11], callback2);
    MenuItem bright = menu.addItem("bright", bitmap_icons[7], callback2);
    MenuItem colors = menu.addItem("colors", bitmap_icons[9], callback2);
    MenuItem rules = menu.addItem("rules", bitmap_icons[8], callback2);
    MenuItem timer = menu.addItem("timer", bitmap_icons[12], callback2);
    MenuItem update = menu.addItem("update", bitmap_icons[13], callback2);
    MenuItem size = menu.addItem("size", bitmap_icons[14], callback2);
    std::vector<MenuItem> settings_submenu = {wifi, ogs, bright, colors, rules, timer, update, size, back};

    MenuItem play = menu.addItem("play", bitmap_icons[0], &play_submenu);
    MenuItem score = menu.addItem("score", bitmap_icons[1], callback2);
    MenuItem settings = menu.addItem("settings", bitmap_icons[2], &settings_submenu);

    std::vector<MenuItem> main_submenu = {play, score, settings};

    MenuItem root = menu.addItem("Main Menu", bitmap_icons[5], &main_submenu);

    return root;
}

MenuItem createGameMenu()
{
    MenuItem back = menu.addItem("back", bitmap_icons[10], show_timer); // back to game
    MenuItem score = menu.addItem("score", bitmap_icons[1], callback2);

    MenuItem confirm = menu.addItem("confirm", bitmap_icons[16], callback2);
    std::vector<MenuItem> resign_menu = {confirm, back};

    MenuItem stop = menu.addItem("resign", bitmap_icons[15], &resign_menu);
    std::vector<MenuItem> game_menu = {back, score, stop};
    MenuItem root = menu.addItem("Game", bitmap_icons[0], &game_menu);

    return root;
}
