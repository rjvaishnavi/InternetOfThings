import thingspeak
import time
import tkinter as tk
import Adafruit_DHT

channel_id =  # variable to store my channel ID
write_key = '' # variable to store my  API WRITE KEY 

pin = 4 # DHT is connected to this pin
sensor = Adafruit_DHT.DHT11 

def measure(channel):
    try:
        humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
        if humidity is not None and temperature is not None:
            print('Temperature = {0:0.2f}*C Humidity = {1:0.2f}%'.format(temperature, humidity)) 
            # this is to print in the command line
        else:
            print('Did not receive any reading from sensor. Please check!')
        # pushing this new value to the cloud
        response = channel.update({'field1': temperature, 'field2': humidity})
    except:
           print("connection failure") # terminates program

if __name__ == "__main__":
        #channel = thingspeak.Channel(id=channel_id, write_key=write_key)
        channel = thingspeak.Channel(id=channel_id,api_key = write_key) # creating connection

        
def start():
     while True:
            measure(channel)
        #free account has a limitation of 15sec between the updates
            time.sleep(15) # time between seding updates

start()
# the GUI portion
root = tk.Tk()
root.title("19MCME03- MQTT Publish")
root.geometry("400x450")
subscribe_button = tk.Button(root, text="Publish", command=start, bg = '#ABC181', fg = 'blue')
subscribe_button.pack(pady = 20)
T = tk.Text(root, height=2, width=30,  padx=20, pady=40)
T.pack()
T.insert(tk.END, '\nPublishing Data\n')
# create button to implement destroy()
close_button =tk.Button(root, text="Close", command=root.destroy).pack(pady = 40)
root.mainloop()



'''
import Adafruit_DHT  
DHT11=Adafruit_DHT.DHT11  # Adafruit_DHT.DHT22 for DHT22 sensor.
while True:  
    try:  
        temp,humid=Adafruit_DHT.read_retry(DHT11,4) # 4 is ithe GPIO number you can change this to your required need  
        print("TEMP={0:0.1f}°C HUMIDITY={1:0.1f}%".format(temp,humid))  
    except KeyboardInterrupt:  
        break  
'''