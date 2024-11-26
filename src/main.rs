#![no_std]
#![no_main]

use embedded_hal::{delay::DelayNs, digital::OutputPin};
use hd44780_driver::HD44780;
use panic_halt as _;
use rp_pico::entry;
use rp_pico::hal::{
    clocks::{init_clocks_and_plls, Clock},
    fugit::RateExtU32,
    gpio::{FunctionI2c, Pins},
    i2c::I2C,
    pac,
    sio::Sio,
    timer::Timer,
    usb::UsbBus,
    watchdog::Watchdog,
};
use rp_pico::XOSC_CRYSTAL_FREQ;
use usb_device::bus::UsbBusAllocator;
use usb_device::prelude::*;
use usbd_midi::{
    data::{
        byte::u7::*,
        midi::{channel::Channel, message::Message, notes::Note},
        usb_midi::{cable_number::CableNumber, usb_midi_event_packet::UsbMidiEventPacket},
    },
    midi_device::MidiClass,
};

// USB config
const VENDOR_ID: u16 = 0x16c0; // V-USB shared VID
const PRODUCT_ID: u16 = 0x05dc; // V-USB MIDI device PID
const MANUFACTURER: &str = "Electric Majesty";
const PRODUCT: &str = "harmi";
const SERIAL: &str = "0001";

#[entry]
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

    let mut delay = cortex_m::delay::Delay::new(core.SYST, clocks.system_clock.freq().to_Hz());

    // Configure GPIO pins
    let mut pins = Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    let i2c = I2C::i2c0(
        pac.I2C0,
        pins.gpio0.reconfigure(),
        pins.gpio1.reconfigure(),
        400.kHz(),
        &mut pac.RESETS,
        125_000_000.Hz(),
    );

    // Configure onboard LED (typically GP25 on Pico)
    let mut led_pin = pins.gpio25.into_push_pull_output();

    let mut lcd = HD44780::new_i2c(i2c, 0x27, &mut delay).unwrap();

    lcd.clear(&mut delay).unwrap();
    lcd.write_str("Hell World", &mut delay).unwrap();

    static mut USB_BUS: Option<UsbBusAllocator<UsbBus>> = None;

    unsafe {
        USB_BUS = Some(UsbBusAllocator::new(UsbBus::new(
            pac.USBCTRL_REGS,
            pac.USBCTRL_DPRAM,
            clocks.usb_clock,
            true,
            &mut pac.RESETS,
        )));
    }
    let usb_bus = unsafe { USB_BUS.as_ref().unwrap() };

    // let usb_bus = UsbBusAllocator::new(UsbBus::new(
    //     pac.USBCTRL_REGS,
    //     pac.USBCTRL_DPRAM,
    //     clocks.usb_clock,
    //     true,
    //     &mut pac.RESETS,
    // ));

    let mut midi = MidiClass::new(usb_bus, 0, 1).unwrap();

    let mut usb_dev = UsbDeviceBuilder::new(usb_bus, UsbVidPid(VENDOR_ID, PRODUCT_ID))
        .strings(&[StringDescriptors::default()
            .manufacturer(MANUFACTURER)
            .product(PRODUCT)
            .serial_number(SERIAL)])
        .unwrap()
        .device_class(0x01)
        .device_sub_class(0x03)
        .device_protocol(0x00)
        .composite_with_iads()
        .build();

    let channel = Channel::Channel1;
    let note = Note::C4;

    lcd.clear(&mut delay).unwrap();
    lcd.write_str("USB Config OK", &mut delay).unwrap();
    delay.delay_ms(1000);

    loop {
        // Continuous USB polling
        if !usb_dev.poll(&mut [&mut midi]) {
            // USB polling error
            lcd.clear(&mut delay).unwrap();
            lcd.write_str("USB Poll Fail", &mut delay).unwrap();
            led_pin.set_high().unwrap();
            delay.delay_ms(500);
            continue;
        }

        // Check USB device state
        match usb_dev.state() {
            UsbDeviceState::Configured => {
                match midi.send_message(UsbMidiEventPacket::from_midi(
                    CableNumber::Cable0,
                    Message::NoteOn(channel, note, U7::MAX),
                )) {
                    Ok(_) => {
                        // Successful send
                        lcd.clear(&mut delay).unwrap();
                        lcd.write_str("MIDI Note On", &mut delay).unwrap();
                        led_pin.set_high().unwrap();
                        delay.delay_ms(100);

                        midi.send_message(UsbMidiEventPacket::from_midi(
                            CableNumber::Cable0,
                            Message::NoteOff(channel, note, U7::MIN),
                        ))
                        .ok();

                        lcd.clear(&mut delay).unwrap();
                        lcd.write_str("MIDI Note Off", &mut delay).unwrap();
                        led_pin.set_low().unwrap();
                        delay.delay_ms(900);
                    }
                    Err(_) => {
                        // MIDI send error
                        lcd.clear(&mut delay).unwrap();
                        lcd.write_str("MIDI Send Err", &mut delay).unwrap();
                        led_pin.set_high().unwrap();
                        delay.delay_ms(200);
                        led_pin.set_low().unwrap();
                    }
                }
            }
            UsbDeviceState::Default => {
                // Default state error
                lcd.clear(&mut delay).unwrap();
                lcd.write_str("USB Default", &mut delay).unwrap();
                led_pin.set_high().unwrap();
                delay.delay_ms(100);
                led_pin.set_low().unwrap();
                delay.delay_ms(900);
            }
            UsbDeviceState::Addressed => {
                // Addressed state error
                lcd.clear(&mut delay).unwrap();
                lcd.write_str("USB Addressed", &mut delay).unwrap();
                led_pin.set_high().unwrap();
                delay.delay_ms(100);
                led_pin.set_low().unwrap();
                delay.delay_ms(900);
            }
            _ => {
                // Other states
                lcd.clear(&mut delay).unwrap();
                lcd.write_str("USB Unknown", &mut delay).unwrap();
                led_pin.set_high().unwrap();
                delay.delay_ms(100);
                led_pin.set_low().unwrap();
                delay.delay_ms(900);
            }
        }
    }
}
