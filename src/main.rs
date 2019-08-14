#![no_std] // don't link the std library
#![no_main] // disable rust-level entry points (_start will be the entry)
#![feature(custom_test_frameworks)]
#![test_runner(crate::test_runner)]
// #[cfg(test)]
// fn test_runner(test: &[&dyn Fn()]) {
//     println!("Running {} tests", tests.len());
//     for test in tests {
//         test();
//     }
// }
#![reexport_test_harness_main = "test_main"]

use core::panic::PanicInfo;
mod vga_buffer;

/// Entry Point.
#[no_mangle] // don't anonymize the name for this function during compile
pub extern "C" fn _start() -> ! {
    println!("Hello World{}", "!");
    #[cfg(test)]
    test_main();

    loop {}
}

/// Function called on panic.
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}
