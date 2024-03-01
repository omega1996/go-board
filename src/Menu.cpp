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
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    // for (;;)
    //   ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void Menu::showPage(MenuItem *root, int selectedIndex)
{

  // _title = root->label;
  display.clearDisplay();
  _currentMenu = *root;
  _currentIndex = selectedIndex;

  display.setTextColor(SSD1306_WHITE);

  // display.drawRect(0, 0, display.width(), 16, SSD1306_WHITE);

  // previous item
  int prevIndex = selectedIndex - 1;
  if (prevIndex < 0)
  {
    prevIndex = root->subItems.size() - 1;
  }
  display.setTextSize(1);
  display.setCursor(10, 17);
  display.write(0x18);
  display.write(0xFE);
  display.println(root->subItems[prevIndex].label);
  // display.println(selectedIndex);

  // current item
  display.drawBitmap(2, 32, root->subItems[selectedIndex].icon, 16, 16, SSD1306_WHITE);
  display.drawRoundRect(0, 29, display.width(), 22, 5, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(25, 32);
  // display.println(F("asddad"));
  display.println(root->subItems[selectedIndex].label);

  // next item
  int nextIndex = selectedIndex + 1;
  if (nextIndex >= root->subItems.size())
  {
    nextIndex = 0;
  }
  display.setTextSize(1);
  display.setCursor(10, 55);
  display.write(0x19);
  display.write(0xFE);
  display.println(root->subItems[nextIndex].label);
  display.display();
}

void Menu::nextItem()
{
  int nextIndex = _currentIndex + 1;
  if (nextIndex >= _currentMenu.subItems.size())
  {
    nextIndex = 0;
  }
  showPage(&_currentMenu, nextIndex);
}

void Menu::prevItem()
{
  int prevIndex = _currentIndex - 1;
  if (prevIndex < 0)
  {
    prevIndex = _currentMenu.subItems.size() - 1;
  }
  showPage(&_currentMenu, prevIndex);
}

bool Menu::selectItem()
{
  Serial.print("H?");
  if (_callbackCalling)
  {
    Serial.print("off callback");
    _callbackCalling = false;
    std::tuple<MenuItem *, int> lastItem = _menuStack.back();
    //_menuStack.pop_back();
    showPage(std::get<0>(lastItem), std::get<1>(lastItem));
    return false;
  }

  if (_currentMenu.subItems[_currentIndex].isBackButton)
  {
    Serial.print("isBackButton");

    // std::tuple<MenuItem *, int> lastItem = _menuStack.back();
    // _menuStack.pop_back();
    display.setTextSize(1);
    display.setCursor(20, 50);
    display.println("sdsd");
    // showPage(std::get<0>(lastItem), std::get<1>(lastItem));
    return false;
  }

  if (_currentMenu.subItems[_currentIndex].callback != NULL)
  {
    Serial.print("callback");
    _currentMenu.subItems[_currentIndex].callback(&display);
    _callbackCalling = true;
    return true;
  }

  if (_currentMenu.subItems[_currentIndex].subItems.size() > 0)
  {
    Serial.print("subItems");
    _menuStack.push_back(std::tuple<MenuItem *, int>{&_currentMenu, _currentIndex});
    showPage(&_currentMenu.subItems[_currentIndex], 0);
    return false;
  }
  return false;
}

void Menu::update_status(bool wifi, bool ogs, int battery)
{
  display.fillRect(0, 0, 128, 16, BLACK);
  display.setTextSize(1);
  display.setCursor(4, 4);

  display.print(_currentMenu.label);

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
