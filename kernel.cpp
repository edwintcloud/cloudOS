#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "driver.h"
#include "keyboard.h"
#include "mouse.h"

void printf(char *str)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;

    static uint8_t x = 0, y = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
        case '\n':
            y++;
            x = 0;
            break;
        case '\t':
            x += 4;
            break;
        case '\b':
            x -= 1;
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
            break;
        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
            x++;
            break;
        }

        // Line Feed
        if (x >= 80)
        {
            y++;
            x = 0;
        }

        // Clear Screen
        if (y >= 25)
        {
            for (y = 0; y < 25; y++)
            {
                for (x = 0; x < 80; x++)
                {
                    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
                }
            }
        }
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(const void *multiboot_structure, uint32_t magic_number)
{
    printf("\n\t\t\t\t\t\t\t** Welcome to Cloud OS **\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    printf("\n-> Initializing Hardware, Stage 1...\n");
    DriverManager drvManager;
    KeyboardDriver keyboard(&interrupts);
    drvManager.AddDriver(&keyboard);
    MouseDriver mouse(&interrupts);
    drvManager.AddDriver(&mouse);

    printf("\n-> Initializing Hardware, Stage 2...\n");
    drvManager.ActivateAll();

    printf("\n-> Initializing Hardware, Stage 3...\n\n");
    interrupts.Activate();

    while (1)
        ;
}