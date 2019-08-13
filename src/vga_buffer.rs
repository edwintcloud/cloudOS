
/// The Standard Color Palette in VGA text mode.
#[allow(dead_code)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u8)]
pub enum Color {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,

}

/// A combination of a foreground and background color.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(transparent)]
struct ColorCode(u8);

impl ColorCode {
    /// Create a new `ColorCode` with the given foreground and background colors.
    fn new(foreground: Color, background: Color) -> ColorCode {
        ColorCode((background as u8) << 4 | (foreground as u8))
    }
}

/// A screen character in the VGA text buffer, consisting of an ASCII character and a `ColorCode`.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(C)]
struct ScreenChar {
    ascii_character: u8,
    color_code: ColorCode,
}

/// The normal buffer height and width.
const BUFFER_HEIGHT: usize = 25;
const BUFFER_WIDTH: usize = 80;

/// A struct representing the VGA text buffer.
#[repr(transparent)]
struct Buffer {
    chars: [[ScreenChar; BUFFER_WIDTH]; BUFFER_HEIGHT],
}

/// Expose public writer type that allow writing ASCII bytes and string to an 
/// underlying `Buffer`. Lines are wrapped at `BUFFER_WIDTH`. Newline characters
/// are supported. The `core::fmt::Write` trait is implemented.
pub struct Writer {
    column_position: usize,
    color_code: ColorCode,
    buffer: &'static mut Buffer,
}

impl Writer {

    /// Write an ASCII byte to the buffer.
    pub fn write_byte(&mut self, byte: u8) {
        match byte {
            b'\n' => self.new_line(),
            byte => {
                if self.column_position >= BUFFER_WIDTH {
                    self.new_line();
                }

                let row = BUFFER_HEIGHT - 1;
                let col = self.column_position;

                let color_code = self.color_code;
                self.buffer.chars[row][col] = ScreenChar {
                    ascii_character: byte,
                    color_code
                };
                self.column_position += 1;
            },
        }
    }
    
    /// Write a new line byte to the buffer.
    pub fn new_line(&mut self) {/* TODO */}

    /// Write a given ASCII string to the buffer.
    pub fn write_string(&mut self, s: &str) {
        for byte in s.bytes() {
            match byte {
                // printable ASCII byte or newline char
                0x20..=0x7e | b'\n' => self.write_byte(byte),
                // not printable by VGA Buffer - print block char
                _ => self.write_byte(0xfe),
            }
        }
    }

}

/// Temporary test function.
pub fn print_something() {
    let mut writer = Writer {
        column_position: 0,
        color_code: ColorCode::new(Color::Magenta, Color::Black),
        buffer: unsafe { &mut *(0xb8000 as *mut Buffer)},
    };

    writer.write_byte(b'H');
    writer.write_string("ello ");
    writer.write_string("Wörld!");
}