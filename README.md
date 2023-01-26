

# temp_esp01_sensors
"Based on ESP01 device and DHT11 sensor for send temperature and humidity value on raspberry Pi 3(RPI3) Mosquitto broker, get the value on InfluxDB and see all on Grafana by any connect devices.

When the mqtt message arrived on the broker it will be intercept by mqtt_subscriber_ for_influxdb, it will parse it and store the data on local to the RPI3 Influxdb database.
Then a local Grafana server, show the value on any connected devices with 1" timeframe.

The RPI3 run at 22%CPU of this total capacity and 31%RAM of this total capacity.

It's absolutely necessary to connect an external storage for run the DB.
You have to modify the influxdb conf file for specify the path storage on your external storage.
Becarefull to accord the good right r and w for the external storage.

I add a Cronjob (crontab -e) who run a script with the main from mqtt_subscriber_for_influxdb.
The best solution is create services wo run at start (man systemctl).

I had install a telegraf server too for show the RPI3 metrics in live.

When i begin tis project i get many Nan value from the DHT11 sensor.
First it's a cheap sensor, we cannot expect great sensitivity from it.
Secondly the PSU (Power Supply) is really important for this type of project.
I recommand to have many attention with the choise of the PSU and the wiring of the esp01 and sensor.
ESP01 run at 3.3v and DHT11 run in the range of 3.3V and 6V.
The better results for me was obtain at 5V for the DHT11.

Thank's for reading !
; )"

