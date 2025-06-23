# Smart Emergency Light System
#### (with Battery Management, USB Output, and MCU Control)
This is an advanced emergency lighting solution powered by a 10,000mAh 6V battery (2 × 6V 5Ah in parallel) and managed by a PIC12F675 microcontroller. 
It integrates intelligent LED panel control, smart automatic charging, USB power output, status indication, manual override, and safety features like current limiting and relay-based automatic cutoff.

Unlike basic emergency lights, this system operates as a smart power hub, designed for efficient battery usage, real-time 
power status monitoring, and enhanced user interaction. It is optimized to extend battery life and deliver reliable backup power intelligently.

## 💡 Features

- 🔋 **10,000mAh 6V rechargeable battery**  
  (2 × 6V 5Ah batteries connected in parallel)

- 🧠 **Microcontroller-based control**  
  Powered by the PIC12F675 MCU

- ⚡ **Smart current-limited battery charging**  
  Uses power resistors with MCU-based monitoring and automatic cutoff

- 🔌 **USB power output**  
  5V regulated via LD1117 LDO

- 💡 **Automatic LED panel control**  
  ON/OFF functionality using relays

- 🧲 **Manual charge initiation**  
  Triggered via a microswitch (KEY1 – force charge button)

- 🔴 **LED Indicators:**
  - Green LED blinks while charging; stays solid when fully charged
  - Red LED glows when battery is critically low (only when plugged in)
  - Separate indicators for 12V and 5V power presence

- 🛡️ **Overcurrent protection**  
  Implemented with high-wattage resistors and protective diodes

- 🔌 **Switchable outputs**  
  Independent switching for USB and dual LED panels

- 🔧 **Adjustable MCU supply voltage (4.76V – 5.70V)**  
  To set and maintain the ADC reference voltage precisely at **5.00V** for improved measurement accuracy

---
## 💻⚙️ Major Hardware Components

| Component             | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| **MCU**              | PIC12F675 – Handles control logic, monitoring, and switching                |
| **MCU Regulator**    | LM317 adjustable regulator for MCU supply and ADC reference (4.76V–5.70V)   |
| **USB Regulator**    | LD1117AG (5V LDO) – Provides regulated 5V output for light USB loads (e.g., USB lamps) |
| **Relays**           | JSM1-12V-5 (×2) – For automatic LED panel switching, charging control, and cutoff |
| **Diodes**              | 1N5408 – For rectification (D1, D2, D4, D5); M7 or 1N4007 – For back-EMF protection (D6, D7) |
| **LEDs**             | 3mm Green/Red (×5) – Status indicators for charging, power presence, and low battery |
| **Power Resistors**   | 1Ω 5W, 2.2Ω 1W (R11,R10) – Used to limit charging current to approximately 1 amp     |
| **Voltage Drop Diode** | D8 – Drops 0.6–0.7V to help limit charging current (in combination with R10, R11) and also prevents reverse current flow |
| **1W Resistors**     | 2.2KΩ 1W (R8, R9) – Discharge bulk capacitors quickly to enable fast relay release and faster LED panel switching |
| **Electrolytic Caps**| 100µF/25V, 1000µF/25V – Used as bulk filtering capacitors                    |
| **Ceramic Caps**     | 0.1µF/100V X7R – For decoupling and ADC input filtering                      |
| **Button**           | KEY1 – SPST momentary panel push button or 6×6×8mm tactile push button       |
| **Potentiometer**    | RP1 (200Ω multi-turn) – For fine-tuning MCU supply and ADC reference voltage |
| **Voltage Sensor**    | 33kΩ (R1, R2) – Forms a voltage divider to scale down input voltage by half, allowing safe battery voltage measurement and protecting the MCU GPIO |
| **Base Current Limit Resistor** | 1kΩ (R12) – Sets the base current for the relay driver transistor and protects the MCU GPIO pin |
| **Relay Driver** | 2N5551 (Q1) – NPN transistor used to drive the relay using the microcontroller’s output signal |


 






