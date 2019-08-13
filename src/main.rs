#![no_std] // don't link the std library
#![no_main] // disable rust-level entry points (_start will be the entry)

use core::panic::PanicInfo;
mod vga_buffer;

/// Entry Point.
#[no_mangle] // don't anonymize the name for this function during compile
pub extern "C" fn _start() -> ! {
    vga_buffer::print_something();

    loop {}
}

/// Function called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
