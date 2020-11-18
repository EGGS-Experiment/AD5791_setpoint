AMO7 - Stepper Motor Controller
===============================
Hardware: v 1.0.0
Software: v 1.1.0
===============================

-------------------------------
Screen Commands:
-------------------------------
(clockwise, starting from "MOTOR NUMBER")

	MOTOR NUMBER

Displays the selected motor.

	STEP DISPLAY
	
Displays the total position in steps. Motors can move a maximum of 12800 full steps in either direction (i.e. a range of 25600 steps).
	
	MICROSTEPS

Displays the current microstep configuration to move.
	
	COARSE DISPLAY

Displays the total position in degrees.

	CALIBRATE

Triggers calibration.
If the specified motor is currently queued up to move, then CALIBRATE will do nothing.

    ZERO
    
Sets the current position to zero.

	MOVE

Moves to the specified angular position. This button cannot be pressed if the selected motor is either already moving, queued up to move, or if alternative mode is selected (due to manual stepping). 

	HOLDING VOLTAGE

Sets the voltage for the motor when stationary.

	MOVING VOLTAGE

Sets the voltage for the motor during stepping.

	ON/OFF

Toggles output to the motor.

-------------------------------
Serial Commands:
-------------------------------

	vout.w [motor number] [mode] [voltage]

Sets the voltage of the specified motor based on the chosen mode. Mode arguments can be "m" (to set moving voltage), "h" (to set holding voltage), and "p" (to set percent fast decay). The voltage can be adjusted in increments of 0.016 to a maximum of 4.08V.

	vout.r [motor number] [mode]

Displays the voltage of the specified motor's mode.

	out.w [motor number] [enable]

Switches the specified motor on or off.

	out.r [motor number]

Displays whether the specified motor is on or off.

	move.w [motor number] [full steps, eighth steps]

Moves the motor to the specified position. Maximum steps is +/- 4000 full steps.
Note that move.w moves the motor to an absolute and not relative position, e.g. "move.w 1 3,5" moves the motor TO 3,5 and rather than an additional 3,5 steps.
If the specified motor is currently queued up to move, then move.w will do nothing.
move.w can move the motor a maximum of 12800 full steps in either direction (i.e. a range of 25600 steps). 

	move.r [motor number]

Displays the position of the motor in full steps and eighth steps.

	calib.w [motor number]

Triggers calibration.
If the specified motor is currently queued up to move, then calib.w will do nothing.

	speed.w [motor number] [speed]

Sets the motor speed in steps/second. The minimum speed is 15.38 steps/second, with a maximum of 10k steps/second. The default speed for all motors is set at 1000 steps/second.
speed.w only affects full steps; microsteps always move at the base speed.

	speed.r [motor number]

Displays the motor speed in steps/second.

	accel.toggle

Toggles acceleration mode.

	round.toggle

Toggles rounding mode.

	alt.toggle

Toggles alternative mode.

	back.toggle

Toggles backlash accounting.

-------------------------------
NOTES:
-------------------------------
	WARNINGS:

1) Please don't touch move_holder, step_holder, or labs() in the code. Something will probably break.
2) While motors are moving, don't turn other motors on/off (e.g. if motor #3 is moving, don't switch motor #7 on/off). However, changing voltage is ok.

	Alternative mode, manual stepping, sensor crossing:

Alternative mode can be toggled by either entering "alt.toggle" into the serial interface, or by pressing both the switches simultaneously without any boxes selected on the screen. This enables 1) manual stepping, and 2) the ability to cross the calibration sensor.
Note that when entering alternative mode, the step displays will reset to the last moved position, abandoning any "unmoved" steps.
In manual stepping, the encoders and switches directly move the motors without the need to press "MOVE". With manual stepping, motors move at a maximum of 333 steps/second. However, "move.w" is unaffected.

    Calibration & sensors:
    
"calib.w" and the "CALIBRATE" button trigger calibration, which moves the motor (always in the same direction) until the motor pin crosses the sensor, then moves 1000 steps in the other direction. If the pin is initially on the sensor, the motor will move 1000 steps in the opposite direction, then begin a normal calibration.
Motor pins are hardcoded to not be able to cross the sensor, and will return an error message in serial if a command attempts to make this happen, unless the device is in alternative mode.
For calibration to be enabled for a motor, motors need to be hardcoded as having a sensor (amo7.h, lines 171-182).
Warning: If calibration is initiated on a motor which has been declared as having a sensor, but does not/is broken, the motor will not be able to stop.

	Rounding mode:

In rounding mode, the motor moves to the next full step at 333 steps/second, moves the specified amount, then returns to the original microstep at 333 steps/second. This is useful when accuracy is important, since moving in full steps from a microstep position causes motor error to build up.

	Using different motors:

AMO7 only works with bipolar stepper motors. Motors must be connected to a DB9 connector. Pins 1 & 2 connect to one H-bridge, while pins 7 & 6 connect to the other H-bridge. Pins 4 & 5 optionally connect to an external encoder. Pin 9 optionally connects to an external sensor used for waveplate calibration. Motors of different step sizes can be used interchangeably during operation, as step size is only used for the coarse display. While this means that the coarse display will only be accurate for its intended motor, step size can easily be adjusted within the code.
		
	Acceleration mode:

When acceleration mode is on, the motor will accelerate if 1) its set speed is greater than the base speed (1000 steps/second), and 2) there are enough steps to fully accelerate and decelerate.
If condition 1) is not met, the motor will simply move at the set speed. If condition 2) is not met, the motor will simply move at the base speed (1000 steps/second).
If acceleration mode is off, the motor will simply start at the speed specified by speed.w.

	Orientation:

The motor orientation of positive and negative steps is determined by the wiring of the motor's H-bridges on the DB9 connector. 

	Speed, acceleration, and timing:

This software uses the ATMega2560's TIMER 1, which uses a 16 bit register in setting delays. The prescaler adjusts the "ticking" of the timer, which is set to 1/8 (i.e. it takes 8 clock cycles for 1 "tick").
Stepping occurs by setting up TIMER 1 with a delay and an interrupt request upon timer completion. This delay is dictated by the speed, as set by speed.w. The step pulse uses a 1:1 duty cycle, i.e. the step pulse is divided 1:1 between HIGH and LOW. As a result, TIMER 1 has a resolution of 1us (2 (duty cycle) x 8 clock cycles / 16MHz = 1us).
However, the stepping delay has an error of about 10us due to the time it takes to process instructions within the timer interrupt. At the highest speed setting (10k steps/second) this creates about 9% error, but at the base speed (1000 steps/second) we see 0.5% error.
Additionally, the frequency of microcontroller interrupts to step means that high-speed stepping will cause the screen to lag.
Acceleration is achieved by decreasing the time between successive steps at a rate of 5 us/step, however, this can be changed in the code.

	Percent fast decay:

The decay mode can be adjusted via the PFD voltage, which can only be set via vout.w. Percentage fast decay is expressed by PFD = ln(3/V_pfd) x 100. For values of PFD greater than 100%, fast-decay mode is selected, while a PFD less than 0% enters slow-decay mode.
