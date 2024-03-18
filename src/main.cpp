#include <Arduino.h>
#include <ESPmDNS.h>

#include "Menu.h"
#include "CallbackManager.h"
#include "GoMenu.h"
#include "GyverButton.h"

#include <CD74HC4067.h>
#include "FastLED.h"

#define DOWN_BTN_PIN 1
#define OK_BTN_PIN 3
#define UP_BTN_PIN 2

// Светодиоды
#define NUM_LEDS 81 // кол-во светодиодов
#define DATA_PIN 14 // Пин светодиодной ленты

// мультиплексоры

const int s0InputPin = 5;    // Пин S0 мультиплексора
const int s1InputPin = 7;    // Пин S0 мультиплексора
const int s2InputPin = 9;    // Пин S0 мультиплексора
const int s3InputPin = 11;   // Пин S0 мультиплексора
const int analogMuxPin = 12; // 12 пин это ADC2_1, ближайший 10 пин ADC1_9

CD74HC4067 input_mux(s0InputPin, s1InputPin, s2InputPin, s3InputPin);

// регистры сдвига

const int latchPin = 40;
const int clockPin = 39;
const int dataPin = 15;
// кнопки

GButton downButton(DOWN_BTN_PIN);
GButton okButton(OK_BTN_PIN);
GButton upButton(UP_BTN_PIN);

bool menuLocked = false;

void readState()
{
  for (int i = 0; i < 9; ++i)
  {
    input_mux.channel(i);
    short state = 1;

    for (int j = 0; j < 9; ++j)
    {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, state >> 8);   // 2 регистр
      shiftOut(dataPin, clockPin, MSBFIRST, state & 0xff); // 1 регистр
      digitalWrite(latchPin, HIGH);
      delay(1);
      state = state << 1;
      int currentSensorValue = analogRead(analogMuxPin);

      int ledIndex = i * 9 + j;

      if (currentSensorValue > 100)
      {

        Serial.print(">");
        Serial.print(ledIndex);
        Serial.print(":");
        Serial.println(currentSensorValue);
      }
    }
  }
};

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
  // menu
  MenuItem root = createRootMenu();
  menu.init(&root);

  menu.showPage();

  // shift reg
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // mux
  pinMode(analogMuxPin, INPUT);

  Serial.println("Setup done");
}

void loop()
{

  readState();
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
    manager.move();
  }

  if (readedChar == 'b')
  {
    // ход черного
    manager.move();
  }
  upButton.tick();
  if (upButton.isClick())
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

  downButton.tick();
  if (downButton.isClick())
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

  okButton.tick();
  if (okButton.isClick())
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
