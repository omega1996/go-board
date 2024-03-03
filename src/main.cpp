#include <Arduino.h>
#include "WiFiManager.h"
#include <ESPmDNS.h>
#include "MenuIcons.h"

#include "Menu.h"
#include "CallbackManager.h"

WiFiManager wm;

unsigned int timeout = 120; // seconds to run for
unsigned int startTime = millis();
bool portalRunning = false;
bool wifi_connected = false;

bool menuLocked = false;

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

// Menu menu();
Menu menu = Menu();
CallbackManager manager;

bool callback2(Adafruit_SSD1306 *display)
{

  // Serial.println(data);
  display->clearDisplay();
  display->display();
  return true;
}

MenuItem createGameMenu()
{
  MenuItem back = menu.addItem("back", bitmap_icons[10], callback2); // back to game
  MenuItem score = menu.addItem("score", bitmap_icons[1], callback2);

  MenuItem confirm = menu.addItem("confirm", bitmap_icons[16], callback2);
  std::vector<MenuItem> resign_menu = {back, confirm};

  MenuItem stop = menu.addItem("resign", bitmap_icons[15], &resign_menu);
  std::vector<MenuItem> game_menu = {back, score, stop};
  MenuItem root = menu.addItem("Game", bitmap_icons[0], &game_menu);

  return root;
}

bool start_game(Adafruit_SSD1306 *display)
{
  display->clearDisplay();
  display->setTextSize(1);

  MenuItem gameMenu = createGameMenu();
  menu.init(&gameMenu);
  menu.showPage();
  // display->display();
  return true;
}

int timer_base_minutes = 5;
int timer_base_seconds = 0;

bool set_timer(Adafruit_SSD1306 *display)
{
  display->clearDisplay();

  display->setCursor(5, 20);
  display->setTextSize(2);

  display->print(timer_base_minutes);
  display->print(":");
  display->print(timer_base_seconds);

  static bool selectMode = false;

  auto displayCallback = [display]()
  {
    Serial.println(selectMode ? "1" : "0");
    display->drawLine(5, 28, 10, 28, WHITE);
    Serial.println("timer display:");
    Serial.println(selectMode ? "1" : "0");
    display->display();
  };
  manager.setDisplayCallback(displayCallback);

  auto timerSelectCallback = [display]()
  {
    Serial.println(selectMode ? "1" : "0");
    selectMode = !selectMode;
    display->drawRoundRect(0, 29, display->width(), 22, 5, SSD1306_WHITE);
    Serial.println(selectMode ? "1" : "0");
    Serial.println("timerSelect");
  };
  auto myNextCallback = [display]()
  {
    Serial.println("timer next");
    Serial.println(selectMode ? "1" : "0");
  };
  auto myPrevCallback = [display]()
  {
    Serial.println("timer prev");
    Serial.println(selectMode ? "1" : "0");
  };

  manager.setNextCallback(myNextCallback);
  manager.setPrevCallback(myPrevCallback);
  manager.setSelectCallback(timerSelectCallback);
  manager.display();
  return true;
}
bool set_rules(Adafruit_SSD1306 *display)
{
  display->clearDisplay();
  return true;
}

MenuItem createRootMenu()
{
  MenuItem back = menu.addItem(true);

  // pair menu
  MenuItem pair_start = menu.addItem("start", bitmap_icons[0], start_game);
  MenuItem pair_timer = menu.addItem("timer", bitmap_icons[12], set_timer);
  MenuItem pair_rules = menu.addItem("rules", bitmap_icons[8], set_rules);

  std::vector<MenuItem> start_submenu = {pair_start, pair_timer, pair_rules, back};
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

void setup()
{
  Serial.begin(115200);

  Serial.setDebugOutput(true);
  delay(1000);
  Serial.println("\n Starting");

  WiFi.mode(WIFI_STA);

  std::vector<const char *> wm_menu = {"wifi", "exit"};
  wm.setMenu(wm_menu);

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(60);

  wifi_connected = wm.autoConnect("GoBoard");

  if (!wifi_connected)
  {
    wm.setConfigPortalBlocking(false);
    wm.startConfigPortal("GoBoard");
    startTime = millis();
    portalRunning = true;
  }

  MenuItem root = createRootMenu();
  menu.init(&root);

  menu.showPage();

  Serial.println("Setup done");
}

void loop()
{
  // Serial.println("[APP] Free memory: " + String(esp_get_free_heap_size()) + " bytes");
  connectWiFi();

  menu.update_status(wifi_connected, false, 1);

  char readedChar = Serial.read();

  if (readedChar == 'u')
  {

    if (!menuLocked)
    {

      menu.prevItem();
    }
    else
    {
      manager.prev();
    }
  }

  if (readedChar == 'd')
  {
    if (!menuLocked)
    {

      menu.nextItem();
    }
    else
    {
      manager.next();
    }
  }

  if (readedChar == 'o')
  {
    if (!menuLocked)
    {

      bool selected_item = menu.selectItem();

      if (selected_item)
      {
        menuLocked = true;
      }
    }
    else
    {
      manager.select();
    }
  }
}
