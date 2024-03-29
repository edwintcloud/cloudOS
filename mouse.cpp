#include "mouse.h"

void printf(char *);

// https://forum.osdev.org/viewtopic.php?t=10247

MouseDriver::MouseDriver(InterruptManager *manager)
    : InterruptHandler(0x2C, manager),
      dataport(0x60),
      commandport(0x64)
{
}

MouseDriver::~MouseDriver()
{
}

void MouseDriver::Activate()
{
    uint16_t *VideoMemory = (uint16_t *)0xb8000;
    offset = 0;
    buttons = 0;
    x = 40;
    y = 12;

    // set cursor to center of screen
    VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4) | ((VideoMemory[80 * y + x] & 0x0F00) << 4) | (VideoMemory[80 * y + x] & 0x00FF);

    // initialize mouse
    commandport.Write(0xA8); // enable aux mouse dev
    commandport.Write(0x20); // enable interrupts
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60); // tell mouse we will send status
    dataport.Write(status);  // send status
    commandport.Write(0xD4);
    commandport.Write(0xF4); // enable mouse
    dataport.Read();         // ACK
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();
    if (!(status & 0x20))
        return esp;

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    if (offset == 0)
    {
        if (buffer[1] != 0 || buffer[2] != 0)
        {

            static uint16_t *VideoMemory = (uint16_t *)0xb8000;

            VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4) | ((VideoMemory[80 * y + x] & 0x0F00) << 4) | (VideoMemory[80 * y + x] & 0x00FF);

            x += buffer[1];
            if (x < 0)
                x = 0;
            if (x >= 80)
                x = 79;

            y -= buffer[2];
            if (y < 0)
                y = 0;
            if (y >= 25)
                y = 24;

            VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4) | ((VideoMemory[80 * y + x] & 0x0F00) << 4) | (VideoMemory[80 * y + x] & 0x00FF);
        }
    }

    return esp;
}
