#include <Arduboy2.h>
#include <Keyboard.h>
#include "payloads_windows.h"
#include "payloads_linux.h"
#include "payloads_macos.h"

String password;

Arduboy2 arduboy;

// Options init Menu
const char option_hid_menu0[] PROGMEM = "Windows";
const char option_hid_menu1[] PROGMEM = "Linux";
const char option_hid_menu2[] PROGMEM = "MacOS";

// Put init menu into an array
const char * const options_init_menu[] PROGMEM =
{
  option_hid_menu0,
  option_hid_menu1,
  option_hid_menu2,
};

// Options Payloads Windows
const char option_windows_menu0[] PROGMEM = "Hello World";
const char option_windows_menu1[] PROGMEM = "Fork bomb";

// Put options Payload Windows into an array
const char * const options_windows_menu[] PROGMEM =
{
  option_windows_menu0,
  option_windows_menu1,
};

// Options Payload Linux
const char option_linux_menu0[] PROGMEM = "Hello World";
const char option_linux_menu1[] PROGMEM = "Basic Terminal Commands";

// Put options Payload Linux into an array
const char * const options_linux_menu[] PROGMEM =
{
  option_linux_menu0,
  option_linux_menu1,
};

// Options Payload MacOS X
const char option_macos_menu0[] PROGMEM = "Passwordless SSH access & SSH Keys";

// Put options Payloads MacOS into an array
const char * const options_macos_menu[] PROGMEM =
{
  option_macos_menu0,
};

const uint8_t optionCount = sizeof(options_init_menu) / sizeof(options_init_menu[0]);
const uint8_t optionCount_windows = sizeof(options_windows_menu) / sizeof(options_windows_menu[0]);
const uint8_t optionCount_linux = sizeof(options_linux_menu) / sizeof(options_linux_menu[0]);
const uint8_t optionCount_macos = sizeof(options_macos_menu) / sizeof(options_macos_menu[0]);

const __FlashStringHelper * FlashString(const char * string)
{
  return reinterpret_cast<const __FlashStringHelper *>(string);
}

// The variable for storing the index of currently selected item.
uint8_t maxIndex = optionCount - 1;
uint8_t selectedIndex;

uint8_t mode = 0;
uint8_t optionMenuCount = optionCount;

void setup(void)
{
  arduboy.begin();
  Serial.begin(9600);
  Serial.println(mode);
  welcome_screen();  
  enterpin();
}

void loop(void)
{
  // Don't run until the next frame is ready
  if(!arduboy.nextFrame())
    return;

  // Update buttons so 'justPressed' works
  arduboy.pollButtons();

  // Selection Arrow
  if(arduboy.justPressed(UP_BUTTON))
  {
    if(selectedIndex > 0)
      --selectedIndex;
  }

  if(arduboy.justPressed(DOWN_BUTTON))
  {
    if(selectedIndex < maxIndex){
      ++selectedIndex;
  }
}

  // Options select payload
  selected_payload();

  // Options select menu
  if(arduboy.justPressed(A_BUTTON)){
    if(selectedIndex == 2 & mode == 0) {
      mode = 3;
      optionMenuCount = optionCount_macos;
      
      maxIndex = optionMenuCount - 1;
    }
     else if(selectedIndex == 1 & mode == 0) 
    {
      mode = 2;
      optionMenuCount = optionCount_linux;
       
      maxIndex = optionMenuCount - 1;    
    }
    else if(selectedIndex == 0 & mode == 0)
    {
      mode = 1;
      optionMenuCount = optionCount_windows;

      maxIndex = optionMenuCount - 1;
    }
  }

  // Back button  
  if(arduboy.justPressed(B_BUTTON))
  {  
    mode = 0;
    optionMenuCount = optionCount;
    
    maxIndex = optionMenuCount - 1;   
  }

  // Clear screen buffer
  arduboy.clear();

  // Set cursor position
  arduboy.setCursor(0, 0);

  // Loop through all options
  for(uint8_t i = 0; i < optionMenuCount; ++i)
  {
    // If the current option is the selected option;
    if(i == selectedIndex)
    {
      // Draw an arrow
      arduboy.print(F("> "));
    }
    else
    {
      // Otherwise just indent
      arduboy.print(F("  "));
    }

// Print the string in the array
// This is quite complicated if you don't know about pointers and casting.  
   if(mode == 0)
     arduboy.println(FlashString(pgm_read_word(&options_init_menu[i])));
   else if(mode == 1)
     arduboy.println(FlashString(pgm_read_word(&options_windows_menu[i])));
   else if(mode == 2)
     arduboy.println(FlashString(pgm_read_word(&options_linux_menu[i])));
   else if(mode == 3)
     arduboy.println(FlashString(pgm_read_word(&options_macos_menu[i])));  
  }

   // Update screen with buffer contents
   arduboy.display();
}

void selected_payload(){
  
  // MacOS X
  if(arduboy.justPressed(A_BUTTON) & selectedIndex == 0 & mode == 3) {
    PasswordlessSSH();
  }
    
  // Linux
  if(arduboy.justPressed(A_BUTTON) & selectedIndex == 0 & mode == 2) {
    HelloWorld_Gnome();
  }
  if(arduboy.justPressed(A_BUTTON) & selectedIndex == 1 & mode == 2) {
    BasicTerminalCommands();
  }

  // Windows
  if(arduboy.justPressed(A_BUTTON) & selectedIndex == 0 & mode == 1) {
    HelloWorld_Win();
  }
  if(arduboy.justPressed(A_BUTTON) & selectedIndex == 1 & mode == 1) {
    ForkBomb();
  }
}

void welcome_screen(void){
  // Clear screen buffer
  arduboy.clear();
  
  // Set cursor position
  arduboy.setCursor(0, 0);

  arduboy.println(F("ARDUBOY BadUSB attack"));

  arduboy.display();
  
  delay(3000);
}

void enterpin(void){  
  // Clear screen buffer
  arduboy.clear();
  
  // Set cursor position
  arduboy.setCursor(0, 0);

  arduboy.println(F("Enter pin:"));

  arduboy.display();
  
  while(1){
    arduboy.pollButtons();
    
    if(arduboy.justPressed(UP_BUTTON))
    {
      password = password + "A";
      arduboy.print(F("*"));
    }
    
    else if(arduboy.justPressed(DOWN_BUTTON))
    {
      password = password + "B";
      arduboy.print(F("*"));
    }

    else if(arduboy.justPressed(LEFT_BUTTON))
    {
      password = password + "C";
      arduboy.print(F("*"));
    }

    else if(arduboy.justPressed(RIGHT_BUTTON))
    {
      password = password + "D";
      arduboy.print(F("*"));
    }
    
    else if(arduboy.justPressed(A_BUTTON))
    {
      arduboy.clear();

      if(password != "DACB"){
        arduboy.clear();
        arduboy.println("Pin incorrect");
        arduboy.display();
        delay(2000);
        password = "";
        enterpin();
      }

      if(password == "DACB"){
        return;
      }
    }  
    arduboy.display();  
  }
}
