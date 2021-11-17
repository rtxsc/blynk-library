# Linux Quick Start Guide (Ubuntu, Raspberry Pi, ...)
Tested on Raspberry Pi 3B PLUS 

### YOU MIGHT NOT NOTICE THIS CLEARLY IN THE OFFICIAL GUIDE! 

HERE LET ME RE-EMPHASIZE FOR ALL BLYNK NEWCOMER
``` 
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
#define BLYNK_DEVICE_NAME "Quickstart Device"
```
### THESE TWO LINES MUST BE AT THE VERY TOP OF YOUR CODE (LINE 0!)
### ABOVE ANYTHING ELSE ! ALL HEADER FILES MUST COME AFTER THESE TWO LINES
```
This is related to old vs new Blynk server!

If you put the #define BLYNK_TEMPLATE_ID "SomeTemplateID"
somewhere below the required Blynk header files,
the library will automatically set the default
server to "blynk-cloud.com" which is the older server for Blynk 0.1(legacy) (no longer supported)

Placing #define BLYNK_TEMPLATE_ID "SomeTemplateID" at the very top will allow the #ifdef method
inside BlynkConfig.h to select the newer Blynk server that is "blynk.cloud"

Trust me, I have wasted a day or two just trying to figure this out.

```

0. Connect your Raspberry Pi to the internet and open it's console. ^_^

1. Install WiringPi:
    http://wiringpi.com/download-and-install/

2. Download and build Blynk:
    ```bash
    $ git clone https://github.com/blynkkk/blynk-library.git
    $ cd blynk-library/linux
    $ make clean all target=raspberry
    ```

3. Run Blynk:
    ```bash
    $ sudo ./blynk --token=YourAuthToken
    
    OR
    // if running cloud.cpp (no parsing required because everything is hard coded)
    bash
    $ sudo ./blynk 
    
    
    ```

We have also provided a build script, you can try just running (inside of the "linux" directory):

```bash
$ ./build.sh raspberry
```
