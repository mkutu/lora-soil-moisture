# LoRa-Based Soil Moisture, Temperature, and Humidity Monitoring System

This project demonstrates how to set up a LoRa-based soil moisture, temperature, and humidity monitoring system using Adafruit Feather M0 with RFM95 LoRa Radio and Monk Makes Plant Monitor. The system reads sensor data and transmits it via LoRa to a Raspberry Pi, which acts as the receiver.

### Repository Structure

```
lora-soil-moisture/
├── README.md
├── transmitter/
│   └── transmitter.ino
└── receiver/
    └── receiver.py
```

## Components

### Transmitter
- [Adafruit Feather M0 with RFM95 LoRa Radio (Product ID: 3178)](https://www.adafruit.com/product/3178)
- [Monk Makes Plant Monitor - Capacitive Moisture Meter - Temperature & Relative Humidity (Product ID: 5587)](https://www.adafruit.com/product/5587)
- [3.7V LiPo Battery](https://www.adafruit.com/product/3898)
- Antenna for RFM95
- Jumper Wires

### Receiver
- Raspberry Pi (Any model with GPIO pins, e.g., Raspberry Pi 3, 4, or Zero)
- [RFM95W LoRa Module](https://www.adafruit.com/product/4074)
- Jumper Wires
- MicroSD Card (16GB or larger recommended)
- Power Supply (5V 2.5A for Raspberry Pi)
- Antenna for RFM95W

## Wiring

### Transmitter Wiring (Feather M0 with RFM95)

| Monk Makes Plant Monitor | Adafruit Feather M0 with RFM95 |
|--------------------------|-------------------------------|
| GND                      | GND                           |
| 3V                       | 3.3V                          |
| RX_IN                    | TX (Pin 1)                    |
| TX_OUT                   | RX (Pin 0)                    |
| ANALOG                   | Analog Pin (A0)               |

### Receiver Wiring (Raspberry Pi)

| RFM95W LoRa Module | Raspberry Pi GPIO Pins          |
|--------------------|---------------------------------|
| VCC                | 3.3V                            |
| GND                | GND                             |
| MISO               | GPIO 9 (MISO)                   |
| MOSI               | GPIO 10 (MOSI)                  |
| SCK                | GPIO 11 (SCK)                   |
| NSS (CS)           | GPIO 8 (CE0)                    |
| RST                | GPIO 25                         |
| DIO0               | GPIO 24                         |




## Setup

### Transmitter Code (Feather M0)
1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/lora-soil-moisture.git
   cd lora-soil-moisture/transmitter
   ```

2. **Open the Code**:
   - Open `transmitter.ino` in the Arduino IDE.

3. **Select the Board**:
   - In the Arduino IDE, go to `Tools` > `Board` > `Adafruit Feather M0`.

4. **Select the Port**:
   - Go to `Tools` > `Port` and select the appropriate port for your Feather M0.

5. **Upload the Code**:
   - Click the `Upload` button in the Arduino IDE to upload the code to the Feather M0.

### Receiver Code (Raspberry Pi)
1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/lora-soil-moisture.git
   cd lora-soil-moisture/receiver
   ```

2. **Install Required Libraries**:
   ```sh
   sudo apt-get update
   sudo apt-get install python3-pip
   pip3 install RPi.GPIO spidev git+https://github.com/hallard/LoRa
   ```

3. **Run the Receiver Code**:
   ```sh
   sudo python3 receiver.py
   ```

## Transmitter Code

The transmitter code reads data from the Plant Monitor and sends it via LoRa. Place this code in `transmitter/transmitter.ino`.

### Receiver Code

The receiver code receives data from the Feather M0 and prints it to the console. Place this code in `receiver/receiver.py`.




## Steps to Connect Multiple Sensors
To connect multiple sensors and send their data to a single receiver, each sensor must be connected to its own Feather M0 with RFM95 LoRa Radio, and each Feather M0 must send data using a unique identifier. The receiver will then distinguish between the data from different sensors based on these identifiers.


1. **Setup Each Sensor with its own Feather M0:**
   - Each sensor will be connected to a separate Feather M0 with RFM95 LoRa Radio.
   - Each Feather M0 will have its own code that includes a unique identifier.

2. **Modify the Transmitter Code to Include a Unique Identifier:**
   - Each transmitter will include a unique ID in the payload.

3. **The Receiver Code Handles Multiple Sensors:**
   - The receiver code will parse the incoming data to distinguish between different sensors based on the unique IDs.

### Transmitter Code (Each Feather M0)

Modify the `transmitter.ino` code to include a unique identifier for each sensor. For example, let's say you have two sensors. You can assign IDs `1` and `2` to them.


## Contributing
Feel free to submit issues, fork the repository and send pull requests. Any contributions are welcome!

## License
This project is licensed under the MIT License.

## Resources

1. [AdaFruit Feather 32u4 with LoRa Radio Module (transmitter) tutorial](https://learn.adafruit.com/adafruit-feather-32u4-radio-with-lora-radio-module)
2. [Adafruit Feather 3D printed case tutorial](https://learn.adafruit.com/3d-printed-case-for-adafruit-feather)
3. [3rd party soil moisture sensor tutorial](https://blog.rubenwardy.com/2022/03/17/plant-monitor/)
