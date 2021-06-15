In this lab work, you will use temperature, humidity and light data to monitor condition
of a baby’s room. You are required to create a circuit with an Arduino board, DHT11
temperature and humidity sensor, LDR light sensor, 10K potentiometer and other
necessary equipment using Arduino Software (IDE).
You should measure the LDR maximum and minimum resistance values in order to
build a voltage divider circuit with a 10K potentiometer. You will place an analog input
of your Arduino’s A0 pin between LDR and Potentiometer. LDR will be used to
determine the day or night value by means of analog reading. The threshold of the Day
and Night sensor should be around 400. Therefore, you need to calibrate your circuit
with the potentiometer, and this step is necessary.
Experiment
You will design a circuit of LDR light sensor and DHT11 temperature and humidity
sensor. You will write an Arduino program to monitor conditions of a room using
temperature, humidity and light data concerning following thresholds.


Thresholds are:
Humidity ϵ [30%, 50%] → “Optimal Humidity”
Humidity < 30% → “Low Humidity”
Humidity > 50% → “High Humidity”
Light >= 400 → “Day”
Light < 400 → “Night”


Temperature during Day ϵ [20°C, 24°C] → “Optimal Temperature”
Temperature during Day < 20°C → “Cold”
Temperature during Day > 24°C → “Hot”
Temperature during Night ϵ [18°C, 21°C] → “Optimal Temperature”
Temperature during Night < 18°C → “Cold”
Temperature during Night > 21°C → “Hot”

Your program should display relevant description on the serial monitor window in an interval of 3
seconds. The text format should be as follow:


Date: 03.06.2021 - Hour: 17:19 – Light: 580 Temperature: 30°C -
Humidity: 45%
Day – Hot - Optimal humidity
------------------------------------
Date: 03.06.2021 - Hour: 18:17 – Light: 353 Temperature: 23°C -
Humidity: 30%
Night – Hot - Low humidity
------------------------------------
Date: 03.06.2021 - Hour: 19:53 – Light: 269 Temperature: 18°C -
Humidity: 70%
Night – Optimal temperature - High humidity
------------------------------------
Date: 03.06.2021 - Hour: 20:14 – Light: 153 Temperature: 16°C -
Humidity: 29%
Night – Cold - Low humidity 