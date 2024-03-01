#include <Arduino.h>
#include "WiFiManager.h"
#include <ESPmDNS.h>
#include "MenuIcons.h"

#include "Menu.h"

WiFiManager wm;

unsigned int timeout = 120; // seconds to run for
unsigned int startTime = millis();
bool portalRunning = false;
bool wifi_connected = false;

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

  wm.resetSettings();
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

bool callback2(Adafruit_SSD1306 *display)
{

  // Serial.println(data);
  display->clearDisplay();
  display->display();
  return true;
}

MenuItem createRootMenu()
{
  int value2 = 10;

  // play menu
  MenuItem pair = menu.addItem("pair", bitmap_icons[4], callback2);
  MenuItem practice = menu.addItem("practice", bitmap_icons[5], callback2);
  MenuItem online = menu.addItem("online", bitmap_icons[11], callback2);
  MenuItem play_back = menu.addItem(true);
  // back?
  std::vector<MenuItem> play_submenu = {pair, practice, online, play_back};

  // settings menu
  MenuItem wifi = menu.addItem("wifi", bitmap_icons[6], reconnect_wifi);
  MenuItem ogs = menu.addItem("ogs", bitmap_icons[11], callback2);
  MenuItem bright = menu.addItem("bright", bitmap_icons[7], callback2);
  MenuItem colors = menu.addItem("colors", bitmap_icons[9], callback2);
  MenuItem rules = menu.addItem("rules", bitmap_icons[8], callback2);
  MenuItem timer = menu.addItem("timer", bitmap_icons[12], callback2);
  MenuItem update = menu.addItem("update", bitmap_icons[13], callback2);
  MenuItem size = menu.addItem("size", bitmap_icons[14], callback2);
  MenuItem settings_back = menu.addItem(true);

  std::vector<MenuItem> settings_submenu = {wifi, ogs, bright, colors, rules, timer, update, size, settings_back};

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
  // Serial.println(readedChar);
  // Serial.println(readedChar);

  if (readedChar == 'u')
  {
    menu.prevItem();
  }

  if (readedChar == 'd')
  {
    menu.nextItem();
  }

  if (readedChar == 'o')
  {
    bool selected_item = menu.selectItem();
    Serial.print("result: ");
    Serial.println(selected_item);
  }
}
