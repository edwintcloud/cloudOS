#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"

class KeyboardDriver : public InterruptHandler
{
    Port8Bit dataport;
    Port8Bit commandport;
    bool shiftActive;

public:
    KeyboardDriver(InterruptManager *manager);
    ~KeyboardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);

protected:
    void handleAnsiKeyPress(uint8_t key);
};

#endif // !__KEYBOARD_H
