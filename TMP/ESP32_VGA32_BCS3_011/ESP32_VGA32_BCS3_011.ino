  /********************************************************************************************************************
 *  Für Deutsche
 *   
 *   Dies ist eine Emulation des Kleincomputerbausatzes Z1013. 
 *   Benötigt werden folgende Komponenten:
 *   - VGA32 V.1.4
 *   - VGA-Monitor mit VGA-Kabel urund Stromversorgungskabel
 *   - PS/2 Tastatur
 *   - 5V Stromversorgung mit Micro-USB-Kabel
 *   
 *   In dieser Version sind 16kB Arbeitsspeicher implementiert. Der EPROM-Bereich ist 4kB groß. Für den Bildspeicher 
 *   wurden 1kB reserviert. Die Ausgabe des Bildschirminhaltes erfolgt momentan noch auf die Serielle Schnittstelle. 
 *   Damit können aber die grafischen Symbole des Z1013 nicht dargestellt werden.
 *    
 *   Mein Dank gilt den Autoren der Bibliotheken 
 *   - Z80, Marat Fayzullin
 *   - DabGL, Fabrizio Di Vittorio
 *
 *   Bitte beachtet die Lizenzhinweise der Autoren!
 *   
 *   
 *   Ich kann keine Garantie für die Fehlerfreiheit des Programms geben. Für entstandene Schäden kann ich nicht
 *   Haftbar gemacht werden.
 *   
 *   Lizenz: Es ist gestattet, dieses Programm privat zu benutzen. Es ist nicht gestattet, dieses Programm für 
 *   kommerzielle Zwecke zu verwenden. Es ist nicht gestattet, das VG32-Modul mit dieser Software zu verkaufen.
 *   
 *   
 *   
 *
 ********************************************************************************************************************/

#include <Z80.h>
#include <fabgl.h>
#include <canvas.h>
#include "character_set.h"
#include "keyboard.h"
#include "memory.h"
#include "SD_card.h"
#include "progsel.h"


fabgl::PS2Controller    PS2Controller;
fabgl::VGA2Controller   DisplayController;
fabgl::Canvas           canvas(&DisplayController);


boolean Schrittmodus = false;
uint8_t  Taste;
uint8_t  Spalte1;
uint8_t  Zeile1;
uint8_t  Spalte2;
uint8_t  Zeile2;
uint8_t  zwSpalte1;
uint8_t  zwZeile1;
uint8_t  z80Port;
uint8_t  z80Val;
uint8_t  InputS7;


#define KassetteOut 12  // Output
#define KassetteIn 2    // Input  -  13 ist tabu, weil das CS der SD-Karte ist

auto keyboard = PS2Controller.keyboard();
//hw_timer_t *Timer3_Cfg = NULL;
hw_timer_t *Timer1_Cfg = NULL; 

int16_t counter = 0;
uint16_t Pruefsumme;
uint8_t bitcounter = 16;
uint8_t wordcounter = 16;
uint8_t onecounter = 2;
uint8_t halfcounter = 2;
uint16_t readword = 0;
uint16_t Ziel;
uint16_t Ende;
uint8_t Step;
uint16_t leader;
uint16_t firstleader = 100;

boolean ZK = false;
uint16_t zeig;
char ASCII;



//--------------------------------------------------------------------------------------

void IRAM_ATTR isr()
{
//  Serial.print(".");
  uint16_t timeX = timerRead(Timer1_Cfg);
  timerRestart(Timer1_Cfg);
//  Serial.println(timeX);
  if (counter > 4)  // die ersten 4 Werte werden ignoriert
  {
    uint8_t error = 0;
    if (timeX<3900 and timeX>2100 and Step == 0)
    { // Es wurde ein Pegelwechsel des Vorspanns erkannt
      // setze die Prüfgsumme auf 0
      Pruefsumme = 0;
      bitcounter = 0;
      wordcounter = 0;
      onecounter = 0;
      halfcounter = 0;
      readword = 0;
      leader++;
//      Serial.println(leader);
    }
    else if (timeX<1950 and timeX>1050 and Step == 20)
    { // jetzt wurde die zweite "1" erkannt
      onecounter++;
      Step = 30;
//      Serial.println("Y");
    }
    else if (timeX<1950 and timeX>1050 and Step == 0 and leader>firstleader)
    { // jetzt wurde eine "1" erkannt
      onecounter++;
      Step = 20;
//      Serial.println("X");
    }
    else if (timeX<1950 and timeX>1050 and Step == 30)
    { // das ist ein 1-Bit
      readword = readword >> 1;
      readword |= 0x8000;
      bitcounter++;
//      Serial.println("1");
    }
    else if (timeX<1001 and timeX>539 and halfcounter == 0 and Step == 30)
    { // das ist der erste Teil einer 0 
      halfcounter = 1;
    }
    else if (timeX<1001 and timeX>539 and halfcounter == 1 and Step == 30)
    { // jetzt wurde das ganze 0-Bit erkannt
      readword = readword >> 1;
      readword &= 0x7FFF;
      bitcounter++;
      halfcounter = 0;
//      Serial.println("0");
    }
//    else Error = 1;
//      Serial.println(readword, HEX);

    if (bitcounter == 16)
    { // ein Word wurde jetzt eingelesen
//      Serial.println(readword, HEX);
      if (wordcounter == 0)
      { // das erste word muss 0x0000 sein
        // hier kommt die Prüfung hin 
//        Serial.print("#");
        if (readword !=0) Serial.println("0-Fehler");
        wordcounter++;
      }
      else if (wordcounter==17)
      {
        // das ist die Prüfsumme
        // Serial.print("P");
        // Serial.print(readword, HEX);
        // Serial.println(Pruefsumme, HEX);
        if (readword - Pruefsumme == 0) 
        {
          Serial.println("OK");
        }
        else
        {
          Serial.println("P-Fehler");
        }
        if (Ziel>Ende) detachInterrupt(KassetteIn);
        Pruefsumme = 0;
        bitcounter = 0;
        wordcounter = 0;
        onecounter = 0;
        halfcounter = 0;
        readword = 0;
        leader = 0;
        firstleader = 8;
        counter = 0;
        Step = 0;
      }
      else if (wordcounter>0 and wordcounter<17)
      {
//       Serial.println(Ziel, HEX);
       // nun kann das Word abgelegt werden
        if (Ziel<=Ende) WrZ80(Ziel++, readword % 256);
        if (Ziel<=Ende) WrZ80(Ziel++, readword / 256);
        Pruefsumme += readword;
        wordcounter++;
      }
      bitcounter = 0;
    }
  }
  counter++;
}




// Memory write -- write the Value to memory location Addr
void WrZ80(register zword Addr, register byte Value)
{

  uint8_t blk = Addr / BLOCK_SIZE;
  Addr = Addr % BLOCK_SIZE;
  if (*(ptrRW+blk) == WRITE_READ) *(ptr[blk]+Addr) = Value;

  
  if (blk == 15 and Addr >= 0xB4)
  {

    //Serial.printf("Zeilen:%X \n", RdZ80(0x3C06));
    uint8_t Zeilen = RdZ80(0x3C06);
    uint16_t Zeichen = Zeilen * 30;
//    Serial.printf("Zeilen:%X  Zeichen:%X\n", Zeilen, Zeichen + 0xB4);
//
//    Serial.print("Block: ");
//    Serial.print(blk);
//    Serial.print("  Addr: ");
//    Serial.println(Addr, HEX);
    uint16_t zw = Addr - 0xB4;
//    Serial.print("  zw: ");
//    Serial.print(zw, HEX);
//    Serial.print("  Value: ");
//    Serial.println(Value, HEX);
    if ((Addr < Zeichen + 0xB4) or Zeichen == 0)
    {
      if (Value < 0xF7) PaintChar((uint8_t)(zw % 30), uint8_t(zw / 30), (uint8_t) Value);
    }
  }
}


// Memory read -- read the value at memory location Addr
byte RdZ80(register zword Addr) 
{
  uint8_t blk = Addr / BLOCK_SIZE;
  Addr = Addr % BLOCK_SIZE;
  return *(ptr[blk]+Addr);
}


// IO -- output the Value on the Port (currently does nothing)
// This is generally optional unless your code uses IO
// Can be left blank.
void OutZ80(register zword Port, register byte Value)
{
  z80Port = (byte) Port;
  z80Val = Value;
  if (z80Port == 8)
  {
    if (Spalte1 == Spalte2) Zeile1 = Zeile1 & Zeile2;
    if (Value == Spalte1) Taste = Zeile1;
    else if (Value == Spalte2) Taste = Zeile2;
    else Taste = 0x0F;
  }
  else if (z80Port == 2)
  {
    pinMode(KassetteOut, OUTPUT);    
    if ((Value & 0x80) == 0x80)
    {
      digitalWrite(KassetteOut, HIGH);
    }
    else
    {
      digitalWrite(KassetteOut, LOW);
    }
  }
}


// IO -- read a value from Port (currently defaults to 0)
// This is generally optional unless your code uses IO
// Can be left empty as long as it returns a byte.
byte InZ80(register zword Port)
{
  uint8_t Output = 0;
  if ((Port & 0x0F) == 2) // der Port für Input muss 2 sein
  {
    if ((z80Port) == 8) // der letze Ausgabeport muss 8 sein
    {
      if (z80Val == 7) InputS7++;
      else if (z80Val == 0) InputS7 = 0;
      Output = Taste;
    }
    if (digitalRead(KassetteOut) == HIGH)
    {
      Output |= 0x80; 
    }
    else
    {
      Output &= ~0x80; // also 0x7F
    }
    // vom Tonband einlesen
    if (digitalRead(KassetteIn) == HIGH)
    {
      Output |= 0x40;
    }
    else
    {
      Output &= ~0x40;
    }
  }
  return Output;
}


// Advanced -- called when an emulator-specific opcode of
// ED FE is encountered. Generally can be left empty.
void PatchZ80(register Z80 *R) {}

// create a CPU core object
Z80 cpu;

void setup()
{
  Serial.begin(115200);
  delay(500);

  // die Blöcke den Zeigern zuordnen, jetzt braucht nur der Zeiger geändert werden, um andere Programme zu starten
  for (uint8_t i=0; i < 64; i++)
  {
    ptr[i] = ram[i];
  }
  ptr[0] = eprom[0];
  ptr[1] = eprom[1];
  ptr[2] = eprom[2];
  ptr[3] = eprom[3];
  ptr[15] = ram_bild[0];

  // Zeiger auf die Berechtigung Lesen oder Lesen und Schreiben
  ptrRW = sto_rw;

  
  // Startbildschirm mit Auswahl der Datei anzeigen
  progsel(true);

 
  // Reset the CPU to 0x00 and zero the regs/flags
  ResetZ80(&cpu);

  PS2Controller.begin(PS2Preset::KeyboardPort0_MousePort1 );

  DisplayController.begin();
  DisplayController.setResolution(VGA_400x300_60Hz);    // VGA_640x480_60Hz);

  Spalte1 = 0;
  Zeile1 = 0xF;
  Spalte2 = 0x0;
  Zeile2  = 0xF;
  zwSpalte1 = 0;
  zwZeile1 = 0xF;

  keyboard = PS2Controller.keyboard();
  keyboard->setLayout(&fabgl::GermanLayout);

  Serial.println("Marke Setup End");
}


void loop() 
{
  if (Schrittmodus)
  {
    Serial.printf("PC:%X  AF:%X  BC:%X  DE:%X  HL:%X\n", cpu.PC.W, cpu.AF.W, cpu.BC.W, cpu.DE.W, cpu.HL.W);
    // warte auf eine Tastatureingabe
    while (!keyboard->virtualKeyAvailable()) {;}; 
    // ascii mode (show ASCIIl, VirtualKeys and scancodes)
    VirtualKeyItem item;
    if (keyboard->getNextVirtualKey(&item)) 
    {
      char ASCII = item.ASCII;
      String vkStr = keyboard->virtualKeyToString(item.vk);
      if (ASCII =0x0D and !item.down)
      {
        NextStep();
      }
    }
  }
  else NextStep();
}


void NextStep()
{
  // hier wird 1 Befehl ausgeführt
  StepZ80(&cpu);

//----------------------------------------------------------------------------------------  

  // Tastaturabfrage
  //    In diesem Abschnitt wird die Eingabe eines Programms per Tastatur simuliert
  if (cpu.PC.W == 0x00C6 and ZK == true)
  {
    ASCII = Programm[zeig];  
    zeig++;
    if (ASCII == '^') ASCII = 0x7F;
    if (ASCII == '#')
    {
      ASCII = 0x7F;
      ZK = false;
    }
    if (ASCII == 0x0D) ASCII = 0x7F;
    cpu.AF.W = ASCII*256;
    cpu.PC.W = 0x00DF;
  }
  else if (cpu.PC.W == 0x00C6)   // Tastatur wird abgefragt
  {
    cpu.AF.W = Z_FLAG;
    uint16_t RuecksprungAdr = 0x00DF;
    VirtualKeyItem item;
    // warte, bis eine Taste gedrückt wurde
    // bleibe in dieser Schleife, bis eine Taste gedrückt und wieder losgelassen wird
    do
    {
      if (!keyboard->virtualKeyAvailable())
      {
        keyboard->getNextVirtualKey(&item);
        boolean gueltig = false;
        // untersuche, ob diese Taste ein gültiges Zeichen oder Steuerbefehl ist
        //  lies den ASCII-Code ein und mache ggf. Anpassungen, wie <Enter> auf 0x7F
        if (!item.down and item.ASCII != 0) gueltig = true;
        if (!item.down and item.scancode[1] == 0x66) 
        { // Backspace
          item.ASCII = 0x5C;
          gueltig = true;
        }
        ASCII = item.ASCII;
        Serial.printf("%s: ", keyboard->virtualKeyToString(item.vk));
        Serial.printf("\tASCII = 0x%02X\t", item.ASCII);
        if (item.ASCII >= ' ') Serial.printf("'%c'", item.ASCII);
        Serial.printf("\t%s", item.down ? "DN" : "UP");
        Serial.printf("\t[");
        for (int i = 0; i < 8 && item.scancode[i] != 0; ++i)
        Serial.printf("%02X ", item.scancode[i]);
        Serial.printf("]");
        Serial.printf("\r\n");

// <F4> ---
        // Test auf <F4>, diese soll ein Testprogramm laden
        if ((item.scancode[0] == 0xF0) and (item.scancode[1] == 0x0C))
        {
          ZK = true;
          ASCII = Programm[0];  
          zeig = 1;
          gueltig = true;
        }
// <F8> --- Warmstart
        // Test auf <F8>
        else if ((item.scancode[0] == 0xF0) and (item.scancode[1] == 0x0A))
        {
          RuecksprungAdr = 0x01DC;
          gueltig = true;
          for (uint16_t adr = 0x3FF0; adr < 0x4010; adr=adr+8)
          {
            Serial.printf("%X  %X %X %X %X %X %X %X %X\n", adr, RdZ80(adr), RdZ80(adr + 1), RdZ80(adr + 2), RdZ80(adr + 3), RdZ80(adr + 4), RdZ80(adr + 5), RdZ80(adr + 6), RdZ80(adr + 7));
          }
        }
// <F9> --- Zeichen '<' kleiner als
        // Test auf <F9>
        else if ((item.scancode[0] == 0xF0) and (item.scancode[1] == 0x01))
        {
          ASCII = '<';
          gueltig = true;
        }
// <F10> --- Zeichen '>' größer als
        // Test auf <F10>
        else if ((item.scancode[0] == 0xF0) and (item.scancode[1] == 0x09))
        {
          ASCII = '>';
          gueltig = true;
        }
// <F3> ---
        // Test auf <F3>, diese soll ein Testprogramm laden
        else if ((item.scancode[0] == 0xF0) and (item.scancode[1] == 0x04))
        {
          Serial.println("Marke 1");
          DisplayController.end();
          delay(50);
          Serial.println("Tschuess ich gehe zu progsel");
          progsel(true);
          Serial.println("Guten Tag zurueck im Hauptprogramm");
          PS2Controller.begin(PS2Preset::KeyboardPort0_MousePort1 );
          DisplayController.begin();
          DisplayController.setResolution(VGA_400x300_60Hz);    // VGA_640x480_60Hz);
          // Bildschirm wiederherstellen
          for (uint16_t i=0x3CB4; i<0x3FFE; i++)
          {
            WrZ80(i,RdZ80(i));
          }
        }
        if (gueltig) break;
      }
    } while (1==1);
    if (ASCII == 0x0D) ASCII = 0x7F;
    cpu.AF.W = ASCII*256;
    cpu.PC.W = RuecksprungAdr;
  }
  
//----------------------------------------------------------------------------------------  

  if (cpu.PC.W == 0x00E0)
  {
    cpu.AF.W = Z_FLAG;
  //    if (keyboard->virtualKeyAvailable()) 
  //    {
  //      // ascii mode (show ASCIIl, VirtualKeys and scancodes)
  //      VirtualKeyItem item;
  //      if (keyboard->getNextVirtualKey(&item)) 
  //      {
  //        if (!item.down)
  //        {
  //          char ASCII = item.ASCII;
  //          String vkStr = keyboard->virtualKeyToString(item.vk);
  //          if (ASCII == 0x0D) ASCII = 0x7F;
  //          Serial.print("Vorher: ");
  //          Serial.print(cpu.AF.W, HEX);
  //          cpu.AF.W = ASCII*256;
  //          Serial.print("  Nachher: ");
  //          Serial.println(cpu.AF.W, HEX);
  //        }
  //      }
  //    }
      cpu.PC.W = 0x012F;
  }

 //----------------------------------------------------------------------------------------  

}

void PaintChar(uint8_t x, uint8_t y, uint8_t Zeichen)
{
  uint8_t OffsetX = 80;
  uint8_t OffsetY = 20;
  uint8_t Char_Size = 1;         // 1 | 2 | 3
  for (uint8_t j=0; j<8; j++)
  {
    uint8_t Zeile = character[Zeichen*8+j];
    for (uint8_t i=0; i<8; i++)
    {
      if ((Zeile & 0x80) > 0)
      {
        canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
        if (Char_Size >= 2)
        {
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
        }
        if (Char_Size >= 3)
        {
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
        }
     }
     else
     {
        canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
        if (Char_Size >= 2)
        {
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
        }
        if (Char_Size >= 3)
        {
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
        }
     }
      Zeile = Zeile << 1;
    }
  }
}
