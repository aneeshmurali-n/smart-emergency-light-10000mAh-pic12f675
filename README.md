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
  - Green LED blinks while charging, stays solid when fully charged
  - Red LED glows when battery is critically low (only when plugged in)
  - Separate indicators for 12V and 5V power presence

- 🛡️ **Overcurrent protection**  
  Implemented with high-wattage resistors and protective diodes

- 🔌 **Switchable outputs**  
  Independent switching for USB and dual LED panels

- 🔧 **Adjustable MCU supply voltage (4.76V – 5.70V)**  
  To set and maintain the ADC reference voltage precisely at **5.00V** for improved measurement accuracy




---

## 💻⚙️ Key Hardware Components and Their Functions
| Component                             | Description |
| ------------------------------------- | --------------------------------------------------------------------------------------------|
| **MCU**                               | PIC12F675 – Handles control logic, monitoring, and switching.|
| **MCU Regulator**                     | LM317 adjustable regulator for MCU supply and ADC reference (4.76V–5.70V).|
| **USB Regulator**                     | LD1117AG (5V LDO) – Provides regulated 5V output for light USB loads (e.g., USB lamps).|
| **Relays**                            | JSM1-12V-5 (×2) – For automatic LED panel switching, charging control, and cutoff.|
| **Diodes**                            | 1N5408 – For rectification (D1, D2, D4, D5), M7 or 1N4007 – For back-EMF protection (D6, D7).|
| **LEDs**                              | 3mm Green/Red (×5) – Status indicators for charging, power presence, and low battery.|
| **Power Resistors**                   | 1Ω 5W, 2.2Ω 1W (R11, R10) – Used to limit charging current to approximately 1 amp. |
| **Voltage Drop Diode**                | D8 – Drops 0.6–0.7V to help limit charging current (in combination with R10, R11) and also prevents reverse current flow. |
| **1W Resistors**                      | 2.2kΩ 1W (R8, R9) – Discharge bulk capacitors quickly to enable fast relay release and faster LED panel switching. |
| **Electrolytic Capacitors**           | 100µF/25V, 1000µF/25V – Used as bulk filtering capacitors.|
| **Ceramic Capacitors**                | 0.1µF/100V X7R – For decoupling and ADC input filtering.|
| **Start Charging Button**             | KEY1 – SPST momentary panel push button (e.g., 6×6×8mm tactile type) used to manually initiate charging by pulling the MCU GPIO pin low. |
| **Charging Button Pull-up Resistor**  | 4.7kΩ (R5) – Keeps the GPIO pin high by default. When the button is pressed, it pulls the pin low to trigger charging. Also limits current into the GPIO.|
| **Potentiometer**                     | RP1 (200Ω multi-turn) – Used to fine-tune the MCU supply and ADC reference voltage. Adjust to precisely 5.00V before inserting the MCU for accurate operation.|
| **LM317 Output Voltage Set Resistor** | Fixed: R6 (270Ω), R7 (750Ω); Adjustable: RP1 (0–200Ω) – Used to set LM317 output voltage (\~4.73V–5.65V). Adjust RP1 to \~60Ω for 5.00V (MCU + ADC reference).|
| **Voltage Sensor**                    | 33kΩ (R1, R2) – Forms a voltage divider to scale down input voltage by half, enabling safe battery voltage measurement and protecting the MCU GPIO. Match resistor values using a multimeter for better accuracy. |
| **Base Current Limit Resistor**       | 1kΩ (R12) – Sets the base current for the relay driver transistor and protects the MCU GPIO pin. |
| **Relay Driver**                      | 2N5551 (Q1) – NPN transistor used to drive the relay using the microcontroller’s output signal. |
| **Input Isolation Diode**             | M7 or 1N4007 (D3) – Isolates the LM317’s input capacitor (100µF, C6) from the main bulk capacitor (1000µF, C8), and prevents reverse current flow. |
| **LED Current Limit Resistors**       | 1kΩ resistors used for current limiting: R13, R14, R15 for power supply indicator LEDs. R3, R4 270Ω used for charging and battery-low indicators. Also protect MCU GPIO pins.|


## ⚙️🔋 Functional Overview

The **Smart Emergency Light** is a microcontroller-based system designed for automatic lighting and intelligent battery charging. It operates on a dual 6V 5Ah SLA battery pack (connected in parallel for 10Ah capacity), providing long-lasting backup power.

### 🔌 Power Input & Regulation
A 9-0-9V AC input is rectified using high-current diodes (1N5408) and filtered by large electrolytic capacitors to produce a stable DC voltage.<br>
**Rectified Voltage Calculation:**
```
VDC = VAC × √2 − diode drop
    = 9 × 1.414 − 0.7
    = 12.02V DC (approx)
```
## 🔋🔁 Power Switching and Relay Operation Overview

The system uses a **rectified and filtered 12V DC** derived from a 9-0-9V AC input (via 1N5408 diodes and large electrolytic capacitors). This 12V DC powers:

- The **LM317 voltage regulator** for the MCU and ADC reference.
- The **charging relay (K1)**.
- The **auto ON/OFF relay (K2)**, which controls LED panel and USB power.

---

### 🔌 Normal (Power ON) Operation

1. The **battery’s positive terminal** connects to the **COM (Common)** of the **charging relay (K1)**.
2. The **NC (Normally Closed)** of K1 is connected to the **NC of K2 (auto ON/OFF relay)**.
3. The **COM of K2** is the final **output** to the **LED panels** and **USB regulator input**.

This forms the path:  
➡️ **Battery → K1 (COM → NC) → K2 (NC → COM) → Output (LEDs/USB)**

4. The **NO (Normally Open)** contact of K1 connects to the **charging voltage**.
5. **K2** is directly powered by the 12V DC line.  
   - When the system is plugged into AC (12V present), **K2 is energized**:
     - COM → NO path is active.
     - The **battery is disconnected** from the load.

---

### 🔄 Charging Control via MCU

- The **MCU monitors battery voltage**.
- When the battery is low or the **charge button is pressed**, the MCU:
  - Sends **5V to the base of Q1 (2N5551)**.
  - Q1 turns **ON**, energizing **K1**.
  - **K1 switches to NO**, connecting **battery → charger**.
  - This **disconnects battery from load** during charging.

- When charging is complete or not needed:
  - MCU sets Q1 base **LOW (0V)**.
  - **K1 de-energizes**, reconnecting the battery to the load via NC.

---

### ⚠️ Power Outage Handling

- If **AC power is lost**, the 12V line drops.
- The **K2 relay de-energizes** and switches to its **Normally Closed (NC)** contact.
- This automatically **connects the battery to the output**, supplying power to the LED panels and USB regulator.
- The outputs (LED panels, USB devices) are controlled via **independent switches**, allowing manual on/off control during backup mode.

---

### ⚡ Fast Switchover Design

To enable **quick transition during outages**:

- The bulk capacitor **C8 (1000µF)** must discharge rapidly.
- Two **2.2kΩ 1W resistors (R8, R9)** are placed in **parallel across C8**.
- This allows **K2 to release quickly**, ensuring the battery connects to the load without delay.












 






