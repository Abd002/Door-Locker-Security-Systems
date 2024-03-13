## Door Locker Security System

This repository contains the implementation of a door locker security system to unlock a door using a password.

### System Requirements

Implement the Door Locker Security System with the following specifications:

1. **Microcontrollers:** Utilizes two ATmega32 Microcontrollers with a frequency of 8MHz.

2. **Layered Architecture Model:**
   - **HMI_ECU (Human Machine Interface):** Includes 2x16 LCD and 4x4 keypad.
   - **Control_ECU:** Includes EEPROM, Buzzer, and DC-Motor.

3. **HMI_ECU Responsibilities:** Interacts with the user, takes inputs through the keypad, and displays messages on the LCD.

4. **Control_ECU Responsibilities:** Handles all processing and decisions in the system, such as password checking, opening the door, and activating the system alarm.

5. **System Sequence:**
   - Step 1: Create a System Password
   - Step 2: Main Options
   - Step 3: Open Door +
   - Step 4: Change Password -
   - Step 5: Error Handling

### Driver Requirements

#### GPIO Driver
- Utilizes the same GPIO driver implemented in the course.
- Used in both ECUs.

#### LCD Driver
- Utilizes a 2x16 LCD.
- Utilizes the LCD driver implemented in the course with 8-bits or 4-bits data mode.
- Connects the LCD control and data bus pins to any MCU pins.
- LCD connected to HMI_ECU.

#### Keypad Driver
- Utilizes a 4x4 Keypad.
- Connects the keypad pins to any MCU pins.
- Keypad connected to HMI_ECU.

#### DC_Motor Driver
- Utilizes the same DC_Motor driver implemented in the fan controller project.
- Motor always runs at maximum speed using Timer0 PWM.
- Motor connected to CONTROL_ECU.
- Connects the motor pins to any MCU pins.

#### EEPROM Driver
- Utilizes the same external EEPROM driver controlled by I2C.
- EEPROM connected to CONTROL_ECU.

#### I2C Driver
- Utilizes the same I2C driver implemented in the course.
- Used in CONTROL_ECU to communicate with the external EEPROM.
- Modifies TWI_init function to accept a pointer to the configuration structure.
- Control_ECU acts as Master with device address 10 and a baud rate of 400K Bits/Sec.

#### UART Driver
- Utilizes the same UART driver implemented in the course.
- Used in both ECUs.
- Modifies UART_init function to accept a pointer to the configuration structure.

#### Timer Driver
- Utilizes the same timer driver implemented in the course.
- Used in both ECUs for timing operations.
- Implements a full Timer driver for TIMER1 with the configuration technique.
- Supports both normal and compare modes.

#### Buzzer Driver
- Implements a full Buzzer driver.
- Buzzer connected to CONTROL_ECU.
- Connects the buzzer pin to any MCU pins.
- Buzzer pin chosen by static configurations.

### Thank You & Good Luck

Eng/Mohamed Tarek
