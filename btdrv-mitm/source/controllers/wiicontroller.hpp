#pragma once
#include "bluetoothcontroller.hpp"

namespace ams::controller {

    enum WiiControllerLEDs {
		WiiControllerLEDs_P1 = 0x10,
		WiiControllerLEDs_P2 = 0x20,
		WiiControllerLEDs_P3 = 0x40,
		WiiControllerLEDs_P4 = 0x80,
	};

    struct WiiButtonData {
		uint8_t dpad_left	: 1;
		uint8_t dpad_right	: 1;
		uint8_t dpad_down	: 1;
		uint8_t dpad_up	    : 1;
		uint8_t plus		: 1;
		uint8_t				: 0;
		
		uint8_t two			: 1;
		uint8_t one 		: 1;
		uint8_t B			: 1;
		uint8_t A			: 1;
		uint8_t minus		: 1;
		uint8_t				: 2;
		uint8_t home 		: 1;
	} __attribute__ ((__packed__));

	struct WiiAccelerometerData {
		uint8_t xyz[3];
	} __attribute__ ((__packed__));

	    struct WiiReport0x30 {
        WiiButtonData   buttons;
    } __attribute__ ((__packed__));

    struct WiiReport0x31 {
        WiiButtonData           buttons;
        WiiAccelerometerData    accel;
    } __attribute__ ((__packed__));

    struct WiiReport0x32 {
        WiiButtonData   buttons;
        uint8_t         extension[8];
    } __attribute__ ((__packed__));

    struct WiiReport0x33 {
        WiiButtonData           buttons;
        WiiAccelerometerData    accel;
        uint8_t                 ir[12];
    } __attribute__ ((__packed__));

    struct WiiReport0x34 {
        WiiButtonData           buttons;
        uint8_t                 extension[19];
    } __attribute__ ((__packed__));

    struct WiiReport0x35 {
        WiiButtonData           buttons;
        WiiAccelerometerData    accel;
        uint8_t                 extension[16];
    } __attribute__ ((__packed__));

    struct WiiReport0x36 {
        WiiButtonData   buttons;
        uint8_t         ir[10];
        uint8_t         extension[9];
    } __attribute__ ((__packed__));

    struct WiiReport0x37 {
        WiiButtonData           buttons;
        WiiAccelerometerData    accel;
        uint8_t                 ir[10];
        uint8_t                 extension[6];
    } __attribute__ ((__packed__));

    struct WiiReport0x3d {
        uint8_t extension[21];
    } __attribute__ ((__packed__));

    struct WiiReportData {
        uint8_t id;
        union {
            WiiReport0x30 report0x30;
            WiiReport0x31 report0x31;
            WiiReport0x32 report0x32;
            WiiReport0x33 report0x33;
            WiiReport0x34 report0x34;
            WiiReport0x35 report0x35;
            WiiReport0x36 report0x36;
            WiiReport0x37 report0x37;
            WiiReport0x3d report0x3d;
        };
	} __attribute__ ((__packed__));

    class WiiController : public BluetoothController {

        public:
            Result initialize(void);

        protected:
            WiiController(ControllerType type, const bluetooth::Address *address) : BluetoothController(type, address) {};

            Result writeMemory(const bluetooth::Address *address, uint32_t writeaddr, const uint8_t *data, uint8_t length);
            Result setReportMode(const bluetooth::Address *address, uint8_t mode);
            Result setPlayerLeds(const bluetooth::Address *address, uint8_t mask);

        private:
            //void mapStickValues(JoystickPosition *dst, const Dualshock4StickData *src);
            //void handleInputReport0x01(const Dualshock4ReportData *data);
            //void handleInputReport0x11(const Dualshock4ReportData *data); 
    };


}
