import requests
import json
import serial
import time
import datetime
reg_no = raw_input().strip()
ser = serial.Serial('COM3', 9600)
fixed_interval = 10
firebase_url = "https://vehicle-detection-system.firebaseio.com/"
humid,smoke,lat,lon = "","","",""
while 1:
    try:
        general = ser.readline().strip().split(':')
        print(general)
        time_now = datetime.datetime.utcnow()
        if general[0] == 'H':
            humid = general[1]
        if general[0] == 'S':
            smoke = general[1]
        if general[0] == 'l':
            lat = float(general[1]) / 1000000
            print lat
        if general[0] == 'L':
            lon = float(general[1]) / 1000000
            print lon
        data = {'humid':humid,'smoke':smoke,'lat':str(lat),'lon':str(lon),'time':str(time_now)}
        result = requests.patch(firebase_url +'/'+ reg_no +'/' +'vehicle.json', data=json.dumps(data))
        #time.sleep(fixed_interval)
    except:
        print("Something")
        break
