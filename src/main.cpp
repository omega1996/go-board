#include <Arduino.h>
#include "WiFiManager.h"
#include <ESPmDNS.h>

#include "Menu.h"

#define LED_BUILTIN 15
#define TRIGGER_PIN 0

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

void reconnect_wifi()
{
  wm.resetSettings();

  Serial.println("Button Pressed, Starting Config Portal");
  wm.setConfigPortalBlocking(false);
  wm.startConfigPortal("GoBoard");
  startTime = millis();
  portalRunning = true;
}

// Menu menu();

Menu menu = Menu();

void setup()
{
  Serial.begin(115200);

  Serial.setDebugOutput(true);
  delay(1000);
  Serial.println("\n Starting");

  WiFi.mode(WIFI_STA);

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // wm.resetSettings();

  std::vector<const char *> wm_menu = {"wifi", "exit"};
  std::string wm_title = "GoBoard";
  wm.setMenu(wm_menu);

  // wm.setHostname("GoBoard");
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

  menu.init();

  menu.show_page();

  Serial.println("Setup done");
}

void loop()
{
  connectWiFi();

  menu.update_status(wifi_connected, false, 1);

  char readedChar = Serial.read();
  // Serial.println(readedChar);

  if (readedChar == 'u')
  {
    menu.prev_item();
  }

  if (readedChar == 'd')
  {
    menu.next_item();
  }

  if (readedChar == 'o')
  {
    int selected_item = menu.select_item();

    switch (selected_item)
    {
    case 4:
      reconnect_wifi();
      break;

    default:
      break;
    }
  }
}
