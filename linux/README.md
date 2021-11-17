# Linux Quick Start Guide (Ubuntu, Raspberry Pi)
Tested on Raspberry Pi 3B PLUS 

### YOU MIGHT NOT AWARE OF THIS CLEARLY IN THE OFFICIAL GUIDE! 

```HERE LET ME RE-EMPHASIZE FOR ALL BLYNK NEWCOMER !```
``` 
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
#define BLYNK_DEVICE_NAME "Quickstart Device"
```
### THESE TWO LINES MUST BE AT THE VERY TOP OF YOUR CODE ```(LINE 0!)```
### ABOVE ANYTHING ELSE ! ALL HEADER FILES MUST COME AFTER THESE TWO LINES

This is related to old vs new Blynk server transition!
For starters, Blynk has 2 servers currently running.

```blynk-cloud.com``` 	: old server for Blynk 0.1 (legacy)

```blynk.cloud```	: new server for Blynk

If you somehow didn't really read or understand the situation and put the 
```
#define BLYNK_TEMPLATE_ID "SomeTemplateID"
```
somewhere below the required Blynk header files,
the library will automatically set the default
server to 
```"blynk-cloud.com"```
that is the older server for Blynk 0.1(legacy) (no longer supported)
plus this won't work with the newer AUTH token provided from ```blynk.cloud```!

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

# Example

### Code Sample 1 : Running the app with command line parsing method for Auth Token (default)

```
#define BLYNK_TEMPLATE_ID   "Your Template ID"
#define BLYNK_DEVICE_NAME   "Your Device Name"

//#define BLYNK_DEBUG
#define BLYNK_PRINT stdout
#ifdef RASPBERRY
  #include <BlynkApiWiringPi.h>
#else
  #include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

static const char *auth, *serv;
static uint16_t port;

#include <BlynkWidgets.h>

BlynkTimer tmr;

BLYNK_WRITE(V1)
{
    printf("Got a value: %s\n", param[0].asStr());
}

void setup()
{
    printf("Running blynk with parsed parameters\n");
    Blynk.begin(auth, serv, port);
    tmr.setInterval(1000, [](){
      Blynk.virtualWrite(V2, BlynkMillis()/1000);
    });
}

void loop()
{
    Blynk.run();
    tmr.run();
}


int main(int argc, char* argv[])
{
    parse_options(argc, argv, auth, serv, port); // perform command line parsing for Auth Token (required)

    setup();
    while(true) {
        loop();
    }

    return 0;
}

```

### Code Sample 2 : Running the app without command line parsing method for Auth Token (hard coding everthing in the code)

```
#define BLYNK_TEMPLATE_ID   	"Your Template ID"
#define BLYNK_DEVICE_NAME   	"Your Device Name"
#define BLYNK_AUTH_TOKEN    	"Your Auth Token" // this will be coming from your blynk.cloud server NOT blynk-cloud.com
#define SERVER		    	"blynk.cloud"
#define PORT			80

//#define BLYNK_DEBUG
#define BLYNK_PRINT stdout
#ifdef RASPBERRY
  #include <BlynkApiWiringPi.h>
#else
  #include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

static const char *auth, *serv;
static uint16_t port;

#include <BlynkWidgets.h>

BlynkTimer tmr;

BLYNK_WRITE(V1)
{
    printf("Got a value: %s\n", param[0].asStr());
}

void setup()
{
    printf("Running blynk with hardcoded parameters\n");
    Blynk.begin(BLYNK_AUTH_TOKEN, SERVER, PORT);
    tmr.setInterval(1000, [](){
      Blynk.virtualWrite(V2, BlynkMillis()/1000);
    });
}

void loop()
{
    Blynk.run();
    tmr.run();
}


int main(int argc, char* argv[])
{
    setup();
    while(true) {
        loop();
    }

    return 0;
}

```
