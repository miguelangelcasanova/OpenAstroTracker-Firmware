#include "hal.h"

#include "../../Constants.hpp"
#include "../../Configuration.hpp"
#include "../../Configuration_adv.hpp"

#include "SoftwareSerial.h"

#define RA_TRANSMISSION RA_WHEEL_CIRCUMFERENCE / RA_PULLEY_TEETH * 2.0
#define DEC_TRANSMISSION DEC_WHEEL_CIRCUMFERENCE / DEC_PULLEY_TEETH * 2.0

namespace hal
{
    namespace axis
    {

        // RA Axis start //
        StepperSpecs raStepper(
            RA_STEPPER_SPR,
            RA_STEPPER_RATED_CURRENT,
            RA_STEPPER_VOLTAGE,
            RA_STEPPER_INDUCTANCE);

#if RA_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
        SoftwareSerial raSerial(RA_SERIAL_PORT_RX, RA_SERIAL_PORT_TX);
        TMC2209 raDriver(
            raStepper,
            RA_MICROSTEPPING,
            &raSerial,
            RA_DRIVER_ADDRESS,
            RA_EN_PIN,
            RA_STEP_PIN,
            RA_DIR_PIN);
#elif RA_DRIVER_TYPE == DRIVER_TYPE_ULN2003
        ULN2003 raDriver(
            raStepper,
            RA_MICROSTEPPING,
            RA_IN1_PIN,
            RA_IN2_PIN,
            RA_IN3_PIN,
            RA_IN4_PIN);
#endif

        RaAxis ra(
            RA_TRANSMISSION,
            raDriver,
            RA_PULSE_MULTIPLIER);
        // RA Axis end //

        // DEC Axis start //
        StepperSpecs decStepper(
            DEC_STEPPER_SPR,
            DEC_STEPPER_RATED_CURRENT,
            DEC_STEPPER_VOLTAGE,
            DEC_STEPPER_INDUCTANCE);

#if DEC_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
        SoftwareSerial decSerial(DEC_SERIAL_PORT_RX, DEC_SERIAL_PORT_TX);
        TMC2209 decDriver(
            decStepper,
            DEC_MICROSTEPPING,
            &decSerial,
            DEC_DRIVER_ADDRESS,
            DEC_EN_PIN,
            DEC_STEP_PIN,
            DEC_DIR_PIN);
#elif DEC_DRIVER_TYPE == DRIVER_TYPE_ULN2003
        ULN2003 decDriver(
            decStepper,
            DEC_MICROSTEPPING,
            DEC_IN1_PIN,
            DEC_IN2_PIN,
            DEC_IN3_PIN,
            DEC_IN4_PIN);
#endif

        DecAxis dec(
            DEC_TRANSMISSION,
            decDriver);
        // DEC Axis end //

    } // namespace axis
} // namespace hal