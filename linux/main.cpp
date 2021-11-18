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
#define BUTTON_MAKER_PHAT   22
#define RELAY               12

#define BLYNK_PRINT stdout

#ifdef RASPBERRY
 #include <BlynkApiWiringPi.h>
#else
 #include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>
#include <string>

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

static const char *auth, *serv;
static uint16_t port;

#include <BlynkWidgets.h>

BlynkTimer timer;
WidgetLED led1(V2);
bool btnState;
bool ledState;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V1)
{
  // Set incoming value from pin V1 to a variable
  int value = param.asInt();
  ledState = value; // sync ledState with value
  digitalWrite(LEDwPi,value);
  digitalWrite(RELAY,value);
  // Update state
  if(value) led1.on();
  else led1.off();
}

BLYNK_WRITE(V4) {
  GpsParam gps(param);

  // Print 6 decimal places for Lat, Lon
  printf("Lat: ");
  printf("%f", gps.getLat(), 7);

  printf("Lon: ");
  printf("%f",gps.getLon(), 7);

  // Print 2 decimal places for Alt, Speed
  printf("Altitute: ");
  printf("%f",gps.getAltitude(), 2);

  printf("Speed: ");
  printf("%f",gps.getSpeed(), 2);

}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.virtualWrite(V1, !digitalRead(BUTTON_MAKER_PHAT)); // to reset Virtual Gate Button
  Blynk.virtualWrite(V2, !digitalRead(BUTTON_MAKER_PHAT)); // to reset LED

  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://allinfo.space/wp-content/uploads/2020/10/643fbf2b8a707f9b0469d0b012854468.jpg");
  Blynk.setProperty(V3, "onImageUrl",  "https://media.istockphoto.com/illustrations/offline-twitch-hud-screen-banner-169-for-stream-offline-background-illustration-id1269086515?k=20&m=1269086515&s=170667a&w=0&h=_1alz5Br-8Lnz7I2Klyi8LJm62-oPLSRwIlSK49Ga4k=");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void checkPhysicalButton()
{
  if (digitalRead(BUTTON_MAKER_PHAT) == false) {
    // btnState is used to avoid sequential toggles
    if (btnState != false) {

      // Toggle LED state
      ledState = !ledState;
      if(ledState) led1.on();
      else led1.off();
      digitalWrite(LEDwPi,  ledState);
      digitalWrite(RELAY,   ledState);

      // Update Button Widget
      Blynk.virtualWrite(V1, ledState);
      Blynk.virtualWrite(V2, ledState);
    }
    btnState = false;
  } 
  else 
  {
    btnState = true;
  }
  // printf("button state:%d led state:%d\n", btnState,ledState);
}

void sendTemperature()
{
  // Generate random temperature value 10.0 to 30.0 (for example)
  float t = float(rand()%100);
  // Send it to the server
  Blynk.virtualWrite(V5, t);
}

void sendSomeString()
{
  // Generate random temperature value 10.0 to 30.0 (for example)
    const char* str1 = "Hello there from Raspberry Pi ";
    int n1 = millis() / 1000L;
    int MAX = 100;
    char *num;
    char buffer[MAX];

    if (asprintf(&num, "%d", n1) == -1) {
        perror("asprintf");
    } else {
        strcat(strcpy(buffer, str1), num);
        // printf("%s\n", buffer);
        // free(num);
    }  
  Blynk.virtualWrite(V6, buffer);
}

void myTimerEvent()
{
  /*
  asprintf function to store the passed integer as a character string. 
  asprintf is part of the GNU C library extension and 
  may not be available in other implementations. 
  It works similarly to sprintf except that the destination 
  character string buffer is allocated dynamically using the 
  malloc function call internally, and the returned pointer 
  should be freed before the program exit. 
  */
    const char* unit = " min";
    unsigned int currentMillis = millis();
    unsigned int seconds = currentMillis / 1000L;
    unsigned int minutes = seconds / 60;
    unsigned int hours = minutes / 60;
    unsigned int days = hours / 24;
    currentMillis %= 1000;
    seconds %= 60;
    minutes %= 60;
    hours %= 24;

    int bufferSize = 10;
    char *currentMillisStr, *secondsStr, *minuteStr, *hoursStr, *daysStr;
    char buffer[bufferSize];
    char bufferMinSec[bufferSize];
    char bufferDayHour[bufferSize];

    asprintf(&secondsStr, "%d", seconds);
    asprintf(&minuteStr, "%d", minutes);
    asprintf(&hoursStr, "%d", hours);
    asprintf(&daysStr, "%d", days);

    strcat(secondsStr,"s");
    strcat(minuteStr,"m:");
    strcat(hoursStr,"h:");
    strcat(daysStr,"d:");

    strcpy(bufferMinSec,strcat(minuteStr,secondsStr));
    strcpy(bufferDayHour, strcat(daysStr,hoursStr));
    strcpy(buffer,strcat(bufferDayHour,bufferMinSec));

    Blynk.virtualWrite(V0, buffer);


    // if (asprintf(&minuteStr, "%d", minutes) == -1) {
    //     perror("asprintf");
    // } else {
    //     strcat(strcpy(buffer, minuteStr),unit);
    //     // printf("minuteInt=%d minuteStr=%s buffer=%s\n", minutes, minuteStr, buffer);
    //     Blynk.virtualWrite(V0, buffer);
    //     // free(num);
    // }  
}

void setup()
{
    Blynk.notify("Device started");
    wiringPiSetup () ;
    pinMode (LEDwPi, OUTPUT) ; // GPIO21 BCM
    pinMode (RELAY, OUTPUT) ; // GPIO12 BCM
    digitalWrite(RELAY, false); // reset to off state at boot
    digitalWrite(LEDwPi, false); // reset to off state at boot

    pinMode (BUTTON_MAKER_PHAT, INPUT);
    Blynk.begin(BLYNK_AUTH_TOKEN, SERVER, PORT);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1000L, sendTemperature);
  timer.setInterval(1000L, sendSomeString);
  timer.setInterval(100L, checkPhysicalButton); // faster polling...call every 100ms


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
