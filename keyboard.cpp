#include "keyboard.h"

char *KeyboardDriver::AnsiKeyboardKeys[128];
void initKeys(char **keys);

KeyboardDriver::KeyboardDriver(InterruptManager *manager)
    : InterruptHandler(0x21, manager),
      dataport(0x60),
      commandport(0x64)
{
    // initialize keys
    initKeys(KeyboardDriver::AnsiKeyboardKeys);

    while (commandport.Read() & 0x1)
    {
        dataport.Read();
    }
    commandport.Write(0xAE); // activate interrupts
    commandport.Write(0x20); // get current state
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // set state
    dataport.Write(status);

    dataport.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver()
{
}

void printf(char *);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if (key < 0x80)
    {
        switch (key)
        {
        case 0xFA:
        case 0xC5:
        case 0x45:
            break;

        default:
            // char *msg = "\nKEYBOARD 0x00\t";
            // char *hex = "0123456789ABCDEF";
            // msg[12] = hex[(key >> 4) & 0x0F];
            // msg[13] = hex[key & 0x0F];
            // printf(msg);
            printf(AnsiKeyboardKeys[key]);
            break;
        }
    }
    return esp;
}

void initKeys(char **keys)
{
    keys[0x2] = "1";
    keys[0x3] = "2";
    keys[0x4] = "3";
    keys[0x5] = "4";
    keys[0x6] = "5";
    keys[0x7] = "6";
    keys[0x8] = "7";
    keys[0x9] = "8";
    keys[0xA] = "9";
    keys[0xB] = "0";
    keys[0xC] = "-";
    keys[0xD] = "=";
    keys[0xE] = "\b"; // backspace
    keys[0xF] = "\t"; // tab
    keys[0x10] = "q";
    keys[0x11] = "w";
    keys[0x12] = "e";
    keys[0x13] = "r";
    keys[0x14] = "t";
    keys[0x15] = "y";
    keys[0x16] = "u";
    keys[0x17] = "i";
    keys[0x18] = "o";
    keys[0x19] = "p";
    keys[0x1A] = "[";
    keys[0x1B] = "]";
    keys[0x2B] = "\\";
    keys[0x3A] = ""; // capslock
    keys[0x1E] = "a";
    keys[0x1F] = "s";
    keys[0x20] = "d";
    keys[0x21] = "f";
    keys[0x22] = "g";
    keys[0x23] = "h";
    keys[0x24] = "j";
    keys[0x25] = "k";
    keys[0x26] = "l";
    keys[0x27] = ";";
    keys[0x28] = "'";
    keys[0x1C] = "\n";
    keys[0x2A] = ""; // left shift
    keys[0x2C] = "z";
    keys[0x2D] = "x";
    keys[0x2E] = "c";
    keys[0x2F] = "v";
    keys[0x30] = "b";
    keys[0x31] = "n";
    keys[0x32] = "m";
    keys[0x33] = ",";
    keys[0x34] = ".";
    keys[0x35] = "/";
    keys[0x36] = ""; // right shift
    keys[0x48] = ""; // up arrow
    // TODO
    keys[0x39] = " "; // spacebar
}
