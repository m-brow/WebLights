WebLights
=========

A Web interface to control basic RBG LED lights.
Designed to control multiple LED light strips at once.


The project has a couple of components:
1. node.js server backend
2. Basic HTML/JS frontend
3. ESP8266 microcontroller code


How it works
------------

The node.js server host a webpage which can individually control the RGB
channels on the light strip.
When a user sets the colour the server updates the RGB values in the /state page.

Meanwhile, each light strip is hooked up to a ESP8266 wifi enabled
microcontroller.
Every second each microcontroller does a GET request to http://weblight/state,
which shows the desired state for each LED channel.
The microcontroller changes the colour by adjusting the PWM output for each channel.

I've setup the node.js server to run on a RaspberryPi.

Prereqs
-------

- Setup RaspberryPi with npm
- Change the rpi hostname to 'weblight'
- RGB LED light strip hooked up to an ESP8622



Setup
----

- Use Platform.io to compile and flash the src/main.cpp file to the microcontroller
- Copy the repo to your rpi
- Navigate to the repo and start the server (`cd <path/to/repo>/web; node server.js`)
- Go to http://weblight/
- ???
- You can now control your lights in the most overly complicated way possible!
