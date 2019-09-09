For automating the measurement process of determing the motorconstant in Robotis Dynamixel motors.

Usage: ./test_calculate_motorconstant <filename> <baudrate>

<baudrate> is the baudrate for communicating with the dynamixel motor

The software will apply increasing amounts of current to the motor and retrieve the measured weight from the digital scale.

All measurements will be recorded to <filename> in csv format, current in [mA] and weight in [g].
