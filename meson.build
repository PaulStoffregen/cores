project('teensy-cores', 'c', 'cpp',
    version: '1.44',
    default_options: [
        'b_staticpic=false',
    ]
)

assert(meson.is_cross_build(), 'Teensy projects can only be built in a cross build environment.')

pkg_mod = import('pkgconfig')

### Teensy Core ###

teensy2_core_incdir = 'teensy'

teensy2_core_src = [
    'teensy/HardwareSerial.cpp',
    'teensy/IPAddress.cpp',
    'teensy/Print.cpp',
    'teensy/Stream.cpp',
    'teensy/Tone.cpp',
    'teensy/WInterrupts.c',
    'teensy/WMath.cpp',
    'teensy/WString.cpp',
    'teensy/keylayouts.c',
    'teensy/main.cpp',
    'teensy/malloc.c',
    'teensy/new.cpp',
    'teensy/pins_teensy.c',
    'teensy/usb.c',
    'teensy/usb_api.cpp',
    'teensy/wiring.c',
    'teensy/yield.cpp',
]

### Teensy 3 Core ###

teensy3_core_incdir = [
    'teensy3',
    'teensy3/avr',
    'teensy3/util',
]

teensy3_core_src = [
    'teensy3/analog.c',
    'teensy3/AudioStream.cpp',
    'teensy3/avr_emulation.cpp',
    'teensy3/DMAChannel.cpp',
    'teensy3/eeprom.c',
    'teensy3/HardwareSerial1.cpp',
    'teensy3/HardwareSerial2.cpp',
    'teensy3/HardwareSerial3.cpp',
    'teensy3/HardwareSerial4.cpp',
    'teensy3/HardwareSerial5.cpp',
    'teensy3/HardwareSerial6.cpp',
    'teensy3/IntervalTimer.cpp',
    'teensy3/IPAddress.cpp',
    'teensy3/keylayouts.c',
    'teensy3/main.cpp',
    'teensy3/math_helper.c',
    'teensy3/memcpy-armv7m.S',
    'teensy3/memset.S',
    'teensy3/mk20dx128.c',
    'teensy3/new.cpp',
    'teensy3/nonstd.c',
    'teensy3/pins_teensy.c',
    'teensy3/Print.cpp',
    'teensy3/serial1.c',
    'teensy3/serial2.c',
    'teensy3/serial3.c',
    'teensy3/serial4.c',
    'teensy3/serial5.c',
    'teensy3/serial6.c',
    'teensy3/serial6_lpuart.c',
    'teensy3/ser_print.c',
    'teensy3/Stream.cpp',
    'teensy3/Tone.cpp',
    'teensy3/touch.c',
    'teensy3/usb_audio.cpp',
    'teensy3/usb_desc.c',
    'teensy3/usb_dev.c',
    'teensy3/usb_flightsim.cpp',
    'teensy3/usb_inst.cpp',
    'teensy3/usb_joystick.c',
    'teensy3/usb_keyboard.c',
    'teensy3/usb_mem.c',
    'teensy3/usb_midi.c',
    'teensy3/usb_mouse.c',
    'teensy3/usb_mtp.c',
    'teensy3/usb_rawhid.c',
    'teensy3/usb_seremu.c',
    'teensy3/usb_serial.c',
    'teensy3/usb_touch.c',
    'teensy3/WMath.cpp',
    'teensy3/WString.cpp',
    'teensy3/yield.cpp',
]

### Teensy 4 Core ###

teensy4_core_incdir = [
    'teensy4',
    'teensy4/avr',
    'teensy4/util',
]

teensy4_core_src = [
    'teensy4/analog.c',
    'teensy4/AudioStream.cpp',
    'teensy4/Blink.cc',
    'teensy4/bootdata.c',
    'teensy4/clockspeed.c',
    'teensy4/DMAChannel.cpp',
    'teensy4/debugprintf.c',
    'teensy4/delay.c',
    'teensy4/digital.c',
    'teensy4/HardwareSerial.cpp',
    'teensy4/HardwareSerial1.cpp',
    'teensy4/HardwareSerial2.cpp',
    'teensy4/HardwareSerial3.cpp',
    'teensy4/HardwareSerial4.cpp',
    'teensy4/HardwareSerial5.cpp',
    'teensy4/HardwareSerial6.cpp',
    'teensy4/HardwareSerial7.cpp',
    'teensy4/HardwareSerial8.cpp',
    'teensy4/interrupt.c',
    'teensy4/IntervalTimer.cpp',
    'teensy4/IPAddress.cpp',
    'teensy4/keylayouts.c',
    'teensy4/libc.c',
    'teensy4/memcpy-armv7m.S',
    'teensy4/memset.S',
    'teensy4/new.cpp',
    'teensy4/nonstd.c',
    'teensy4/Print.cpp',
    'teensy4/pwm.c',
    'teensy4/startup.c',
    'teensy4/Stream.cpp',
    'teensy4/tempmon.c',
    'teensy4/Tone.cpp',
    'teensy4/usb_desc.c',
    'teensy4/usb_inst.cpp',
    'teensy4/usb_serial.c',
    'teensy4/WMath.cpp',
    'teensy4/WString.cpp',
    'teensy4/yield.cpp',
]

teensy_core = meson.get_cross_property('teensy_core') # Which teensy core treee to use

teensy_core_src =  []
teensy_core_incdir = []

if teensy_core == 'teensy' # Teensy(++) 2.0
    teensy_core_src = teensy2_core_src
    teensy_core_incdir = teensy2_core_incdir
elif teensy_core == 'teensy3'
    teensy_core_src = teensy3_core_src
    teensy_core_incdir = teensy3_core_incdir
elif teensy_core == 'teensy4'
    teensy_core_src = teensy4_core_src
    teensy_core_incdir = teensy4_core_incdir
endif

teensy_core_lib = static_library('teensy-core', teensy_core_src,
                                 cpp_args: '-Wno-non-virtual-dtor',
                                 include_directories: include_directories(teensy_core_incdir)
)

teensy_core_dep = declare_dependency(
    link_with: teensy_core_lib,
    include_directories: include_directories(teensy_core_incdir),
)

ldscript = join_paths(meson.current_source_dir(), teensy_core,
                      meson.get_cross_property('teensy_mcu') + '.ld')


### Teensy USB RawHID ###

#teensy_usb_rawhid_incdir = teensy_core_incdir
#teensy_usb_rawhid_incdir += teensy2_core_incdir
#teensy_usb_rawhid_incdir += 'usb_rawhid'

#teensy_usb_rawhid_src = [
#    'usb_rawhid/usb.c',
#    'usb_rawhid/usb_api.cpp',
#]

#teensy_usb_rawhid_lib = static_library('teensy-usb-rawid', teensy_usb_rawhid_src,
#                                        include_directories: include_directories(teensy_usb_rawhid_incdir),
#                                        dependencies: teensy_core_dep
#)

#teensy_usb_rawhid_dep = declare_dependency(
#    link_with: teensy_usb_rawhid_lib,
#    include_directories: include_directories(teensy_usb_rawhid_incdir),
#)
