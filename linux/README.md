# Linux Quick Start Guide (Ubuntu, Raspberry Pi)
Tested on Raspberry Pi 3B PLUS 

### YOU MIGHT NOT AWARE OF THIS CLEARLY IN THE OFFICIAL GUIDE! 

`````````````````HERE LET ME RE-EMPHASIZE FOR ALL BLYNK NEWCOMER !`````````````
``` 
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
#define BLYNK_DEVICE_NAME "Quickstart Device"
```
### THESE TWO LINES MUST BE AT THE VERY TOP OF YOUR CODE (LINE 0!)
### ABOVE ANYTHING ELSE ! ALL HEADER FILES MUST COME AFTER THESE TWO LINES

This is related to old vs new Blynk server!

If you put the 
```
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
```
somewhere below the required Blynk header files,
the library will automatically set the default
server to 
```"blynk-cloud.com"```
which is the older server for Blynk 0.1(legacy) (no longer supported)
plus this won't work with the newer AUTH token provided from blynk.cloud!

Placing 
```
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
```
at the very top will allow the ```#ifdef``` method
inside ```BlynkConfig.h``` to select the newer Blynk server that is 
```"blynk.cloud"```

Here are the lines from BlynkConfig.h for your reference.
This is the sole reason why you CANNOT define ```BLYNK_TEMPLATE_ID```
below the pre-requisite Blynk header files.

```
#ifdef BLYNK_TEMPLATE_ID
#define BLYNK_DEFAULT_DOMAIN     "blynk.cloud"
#else
#define BLYNK_DEFAULT_DOMAIN     "blynk-cloud.com"
#endif
```

Trust me, I have wasted a day or two just trying to figure this out.
Hopefully this guide will help you save some time tinkering around the bushes.

### How to run this on your Raspberry Pi or any Linux machine

0. Connect your Raspberry Pi to the internet and open it's console. ^_^

1. Install WiringPi:
    http://wiringpi.com/download-and-install/

2. Download and build Blynk:
    ```bash
    $ git clone https://github.com/blynkkk/blynk-library.git
    $ cd blynk-library/linux
    ```
3. Edit Makefile for the source file you want to compile. By default, main.cpp is selected.

    ```
    $ sudo nano Makefile
    
    SOURCES=main.cpp \
	../src/utility/BlynkDebug.cpp \
	../src/utility/BlynkHandlers.cpp \
	../src/utility/BlynkTimer.cpp
    ```
    
4. Build the executable file (default build name is ```blynk```).
    ```
    $ make clean all target=raspberry
    ```

5. Run Blynk:
    ```bash
    $ sudo ./blynk --token=YourAuthToken
    
    OR
    
    // executing cloud.cpp from Makefile (no parsing required because everything is hard coded)
    
    $ sudo ./blynk 
    
    ```

We have also provided a build script, you can try just running (inside of the "linux" directory):

```bash
$ ./build.sh raspberry
```
