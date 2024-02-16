#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SSD1306_NO_SPLASH


#include "Menu.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int _current_item = 0;
int _prev_item = 0;
int _next_item = 0;

// menu
// 0: main menu,
// 1: play submenu,
// 2: calculate
// 3: settings submenu
// 4: wifi
int _current_menu_level = 0;

void Menu::init()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    // for (;;)
    //   ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void Menu::_calculate_items()
{
  int count_length;
  switch (_current_menu_level)
  {
  case 0:
    count_length = 3;
    break;
  case 1:
    count_length = 3;
    break;
  case 2:
    count_length = 1;
    break;
  case 3:
    count_length = 4;
    break;
  }
  _prev_item = _current_item - 1;
  if (_prev_item < 0)
  {
    _prev_item = count_length - 1;
  }
  _next_item = _current_item + 1;
  if (_next_item >= count_length)
  {
    _next_item = 0;
  }
}

void Menu::_page_display(int icons[], char names[][20])
{

  _calculate_items();
  display.setTextColor(SSD1306_WHITE);

  // display.drawRect(0, 0, display.width(), 16, SSD1306_WHITE);

  // previous item
  display.setTextSize(1);
  display.setCursor(10, 17);
  display.write(0x18);
  display.write(0xFE);
  display.println(names[_prev_item]);

  // current item
  display.drawBitmap(2, 32, bitmap_icons[icons[_current_item]], 16, 16, SSD1306_WHITE);
  display.drawRoundRect(0, 29, display.width(), 22, 5, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(25, 32);
  // display.println(F("asddad"));
  display.println(names[_current_item]);

  // next item
  display.setTextSize(1);
  display.setCursor(10, 55);
  display.write(0x19);
  display.write(0xFE);
  display.println(names[_next_item]);
}

void Menu::show_calculate_page()
{
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("Please wait...");
}

void Menu::next_item()
{
  _current_item = _next_item;
  show_page();
}

void Menu::prev_item()
{
  _current_item = _prev_item;
  show_page();
}

void Menu::show_page()
{
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  // _calculate_items();

  switch (_current_menu_level)
  {
  case 0:
    show_main_page();
    break;
  case 1:
    show_play_page();
    break;
  case 2:
    show_calculate_page();
    break;
  case 3:
    show_settings_page();
    break;
  case 4:
    show_wifi_page();
  }

  display.display();
};

void Menu::show_main_page()
{
  char names[3][20] = {{"Play"}, {"Score"}, {"Settings"}};
  int icons[3] = {0, 1, 2};
  _page_display(icons, names);
}

void Menu::show_play_page()
{
  char names[3][20] = {{"Pair"}, {"Solo"}, {"Practice"}};
  int icons[3] = {4, 3, 5};
  _page_display(icons, names);
}

void Menu::show_settings_page()
{
  int icons[4] = {6, 7, 8, 9};
  char names[4][20] = {{"Wi-Fi"}, {"Bright"}, {"Rules"}, {"Colors"}};
  _page_display(icons, names);
}

void Menu::show_wifi_page()
{
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("Connect to WiFi");
  display.println("hotspot GoBoard!");
};

int Menu::select_item()
{
  switch (_current_menu_level)
  {
  // main menu
  case 0:
    switch (_current_item)
    {
      // play
    case 0:
      _current_menu_level = 1;
      break;

      // score
    case 1:
      _current_menu_level = 2;
      break;

      // settings
    case 2:
      _current_menu_level = 3;
      break;
    }

    break;

  // play submenu
  case 1:
    switch (_current_item)
    {
      // pair
    case 0:
      _current_menu_level = 0;
      break;

      // solo
    case 1:
      _current_menu_level = 0;
      break;

      // practice
    case 2:
      _current_menu_level = 0;
      break;
    }

    break;

  // score submenu
  case 2:
    switch (_current_item)
    {
    case 0:
      _current_menu_level = 0; // go to main menu, no variants
      break;
    }

    break;
  // Settings submenu
  case 3:
    switch (_current_item)
    {
      // wifi
    case 0:
      _current_menu_level = 4;
      break;

      // brightness
    case 1:
      _current_menu_level = 0;
      break;

      // rules
    case 2:
      _current_menu_level = 0;
      break;

      // colors
    case 4:
      _current_menu_level = 0;
      break;
    }

    break;

  // wifi
  case 4:
    _current_menu_level = 0; // go to main menu, no variants

    break;
  }
  _current_item = 0;
  show_page();

  return _current_menu_level;
}

void Menu::update_status(bool wifi, bool ogs, int battery)
{
  display.fillRect(0, 0, 128, 16, BLACK);
  display.setTextSize(1);
  display.setCursor(4, 4);
  switch (_current_menu_level)
  {
  case 0:
    display.print(F("Main Menu"));
    break;
  case 1:
    display.print(F("Play"));
    break;
  case 2:
    display.print(F("Score"));
    break;
  case 3:
    display.print(F("Settings"));
    break;
  case 4:
    display.print(F("WiFi connect"));
    break;
  }

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