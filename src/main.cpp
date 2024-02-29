#include <Arduino.h>
#include "WiFiManager.h"
#include <ESPmDNS.h>

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

void reconnect_wifi()
{
  wm.resetSettings();

  Serial.println(F("Button Pressed, Starting Config Portal"));
  wm.setConfigPortalBlocking(false);
  wm.startConfigPortal("GoBoard");
  startTime = millis();
  portalRunning = true;
}

// Menu menu();
Menu menu = Menu("GoBoard");

void setup()
{
  menu.init();
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

  menu.showPage();

  Serial.println("Setup done");
}

void loop()
{
  // connectWiFi();

  menu.update_status(wifi_connected, false, 1);

  char readedChar = Serial.read();
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
  }
}
