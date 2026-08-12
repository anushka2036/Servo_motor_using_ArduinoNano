# 🎛️ Servo Motor Control Using Arduino Nano

This project demonstrates how to control a **servo motor using an Arduino Nano** with two input devices: a **potentiometer** and a **joystick module**.

The potentiometer is given **priority control** when it is intentionally moved. When the potentiometer remains stable, the **joystick controls the servo motor**. The project also uses a simple smoothing technique to reduce unwanted fluctuations in potentiometer readings.

## 🚀 Project Features

* Control a servo motor using a potentiometer
* Control the same servo using a joystick
* Potentiometer gets priority when it is moved
* Joystick controls the servo when the potentiometer is stable
* Uses analog input readings from Arduino Nano
* Applies software smoothing to make potentiometer control more stable
* Displays the active control source and servo angle through the Serial Monitor

---

## 🛠️ Components Required

| Component          |    Quantity |
| ------------------ | ----------: |
| Arduino Nano       |           1 |
| Servo Motor (SG90) |           1 |
| Potentiometer      |           1 |
| Joystick Module    |           1 |
| Jumper Wires       | As required |
| USB Cable          |           1 |

---

# 💻 Software Requirements

* **Arduino IDE**
* Arduino Nano
* USB cable
* `Servo` library

The **Servo library** is included with the standard Arduino IDE installation, so normally no additional library installation is required.

---

# ⚙️ Installing Arduino IDE

## 1. Download Arduino IDE

Download Arduino IDE from the official Arduino website:

**https://www.arduino.cc/en/software/**

Install the version appropriate for your operating system.

## 2. Connect the Arduino Nano

1. Connect the Arduino Nano to your computer using a USB cable.
2. Open **Arduino IDE**.
3. Select the board:

```text
Tools → Board → Arduino AVR Boards → Arduino Nano
```

4. Select the appropriate serial port:

```text
Tools → Port → COMx
```

The COM port number may be different on your computer.

> **Note:** Some Arduino Nano clones use the CH340 USB-to-serial chip. If the board is not detected, the appropriate USB driver may need to be installed.

---

# 🔌 Building the Circuit

Build the circuit by following the attached circuit diagram.

## 1. Servo Motor Connections

The project uses an **SG90 servo motor**.

| Servo Wire | Arduino Nano |
| ---------- | ------------ |
| Signal     | D3           |
| VCC        | 5V           |
| GND        | GND          |

The servo signal wire is connected to **Digital Pin 3**.

---

## 2. Potentiometer Connections

The potentiometer is used to provide an analog control value.

| Potentiometer      | Arduino Nano |
| ------------------ | ------------ |
| One outer pin      | 5V           |
| Middle pin (wiper) | A1           |
| Other outer pin    | GND          |

The middle pin provides the variable analog voltage to **A1**.

---

## 3. Joystick Module Connections

The joystick module's X-axis output is used to control the servo.

| Joystick     | Arduino Nano |
| ------------ | ------------ |
| VCC          | 5V           |
| GND          | GND          |
| VRx / X-axis | A0           |

The X-axis analog signal is connected to **A0**.

> The joystick's other controls are not required for this project. Only its X-axis output is used.

---

# 📌 Pin Configuration

The Arduino program uses the following pins:

```cpp
const int joyPin = A0;
const int potPin = A1;
const int servoPin = 3;
```

Therefore:

```text
Joystick X-axis → A0
Potentiometer   → A1
Servo Signal    → D3
```

---

# 📁 Project Structure

A recommended GitHub repository structure is:

```text
Servo-Motor-Potentiometer-Arduino/
│
├── README.md
├── circuitdiagram_potentiometer.jpg
└── README.mdpotentiometer.ino
```

You can also add photos or videos of the completed project later.

---

# 💻 Understanding the Code

The project uses the Arduino **Servo library**:

```cpp
#include <Servo.h>
```

A servo object is then created:

```cpp
Servo myServo;
```

The code assigns:

```cpp
joyPin = A0
potPin = A1
servoPin = 3
```

The servo is attached to Digital Pin 3:

```cpp
myServo.attach(servoPin);
```

---

# 🧠 How the Control Logic Works

The program follows a **priority-based control system**.

### Step 1 — Read the Potentiometer

The Arduino continuously reads the potentiometer:

```cpp
int rawPotValue = analogRead(potPin);
```

The reading ranges approximately from:

```text
0 → 1023
```

### Step 2 — Smooth the Reading

The program applies a simple smoothing filter:

```cpp
float currentSmoothedPotValue =
    (0.9 * lastSmoothedPotValue) +
    (0.1 * rawPotValue);
```

This reduces sudden changes and unwanted noise in the potentiometer reading.

### Step 3 — Detect Potentiometer Movement

The program checks whether the smoothed potentiometer value has changed significantly.

```cpp
if (abs(currentSmoothedPotValue -
        lastSmoothedPotValue) > potThreshold)
```

The threshold used in the program is:

```cpp
const int potThreshold = 4;
```

If the change is greater than this threshold, the potentiometer is considered to be intentionally moved.

### Step 4 — Potentiometer Gets Priority

When the potentiometer is moved, its value is converted into a servo angle:

```cpp
int servoAngle =
    map(currentSmoothedPotValue, 0, 1023, 0, 180);
```

The servo then moves between:

```text
0° → 180°
```

The Serial Monitor displays:

```text
Control: Potentiometer -- Angle: XX
```

### Step 5 — Joystick Takes Control

When the potentiometer is stable, the Arduino reads the joystick:

```cpp
int joyValue = analogRead(joyPin);
```

The joystick value is also mapped from:

```text
0 → 1023
```

to:

```text
0° → 180°
```

The servo is then controlled according to the joystick position.

The Serial Monitor displays:

```text
Control: Joystick -- Angle: XX
```

---

# 🔄 Working Flow

```text
              START
                ↓
        Initialize Servo
                ↓
       Read Potentiometer
                ↓
       Smooth Pot Reading
                ↓
   Has Potentiometer Moved?
          /             \
        YES              NO
         ↓                ↓
 Potentiometer        Read Joystick
    Control                 ↓
         ↓             Calculate Angle
 Calculate Angle            ↓
         ↓              Move Servo
     Move Servo              ↓
         ↓                   └──────┐
         └──────────────────────────┘
                    ↓
               Repeat Loop
```

---

# 📤 Uploading the Program

1. Open `potentiometer.ino` in Arduino IDE.
2. Connect the Arduino Nano to your computer.
3. Select:

```text
Tools → Board → Arduino AVR Boards → Arduino Nano
```

4. Select the correct COM port.
5. Click **Verify** to compile the program.
6. Click **Upload** to transfer the program to the Arduino.

After successful uploading, the servo will start responding to the potentiometer and joystick.

---

# 🖥️ Using the Serial Monitor

The program communicates at:

```cpp
Serial.begin(9600);
```

To view the output:

```text
Tools → Serial Monitor
```

Set the baud rate to:

```text
9600
```

You will see messages such as:

```text
Control: Joystick -- Angle: 92
Control: Joystick -- Angle: 125
Control: Potentiometer -- Angle: 145
```

This allows you to identify which input is currently controlling the servo.



# ⚠️ Important Notes

* Make sure the **Arduino, servo, joystick, and potentiometer share a common GND**.
* Do not accidentally connect the servo signal wire to 5V.
* The SG90 servo can draw more current than an Arduino Nano's onboard regulator can comfortably provide under some conditions. For reliable operation, an appropriate external 5V supply can be used, with its **GND connected to Arduino GND**.
* The actual usable servo angle may vary slightly depending on the servo model.

---


## 👩‍💻 Author

**Anushka Singh**

Built using **Arduino Nano, SG90 Servo Motor, Potentiometer, Joystick Module, and Arduino C/C++**.
