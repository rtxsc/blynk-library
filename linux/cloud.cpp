/**
 * @file       test.cpp
 * @author     ClumzyaziD
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2021 ClumzyaziD
 * @date       Nov 2021
 * @brief
 */
/***************************************************
 * Change these settings to match your need
 ***************************************************
#ifdef BLYNK_TEMPLATE_ID
#define BLYNK_DEFAULT_DOMAIN     "blynk.cloud"
#else
#define BLYNK_DEFAULT_DOMAIN     "blynk-cloud.com"
#endif

#define BLYNK_DEFAULT_PORT       80
#define BLYNK_DEFAULT_PORT_SSL   443

/*************************************************************/
#define BLYNK_TEMPLATE_ID   "TMPL4RlNw9L2"
#define BLYNK_DEVICE_NAME   "PieMeUp"
#define BLYNK_AUTH_TOKEN    "L21VqO7Hk9K5QfvUHS85-fyGDYr7LC_a"
#define SERVER              "blynk.cloud"
#define PORT                80
#define LEDwPi              21

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

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V1)
{
  // Set incoming value from pin V1 to a variable
  int value = param.asInt();
  digitalWrite(LEDwPi,value);

    printf("blynk.cloud server = Got a value: %d\n", value);
  // Update state
  Blynk.virtualWrite(V2, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://allinfo.space/wp-content/uploads/2020/10/643fbf2b8a707f9b0469d0b012854468.jpg");
  Blynk.setProperty(V3, "onImageUrl",  "https://media.istockphoto.com/illustrations/offline-twitch-hud-screen-banner-169-for-stream-offline-background-illustration-id1269086515?k=20&m=1269086515&s=170667a&w=0&h=_1alz5Br-8Lnz7I2Klyi8LJm62-oPLSRwIlSK49Ga4k=");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

BLYNK_DISCONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://media.istockphoto.com/illustrations/offline-twitch-hud-screen-banner-169-for-stream-offline-background-illustration-id1269086515?k=20&m=1269086515&s=170667a&w=0&h=_1alz5Br-8Lnz7I2Klyi8LJm62-oPLSRwIlSK49Ga4k=");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}


// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, millis() / 1000);
}

void setup()
{
    wiringPiSetup () ;
    pinMode (LEDwPi, OUTPUT) ; // GPIO21 BCM
    Blynk.begin(BLYNK_AUTH_TOKEN, SERVER, PORT);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

int main(int argc, char* argv[])
{
    // parse_options(argc, argv, auth, serv, port);

    setup();
    while(true) {
        loop();
    }

    return 0;
}
