/*
  Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com) - <http://www.fabgl.com>
  Copyright (c) 2019-2022 Fabrizio Di Vittorio.
  All rights reserved.


* Please contact fdivitto2013@gmail.com if you need a commercial license.


* This library and related software is available under GPL v3.

  FabGL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FabGL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FabGL.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "fabgl.h"



fabgl::VGA16Controller   DisplayController;
fabgl::Terminal          Terminal;
fabgl::PS2Controller     PS2Controller;


void Serial.printf(const char * format, ...)
{
  va_list ap;
  va_start(ap, format);
  int size = vsnprintf(nullptr, 0, format, ap) + 1;
  if (size > 0) {
    va_end(ap);
    va_start(ap, format);
    char buf[size + 1];
    vsnprintf(buf, size, format, ap);
    Serial.write(buf);
    Terminal.write(buf);
  }
  va_end(ap);
}


void printHelp()
{
  Serial.printf("\e[93m\n\nPS/2 Keyboard Virtual Keys\r\n");
  Serial.printf("Chip Revision: %d   Chip Frequency: %d MHz\r\n", ESP.getChipRevision(), ESP.getCpuFreqMHz());

  printInfo();

  Serial.printf("Commands:\r\n");
  Serial.printf("  1 = US Layout       2 = UK Layout       3 = DE Layout\r\n");
  Serial.printf("  4 = IT Layout       5 = ES Layout       6 = FR Layout\r\n");
  Serial.printf("  7 = BE Layout       8 = NO Layout\r\n");
  Serial.printf("  r = Reset\r\n");
  Serial.printf("  q = Scancode set 1  w = Scancode set 2\r\n");
  Serial.printf("  l = Test LEDs\r\n");
  Serial.printf("Various:\r\n");
  Serial.printf("  h = Print This help\r\n\n");
  Serial.printf("Use Serial Monitor to issue commands\r\n\n");
}


void printInfo()
{
  auto keyboard = PS2Controller.keyboard();

  if (keyboard->isKeyboardAvailable()) {
    Serial.printf("Device Id = ");
    switch (keyboard->identify()) {
      case PS2DeviceType::OldATKeyboard:
        Serial.printf("\"Old AT Keyboard\"");
        break;
      case PS2DeviceType::MouseStandard:
        Serial.printf("\"Standard Mouse\"");
        break;
      case PS2DeviceType::MouseWithScrollWheel:
        Serial.printf("\"Mouse with scroll wheel\"");
        break;
      case PS2DeviceType::Mouse5Buttons:
        Serial.printf("\"5 Buttons Mouse\"");
        break;
      case PS2DeviceType::MF2KeyboardWithTranslation:
        Serial.printf("\"MF2 Keyboard with translation\"");
        break;
      case PS2DeviceType::M2Keyboard:
        Serial.printf("\"MF2 keyboard\"");
        break;
      default:
        Serial.printf("\"Unknown\"");
        break;
    }
    Serial.printf("  Keyboard Layout: \"%s\"\r\n", keyboard->getLayout()->name);
  } else
    Serial.printf("Keyboard Error!\r\n");
}



void setup()
{
//  Serial.begin(115200);
  delay(500);  // avoid garbage into the UART
  Serial.write("\r\n\nReset\r\n");

  PS2Controller.begin(PS2Preset::KeyboardPort0);

  DisplayController.begin();
  DisplayController.setResolution(VGA_640x480_60Hz);

  Terminal.begin(&DisplayController);
  Terminal.enableCursor(true);

  //PS2Controller.keyboard()->setTypematicRateAndDelay(33, 500);

  printHelp();
}




void loop()
{
  auto keyboard = PS2Controller.keyboard();

  //static fabgl::VirtualKey lastvk = fabgl::VK_NONE; // avoid to repeat last vk

  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case 'h':
        printHelp();
        break;
      case '1':
        keyboard->setLayout(&fabgl::USLayout);
        printInfo();
        break;
      case '2':
        keyboard->setLayout(&fabgl::UKLayout);
        printInfo();
        break;
      case '3':
        keyboard->setLayout(&fabgl::GermanLayout);
        printInfo();
        break;
      case '4':
        keyboard->setLayout(&fabgl::ItalianLayout);
        printInfo();
        break;
      case '5':
        keyboard->setLayout(&fabgl::SpanishLayout);
        printInfo();
        break;
      case '6':
        keyboard->setLayout(&fabgl::FrenchLayout);
        printInfo();
        break;
      case '7':
        keyboard->setLayout(&fabgl::BelgianLayout);
        printInfo();
        break;
      case '8':
        keyboard->setLayout(&fabgl::NorwegianLayout);
        printInfo();
        break;
      case 'r':
        keyboard->reset();
        printInfo();
        break;
      case 'l':
        for (int i = 0; i < 8; ++i) {
          keyboard->setLEDs(i & 1, i & 2, i & 4);
          delay(1000);
        }
        delay(2000);
        if (keyboard->setLEDs(0, 0, 0))
          Serial.printf("OK\r\n");
        break;
      case 'q':
        keyboard->setScancodeSet(1);
        Serial.printf("Scancode Set = %d\r\n", keyboard->scancodeSet());
        break;
      case 'w':
        keyboard->setScancodeSet(2);
        Serial.printf("Scancode Set = %d\r\n", keyboard->scancodeSet());
        break;
    }
  }

  if (keyboard->virtualKeyAvailable()) {
    // ascii mode (show ASCIIl, VirtualKeys and scancodes)
    VirtualKeyItem item;
    if (keyboard->getNextVirtualKey(&item)) {
      Serial.printf("%s: ", keyboard->virtualKeyToString(item.vk));
      Serial.printf("\tASCII = 0x%02X\t", item.ASCII);
      if (item.ASCII >= ' ')
        Serial.printf("'%c'", item.ASCII);
      Serial.printf("\t%s", item.down ? "DN" : "UP");
      Serial.printf("\t[");
      for (int i = 0; i < 8 && item.scancode[i] != 0; ++i)
        Serial.printf("%02X ", item.scancode[i]);
      Serial.printf("]");
      Serial.printf("\r\n");
    }
  }

}
