#include <Arduino.h>
#include "WiFiManager.h"
#include <ESPmDNS.h>
#include "MenuIcons.h"

#include "Menu.h"
#include "CallbackManager.h"
#include "GoMenu.h"


bool menuLocked = false;

bool set_rules(Adafruit_SSD1306 *display)
{

  auto myPrevCallback = []()
  {
    // menuLocked = false;
  };
  manager.setSelectCallback(myPrevCallback);
  return false;
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
  if (menuLocked)
  {
    manager.display();
  }

  char readedChar = Serial.read();

  if (readedChar == 'w')
  {
    // ход белого
  }

  if (readedChar == 'b')
  {
    // ход черного
  }

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
