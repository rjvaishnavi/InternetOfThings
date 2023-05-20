#pip3 install mysql-connector-python
#pip install Adafruit_DHT
#pip install tk

import mysql.connector
import time
import Adafruit_DHT
import tkinter as tk

# creating a connection to the MySQL database of the 16905 pi from another pi that has Raspi on it
db = mysql.connector.connect(
    host='192.168.1.100',
    port='3306',
    user='',
    password='',
    database=''
)

# creating a cursor to execute SQL commands
cursor = db.cursor()

# creating a table to store sensor data
cursor.execute('''
CREATE TABLE IF NOT EXISTS sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME NOT NULL,
    temperature FLOAT NOT NULL,
    humidity FLOAT NOT NULL
)
''')

# creating a function to get sensor data
def get_sensor_data():
    sensor = Adafruit_DHT.DHT11
    pin = 4
    humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
    if humidity is not None and temperature is not None:
        return humidity, temperature
    else:
        return None, None

#function to test db connection in local db server
#def get_sensor_data():
 #   return 10, 10


# creating a function to add sensor data to the database
def add_sensor_data():
    humidity , temperature = get_sensor_data()
    timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
    cursor.execute('INSERT INTO sensor_data (timestamp, temperature, humidity) VALUES (%s, %s, %s)', (timestamp, temperature, humidity))
    db.commit()
    print('Sensor data added successfully')

#add_sensor_data()
#add_sensor_data()
#add_sensor_data()

# GUI Portion
root = tk.Tk()
root.geometry("400x100")
root.title('Sensor Data Collection - 19MCME03')

# create a button to add sensor data to the database
add_data_button = tk.Button(root, text='Add DHT Sensor Data', command=add_sensor_data)
add_data_button.pack(pady = 20)

root.mainloop()