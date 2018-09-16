// Pultoscope.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
// für den cpp compiler

#define A0 0
#define A1 0
#define A2 0
#define A3 0
#define A4 0
#define A5 0
#define A6 0
#define A7 0

#define byte char
#define INPUT 0
#define INPUT_PULLUP 0
#define OUTPUT 0
#define HIGH 0
#define LOW 0
#define CHANGE 0
#define ADCH 0
#define ADCL 0


#define BLACK 0
#define WHITE 0

#define millis() 0
#define attachInterrupt(pin, func, edge)
#define delay(int)
#define delayMicroseconds(int)
#define digitalRead(int) int
#define digitalWrite(int, byte)
#define analogRead(a) (a)
#define pinMode(int, byte)
#define noInterrupts()
#define interrupts()
#define pinMode(int, byte)
#define eeprom_read_byte(int) 0
#define eeprom_write_byte(int, val)

#define int8_t char //int8_t +125 und -124

int ADCSRA = 0;
int ADMUX = 0;
int TIMSK1 = 0;
int OCIE1A = 0;
int OCR1A = 0;
int TCCR1A = 0;
int TCCR1B = 0;
int WGM12 = 0;
int CS12 = 0;
int CS10 = 0;

class _Serial
{
public:
  void _Serial::begin(int) {};
  int _Serial::available() { return 0; };
  int _Serial::read() { return 0; };
};
#define Serial _Serial() 


int B00001100 = 0;
// CyberLib
//int D11_Read = 0; 

//Adafruit_PCD8544
class Adafruit_PCD8544
{
public:
  Adafruit_PCD8544::Adafruit_PCD8544(int, int, int, int, int) {};
  void Adafruit_PCD8544::begin() {};
  void Adafruit_PCD8544::display() {};
  void Adafruit_PCD8544::clearDisplay() {};
  void Adafruit_PCD8544::setContrast(int) {};
  //Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
  void Adafruit_PCD8544::setTextSize(int s) {};
  void Adafruit_PCD8544::setCursor(int x0, int y0) {};
  void Adafruit_PCD8544::drawPixel(int x0, int y0, int color) {};
  void Adafruit_PCD8544::drawLine(int x0, int y0, int x1, int y1, int color) {};
  void Adafruit_PCD8544::fillCircle(int x0, int y0, int r, int color) {};
  void Adafruit_PCD8544::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color) {};
  
  void Adafruit_PCD8544::println(char[]) {};
  void Adafruit_PCD8544::println(char) {};
  void Adafruit_PCD8544::setTextColor(int color, int backgroudcolor = 0) {};
  void Adafruit_PCD8544::print(void*) {};
  void Adafruit_PCD8544::print(double, int = 0) {};
};

//PWM
#define pwmWrite(int, byte)

//FreqCount
class _FreqCount
{
public:
  void _FreqCount::begin(int) {};
  int _FreqCount::available() { return 0; };
  int _FreqCount::read() { return 0; };
};
#define FreqCount _FreqCount() 
#define InitTimersSafe()
#define SetPinFrequencySafe(a, b) (a)

///###################################################################

//pin definses
/*
Each of the 14 digital pins
used as an input or output,
using pinMode, digitalWrite, and digitalRead functions.They operate at 3.3 or 5 volts(depending on the model).Each pin can provide or receive a maximum of 40 mA and has an internal pull - up resistor(disconnected by default) of 20 - 50 kOhms.In addition, some pins have specialized functions :
*/
#define PIN_00 0  //0  D0  RX
#define PIN_01 1  //1  D1  TX
#define PIN_02 2  //2  D2  INT0 (Interrupt)
#define PIN_02_INT0 0
#define PIN_03 3  //3  D3  PWM - INT1 (Interrupt)
#define PIN_03_INT1 1
#define PIN_04 4  //4  D4
#define PIN_05 5  //5  D5  PWM
#define PIN_06 6  //6  D6  PWM
#define PIN_07 7  //7  D7
#define PIN_08 8  //8  D8
#define PIN_09 9  //9  D9  PWM
#define PIN_10 10 //10 D10 PWM - SPI SS
#define PIN_11 11 //11 D11 PWM - SPI MOSI
#define PIN_12 12 //12 D12 SPI MISO
#define PIN_13 13 //13 D13 LED - SPI SCK
#define PIN_14 A0 //14 A0
#define PIN_15 A1 //15 A1
#define PIN_16 A2 //16 A2
#define PIN_17 A3 //17 A3
//(ausgelagerte)
#define PIN_18 A4 //18 A4 - I2C SDA
#define PIN_19 A5 //19 A5 - I2C SCL
//(ausgelagerte)
#define PIN_20 A6 //A6 A6
#define PIN_21 A7 //A7 A7
/*
There is another pin on the board :
Reset. Bring this line LOW to reset the microcontroller
*/

// Arduino ino quelle
// Pultoscope for Arduino ProMini
//Страница проэкта  http://srukami.inf.ua/pultoscop_v25110.html


//#define DEBUG_MODE  0   // Degug settings comment in for debuging
#ifdef DEBUG_MODE
// this code ohnly compliling if DEBUG_MODE is define
#endif

#define overClockRate 16  // 16 MHz is default (enter MHz by changeing the Quarz, max 27MHz) //Частота на которой работает Ардуино
float ClockRate = overClockRate / 16.0;

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <FreqCount.h> 
#include <PWM.h>
//#include <CyberLib.h> // get info for read data is it faster?
#define led  9   //пин для генератора сигналов (не менять)
#define dds  10   //пин для генератора dds (не менять)
//###########################пользовательские настройки
//#define power 8 //пин который опрашивает кнопку включения
#define PowerOFF_Pin 14 //Pin to Power off
#define TimerPowerOFF 50 // x read cicles off pressed ok button to power off
#define InputStepLeft 13  //кнопка ЛЕВО(можно любой пин)
#define InputButtonOK 12    //кнопка ОК(можно любой пин)
#define InputStepRight 11 //кнопка ПРАВО(можно любой пин)
#define Battery_Volt_Pin A5 //любой своюодный аналоговый пин для измерения напряжения АКБ 

/// dreh encoder

//+++++++++


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 4, 3, 2);//пины к которым у вас подключен дисплей         

// todo per einstellung ermöglichen zu ändern kann im eeprom gespeichert werden? sollte es, fals zu gering eingestellt wird es schwer?
byte displayContrast = 52;//контрастность дисплея

// speedTTL
#define DefaulSpeedTTL 9600
#define DefaultPWNGeneratorFrequency 500

#define MinPWM 0
#define MaxPWM 255

#define MinMultiplikator 0
#define MaxMultiplikator 4

#define MinTrigger 20 // breite monitor
#define MaxTrigger 230 // breite monitor
#define StepTrigger 20 // breite monitor
byte Trigger = MinTrigger;   //уровень синхронизации 0 до 255 


// todo ist es wirlich 5,0
float VCC = 5.0;  //напряжение питания, меряем мультиметром

//###########################################################


// nokia 5110 > 84x48
// OLED Display >  128×64
#define monitorWidth 84 // breite monitor
#define monitorHight 48 // höhe monitor
//Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc

// see for sizes in Adafruit lib
#define printCharSize1Width 6 
#define printCharSize1Hight 8
#define printCharSize2Width (printCharSize1Width * 2) 
#define printCharSize2Hight (printCharSize1Hight * 2)
#define printCharSize3Width (printCharSize1Width * 3) 
#define printCharSize3Hight (printCharSize1Hight * 3)
// etc

#define displayBorderLeft 2 // ?
#define displayBorderRight displayBorderLeft // ?
#define displayBorderTop  0 // ?
#define displayBorderBottom  1 // ?
#define displayWidth (monitorWidth - (displayBorderLeft + displayBorderRight)) // breite viewport 
#define displayHight (monitorHight - (displayBorderTop + displayBorderBottom)) // höhe viewport
#define memorySize 700 // size of memory

#define MinMemoryPosition 0
#define MaxMemoryPosition (memorySize - displayWidth)
#define StepMemoryPosition 10

#define MinReadInterval 1
#define MaxReadInterval 9
#define DefaultReadInterval 7

#define MinFrequency 0
#define MaxFrequency 27000

#define MinTTLFrequency 0
#define MaxTTLFrequency 250000

byte Memory[memorySize];
int Memory_Position = 0; // Position der memoryanzeige

// multi usable variable
long gLongVariable; // in Pultoscope and PWMGenerator as Frequency, in TTL as TTLSpeed
int gIntVariable; // in Pultoscope as VMax, in PWMGenerator as PWM
byte gByteVariable; // in Pultoscope as ReadInterval, in PWMGenerator as Multiplikator

#define ADMUX_ExternRefVoltage 0b01100011
#define ADMUX_InternRefVoltage 0b11100011 // is 1.1V on (ATmega168/328) or 2.56V on (ATmega8)

void printInverted(char* text, bool inverted)
{
  if (inverted) display.setTextColor(WHITE, BLACK);
  display.println(text);
  if (inverted) display.setTextColor(BLACK);
}

// drehencoder implementieren
#define encoderClockPin  PIN_02 // interrupt pin = clock pin of encoder
#define encoderClockInterruptPin  PIN_02_INT0
#define encoderDataPin  4 // todo find other digital pin = data pin of encoder
#define encoderSwitchPin  PIN_03 // interrupt pin = switch pin of encoder
#define encoderSwitchInterruptPin  PIN_03_INT1 // interrupt pin = switch pin of encoder

void setupEncoderInterrupt() {
  pinMode(encoderClockPin, INPUT_PULLUP); // PullUp against floating input and to use interrupt LOW
  pinMode(encoderDataPin, INPUT_PULLUP); // PullUp against floating input
  pinMode(encoderSwitchPin, INPUT_PULLUP); // PullUp against floating input

  attachInterrupt(encoderClockInterruptPin, encoderCloskInterrupt, LOW); // low for debouncing (try rising or chnage)
  attachInterrupt(encoderSwitchInterruptPin, encoderSwitchInterrupt, CHANGE); // need a Harware debounce
}

byte debouncingTimer = 5 * ClockRate; // debouncing by 5 ms

volatile byte encoderPos = 0;
byte encoderPosLast = 0;
unsigned long lastClockInterupt = 0;
void encoderCloskInterrupt() {
  unsigned long currentInterupt = millis();
  if (currentInterupt - lastClockInterupt > debouncingTimer) // debouncing by 5 ms
  {
    lastClockInterupt = currentInterupt;
    if (digitalRead(encoderDataPin))
      --encoderPos; // left 
    else
      ++encoderPos; // right
  }
}

#define longClickTime 1500 // capacetor size relevant/ time for set OK Button is long klicked else its short
#define ClickState_NONE 0
#define ClickState_SHORT 1
#define ClickState_LONG 2
volatile byte encoderClickState = ClickState_NONE;
unsigned long lastSwitchInterupt = 0;
void encoderSwitchInterrupt() {
  // read click if old state was readed
  if (encoderClickState == ClickState_NONE)
  {
    // todo check the direction
    if (digitalRead(encoderSwitchPin))
    { // button released
      unsigned long currentInterupt = millis();
      if (currentInterupt - lastSwitchInterupt > debouncingTimer) // debouncing/stabilization time
      {
        if (currentInterupt - lastSwitchInterupt > (longClickTime * ClockRate))
          encoderClickState = ClickState_LONG;
        else
          encoderClickState = ClickState_SHORT;
      }
      lastSwitchInterupt = 0;
    }
    else if (!lastSwitchInterupt)
    { // button pressed
      lastSwitchInterupt = millis();
    }
  }
}

void checkEncoderPosition() {

  // check the left right buttons
  if (encoderPos != encoderPosLast)
  {
    byte encoderPosNew = encoderPos; // save volatile value
    bool directionRight = true;
    int dif = encoderPosNew - encoderPosLast;
    if (dif < 0)
    {
      dif *= -1;
      directionRight = false;
    }
    // if dif > x is a overflow
    if (dif > 100) directionRight = !directionRight;
    encoderPosLast = encoderPosNew;
    if (directionRight)
      stepRight();
    else
      stepLeft();
  }

  // todo add harsdare Debounce
  if (encoderClickState != ClickState_NONE)
  {
    if (encoderClickState == ClickState_SHORT) // todo check klick is short
      shortClick();
    else
      longClick();
    encoderClickState = ClickState_NONE; // reset state to read a new one
  }

}


// EEPROM Size ATmega328=1kb/ATmega168=512b 
//#define UPDATE_EEPROM // Comment in for write to eeprom
#define eepromVersion 1 // EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Version 1 // Legth=1 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Sinus 2 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Triangle 34 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Saw 66 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_NextFree 98 // Legth=1024/512-98 free space

byte EepromRead(int adress)
{
  return eeprom_read_byte((uint8_t*)adress);
}
void EepromRead(int adress, byte data[], bool reverse = false)
{
  EepromReadFixLength(adress, data, sizeof(data), reverse);
}
void EepromReadFixLength(int adress, byte data[], int length, bool reverse = false)
{
  int step = reverse ? -1 : 1;
  if (reverse) adress += length - 1;
  for (int i = 0; i < length; ++i, adress += step) {
    data[i] = EepromRead(adress);
  }
}
void EepromWrite(int adress, byte value)
{
  if (EepromRead(adress) != value)
    eeprom_write_byte((uint8_t*)adress, value);
}

int PowerOFF = 0;//состояние кнопки питания
void checkForShutdown() {
  /////////////////////////////////////////Hold ok button to power off
  if (digitalRead(InputButtonOK) == HIGH) 
  { ++PowerOFF; delay(10);
  // hold time is enoth to power of
  if (PowerOFF >= TimerPowerOFF)
  { digitalWrite(PowerOFF_Pin, LOW); }
  }
  else
  {
    PowerOFF = 0;
  }
}

void stepLeft() {

}

void stepRight() {

}

void shortClick() {

}

void longClick() {

}

#define MainMenu_Osziloscope 1
#define MainMenu_PWNGenerator 2
#define MainMenu_DDSGenerator 3
#define MainMenu_SerialTerminal 4
#define MainMenu_First MainMenu_Osziloscope
#define MainMenu_Last MainMenu_SerialTerminal
byte MainMenuPos = MainMenu_First;

#define OsziloscopeMenu_SettingVoltRef 1
#define OsziloscopeMenu_Setting_ReadInterval 2
#define OsziloscopeMenu_SettingScrollMemory 3
#define OsziloscopeMenu_SettingTrigger 4
#define OsziloscopeMenu_First OsziloscopeMenu_SettingVoltRef
#define OsziloscopeMenu_Last OsziloscopeMenu_SettingTrigger

#define PWMGeneratorMenu_PWM 1
#define PWMGeneratorMenu_Freq 2
#define PWMGeneratorMenu_First PWMGeneratorMenu_PWM
#define PWMGeneratorMenu_Last PWMGeneratorMenu_Freq

#define DDSGeneratorMenu_Sinus 1
#define DDSGeneratorMenu_Triangle 2
#define DDSGeneratorMenu_Saw 3
#define DDSGeneratorMenu_SawReverse 4
#define DDSGeneratorMenu_First DDSGeneratorMenu_Sinus
#define DDSGeneratorMenu_Last DDSGeneratorMenu_SawReverse
byte ManuPosition = 0; // selected Menu option

// todo buchstaben in zeile ermitteln 84px
#define DisplayTextStartPos 10 // starts with display of text

#define LANGUAGE_DE // change Language DE/RU/EN
#if defined(LANGUAGE_DE)
#define L_MainMenu_Pultoscope "Oszilloskop"
#define L_MainMenu_PWNGenerator "PWMGenerator"
#define L_MainMenu_DDSGenerator "DDSGenerator"
#define L_MainMenu_SerialTerminal "TTLTerminal"
#define L_MainMenu_Battery "Batterie"
#define L_MainMenu_ShortVoltage 'V'

#define L_PultoscopeMenu_ShortPause 'P'
#define L_PultoscopeMenu_Herz "Hz"
#define L_PultoscopeMenu_KiloHerz "kHz"

#define L_PWNGeneratorMenu_ShortPWM "PWM"

#define L_DDSGeneratorMenu_Sinus "Sinus"
#define L_DDSGeneratorMenu_Triangle "Dreieck"
#define L_DDSGeneratorMenu_Saw "Sägezahn"
#define L_DDSGeneratorMenu_SawReverse "Sägez. neg."
#define L_DDSGeneratorMenu_Frequence "Frequenz"

#define L_SerialTerminalMenu_Terminal "Terminal"
#define L_SerialTerminalMenu_Speed "Frequenz"
#define L_SerialTerminalMenu_Start "Mit ОК starten"
#elif defined(LANGUAGE_RU)
#define L_MainMenu_Pultoscope "Пультоскоп"
#define L_MainMenu_PWNGenerator "ШИМгенератор"
#define L_MainMenu_DDSGenerator "ЦВСгенератор"
#define L_MainMenu_SerialTerminal "ТТЛТерминал"
#define L_MainMenu_Battery "Батарея"
#define L_MainMenu_ShortVoltage 'В'

#define L_PultoscopeMenu_ShortPause 'П'
#define L_PultoscopeMenu_Herz "Гц"
#define L_PultoscopeMenu_KiloHerz "кГц"

#define L_PWNGeneratorMenu_ShortPWM "ШИМ"

#define L_DDSGeneratorMenu_Sinus "Синус"
#define L_DDSGeneratorMenu_Triangle "Треугольник"
#define L_DDSGeneratorMenu_Saw "Пила"
#define L_DDSGeneratorMenu_SawReverse "Пила Обр."
#define L_DDSGeneratorMenu_Frequence "Частота"

#define L_SerialTerminalMenu_Terminal "Терминал"
#define L_SerialTerminalMenu_Speed "Скорость"
#define L_SerialTerminalMenu_Start "Нажми ОК-старт"
#else // LANGUAGE_EN
#define L_MainMenu_Pultoscope "Oscilloscope"
#define L_MainMenu_PWNGenerator "PWMGenerator"
#define L_MainMenu_DDSGenerator "DDSGenerator"
#define L_MainMenu_SerialTerminal "TTLTerminal"
#define L_MainMenu_Battery "Battery"
#define L_MainMenu_ShortVoltage 'V'

#define L_PultoscopeMenu_ShortPause 'P'
#define L_PultoscopeMenu_Herz "Hz"
#define L_PultoscopeMenu_KiloHerz "kHz"

#define L_PWNGeneratorMenu_ShortPWM "PWM"

#define L_DDSGeneratorMenu_Sinus "Sinus"
#define L_DDSGeneratorMenu_Triangle "Triangle"
#define L_DDSGeneratorMenu_Saw "Sawtooth"
#define L_DDSGeneratorMenu_SawReverse "Sawt. neg."
#define L_DDSGeneratorMenu_Frequence "Frequence"

#define L_SerialTerminalMenu_Terminal "Terminal"
#define L_SerialTerminalMenu_Speed "Frequenz"
#define L_SerialTerminalMenu_Start "With ОК start"
#endif

#define GeneratorSignalIntervall 32

// setup
// todo setup darf keine schleife enthalten
void setup() {
#ifdef UPDATE_EEPROM
  if (EepromRead(eepromAdress_Version) != eepromVersion)
  {
    int adress = eepromAdress_Version;
    EepromUpdate(adress, eepromVersion);

    adress = eepromAdress_Sinus;
    byte dataSinus[GeneratorSignalIntervall] = { 1,6,15,29,48,69,92,117,143,168,191,212,229,243,251,255,254,248,237,222,203,181,156,131,106,81,59,39,22,10,3,1 };
    for (int i = 0; i < GeneratorSignalIntervall; ++i)
      EepromUpdate(adress++, dataSinus[i]);

    adress = eepromAdress_Triangle;
    byte dataTriangle[GeneratorSignalIntervall] = { 1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,255,239,223,207,191,175,159,143,127,111,95,79,63,47,31,15,1 };
    for (int i = 0; i < GeneratorSignalIntervall; ++i)
      EepromUpdate(adress++, dataTriangle[i]);

    adress = eepromAdress_Saw;
    byte dataSaw[GeneratorSignalIntervall] = { 1,9,17,25,33,41,49,57,65,73,81,89,97,105,113,121,129,137,145,153,161,169,177,185,193,201,209,217,225,235,245,255 };
    for (int i = 0; i < GeneratorSignalIntervall; ++i)
      EepromUpdate(adress++, dataSaw[i]);
  }
#endif // UPDATE_EEPROM

  setupEncoderInterrupt();

  pinMode(A4, INPUT);
  digitalWrite(OFF, HIGH);

  display.begin();
  display.setContrast(displayContrast);
  while (!InputButton(InputButtonOK)) {
    checkForShutdown();

    if (InputStep(InputStepLeft)) { delay(300); if (--MainMenuPos < MainMenu_First) { MainMenuPos = MainMenu_Last; } }
    else if (InputStep(InputStepRight)) { delay(300); if (++MainMenuPos > MainMenu_Last) { MainMenuPos = MainMenu_First; } }

    /////////////////////////////////////////удержание кнопки отключения 
    if (true) // if hase change
    {
      display.clearDisplay();
      display.setCursor(DisplayTextStartPos, 0);
      printInverted(L_MainMenu_Pultoscope, MainMenuPos == MainMenu_Osziloscope);
      display.setCursor(DisplayTextStartPos, 10);
      printInverted(L_MainMenu_PWNGenerator, MainMenuPos == MainMenu_PWNGenerator);
      display.setCursor(DisplayTextStartPos, 20);
      printInverted(L_MainMenu_DDSGenerator, MainMenuPos == MainMenu_DDSGenerator);
      display.setCursor(DisplayTextStartPos, 30);
      printInverted(L_MainMenu_SerialTerminal, MainMenuPos == MainMenu_SerialTerminal);
    }
    if (true) // volt chaged todo 5.0 sind ausgang für 5 volt was nicht immer stimmt
    {
      display.setCursor(0, 40);
      display.print(L_MainMenu_Battery);
      display.print('=');
      display.print(analogRead(Battery_Volt_Pin)*5.0 / 1024); // readVoltage
      display.print(L_MainMenu_ShortVoltage);
    }
    display.display();
  }

  if (MainMenuPos == MainMenu_Osziloscope) {
    // gLongVariable als Frequency
    gLongVariable = MinFrequency;
    // gLongVariable als VMax
    gIntVariable = 0;
    // gByteVariable als ReadInterval
    gByteVariable = DefaultReadInterval;
    ManuPosition = OsziloscopeMenu_First;
    FreqCount.begin(1000);
    ADMUX = ADMUX_ExternRefVoltage; // extern voltage referenc
  }
  else if (MainMenuPos == MainMenu_PWNGenerator) {
    // gLongVariable als Frequency
    gLongVariable = DefaultPWNGeneratorFrequency;
    // gIntVariable als PWM
    gIntVariable = MaxPWM / 2;
    // gByteVariable als Multiplikator
    gByteVariable = MinMultiplikator;
    ManuPosition = PWMGeneratorMenu_First;
    InitTimersSafe();
    bool success = SetPinFrequencySafe(led, gLongVariable);
  }
  else if (MainMenuPos == MainMenu_DDSGenerator) {
    ManuPosition = DDSGeneratorMenu_First;
    InitTimersSafe();
    bool success = SetPinFrequencySafe(led, 200000);
  }
  else if (MainMenuPos == MainMenu_SerialTerminal)
  {
    // gLongVariable als TTLSignal
    gLongVariable = DefaulSpeedTTL; //скорость терминала 
  }
  display.setTextColor(BLACK);
  delay(500);
}

bool InputStep(int direction)
{
  // todo hier kann es an den controler angepasst werden z.B. encoder
  return (digitalRead(direction) == HIGH);
}

bool InputButton(int button)
{
  // todo hier kann es an den controler angepasst werden z.B. encoder
  return (digitalRead(button) == HIGH);
}

void loop() {
  if (MainMenuPos == MainMenu_Osziloscope) { Oscilloscope(); }
  else if (MainMenuPos == MainMenu_PWNGenerator) { PWMGenerator(); }
  else if (MainMenuPos == MainMenu_DDSGenerator) { DDSGenerator(); }
  else if (MainMenuPos == MainMenu_SerialTerminal) { TTL(); }

  ///////////////////////////////////////// long press for reboot (todo if menu not in setup, then can be realocate )
  checkForShutdown();
}

//####################################### Oscilloscope
bool Pause_Mode = false; // Pause Flag

void Oscilloscope() {
  long Frequency = gLongVariable;
  int VMax = gIntVariable;
  byte ReadInterval = gByteVariable;
  // read input
  if (InputButton(InputButtonOK)) { if (++ManuPosition > OsziloscopeMenu_Last) { ManuPosition = OsziloscopeMenu_First; Pause_Mode = false; } } // next menu step, reset menu et end
  if (ManuPosition == OsziloscopeMenu_SettingVoltRef) {
    if (InputStep(InputStepLeft) || InputStep(InputStepRight)) {
      // toggle intern/extern
      if (ADMUX == ADMUX_InternRefVoltage)
        ADMUX = ADMUX_ExternRefVoltage; // extern voltage referenc
      else
        ADMUX = ADMUX_InternRefVoltage; // intern voltage referenc of 1.1V
    }
  }
  else if (ManuPosition == OsziloscopeMenu_Setting_ReadInterval) {
    if (InputStep(InputStepLeft)) { if (--ReadInterval < MinReadInterval) { ReadInterval = MinReadInterval; } }
    else if (InputStep(InputStepRight)) { if (++ReadInterval > MaxReadInterval) { ReadInterval = MaxReadInterval; } }
    gByteVariable = ReadInterval;
  }
  else if (ManuPosition == OsziloscopeMenu_SettingScrollMemory) {
    Pause_Mode = true; // auto Pause
    if (InputStep(InputStepLeft)) { if ((Memory_Position -= StepMemoryPosition) < MinMemoryPosition) { Memory_Position = MinMemoryPosition; } }
    else if (InputStep(InputStepRight)) { if ((Memory_Position += StepMemoryPosition) > MaxMemoryPosition) { Memory_Position = MaxMemoryPosition; } }
  }
  else if (ManuPosition == OsziloscopeMenu_SettingTrigger) {
    Memory_Position = 0; // scroll to start
    Pause_Mode = false; // release pause
    if (InputStep(InputStepLeft)) { if ((Trigger -= StepTrigger) < MinTrigger) { Trigger = MinTrigger; } }
    else if (InputStep(InputStepRight)) { if ((Trigger += StepTrigger) > MaxTrigger) { Trigger = MaxTrigger; } }
  }

  byte startPoint = Memory_Position;
  delay(5);
  if (!Pause_Mode)
  {
    //read data to memory
    ReadInputToMemory(ReadInterval);

    //####################################### find trigger start
    for (int i = 0; i < memorySize - displayWidth; ++i) {
      if (Memory[i] < Trigger && Memory[i] > Trigger)
      {
        startPoint = i;
        break;
      }
    }
    
    // found max voltage level
    for (int i = 0; i < memorySize; ++i)
    {
      if (VMax < Memory[i]) { VMax = Memory[i]; }
    }
    gIntVariable = VMax;

    // found frequency
    if (ADMUX == ADMUX_ExternRefVoltage) {
      if (((VMax*VCC) / 255) > 2.5) {
        Frequency = ReadFrequency() * ClockRate;
      }
      else {
        Frequency = CalcFrequency(ReadInterval) *ClockRate;
      }
    }
    else {
      Frequency = CalcFrequency(ReadInterval) * ClockRate;
    }
    gLongVariable = Frequency;
  }

  //####################################### printing
  display.clearDisplay();
  if (Pause_Mode) {
    // print memory position
    int Relation = memorySize / displayWidth;
    int Selector_Length = displayWidth / Relation;
    display.drawLine(Memory_Position / Relation, 8, Memory_Position / Relation + Selector_Length, 8, BLACK);
    // todo old display.drawLine(Memory_Position / Relation8, 9, Memory_Position / Relation + Selector_Length, 9, BLACK);
    // new is a full line
    display.drawLine(0, 9, monitorWidth, 9, BLACK);
  }
  else
  {
    //print synchronisation level indikator 
    // todo make treangle
    int circle_radius = 2;
    int circle_radius_border = 2;
    if (ManuPosition == OsziloscopeMenu_SettingTrigger) {
      //display.drawTriangle();
      display.fillCircle(monitorWidth - (2 * circle_radius), displayHight - Trigger / 7, circle_radius + circle_radius_border, BLACK);
      display.fillCircle(monitorWidth - (2 * circle_radius), displayHight - Trigger / 7, circle_radius, WHITE);
    }
    else {
      display.fillCircle(monitorWidth - (2 * circle_radius), displayHight - Trigger / 7, circle_radius, BLACK);
    }
  }

  //####### print graph from memory
  int xPos = 3;
  for (int i = startPoint; i < startPoint + displayWidth; ++i) {
    if (ReadInterval < 8)
      ++xPos;
    else if (ReadInterval == 8)
      xPos += 2;
    else if (ReadInterval == 9)
      xPos += 3;
    display.drawLine(xPos, displayHight - (Memory[i] / 7), xPos + 1, displayHight - (Memory[i + 1]) / 7, BLACK);
    display.drawLine(xPos + 1, (displayHight - (Memory[i] / 7)) + 1, xPos + 2, ((displayHight - Memory[i + 1]) / 7) + 1, BLACK);
  }

  // todo use size given by monitor
  //#######################################отрисовка графика
  for (byte i = displayHight; i > 5; i -= 7) {
    display.drawPixel(0, i, BLACK); 
    display.drawPixel(1, i, BLACK); 
    display.drawPixel(2, i, BLACK); }//разметка экрана  вертикальная
  //////////////////////////////////////////////////сетка
  byte widthPart1of4 = monitorWidth * (1 / 4);
  byte widthPart2of4 = monitorWidth * (2 / 4);
  byte widthPart3of4 = monitorWidth * (3 / 4);
  for (byte i = displayHight; i > 5; i -= 3) { 
    display.drawPixel(widthPart1of4, i, BLACK); 
    display.drawPixel(widthPart2of4, i, BLACK); 
    display.drawPixel(widthPart3of4, i, BLACK); }
  for (byte i = 3; i < monitorWidth; i += 3) { 
    display.drawPixel(i, 33, BLACK);  // todo why 19 and 33
    display.drawPixel(i, 19, BLACK); }
  //////////////////////////////////////////////////сетка

  //####################################### Print menu
  // print head line
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  if (ManuPosition == OsziloscopeMenu_SettingVoltRef)  display.setTextColor(WHITE, BLACK);
  if (ADMUX == ADMUX_ExternRefVoltage)  {
    display.print(VCC, 1);  }
  else  {
    display.print("1.1");  }
  display.setTextColor(BLACK);
  display.print(' ');
  if (ManuPosition == OsziloscopeMenu_Setting_ReadInterval)  display.setTextColor(WHITE, BLACK);
  display.print(ReadInterval);
  display.setTextColor(BLACK);
  display.print(' ');
  if (ManuPosition == OsziloscopeMenu_SettingScrollMemory) display.setTextColor(WHITE, BLACK);
  display.print(L_PultoscopeMenu_ShortPause);
  display.setTextColor(BLACK);

  if (Frequency < 1000L) {
    display.print(' ');  // todo format output
    display.print(Frequency);
    display.print(L_PultoscopeMenu_Herz);
  }
  else {
    if (Frequency < 10000)
      display.print((Frequency / 1000.0), 2);
    else if (Frequency < 100000)
      display.print((Frequency / 1000.0), 1);
    else
      display.print((Frequency / 1000.0), 0);
    display.print(L_PultoscopeMenu_KiloHerz);
  }

  // print bottom line
  // todo format festlegen
  display.setCursor(0, monitorHight - printCharSize1Hight);
  if (ADMUX == ADMUX_ExternRefVoltage) {
    display.print((VMax*VCC) / 255, 1);
  }
  else {
    display.print((VMax*1.1) / 255, 1);
  }
  display.print(L_MainMenu_ShortVoltage);
  //#######################################draw ing
  delay(200);
  display.display();
}

long CalcFrequency(byte ReadInterval)
{
  // Ermitlung der Frequenz zwischen 2 triggern
  bool searchRising = false;
  int Trigger_Size = -1;
  for (int i = 0; i < memorySize; ++i) {
    // serach low pegel to start rising
    if (Trigger_Size < 0) {
      if (!searchRising && Memory[i] < Trigger) { searchRising = true; }
      else if (searchRising && Memory[i] > Trigger) { Trigger_Size = i; searchRising = false; }
    }
    else {
      if (!searchRising && Memory[i] < Trigger) { searchRising = true; }
      else if (searchRising && Memory[i] > Trigger) {
        Trigger_Size = i - Trigger_Size;
        if (Trigger_Size > 1) break; // stop searching (by 1 search next, because is dangerous)
      }
    }
  }

  long Frec = 0;
  if (Trigger_Size > 1) // >1 da es sonst eine division durch null entstehen kann
  {
    if (ReadInterval == 1) { Frec = 1000000 / (Trigger_Size * 500); }//delitel 128
    else if (ReadInterval == 2) { Frec = 1000000 / (Trigger_Size * 3.27) / 32; }//delitel 128 ?
    else if (ReadInterval == 3) { Frec = 1000000 / (Trigger_Size * 3.27) / 32; }//delitel 128
    else if (ReadInterval == 4) { Frec = 1000000 / (Trigger_Size * 3.27) / 16; }//delitel 64
    else if (ReadInterval == 5) { Frec = 1000000 / (Trigger_Size * 3.27) / 4; }//delitel 16
    else if (ReadInterval == 6) { Frec = 1000000 / (Trigger_Size * 3.27) / 8; }//delitel 32
    else if (ReadInterval == 7) { Frec = 1000000 / (Trigger_Size * 3.27) / 2; }//delitel 8
    else /* if (ReadInterval >= 8) */ { Frec = 1000000 / ((Trigger_Size - 1) * 3.27); }//delitel 4
  }
  return Frec;
}

long ReadFrequency()
{
  if (FreqCount.available())
    return FreqCount.read();
  else
    return 0;
}

void ReadInputToMemory(byte ReadInterval) {
  //ADCSRA - ADC Control and Status Register A
  // [0-7] Bit position and description
  // [0-2] ADPS[2:0] : ADC Prescaler Select Bits
  // These bits determine the division factor between the system clock frequency and the input clock to the ADC.
  // [3] - ADIE: ADC Interrupt Enable
  // When this bit is written to one and the I - bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
  // [4] - ADIF : ADC Interrupt Flag
  // This bit is set when an ADC conversion completes and the Data Registers are updated.The ADC Conversion
  // Complete Interrupt is executed if the ADIE bit and the I - bit in SREG are set.ADIF is cleared by hardware when
  // executing the corresponding interrupt handling vector.Alternatively, ADIF is cleared by writing a logical one to
  // the flag.Beware that if doing a Read - Modify - Write on ADCSRA, a pending interrupt can be disabled.This also
  // applies if the SBI and CBI instructions are used.
  // [5] - ADATE: ADC Auto Trigger Enable
  // When this bit is written to one, Auto Triggering of the ADC is enabled.The ADC will start a conversion on a
  // positive edge of the selected trigger signal.The trigger source is selected by setting the ADC Trigger Select bits,
  // ADTS in ADCSRB.
  // [6] - ADSC : ADC Start Conversion
  // In Single Conversion mode, write this bit to one to start each conversion.
  // In Free Running mode, write this bit to one to start the first conversion.
  // The first conversion after ADSC has been written after the ADC has been enabled, or if ADSC is written at the
  // same time as the ADC is enabled, will take 25 ADC clock cycles instead of
  // the normal 13. This first conversion performs initialization of the ADC.
  // ADSC will read as one as long as a conversion is in progress.When the conversion is complete, it returns to
  // zero.Writing zero to this bit has no effect.
  // [7] - ADEN: ADC Enable
  // Writing this bit to one enables the ADC.By writing it to zero, the ADC is turned off.Turning the ADC off while a
  // conversion is in progress, will terminate this conversion.

  // change Prescalar
  if (ReadInterval >= 7)
    ADCSRA = 0b11100010; //delitel 4
  else if (ReadInterval == 6)
    ADCSRA = 0b11100011; //delitel 8
  else if (ReadInterval == 5)
    ADCSRA = 0b11100100; //delitel 16
  else if (ReadInterval == 4)
    ADCSRA = 0b11100101; //delitel 32
  else if (ReadInterval == 3)
    ADCSRA = 0b11100110; //delitel 64
  else //if (ReadInterval <= 2) 
    ADCSRA = 0b11100111; //delitel 128

                         
  noInterrupts();
  //  todo komment was genau passiert
  if (ReadInterval == 1) {
    for (int i = 0; i < memorySize; ++i) {
      while (!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA |= 0x10; // start ADC measurements // im forum gab es auch diese schreibweiseADCSRA |=(1<<ADSC); 
      delayMicroseconds(500); // todo why a delay?
      Memory[i] = ADCH;
      // fetch adc data from forum
      //byte lowData = ADCL; 
      //int Data = (ADCH << 8) | ADCL;
      //Data -= 0x200; // into a signed int
      //Data <<= 6; // form into a 16b signed int
    }
  }
  else {
    for (int i = 0; i < memorySize; ++i) {
      while (!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA |= 0x10;
      Memory[i] = ADCH;
    }
  }
  interrupts();
}


//#######################################generator
#define PWMGeneratorMenu_PWM 1
#define PWMGeneratorMenu_Freq 2

void PWMGenerator() {
  long Frequency = gLongVariable;
  int PWM = gIntVariable;
  byte Multiplikator = gByteVariable;
  
  if (InputButton(InputButtonOK)) {//переключение разряда выбора частоты 
    if (++Multiplikator > MaxMultiplikator)
    {
      Multiplikator = MinMultiplikator;
      if (++ManuPosition > PWMGeneratorMenu_Last) ManuPosition = PWMGeneratorMenu_First;
    }
    delay(debouncingTimer);
  }

  if (ManuPosition == PWMGeneratorMenu_PWM) {
    if (InputStep(InputStepLeft)) {
      if (--PWM < MinPWM) PWM = MinPWM;
      delay(debouncingTimer);
    }
    else if (InputStep(InputStepRight)) {
      if (++PWM > MaxPWM) PWM = MaxPWM;
      delay(debouncingTimer); 
    }
    gIntVariable = PWM;
  }
  else// if (ManuPosition == PWMGeneratorMenu_Freq) 
  {
    if (InputStep(InputStepLeft)) {
      Frequency -= (1 * (10 ^ Multiplikator));
      if (Frequency < MinFrequency) Frequency = MinFrequency;
      gLongVariable = Frequency;
      SetPinFrequencySafe(led, Frequency);
      delay(debouncingTimer); 
    }
    else if (InputStep(InputStepRight)) {
      Frequency += (1 * (10 ^ Multiplikator));
      // todo max frquency
      if (Frequency > MaxFrequency) Frequency = MaxFrequency;
      gLongVariable = Frequency;
      SetPinFrequencySafe(led, Frequency);
      delay(debouncingTimer);
    }
  }
  //////////// printing
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(L_PWNGeneratorMenu_ShortPWM);
  display.print('=');
  display.print(PWM * 100.0 / 255);
  display.print(" %");
  int pwmPercent = displayWidth * (PWM / 255.0);
  display.drawLine(0, 0, pwmPercent, 0, BLACK);
  display.drawLine(0, 1, pwmPercent, 1, BLACK);
  display.drawLine(0, 2, pwmPercent, 2, BLACK);
  display.drawLine(0, 15, pwmPercent, 15, BLACK);
  display.drawLine(0, 16, pwmPercent, 16, BLACK);
  display.drawLine(0, 17, pwmPercent, 17, BLACK);
  ///////////    
  display.setCursor(5, 20);
  display.setTextSize(2);
  long RealFrequency = Frequency*ClockRate;
  if (RealFrequency < 1000)
  {
    display.print(RealFrequency);

    display.setTextSize(1);
    display.println(L_PultoscopeMenu_Herz);
  }
  else
  {
    if (RealFrequency < 10000)
      display.print((RealFrequency / 1000.0), 2);
    else if (RealFrequency < 100000)
      display.print((RealFrequency / 1000.0), 1);
    else
      display.print((RealFrequency / 1000.0), 0);

    display.setTextSize(1);
    display.println(L_PultoscopeMenu_KiloHerz);
  }
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print(">>");

  if (ManuPosition == PWMGeneratorMenu_PWM) {
    display.print(L_PWNGeneratorMenu_ShortPWM);
    display.print(' ');
    display.print(PWM*100.0 / 255);
    display.print('%');
  }
  else //if(ManuPosition == PWMGeneratorMenu_Freq)
  {
    display.print(" x");
    display.print((1 * (10 ^ Multiplikator)) * ClockRate, 0);
  }
  display.print("<<");
  pwmWrite(led, PWM);
  delay(300);
  display.display();
}

/////////////////////DDS
void DDSGenerator() {

  if (ManuPosition == DDSGeneratorMenu_Sinus) EepromReadFixLength(eepromAdress_Sinus, Memory, GeneratorSignalIntervall);
  else if (ManuPosition == DDSGeneratorMenu_Triangle)  EepromReadFixLength(eepromAdress_Triangle, Memory, GeneratorSignalIntervall);
  else if (ManuPosition == DDSGeneratorMenu_Saw) EepromReadFixLength(eepromAdress_Saw, Memory, GeneratorSignalIntervall);
  else if (ManuPosition == DDSGeneratorMenu_SawReverse) EepromReadFixLength(eepromAdress_Saw, Memory, GeneratorSignalIntervall, true);

  display.setCursor(DisplayTextStartPos, 0);
  printInverted(L_DDSGeneratorMenu_Sinus, ManuPosition == DDSGeneratorMenu_Sinus);
  display.setCursor(DisplayTextStartPos, 10);
  printInverted(L_DDSGeneratorMenu_Triangle, ManuPosition == DDSGeneratorMenu_Triangle);
  display.setCursor(DisplayTextStartPos, 20);
  printInverted(L_DDSGeneratorMenu_Saw, ManuPosition == DDSGeneratorMenu_Saw);
  display.setCursor(DisplayTextStartPos, 30);
  printInverted(L_DDSGeneratorMenu_SawReverse, ManuPosition == DDSGeneratorMenu_SawReverse);
  // todo weitere frequencys
  //display.setCursor(0,40);
    //display.print(L_DDSGeneratorMenu_Frequence);
  //display.print('=');
  // display.print(57);
  // display.print(L_PultoscopeMenu_Herz);

  delay(100);
  display.display();

  GenerateSignal();
  if (++ManuPosition > DDSGeneratorMenu_Last)  ManuPosition = DDSGeneratorMenu_First;
  delay(200);
}

void GenerateSignal() {
  Memory_Position = GeneratorSignalIntervall; // ans ende setzen, damit gleich mit null begonnen wird
  while (!InputStep(InputStepRight)) {
    if (++Memory_Position == GeneratorSignalIntervall)
      Memory_Position = 0;
    pwmWrite(dds, Memory[Memory_Position]);
  }
}
/////////////////////end DDS

/////////////////////TTL
void TTL() {
  long speedTTL = gLongVariable;

  if (InputStep(InputStepRight)) { if ((speedTTL += 100) > MaxTTLFrequency) { speedTTL = MinTTLFrequency; } }
  else if (InputStep(InputStepLeft)) { if ((speedTTL -= 100) < MinTTLFrequency) { speedTTL = MaxTTLFrequency; } }
  gLongVariable = speedTTL;

  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(DisplayTextStartPos, 0);
  display.println(L_SerialTerminalMenu_Terminal);
  display.setCursor(DisplayTextStartPos, 10);
  display.println(L_SerialTerminalMenu_Speed);
  display.setCursor(DisplayTextStartPos, 20);
  display.print('-');
  display.print(speedTTL);
  display.println('+');
  display.setCursor(0, 30);
  display.println(L_SerialTerminalMenu_Start);

  if (InputButton(InputButtonOK)) {
    Serial.begin(speedTTL*ClockRate);
    display.clearDisplay();
    delay(100);
    char incomingBytes;
    int width = 0;
    int height = 0;
    display.setCursor(width, height);
    while (true) {
      // todo can use memory for history to scroll up and down
      // todo ohne history kann man auch setTextWrap(true) nutzen, spart man sich die zählung
      if (Serial.available() > 0) { // wait for data
        incomingBytes = Serial.read(); // Считывание байта в переменную incomeByte
        display.setCursor(width, height);
        display.print(incomingBytes); // Печать строки в буффер дисплея
        display.display();
        width += printCharSize1Width;
        // if end row go to next
        if (width == monitorWidth) { 
          width = 0; height += printCharSize1Hight;
          display.setCursor(width, height);
        }
        // if last row clean up and back to beginn
        if (height == monitorHight) {
          width = 0; height = 0;
          display.clearDisplay();
          delay(100);
          display.setCursor(width, height);
        }
      }
      ///////////////////////////////////////// long press for reboot (todo if menu not in setup, then can be realocate )
      //checkForShutdown(); // todo or to brack
      if (InputButton(InputButtonOK))
      {
        delay(100);
        break;
      }
    }
  }
}
/////////////////////end TTL
