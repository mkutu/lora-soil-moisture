import time
import RPi.GPIO as GPIO
from sx127x import SX127x
from sx127x.board_config import BOARD
from sx127x.constants import MODE, CODING_RATE

class LoRaReceiver(SX127x):
    def __init__(self, verbose=False):
        super(LoRaReceiver, self).__init__(board_config=BOARD, verbose=verbose)
        self.set_mode(MODE.SLEEP)
        self.set_dio_mapping([0] * 6)

    def start(self):
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT)
        while True:
            if GPIO.input(BOARD.DIO0) == 1:
                # Read the incoming payload
                payload = self.read_payload(nocheck=True)
                
                # Check if the payload length is as expected
                if len(payload) == 7:
                    # Extract the sensor ID from the first byte of the payload
                    sensor_id = payload[0]
                    
                    # Extract the moisture value from the next two bytes
                    moisture = (payload[1] << 8) | payload[2]
                    
                    # Extract the temperature value from the next two bytes
                    temperature = (payload[3] << 8) | payload[4]
                    
                    # Extract the humidity value from the last two bytes
                    humidity = (payload[5] << 8) | payload[6]
                    
                    # Print out the data along with the sensor ID
                    print(f"Sensor ID: {sensor_id}")
                    print(f"Soil Moisture: {moisture}")
                    print(f"Temperature: {temperature}")
                    print(f"Humidity: {humidity}")
                
                # Reset the RX pointer to prepare for the next packet
                self.reset_ptr_rx()
                self.set_mode(MODE.RXCONT)
            
            # Small delay to avoid excessive CPU usage
            time.sleep(1)

# Board configuration
BOARD.setup()
BOARD.reset()

# Initialize the LoRa receiver
lora = LoRaReceiver(verbose=False)

# Set up the LoRa parameters
lora.set_pa_config(pa_select=1)
lora.set_spreading_factor(7)
lora.set_bandwidth(7)
lora.set_coding_rate(CODING_RATE.CR4_5)
lora.set_preamble(8)
lora.set_freq(915.0)
lora.set_sync_word(0x34)
lora.set_power(14)

try:
    lora.start()
except KeyboardInterrupt:
    print("KeyboardInterrupt")
finally:
    print("Cleaning up")
    GPIO.cleanup()
