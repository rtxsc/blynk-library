# Linux Quick Start Guide (Ubuntu, Raspberry Pi, ...)
## YOU MIGHT NOT NOTICE THIS CLEARLY! HERE LET ME RE-EMPHASIZE 
## #define BLYNK_TEMPLATE_ID "SomeTemplateID"
## #define BLYNK_DEVICE_NAME "Quickstart Device"
## THESE TWO LINES MUST BE AT THE VERY TOP OF YOUR CODE (LINE 0)
## ABOVE ANYTHING ELSE / ALL INCLUDED HEADER FILES MUST FOLLOW THESE TWO LINES

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
    ```

We have also provided a build script, you can try just running (inside of the "linux" directory):

```bash
$ ./build.sh raspberry
```
