#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager *manager)
    : InterruptHandler(0x21, manager),
      dataport(0x60),
      commandport(0x64),
      shiftActive(false)
{

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

    // handle key press for current keyboard
    handleAnsiKeyPress(key);

    // char *msg = "\nKEYBOARD 0x00\t";
    // char *hex = "0123456789ABCDEF";
    // msg[12] = hex[(key >> 4) & 0x0F];
    // msg[13] = hex[key & 0x0F];
    // printf(msg);

    // if (key < 0x80)
    // {
    //     switch (key)
    //     {
    //     case 0xFA:
    //     case 0xC5:
    //     case 0x45:
    //         break;

    //     default:

    //         break;
    //     }
    // }
    return esp;
}

void KeyboardDriver::handleAnsiKeyPress(uint8_t key)
{
    switch (key)
    {
    case 0x2:
        shiftActive ? printf("!") : printf("1");
        break;
    case 0x3:
        shiftActive ? printf("@") : printf("2");
        break;
    case 0x4:
        shiftActive ? printf("#") : printf("3");
        break;
    case 0x5:
        shiftActive ? printf("$") : printf("4");
        break;
    case 0x6:
        shiftActive ? printf("%") : printf("5");
        break;
    case 0x7:
        shiftActive ? printf("^") : printf("6");
        break;
    case 0x8:
        shiftActive ? printf("&") : printf("7");
        break;
    case 0x9:
        shiftActive ? printf("*") : printf("8");
        break;
    case 0xA:
        shiftActive ? printf("(") : printf("9");
        break;
    case 0xB:
        shiftActive ? printf(")") : printf("0");
        break;
    case 0xC:
        shiftActive ? printf("_") : printf("-");
        break;
    case 0xD:
        shiftActive ? printf("+") : printf("=");
        break;
    case 0xE: // BACKSPACE
        shiftActive ? printf("\b\b\b\b") : printf("\b");
        break;
    case 0xF:                                    // TAB
        shiftActive ? printf("") : printf("\t"); // TODO: reverse tab
        break;
    case 0x10:
        shiftActive ? printf("Q") : printf("q");
        break;
    case 0x11:
        shiftActive ? printf("W") : printf("w");
        break;
    case 0x12:
        shiftActive ? printf("E") : printf("e");
        break;
    case 0x13:
        shiftActive ? printf("R") : printf("r");
        break;
    case 0x14:
        shiftActive ? printf("T") : printf("t");
        break;
    case 0x15:
        shiftActive ? printf("Y") : printf("y");
        break;
    case 0x16:
        shiftActive ? printf("U") : printf("u");
        break;
    case 0x17:
        shiftActive ? printf("I") : printf("i");
        break;
    case 0x18:
        shiftActive ? printf("O") : printf("o");
        break;
    case 0x19:
        shiftActive ? printf("P") : printf("p");
        break;
    case 0x1A:
        shiftActive ? printf("{") : printf("[");
        break;
    case 0x1B:
        shiftActive ? printf("}") : printf("]");
        break;
    case 0x2B:
        shiftActive ? printf("|") : printf("\\");
        break;
    case 0x3A:                                 // CAPSLOCK
        shiftActive ? printf("") : printf(""); // TODO: implement
        break;
    case 0x1E:
        shiftActive ? printf("A") : printf("a");
        break;
    case 0x1F:
        shiftActive ? printf("S") : printf("s");
        break;
    case 0x20:
        shiftActive ? printf("D") : printf("d");
        break;
    case 0x21:
        shiftActive ? printf("F") : printf("f");
        break;
    case 0x22:
        shiftActive ? printf("G") : printf("g");
        break;
    case 0x23:
        shiftActive ? printf("H") : printf("h");
        break;
    case 0x24:
        shiftActive ? printf("J") : printf("j");
        break;
    case 0x25:
        shiftActive ? printf("K") : printf("k");
        break;
    case 0x26:
        shiftActive ? printf("L") : printf("l");
        break;
    case 0x27:
        shiftActive ? printf(":") : printf(";");
        break;
    case 0x28:
        shiftActive ? printf("\"") : printf("\'");
        break;
    case 0x1C: // ENTER
        shiftActive ? printf("") : printf("\n");
        break;
    case 0x2A: // LSHIFT
    case 0x36: // RSHIFT
        shiftActive = true;
        break;
    case 0x2C:
        shiftActive ? printf("Z") : printf("z");
        break;
    case 0x2D:
        shiftActive ? printf("X") : printf("x");
        break;
    case 0x2E:
        shiftActive ? printf("C") : printf("c");
        break;
    case 0x2F:
        shiftActive ? printf("V") : printf("v");
        break;
    case 0x30:
        shiftActive ? printf("B") : printf("b");
        break;
    case 0x31:
        shiftActive ? printf("N") : printf("n");
        break;
    case 0x32:
        shiftActive ? printf("M") : printf("m");
        break;
    case 0x33:
        shiftActive ? printf("<") : printf(",");
        break;
    case 0x34:
        shiftActive ? printf(">") : printf(".");
        break;
    case 0x35:
        shiftActive ? printf("?") : printf("/");
        break;
    case 0x48:                                 // UPARROW
        shiftActive ? printf("") : printf(""); // TODO: implement
        break;
    case 0x39: // SPACEBAR
        shiftActive ? printf(" ") : printf(" ");
        break;
    case 0xAA: // LSHIFT RELEASE
    case 0xB6: // RSHIFT RELEASE
        shiftActive = false;
        break;
        // TODO : implement other keys

    default:
        break;
    }
}
