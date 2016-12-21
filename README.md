# Postur3
An experiement for the ESSS 2017

It is a LEGO Mindstorms EV3 device, that measures the angle of your back/neck. It measures the distace to the upper back, while the lower back is pressing a button (to ensure that you are sitting and leaning your back). After it sends these measurements to the Arduino via I2C. Then the Arduino writes what it has received to a SD card for later reviewing.

It uses the LEGO Mindstorms EV3, the Mindstorms IR sensor, an Arduino (Genuino) UNO, the Mindstorms push button and a TFT screen shield for the Arduino (I am using it as the SD card slot). The LEGO Mindstorms EV3 is also using a 3rd party programming block to connect Arduino with the EV3, from dexterindustries.com.