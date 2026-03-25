# Bus Stop Request System (Arduino)

This project is a simple Arduino-based system designed for **commuters and bus drivers**. It allows passengers to signal when they want to stop, helping drivers respond quickly and safely.

---

## Project Overview

The system provides a **button-based stop request mechanism**:

- Passenger presses a button  
- System alerts the driver  
- Driver prepares to stop at the next location  

This improves:
- passenger convenience  
- driver awareness  
- transport efficiency  

---

## Features

### 🛑 Stop Request Button
- Passenger presses button to request stop  
- Simple and reliable  

---

### 🔔 Driver Alert System
- Activates buzzer when button is pressed  
- Provides immediate audio alert  

---

### 💡 Visual Indicator
- LED lights up when stop is requested  
- Clearly visible to driver  

---

### 🔄 Reset Mechanism
- System resets after stop  
- Ready for next passenger  

---

## System Workflow

### 1. Idle State
- System waits for passenger input  
- LED and buzzer are OFF  

---

### 2. Stop Request
- Passenger presses button  
- System:
  - turns ON buzzer  
  - turns ON LED  

---

### 3. Driver Response
- Driver sees LED and hears buzzer  
- Prepares to stop  

---

### 4. Reset
- System turns OFF after stop  
- Returns to idle state  

---

## Pin Configuration

| Component | Arduino Pin |
|----------|------------|
| Button   | 3          |
| Buzzer   | 8          |
| LED      | 13         |

---

## Wiring Connections

### 🔘 Button (Stop Request)
- One side → Pin **3**  
- Other side → **GND**  
- Uses `INPUT_PULLUP` (no resistor needed)

---

### 🔔 Buzzer
- Positive (+) → Pin **8**  
- Negative (–) → **GND**

---

### 💡 LED Indicator
- Positive (+) → Pin **13**  
- Negative (–) → **220Ω resistor → GND**

---

## Hardware Components

- Arduino (Uno / Nano)  
- Push Button  
- Buzzer  
- LED  
- 220Ω Resistor  
- Jumper Wires  
- Power Supply  

---

## Notes

- Uses internal pull-up resistor for button  
- Use active buzzer for easier setup  
- Ensure secure wiring (for moving vehicle use)  

---

## Limitations

- No wireless communication  
- No passenger count system  
- Manual reset (depending on code logic)  

---

## Summary

This project demonstrates a simple **bus stop request system** that helps:

- commuters easily signal stops  
- drivers respond quickly  
- improve public transport experience  

It is suitable for:

- buses  
- jeepneys  
- shuttle services  
- transportation prototypes  
