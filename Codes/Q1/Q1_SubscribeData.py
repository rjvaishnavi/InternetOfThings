#Installations to do:
#pip install paho-mqtt
#pip install tk


import tkinter as tk
from tkinter import *
import random
import paho.mqtt.client as mqtt
import json
from time import sleep
import time

# def collect_dht ():
# useUnsecuredTCP = True

channelID = "" # variable to store my channel ID
api_key = "" # variable to store my  API READ KEY 
mqtt_host = 'mqtt3.thingspeak.com' #mqtt host id

# my mqtt device details
mqtt_username = ""
mqtt_clientID = ""
mqtt_passwd = ""

topic = 'channels/' + channelID + '/subscribe'
temp = "Temperature Humidity"

t_port = 80 # connection port

#defining my own on_connect
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected Sucessfully!")
    else:
        print("Connect returned result code:" + str(rc))

#defining my own on_message recieved what should happen
def on_message(client, userdata, message):
    #print("reached")
    #print("Received message:", str(message.payload.decode("utf-8")))
    decoded_message=str(message.payload.decode("utf-8")) 
    msg= json.loads(decoded_message) # converting recieved message to a json format
   # print("Temperature = " + str(msg['field1']) + '* C')
   # print("Humidity = " + str(msg['field2']) + " %" )
    temp = " Temperature = " + str(msg['field1']) + "*c  Humidity = " + str(msg['field2']) + " %" 
    print(temp) #printing recieved values
    #T.insert(tk.END, temp)
    #label.configure(text=temp)
    #root.after(1, update_label, root, label)

#main function
def my_subscribe():
    client = mqtt.Client(mqtt_clientID)  #making a client mqtt object
    client.on_message = on_message 
    client.username_pw_set(mqtt_username, mqtt_passwd)
    client.on_connect = on_connect 
    client.connect(mqtt_host, 1883) #connecting to the mqtt client
    client.subscribe(topic)
    client.loop_forever() 

#the GUI portion
root = tk.Tk()
root.title("19MCME03- MQTT Subscribe")
root.geometry("400x300")

subscribe_button = tk.Button(root, text="Subscribe", command=my_subscribe, bg = '#ABC181', fg = 'blue')
subscribe_button.pack(pady = 20)
T = tk.Text(root, height=2, width=30,  padx=20, pady=20)
T.pack()
T.insert(tk.END, 'Subscribing Data\n')

# create button to implement destroy()
close_button =tk.Button(root, text="Close", command=root.destroy).pack(pady = 40)
root.mainloop()