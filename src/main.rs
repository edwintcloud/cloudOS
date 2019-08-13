#![no_std] // don't link the std library
#![no_main] // disable rust-level entry points (_start will be the entry)

use core::panic::PanicInfo;

static HELLO: &[u8] = b"Hello World!";

/// Entry Point.
#[no_mangle] // don't anonymize the name for this function during compile
pub extern "C" fn _start() -> ! {
    let vga_buffer = 0xb8000 as *mut u8;

    for (i, &byte) in HELLO.iter().enumerate() {
        unsafe {
            *vga_buffer.offset(i as isize * 2) = byte;
            *vga_buffer.offset(i as isize * 2 + 1) = 0xb; // set color to light cyan
        }
    }

    loop {}
}

/// Function called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
