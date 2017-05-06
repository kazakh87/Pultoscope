//Страница проэкта  http://srukami.inf.ua/pultoscop_v25110.html
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <FreqCount.h> 
#include <PWM.h>
#include <CyberLib.h>
#define led  9   //пин для генератора сигналов (не менять)
#define dds  10   //пин для генератора dds (не менять)
//#################№№№№№№####пользовательские настройки
#define power 8 //пин который опрашивает кнопку включения
#define OFF 14//пин который управляет ключем питания
#define  timepowerON 50 //время удержания кнопки выключения
#define levo 13  //кнопка ЛЕВО(можно любой пин)
#define ok 12    //кнопка ОК(можно любой пин)
#define pravo 11 //кнопка ПРАВО(можно любой пин)
#define akb A5 //любой своюодный аналоговый пин для измерения напряжения АКБ 
#define overclock 16  //Частота на которой работает Ардуино 
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 4, 3, 2);//пины к которым у вас подключен дисплей         

byte cont = 52;//контрастность дисплея
byte SinU = 30;   //уровень синхронизации 0 до 255 
int PWM = 128;//стартовое значение ШИМ от 0 до 255        
long frequency = 500; //стартовое значение частоты в Гц
float VCC = 5.0;  //напряжение питания, меряем мультиметром

                  //###########################################################

int d = 0;
byte menuDDS = 0;

int powerON = 0;//состояние кнопки питания
byte hag = 0;
int mnog = 0;
byte mass[701];
byte x = 0;
byte menu = 0;//переменная выбора меню 
bool opornoe = 1; //флаг опорного напряжения
byte pultoskop = 0; //флаг выбора генератора или осциллографа
byte razv = 6;
unsigned long count = 0;
byte sinX = 30;
byte meaX = 83;
int Vmax = 0;// максимальное напряжение 
byte sinhMASS = 0;
long countX = 0;
long speedTTL = 9600; //скорость терминала 
int prokr = 0;

void printInverted(char* text, bool inverted)
{
  if (inverted) display.setTextColor(WHITE, BLACK);
  display.println(text);
  if (inverted) display.setTextColor(BLACK);
}


// todo drehencoder implementieren
// EEPROM Size ATmega328=1kb/ATmega168=512b 
#define UPDATE_EEPROM // Comment in for write to eeprom
#define eepromVersion 1 // EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Version 1 // Legth=1 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Sinus 2 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Triangle 34 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_Saw 66 // Legth=32 EEPROM Version Protects the eeprom for unneeded write circuets
#define eepromAdress_NextFree 98 // Legth=1024/512-98 free space

byte EepromRead(int adress)
{
  return 0;// todo need implement
}
void EepromRead(int adress, byte data[], bool reverse = false)
{
  int step = reverse ? -1 : 1;
  if (reverse) adress += sizeof(data);
  for (int i = 0; i < sizeof(data) - 1; ++i, adress += step) {
    data[i] = EepromRead(adress);
  }
}
void _EepromWrite(int adress, byte value)
{
  // todo need implement
}
void EepromUpdate(int adress, byte value)
{
  if (EepromRead(adress) != value)
    _EepromWrite(adress, value);
}


void checkForShutdown() {
  /////////////////////////////////////////удержание кнопки отключения
  if (digitalRead(power) == HIGH) { powerON++; delay(10); }
  if (powerON >= timepowerON) { digitalWrite(OFF, LOW); }///отключаем питание
}

// todo add Debounce
volatile bool hasInputChange = false;
void stepLeft() {
  hasInputChange = true;

}

void stepRight() {
  hasInputChange = true;

}

void enterClicked() {

}

#define MainMenu_Pultoscope 1
#define MainMenu_PWNGenerator 1
#define MainMenu_DDSGenerator 1
#define MainMenu_SerialTerminal 1
byte MainMenuPos = 0;

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


// setup
// todo setup darf keine schleife enthalten
void setup() {
#ifdef UPDATE_EEPROM
  if (EepromRead(eepromAdress_Version) != eepromVersion)
  {
    int adress = eepromAdress_Version;
    EepromUpdate(adress, eepromVersion);

    adress = eepromAdress_Sinus;
    byte dataSinus[32] = { 1,6,15,29,48,69,92,117,143,168,191,212,229,243,251,255,254,248,237,222,203,181,156,131,106,81,59,39,22,10,3,1 };
    for (int i = 0; i < 32; ++i)
      EepromUpdate(adress++, dataSinus[i]);

    adress = eepromAdress_Triangle;
    byte dataTriangle[32] = { 1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,255,239,223,207,191,175,159,143,127,111,95,79,63,47,31,15,1 };
    for (int i = 0; i < 32; ++i)
      EepromUpdate(adress++, dataTriangle[i]);

    adress = eepromAdress_Saw;
    byte dataSaw[32] = { 1,9,17,25,33,41,49,57,65,73,81,89,97,105,113,121,129,137,145,153,161,169,177,185,193,201,209,217,225,235,245,255 };
    for (int i = 0; i < 32; ++i)
      EepromUpdate(adress++, dataSaw[i]);
  }
#endif // UPDATE_EEPROM

  pinMode(A4, INPUT);
  digitalWrite(OFF, HIGH);//включем питание 
                          //Serial.begin(9600);
  display.begin();
  display.setContrast(cont);
  while (digitalRead(ok) == LOW) {
    checkForShutdown();

    /////////////////////////////////////////удержание кнопки отключения 
    if (true) // if hase change
    {
      display.clearDisplay();
      display.setCursor(DisplayTextStartPos, 0);
      printInverted(L_MainMenu_Pultoscope, pultoskop == 0);
      display.setCursor(DisplayTextStartPos, 10);
      printInverted(L_MainMenu_PWNGenerator, pultoskop == 1);
      display.setCursor(DisplayTextStartPos, 20);
      printInverted(L_MainMenu_DDSGenerator, pultoskop == 2);
      display.setCursor(DisplayTextStartPos, 30);
      printInverted(L_MainMenu_SerialTerminal, pultoskop == 3);
    }
    if (true) // volt chaged todo 5.0 sind ausgang für 5 volt was nicht immer stimmt
    {
      display.setCursor(0, 40);
      display.print(L_MainMenu_Battery);
      display.print('=');
      display.print(analogRead(akb)*5.0 / 1024);
      display.print(L_MainMenu_ShortVoltage);
    }
    if (digitalRead(levo) == HIGH) { delay(300); pultoskop = pultoskop + 1; }
    if (digitalRead(pravo) == HIGH) { delay(300); pultoskop = pultoskop + 1; }
    if (pultoskop > 3) { pultoskop = 0; }
    delay(50);
    display.display();
  }
  if (pultoskop == 2) { InitTimersSafe(); bool success = SetPinFrequencySafe(led, 200000); }
  if (pultoskop == 0) { FreqCount.begin(1000); }
  if (pultoskop == 1) { InitTimersSafe(); bool success = SetPinFrequencySafe(led, frequency); }
  display.setTextColor(BLACK);
  delay(500);
}

void Zamer() {
  if (razv >= 6) { ADCSRA = 0b11100010; }//delitel 4
  else if (razv == 5) { ADCSRA = 0b11100011; }//delitel 8
  else if (razv == 4) { ADCSRA = 0b11100100; }//delitel 16
  else if (razv == 3) { ADCSRA = 0b11100101; }//delitel 32
  else if (razv == 2) { ADCSRA = 0b11100110; }//delitel 64
  else if (razv <= 1) { ADCSRA = 0b11100111; }//delitel 128
  if (razv == 0) {
    for (int i = 0; i < 700; i++) {
      while ((ADCSRA & 0x10) == 0);
      ADCSRA |= 0x10;
      delayMicroseconds(500);
      mass[i] = ADCH;
    }
  }
  else {
    for (int i = 0; i < 700; i++) {
      while ((ADCSRA & 0x10) == 0);
      ADCSRA |= 0x10;
      mass[i] = ADCH;
    }
  }

}
void loop() {
  checkForShutdown();

  /////////////////////////////////////////удержание кнопки отключения    
  if (pultoskop == 0) { Oscilloscope(); }
  if (pultoskop == 1) { Generator(); }
  if (pultoskop == 2) { DDSGenerator(); }
  if (pultoskop == 3) { TTL(); }
}
//#######################################режим Осциллографа
bool pause = false; //флаг режима паузы
void Oscilloscope() {
  if (opornoe == 0) { ADMUX = 0b11100011; }//выбор внутреннего опорного 1,1В
  if (opornoe == 1) { ADMUX = 0b01100011; }//Выбор внешнего опорного
  delay(5);
  if (!pause) { Zamer(); }
  //#######################################определение точки синхронизации
  bool flagSINHRO = 0;
  bool flagSINHRnull = 0;
  for (int y = 1; y < 255; y++) {
    if (flagSINHRO == 0) { if (mass[y] < SinU) { flagSINHRnull = 1; } }
    if (flagSINHRO == 0) { if (flagSINHRnull == 1) { if (mass[y] > SinU) { flagSINHRO = 1; sinhMASS = y; } } }
  }
  //#######################################определение точки синхронизации
  //максимальное значение сигнала##########################
  Vmax = 0;
  for (int y = 1; y < 255; y++) { if (Vmax < mass[y]) { Vmax = mass[y]; } }
  //максимальное значение сигнала##########################
  //#######################################определение точки синхронизации
  //#######################################отрисовка графика 
  if (!pause) {
    display.clearDisplay();
    display.fillCircle(80, 47 - SinU / 7, 2, BLACK);//рисуем уровень синхронизации    
    x = 3;
    for (int y = sinhMASS; y < sinhMASS + 80; y++) {
      if (razv < 7) { x++; }
      if (razv == 7) { x = x + 2; }
      if (razv == 8) { x = x + 3; }
      display.drawLine(x, 47 - mass[y] / 7, x + 1, 47 - mass[y + 1] / 7, BLACK);
      display.drawLine(x + 1, 47 - mass[y] / 7 + 1, x + 2, 47 - mass[y + 1] / 7 + 1, BLACK);
    }
    sinhMASS = 0;
  }
  if (pause) {
    display.clearDisplay();
    display.drawLine(prokr / 8, 8, prokr / 8 + 6, 8, BLACK);//шкала прокрутки
    display.drawLine(prokr / 8, 9, prokr / 8 + 6, 9, BLACK);//шкала прокрутки
    x = 3;
    for (int y = prokr; y < prokr + 80; y++) {
      if (razv < 7) { x++; }
      if (razv == 7) { x = x + 2; }
      if (razv == 8) { x = x + 3; }
      display.drawLine(x, 47 - mass[y] / 7, x + 1, 47 - mass[y + 1] / 7, BLACK);
      display.drawLine(x + 1, 47 - mass[y] / 7 + 1, x + 2, 47 - mass[y + 1] / 7 + 1, BLACK);
    }
  }
  //#######################################отрисовка графика
  for (byte i = 47; i > 5; i = i - 7) { display.drawPixel(0, i, BLACK); display.drawPixel(1, i, BLACK); display.drawPixel(2, i, BLACK); }//разметка экрана  вертикальная
 //////////////////////////////////////////////////сетка
  for (byte i = 47; i > 5; i = i - 3) { display.drawPixel(21, i, BLACK); display.drawPixel(42, i, BLACK); display.drawPixel(63, i, BLACK); }
  for (byte i = 3; i < 84; i = i + 3) { display.drawPixel(i, 33, BLACK); display.drawPixel(i, 19, BLACK); }
  //////////////////////////////////////////////////сетка
  //#######################################отрисовка menu
  if (menu == 0) {
    display.setCursor(0, 0);
    display.setTextColor(WHITE, BLACK);
    if (opornoe == 0) { display.print("1.1"); }
    if (opornoe == 1) { display.print(VCC, 1); }
    display.setTextColor(BLACK);
    display.print(' ');
    display.print(razv);
    display.print(' ');
    display.print(L_PultoscopeMenu_ShortPause);
    if (digitalRead(levo) == HIGH) { opornoe = !opornoe; }
    if (digitalRead(pravo) == HIGH) { opornoe = !opornoe; }
  }
  if (menu == 1) {
    display.setCursor(0, 0);
    if (opornoe == 0) { display.print("1.1"); }
    if (opornoe == 1) { display.print(VCC, 1); }
    display.print(' ');
    display.setTextColor(WHITE, BLACK); // 'inverted' text 
    display.print(razv);
    display.setTextColor(BLACK); // 'inverted' text
    display.print(' ');
    display.print(L_PultoscopeMenu_ShortPause);
    if (digitalRead(levo) == HIGH) { razv = razv - 1; if (razv == 255) { razv = 0; } }
    if (digitalRead(pravo) == HIGH) { razv = razv + 1; if (razv == 9) { razv = 8; } }
  }
  if (menu == 2) {
    display.setCursor(0, 0);
    if (opornoe == 0) { display.print("1.1"); }
    if (opornoe == 1) { display.print(VCC, 1); }
    display.print(' ');
    display.print(razv);
    display.print(' ');
    display.setTextColor(WHITE, BLACK); // 'inverted' text 
    display.print(L_PultoscopeMenu_ShortPause);
    display.setTextColor(BLACK);
    pause = true;
    if (digitalRead(levo) == HIGH) { prokr = prokr - 10; if (prokr < 0) { prokr = 0; } }
    if (digitalRead(pravo) == HIGH) { prokr = prokr + 10; if (prokr > 620) { prokr = 620; } }
  }
  if (menu == 3) {
    prokr = 0;
    pause = false;
    display.setCursor(0, 0);
    if (opornoe == 0) { display.print("1.1"); }
    if (opornoe == 1) { display.print(VCC, 1); }
    display.print(' ');
    display.print(razv);
    display.print(' ');
    display.print(L_PultoscopeMenu_ShortPause);
    if (digitalRead(levo) == HIGH) { SinU = SinU - 20; if (SinU < 20) { SinU = 20; } }
    if (digitalRead(pravo) == HIGH) { SinU = SinU + 20; if (SinU > 230) { SinU = 230; } }
    // todo change to triangle
    display.fillCircle(80, 47 - SinU / 7, 5, BLACK);
    display.fillCircle(80, 47 - SinU / 7, 2, WHITE);
  }
  if (digitalRead(ok) == HIGH) { menu++; if (menu == 4) { menu = 0; pause = false; } }//перебор меню
  if (FreqCount.available()) { count = FreqCount.read(); }//вывод частоты по готовности счетчика
                                                          //#######################################частоты сигнала
  byte Frec1 = 0;
  long Frec = 0;
  bool flagFrec1 = 0;
  bool flagFrec2 = 0;
  bool flagFrec3 = 0;
  for (int y = 1; y < 255; y++) {
    if (flagFrec1 == 0) { if (mass[y] < SinU) { flagFrec2 = 1; } }
    if (flagFrec1 == 0) { if (flagFrec2 == 1) { if (mass[y] > SinU) { flagFrec1 = 1; Frec1 = y; } } }
    if (flagFrec1 == 1) { if (mass[y] < SinU) { flagFrec3 = 1; } }
    if (flagFrec3 == 1) {
      if (mass[y] > SinU) {
        if (razv >= 6) { Frec = 1000000 / ((y - Frec1 - 1)*3.27); }//delitel 4
        if (razv == 5) { Frec = 1000000 / ((y - Frec1)*3.27) / 2; }//delitel 8
        if (razv == 4) { Frec = 1000000 / ((y - Frec1)*3.27) / 4; }//delitel 16
        if (razv == 3) { Frec = 1000000 / ((y - Frec1)*3.27) / 8; }//delitel 32
        if (razv == 2) { Frec = 1000000 / ((y - Frec1)*3.27) / 16; }//delitel 64
        if (razv == 2) { Frec = 1000000 / ((y - Frec1)*3.27) / 32; }//delitel 128
        if (razv == 1) { Frec = 1000000 / ((y - Frec1)*3.27) / 32; }//delitel 128
        if (razv == 0) { Frec = 1000000 / ((y - Frec1) * 500); }//delitel 128
        flagFrec1 = 0; flagFrec3 = 0;
      }
    }
  }
  //#######################################частоты сигнала
  display.setTextColor(BLACK);
  if (opornoe == 1) {
    if ((Vmax*VCC / 255) > 2.5) { countX = count*(overclock / 16.0); }
    if ((Vmax*VCC / 255) < 2.5) { countX = Frec*(overclock / 16.0); }
  }
  if (opornoe == 0) { countX = Frec*(overclock / 16.0); }

  if (countX < 1000) { display.print(' '); display.print(countX); display.print(L_PultoscopeMenu_Herz); }
  else if (countX >= 1000) { float countXK = countX / 1000.0; display.print(countXK, 1); display.print(L_PultoscopeMenu_KiloHerz); }

  if (opornoe == 1) {
    display.setCursor(0, 40); display.setTextColor(BLACK);
    display.print(Vmax*VCC / 255, 1);
  }
  if (opornoe == 0) {
    display.setCursor(0, 40); display.setTextColor(BLACK);
    display.print(Vmax*1.1 / 255, 1);
  }
  display.print(L_MainMenu_ShortVoltage);
  //#######################################отрисовка menu
  delay(200);
  display.display();
}

//#######################################режим ренератора
bool flag = false;
void Generator() {
  display.clearDisplay();
  if (flag) {//флаг выборов режима настройки ШИМ или Частоты
    if (digitalRead(levo) == HIGH) {
      if (--PWM < 0) PWM = 255;
      delay(3);//защита от дребезга

    }
    else if (digitalRead(pravo) == HIGH) {
      if (++PWM > 255) PWM = 0;
      delay(3);//защита от дребезга 
    }
  }
  else {//флаг выборов режима настройки ШИМ или Частоты
    if (digitalRead(levo) == HIGH) {
      frequency -= mnog;
      if (frequency < 0) frequency = 0;
      SetPinFrequencySafe(led, frequency);
      delay(3);//защита от дребезга 
    }
    else if (digitalRead(pravo) == HIGH) {
      frequency += mnog;
      // todo max frquency
      if (frequency > 27000) frequency = 27000;
      SetPinFrequencySafe(led, frequency);
      delay(3);//защита от дребезга 
    }
  }
  if (digitalRead(ok) == HIGH) {//переключение разряда выбора частоты 
    if (++hag >= 5) { hag = 0;    flag = false;    }
    delay(3);//защита от дребезга
  }
  ////////////
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(L_PWNGeneratorMenu_ShortPWM);
  display.print('=');
  display.print(PWM * 100.0 / 255);
  display.print(" %");
  double pwmPercent = 83 * PWM / 255.0;
  display.drawLine(0, 0, pwmPercent, 0, BLACK);
  display.drawLine(0, 1, pwmPercent, 1, BLACK);
  display.drawLine(0, 2, pwmPercent, 2, BLACK);
  display.drawLine(0, 15, pwmPercent, 15, BLACK);
  display.drawLine(0, 16, pwmPercent, 16, BLACK);
  display.drawLine(0, 17, pwmPercent, 17, BLACK);
  ///////////    
  display.setCursor(5, 20);
  display.setTextSize(2);
  long frequencyX = frequency*(overclock / 16.0);
  if (frequencyX < 1000)
  {
    display.print(frequencyX);
    display.setTextSize(1);
    display.println(L_PultoscopeMenu_Herz);
  }
  else
  {
    if (frequencyX < 10000)
      display.print((frequencyX / 1000.0), 2);
    else if (frequencyX < 100000)
      display.print((frequencyX / 1000.0), 1);
    else
      display.print((frequencyX / 1000.0), 0);

    display.setTextSize(1);
    display.println(L_PultoscopeMenu_KiloHerz);
  }
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print(">>");

  if (hag == 4) {//выбор  PWM
    display.print(L_PWNGeneratorMenu_ShortPWM);
    display.print(' ');
    display.print(PWM*100.0 / 255);
    display.print('%');
    flag = true;
  }
  else
  {
    if (hag == 0) {//выбор множителя частоты
      mnog = 1;
    }
    else if (hag == 1) {//выбор множителя частоты
      mnog = 10;
    }
    else if (hag == 2) {//выбор множителя частоты
      mnog = 100;
    }
    else if (hag == 3) {//выбор множителя частоты
      mnog = 1000;
    }
    display.print(" x");
    display.print(mnog * (overclock / 16.0), 0);
  }
  display.print("<<");
  pwmWrite(led, PWM);
  delay(300);
  display.display();
}
/////////////////////DDS

// todo auslagerung in den eeprom und lesen bei bedarf
byte* dots = nullptr;
// todo einmalig laden und im speicher ablegen, bzw aussicher
//byte dotsSpeicher[32] = {};
//byte sinM[32] = { 1,6,15,29,48,69,92,117,143,168,191,212,229,243,251,255,254,248,237,222,203,181,156,131,106,81,59,39,22,10,3,1 };
//byte trianglM[32] = { 1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,255,239,223,207,191,175,159,143,127,111,95,79,63,47,31,15,1 };
// todo kann man es auch umgehert lesen?
//byte pilaM[32] = { 1,9,17,25,33,41,49,57,65,73,81,89,97,105,113,121,129,137,145,153,161,169,177,185,193,201,209,217,225,235,245,255 };
//byte RpilaM[32] = { 250,246,238,230,222,214,206,198,190,182,174,166,158,150,142,134,126,118,110,102,94,86,78,70,62,54,41,33,25,17,9,1 };

void GenerateSignal() {
  while (digitalRead(pravo) == LOW) {
    pwmWrite(dds, dots[d++]);
    if (d == 32) d = 0;
  }
}

void DDSGenerator() {
  if (menuDDS == 0) menuDDS == 1;

  if (dots == nullptr) dots = new byte[32];

  if (menuDDS == 1) EepromRead(eepromAdress_Sinus, dots);
  else if (menuDDS == 2)  EepromRead(eepromAdress_Triangle, dots);
  else if (menuDDS == 3) EepromRead(eepromAdress_Saw, dots);
  else if (menuDDS == 4) EepromRead(eepromAdress_Saw, dots, true);

  display.setCursor(DisplayTextStartPos, 0);
  printInverted(L_DDSGeneratorMenu_Sinus, menuDDS == 1);
  display.setCursor(DisplayTextStartPos, 10);
  printInverted(L_DDSGeneratorMenu_Triangle, menuDDS == 2);
  display.setCursor(DisplayTextStartPos, 20);
  printInverted(L_DDSGeneratorMenu_Saw, menuDDS == 3);
  display.setCursor(DisplayTextStartPos, 30);
  printInverted(L_DDSGeneratorMenu_SawReverse, menuDDS == 4);
  //display.setCursor(0,40);
    //display.print(L_DDSGeneratorMenu_Frequence);
  //display.print('=');
  // display.print(57);
  // display.print(L_PultoscopeMenu_Herz);

  delay(100);
  display.display();
  GenerateSignal();
  menuDDS++;
  if (menuDDS >= 5)  menuDDS = 1;
  delay(200);
}
/////////////////////end DDS

/////////////////////TTL
void TTL() {
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
  if (digitalRead(pravo) == HIGH) { speedTTL = speedTTL + 100; }
  if (digitalRead(levo) == HIGH) { speedTTL = speedTTL - 100; }
  if (speedTTL < 0) { speedTTL = 250000; }
  if (speedTTL > 250000) { speedTTL = 0; }
  if (digitalRead(ok) == HIGH) {
    Serial.begin(speedTTL*(16 / overclock));
    display.clearDisplay();
    delay(100);
    display.display();
    int x = 0;
    int y = 0;
    while (1) {
      char incomingBytes;
      if (Serial.available() > 0) { // Если в буфере есть данные
        incomingBytes = Serial.read(); // Считывание байта в переменную incomeByte
        display.setCursor(x, y);
        display.print(incomingBytes); // Печать строки в буффер дисплея
        display.display(); x = x + 6;
        if (x == 84) { x = 0; y = y + 8; }
        if (y == 48) {
          x = 0; y = 0;
          display.clearDisplay();
          delay(100);
          display.display();
        }
      }
    }
  }
  delay(100);
  display.display();
}
/////////////////////end TTL
