#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SSD1306_NO_SPLASH

#include "Menu.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Menu::Menu()
{
}

void Menu::init(MenuItem *root)
{

  _rootMenu = *root;

  _menuStack.push_back({&_rootMenu, 0});
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    // for (;;)
    //   ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void Menu::showPage()
{

  display.clearDisplay();

  MenuState lastState = _menuStack.back();

  MenuItem root = *lastState.parent;

  int selectedIndex = lastState.selectedIndex;

  Serial.print(selectedIndex);

  display.setTextColor(SSD1306_WHITE);

  // display.drawRect(0, 0, display.width(), 16, SSD1306_WHITE);

  // previous item
  int prevIndex = selectedIndex - 1;
  if (prevIndex < 0)
  {
    prevIndex = root.subItems.size() - 1;
  }
  display.setTextSize(1);
  display.setCursor(10, 17);
  display.write(0x18);
  display.write(0xFE);
  display.println(root.subItems[prevIndex].label);
  // display.println(selectedIndex);

  // current item
  display.drawBitmap(2, 32, root.subItems[selectedIndex].icon, 16, 16, SSD1306_WHITE);
  display.drawRoundRect(0, 29, display.width(), 22, 5, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(25, 32);
  // display.println(F("asddad"));
  display.println(root.subItems[selectedIndex].label);

  // next item
  int nextIndex = selectedIndex + 1;
  if (nextIndex >= root.subItems.size())
  {
    nextIndex = 0;
  }
  display.setTextSize(1);
  display.setCursor(10, 55);
  display.write(0x19);
  display.write(0xFE);
  display.println(root.subItems[nextIndex].label);
  display.display();
}

void Menu::nextItem()
{
  MenuState &lastState = _menuStack.back();

  MenuItem root = *lastState.parent;

  lastState.selectedIndex++;
  if (lastState.selectedIndex >= root.subItems.size())
  {
    lastState.selectedIndex = 0;
  }

  // lastState.selectedIndex = nextIndex;

  showPage();
}

void Menu::prevItem()
{
  MenuState &lastState = _menuStack.back();

  MenuItem root = *lastState.parent;

  lastState.selectedIndex--;
  if (lastState.selectedIndex < 0)
  {
    lastState.selectedIndex = root.subItems.size() - 1;
  }
  showPage();
}

bool Menu::selectItem()
{

  MenuState lastState = _menuStack.back();

  MenuItem root = *lastState.parent;

  int selectedIndex = lastState.selectedIndex;

  Serial.println("H?:");
  if (_callbackCalling)
  {
    Serial.print("off callback");
    _callbackCalling = false;

    showPage();
    return false;
  }

  if (root.subItems[selectedIndex].isBackButton)
  {
    Serial.print("isBackButton");

    if (!_menuStack.empty())
    {
      _menuStack.pop_back();
      showPage();
    }
    return false;
  }

  if (root.subItems[selectedIndex].callback != NULL)
  {
    Serial.print("callback");
    root.subItems[selectedIndex].callback(&display);
    _callbackCalling = true;
    return true;
  }

  if (root.subItems[selectedIndex].subItems.size() > 0)
  {
    Serial.print("subItems");
    _menuStack.push_back({&root.subItems[selectedIndex], 0});
    showPage();
    return false;
  }
  return false;
}

void Menu::update_status(bool wifi, bool ogs, int battery)
{
  display.fillRect(0, 0, 128, 16, BLACK);
  display.setTextSize(1);
  display.setCursor(4, 4);

  MenuState lastState = _menuStack.back();

  MenuItem root = *lastState.parent;

  display.print(root.label);

  if (wifi)
  {
    display.drawBitmap(88, 4, epd_bitmap_status[0], 8, 8, SSD1306_WHITE);
  }
  else
  {
    display.drawBitmap(88, 4, epd_bitmap_status[1], 8, 8, SSD1306_WHITE);
  }

  if (ogs)
  {
    display.drawBitmap(102, 4, epd_bitmap_status[2], 8, 8, SSD1306_WHITE);
  }
  else
  {
    display.drawBitmap(102, 4, epd_bitmap_status[3], 8, 8, SSD1306_WHITE);
  }

  display.drawBitmap(116, 4, epd_bitmap_battery[battery], 8, 8, SSD1306_WHITE);
  display.display();
}

MenuItem Menu::addItem(const char *label, const uint8_t *icon, bool (*callback)(Adafruit_SSD1306 *display))
{
  MenuItem item = {label, callback, icon};
  return item;
}

MenuItem Menu::addItem(const char *label, const uint8_t *icon, std::vector<MenuItem> *submenu)
{
  // Создаем MenuItem, инициализируя его поля
  MenuItem item = {label, nullptr, icon, *submenu};

  return item;
}

MenuItem Menu::addItem(bool isBackButton)
{

  // Создаем MenuItem, инициализируя его поля
  MenuItem item = {"back", nullptr, bitmap_icons[0], {}, isBackButton};

  return item;
}
