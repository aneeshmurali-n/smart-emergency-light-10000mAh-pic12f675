# Smart Emergency Light System 
> 🚧 This repository is under active development.
#### (with Battery Management, USB Output, and MCU Control)
This is an advanced emergency lighting solution powered by a 10,000mAh 6V battery (2 × 6V 5Ah in parallel) and managed by a PIC12F675 microcontroller. 
It integrates intelligent LED panel control, smart automatic charging, USB power output, status indication, manual override, and safety features like current limiting and relay-based automatic cutoff.

Unlike basic emergency lights, this system operates as a smart power hub, designed for efficient battery usage, real-time 
power status monitoring, and enhanced user interaction. It is optimized to extend battery life and deliver reliable backup power intelligently.
<br>
<br>
<br>
# 💡 Features

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
  <br>
---
<br>

# 💻⚙️ Key Hardware Components and Their Functions
<br>

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
| **LED Current Limit Resistors**       | 1kΩ resistors used for current limiting: R13, R14, R15, R16 for power supply indicator LEDs. R3, R4 270Ω used for charging and battery-low indicators. Also protect MCU GPIO pins.|
<br>
<br>
<br>

# ⚙️🔋 Functional Overview
<br>

# 🔌MCU & Relay Power Supply Calculation:
![image](https://github.com/user-attachments/assets/960b5701-4a17-4e42-867d-4ba9e1641357)

A 9V-0-9V center-tapped AC input is rectified using high-current diodes (1N5408) and filtered by large electrolytic capacitors to produce a stable 12V DC supply for relays and the MCU voltage regulator.

### Rectified Voltage Calculation:
```
VDC = VAC × √2 − diode drop
    = 9 × 1.414 − 0.7
    = 12.02V DC (approx)   
```
<br>

## 🔋🎛️LM317 MCU Regulator Output Voltage Calculation:

### 🔣 Formula:
```
Vout = 1.25 × (1 + R2 / R1) + Iadj × R2
```
- `Iadj` is typically ~50 μA (0.00005 A)


### 📌 Given:
- **R1 = R6 = 270Ω**
- **R2 = R7 + RP1 = 750Ω + 0–200Ω variable resistor**
- So, **R2 range: 750Ω to 950Ω**
- **Iadj ≈ 50μA**


### 📐 Calculations:

#### Case 1: **R2 = 750Ω**
```
Vout = 1.25 × (1 + 750 / 270) + 0.00005 × 750
     = 1.25 × (1 + 2.777) + 0.0375
     = 1.25 × 3.777 + 0.0375
     = 4.721 + 0.0375
     ≈ 4.76V
```

#### Case 2: **R2 = 950Ω**
```
Vout = 1.25 × (1 + 950 / 270) + 0.00005 × 950
     = 1.25 × (1 + 3.5185) + 0.0475
     = 1.25 × 4.5185 + 0.0475
     = 5.648 + 0.0475
     ≈ 5.70V
```

### 🧮 Solving for R2 for 5.00 V Output:

```
5.00 = 1.25 × (1 + R2 / 270) + 0.00005 × R2
```

Simplify:
```
5.00 = 1.25 + (1.25 / 270) × R2 + 0.00005 × R2
5.00 - 1.25 = R2 × (0.00463 + 0.00005)
3.75 = R2 × 0.00468
R2 = 3.75 / 0.00468 ≈ 801 Ω
```

### 🎛️ Potentiometer Adjustment:

- Fixed part: `R7 = 750 Ω`
- Potentiometer (RP1) required setting:
```
RP1 = R2 - R7 = 801 Ω - 750 Ω = 51 Ω
```

### ✅ Result:
With **R1 = 270Ω** and **R2 = 750Ω to 950Ω**, the LM317 output voltage will range approximately from:

```
Vout ≈ 4.76V to 5.70V
```
### ✅ Set the potentiometer to approximately **51 Ω** to get a stable **5.00 V** output from the LM317.


### ✅ Final Component Values:

| Component | Value           |
|----------:|------------------|
| **R6**    | 270 Ω (fixed)     |
| **R7**    | 750 Ω (fixed)    |
| **RP1**   | **51 Ω** (from 200 Ω range) |

---
<br>

# ⚡🔋Charging Power Supply, Current Limit & Control
![image](https://github.com/user-attachments/assets/23fa0a38-a06d-4c4c-9a1b-1a395165e2b6)

A 7.5V-0-7.5V center-tapped AC input is rectified using high-current diodes (1N5408) and filtered by large electrolytic capacitors to produce a stable DC voltage for battery charging.<br>

### Rectified Voltage Calculation:
```
VDC = VAC × √2 − diode drop
    = 7.5 × 1.414 − 0.7
    = 9.91V DC (approx)
```
<br>

## 🔋🔌 Battery Charging Current Limit: Requirements and Calculations

### 🔋 Battery Setup:
```
• Two 6V 5Ah batteries connected in parallel
• Total capacity:
  10Ah
• Recommended charge rate:
  C/10 = 10000mAh / 10 = 1000mA = 1A
```


### 🪫⚙️ Components That Limit Charging Current:

```
R10 and R11  
D8 = Diode with  0.7V forward voltage drop
```


### 📅 Calculating Required Resistance for 1A Limit
```
To find the required resistance to limit the charging current to 1A, we apply Ohm’s Law:
R = V / I
```


### ✅ Given:

- **Charging power supply voltage:** 9.91V  
- **Battery voltage (discharged):** 6V  
- **Diode D8 voltage drop:** 0.7V  
- **Target charging current:** 1A



### ⚡ Voltage across the resistors (R10,R11):
```
VR = V supply - V battery - V diode  
VR = 9.91V - 6V - 0.7V  
VR = 3.21V
```


### ⚡️Ω Required resistance:
```
R = V / I  
R = 3.21V / 1A  
R = 3.21Ω
```



✅ To limit charging current to **1A**, use a total resistance of **3.21Ω**  
So We can use R10 = 1Ω and R11 = 2.2Ω → **Total = 3.2Ω**, which gives approx **1.003A**

<br>
<br>

### 🔥 Resistor Power Dissipation Calculation: 
```
To calculate power (wattage) dissipated in the current-limiting resistors, use:

P = I² × R


✅ Given:
• Charging current I = 1A  
• R10 = 1Ω  
• R11 = 2.2Ω

Power in R10:
P = 1² × 1 = 1W

Power in R11:
P = 1² × 2.2 = 2.2W

✅ Total Power Dissipation:

P total = 1W + 2.2W = 3.2W
```

#### 🛡️ Recommended Resistor Ratings:
| Resistor | Actual Power | Recommended Rating |
|----------|--------------|--------------------|
| R10      | 1W           | 2W or 5W           |
| R11      | 2.2W         | 5W                 |

### ✅ Conclusion

We are using **5W resistors** for both **R10 (1Ω)** and **R11 (2.2Ω)**.

Since the calculated power dissipation is:

- **R10:** 1W  
- **R11:** 2.2W  
- **Total:** 3.2W

Using **5W-rated resistors** provides plenty of thermal margin, making the design:

- ✅ **Safe**
- ✅ **Sufficient**
- ✅ **Reliable** for long-term operation
---
























 






