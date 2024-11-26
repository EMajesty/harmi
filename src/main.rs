#![no_std]
#![no_main]

use embedded_hal::digital::OutputPin;
use panic_halt as _;
use rp_pico::hal::{
    clocks::{init_clocks_and_plls, Clock},
    gpio::{FunctionI2c, Pins},
    pac,
    sio::Sio,
    timer::Timer,
    watchdog::Watchdog,
};
use rp_pico::XOSC_CRYSTAL_FREQ;

#[rp_pico::entry]
fn main() -> ! {
    // Grab peripherals
    let mut pac = pac::Peripherals::take().unwrap();
    let core = pac::CorePeripherals::take().unwrap();

    // Configure system clock
    let mut watchdog = Watchdog::new(pac.WATCHDOG);
    let sio = Sio::new(pac.SIO);

    // External high-speed crystal oscillator
    let external_xosc_freq = XOSC_CRYSTAL_FREQ;
    let clocks = init_clocks_and_plls(
        external_xosc_freq,
        pac.XOSC,
        pac.CLOCKS,
        pac.PLL_SYS,
        pac.PLL_USB,
        &mut pac.RESETS,
        &mut watchdog,
    )
    .ok()
    .unwrap();

    // Configure GPIO pins
    let mut pins = Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    // Configure onboard LED (typically GP25 on Pico)
    let mut led_pin = pins.gpio25.into_push_pull_output();
    loop{}
}
