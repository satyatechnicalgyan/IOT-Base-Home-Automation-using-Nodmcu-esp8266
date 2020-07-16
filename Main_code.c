
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/*****************************Define  Pin ***************************/
#define Light1            D8
#define Light2            D7
#define Light3            D6
#define Light4            D5
#define Light5            D4
#define Light6            D3
#define Light7            D2
#define Light8            D1
#define Light9            D0

#define WLAN_SSID       "Enter your SSID"             // Your SSID
#define WLAN_PASS       "Your Posword"               // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                       // use 8883 for SSL
#define AIO_USERNAME    "Mmitskn184812"            // Replace it with your username
#define AIO_KEY         "Enter Key"                // Replace with your Project Auth Key

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/


// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe Relay1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1");  // FeedName
Adafruit_MQTT_Subscribe Relay2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2"); // FeedName
Adafruit_MQTT_Subscribe Relay3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay3"); // FeedName
Adafruit_MQTT_Subscribe Relay4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay4"); // FeedName
Adafruit_MQTT_Subscribe Relay5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay5");  // FeedName
Adafruit_MQTT_Subscribe Relay6 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay6"); // FeedName 
Adafruit_MQTT_Subscribe Relay7 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay7"); // FeedName
Adafruit_MQTT_Subscribe Relay8 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay8"); // FeedName
Adafruit_MQTT_Subscribe Relay9 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay9"); // FeedName



void MQTT_connect();

void setup() {
  Serial.begin(115200);

 /***************************Define OUTPUT Pin*********************************/
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(Light4, OUTPUT);
  pinMode(Light5, OUTPUT);
  pinMode(Light6, OUTPUT);
  pinMode(Light7, OUTPUT);
  pinMode(Light8, OUTPUT);
  pinMode(Light9, OUTPUT);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Relay1);
  mqtt.subscribe(&Relay2);
  mqtt.subscribe(&Relay3);
  mqtt.subscribe(&Relay4);
  mqtt.subscribe(&Relay5);
  mqtt.subscribe(&Relay6);
  mqtt.subscribe(&Relay7);
  mqtt.subscribe(&Relay8);
  mqtt.subscribe(&Relay9);
}

void loop() {

  MQTT_connect();


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
//Relay 1
    
    if (subscription == &Relay1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay1.lastread);
      int Relay1_State = atoi((char *)Relay1.lastread);
      digitalWrite(Light1, Relay1_State);

    }

    //Relay 2
    if (subscription == &Relay2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay2.lastread);
      int Relay2_State = atoi((char *)Relay2.lastread);
      digitalWrite(Light2, Relay2_State);
    }
    //Relay 3
    if (subscription == &Relay3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay3.lastread);
      int Relay3_State = atoi((char *)Relay3.lastread);
      digitalWrite(Light3, Relay3_State);
    }
    //Relay 4
    if (subscription == &Relay4) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay4.lastread);
      int Relay4_State = atoi((char *)Relay4.lastread);
      digitalWrite(Light4, Relay4_State);

    }
    //Relay 5
    if (subscription == &Relay5) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay5.lastread);
      int Relay5_State = atoi((char *)Relay5.lastread);
      digitalWrite(Light5, Relay5_State);

    }
    //Relay 6
    if (subscription == &Relay6) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay6.lastread);
      int Relay6_State = atoi((char *)Relay6.lastread);
      digitalWrite(Light6, Relay6_State);

    }
    //Relay 7
    if (subscription == &Relay7) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay7.lastread);
      int Relay7_State = atoi((char *)Relay7.lastread);
      digitalWrite(Light7, Relay7_State);

    }
    //Relay 8
    if (subscription == &Relay8) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay8.lastread);
      int Relay8_State = atoi((char *)Relay8.lastread);
      digitalWrite(Light8, Relay8_State);

    }
    //Relay 9
    if (subscription == &Relay9) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay9.lastread);
      int Relay9_State = atoi((char *)Relay9.lastread);
      digitalWrite(Light9, Relay9_State);

    }
  }


}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");

}
