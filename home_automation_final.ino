
#include <ESP8266WiFi.h>
#include <IRsend.h>
#define IR D7

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
 
#include <WiFi.h>
#include <PubSubClient.h>

const uint16_t kIrLed = D7;  
IRsend irsend(kIrLed);

long lastReconnectAttempt = 0;

#define LED1 18
#define LED2 5
#define LED3 23
#define LED4 22
#define LED5 16
#define LED6 17
#define LED7 19
#define LED8 21
#define LED9 34


#define Touch1 T0   //4
#define Touch2 T3   //15
#define Touch3 T4   //13
#define Touch4 T5   //12
#define Touch5 T6   //14
#define Touch6 T7   //27
#define Touch7 T9   //33
#define Touch8 T8   //32
#define Touch9 T9   //32


int touch1,touch9, touch2, touch3, touch4, touch5, touch6, touch7, touch8;
boolean a = true;
boolean b = true;
boolean c = true;
boolean d = true;
boolean e = true;
boolean f = true;
boolean g = true;
boolean h = true;
boolean j = true;


const char* ssid = "oppo manthan";
const char* password =  "manavadaria";

//Enter your mqtt server configurations
const char* mqttServer = "postman.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort =   12323;       //Port number
const char* mqttUser = "ckekwtxs"; //User
const char* mqttPassword = "wQMFGb8emx3A"; //Password

WiFiClient espClient;
PubSubClient client(espClient);

boolean reconnect() {
  Serial.println("Reconnecting to mqtt");
  if (client.connect("ckekwtxs", mqttUser, mqttPassword )) {
    // Once connected, publish an announcement...
   
  client.subscribe("esp/test");
  }
  return client.connected();
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);

lastReconnectAttempt = 0;


  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ckekwtxs", mqttUser, mqttPassword ))
    {
      Serial.println("connected");  
    }
    else
    {
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      setup();
      delay(2000);
    }
  }
  client.publish("esp/test", "Hello From Wemos D1");
  client.subscribe("esp/test");
  digitalWrite(LED1,1);
  digitalWrite(LED2,1);
  digitalWrite(LED3,1);
  digitalWrite(LED4,1);
  digitalWrite(LED5,1);
  digitalWrite(LED6,1);
  digitalWrite(LED7,1);
  digitalWrite(LED8,1);
}

void MQTTcallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");

  String message;
  for (int i = 0; i < length; i++)
  {
    message = message + (char)payload[i];  //Conver *byte to String
  }

  Serial.print(message);

  if (message == "#relay1on")
  {
    Serial.println("Relay 1 on from Web Socket");
    digitalWrite(LED1, 1);
    a=true;
  }
  if (message == "#relay1off")
  {
    Serial.println("Relay 1 off from Web Socket");
    digitalWrite(LED1, 0);
    a=false;
  }

  if (message == "#relay2on")
  {
    Serial.println("Relay 2 on from Web Socket");
    digitalWrite(LED2, 1);
    b=true;
  }
  if (message == "#relay2off")
  {
    Serial.println("Relay 2 off from Web Socket");
    digitalWrite(LED2, 0);
    b=false;
  }

  if (message == "#relay3on")
  {
    Serial.println("Relay 3 on from Web Socket");
    digitalWrite(LED3, 1);
    c=true;
  }
  if (message == "#relay3off")
  {
    Serial.println("Relay 3 off from Web Socket");
    digitalWrite(LED3, 0);
    c=false;
  }

  if (message == "#relay4on")
  {
    Serial.println("Relay 4 on from Web Socket");
    digitalWrite(LED4, 1);
    d=true;
  }
  if (message == "#relay4off")
  {
    Serial.println("Relay 4 off from Web Socket");
    digitalWrite(LED4, 0);
    d=false;
  }

  if (message == "#relay5on")
  {
    Serial.println("Relay 5 on from Web Socket");
    digitalWrite(LED5, 1);
    e=true;
  }
  if (message == "#relay5off")
  {
    Serial.println("Relay 5 off from Web Socket");
    digitalWrite(LED5, 0);
    e=false;
  }

  if (message == "#relay6on")
  {
    Serial.println("Relay 6 on from Web Socket");
    digitalWrite(LED6, 1);
    f=true;
  }
  if (message == "#relay6off")
  {
    Serial.println("Relay 6 off from Web Socket");
    digitalWrite(LED6, 0);
    f=false;
  }

  if (message == "#relay7on")
  {
    Serial.println("Relay 7 on from Web Socket");
    digitalWrite(LED7, 1);
    g=true;
  }
  if (message == "#relay7off")
  {
    Serial.println("Relay 7 off from Web Socket");
    digitalWrite(LED7, 0);
    g=false;
  }

  if (message == "#relay8on")
  {
    Serial.println("Relay 8 on from Web Socket");
    digitalWrite(LED8, 1);
    h=true;
  }
  if (message == "#relay8off")
  {
    Serial.println("Relay 8 off from Web Socket");
    digitalWrite(LED8, 0);
    h=false;
  }

  //IR Send
  if (message == "power")  
  {
    uint16_t d1[67] = {9040, 4524,  550, 560,  550, 1696,  548, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 1696,  550, 1696,  548, 560,  548, 560,  550, 560,  550, 1694,  550, 560,  550, 560,  550, 1696,  548, 560,  550, 1696,  548, 1696,  548, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  550};  // NEC 40BF12ED
    irsend.sendRaw(d1, 67, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Power");
    delay(1);
  }
  
  if (message == "mute")  
  {
    uint16_t d2[71] = {9052, 4524,  550, 560,  550, 1696,  552, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  552, 560,  552, 1696,  550, 1698,  550, 1698,  552, 1696,  552, 1698,  552, 1696,  552, 1696,  552, 560,  550, 560,  552, 1696,  552, 560,  552, 560,  550, 1698,  550, 560,  552, 560,  552, 1698,  550, 1696,  552, 560,  550, 1696,  552, 1696,  550, 560,  550, 1696,  552, 40554,  9050, 2250,  550};  // NEC 40BF926D
    irsend.sendRaw(d2, 71, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Mute HM");
    delay(1);
  }
  
  if (message == "source")  
  {
    uint16_t d3[71] = {9398, 4140,  578, 558,  552, 1694,  578, 530,  552, 558,  552, 558,  552, 558,  552, 558,  552, 556,  552, 1694,  550, 558,  552, 1694,  550, 1696,  550, 1696,  550, 1694,  552, 1692,  552, 1694,  576, 1668,  576, 532,  552, 1696,  550, 1694,  550, 558,  550, 558,  552, 556,  552, 556,  552, 558,  552, 1694,  550, 558,  552, 556,  552, 1696,  550, 1696,  550, 1694,  552, 1694,  552, 40540,  9042, 2252,  576};  // NEC 40BFB04F
    irsend.sendRaw(d3, 71, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Source HM");
    delay(1);
  }
  
  if (message == "tone")  
  {
    uint16_t d4[73] = {9042, 4524,  548, 562,  548, 1698,  550, 560,  550, 560,  550, 560,  550, 560,  550, 560,  552, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  550, 1696,  550, 1696,  550, 1696,  550, 1698,  548, 1696,  548, 560,  550, 558,  552, 1694,  552, 1696,  550, 558,  552, 556,  552, 558,  552, 558,  552, 1694,  550, 1696,  550, 560,  550, 560,  552, 1696,  550, 1696,  550, 1694,  552, 40538,  9074, 202,  158, 1864,  550};  // NEC 40BF9867
    irsend.sendRaw(d4, 73, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Tone HM");
    delay(1);
  }
  
  if (message == "next")  
  {
    uint16_t d5[73] = {9044, 4526,  548, 562,  548, 1698,  550, 560,  548, 560,  550, 560,  550, 560,  548, 560,  548, 560,  548, 1698,  550, 560,  548, 1696,  550, 1696,  548, 1698,  550, 1696,  548, 1698,  548, 1696,  548, 562,  548, 560,  550, 560,  548, 562,  548, 560,  548, 562,  548, 1698,  550, 560,  548, 1698,  550, 1696,  548, 1696,  550, 1696,  548, 1698,  548, 1698,  548, 560,  548, 1698,  548, 40542,  9042, 2252,  550};  // NEC 40BF02FD
    irsend.sendRaw(d5, 73, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Next HM");
    delay(1);
  }
  
  if (message == "previous")  
  {
    uint16_t d6[73] = {9040, 4522,  550, 560,  550, 1696,  550, 560,  550, 560,  548, 560,  550, 560,  550, 560,  550, 560,  548, 1696,  550, 560,  548, 1696,  550, 1696,  550, 1698,  548, 1696,  550, 1696,  550, 1696,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 560,  550, 560,  550, 1696,  550, 560,  550, 1696,  550, 1696,  550, 560,  550, 1696,  548, 1698,  548, 1696,  550, 560,  550, 1698,  548};  // NEC 40BF22DD
    irsend.sendRaw(d6, 73, 38);  // Send a raw data capture at 38kHz.
    Serial.println("Previous HM");
    delay(1);
  }

  //IR send Over 
  //AS many as code we can enter

  Serial.println();
  Serial.println("-----------------------");
}

void loop()
{
  /*
  if (!client.connected())
  {
   client.connect("ckekwtxs", mqttUser, mqttPassword );
   setup();
  }*/



if (!client.connected()) {
    Serial.println("mqtt NOT connected");
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
   client.loop();
  }



 
  //client.loop();
  touch9 = touchRead(Touch9);
  Serial.println(touch9);


  if (touch9 < 40)
  {
    if (j == false)
    {
      digitalWrite(LED9, HIGH);
      Serial.println("light 9 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay9on");
      j = true;
      delay(300);
    }
    else if (j == true)
    {
      digitalWrite(LED9, LOW);
      Serial.println("light 9 ON from touch sensor");
      client.publish("esp/testStatus", "#relay9off");
      j = false;
      delay(300);
    }
  }


   
touch1 = touchRead(Touch1);
  Serial.println(touch1);

  if (touch1 < 40)
  {
    if (a == false)
    {
      digitalWrite(LED1, HIGH);
      Serial.println("light 1 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay1on");
      a = true;
      delay(300);
    }
    else if (a == true)
    {
      digitalWrite(LED1, LOW);
      Serial.println("light 1 ON from touch sensor");
      client.publish("esp/testStatus", "#relay1off");
      a = false;
      delay(300);
    }
  }

   

  touch2 = touchRead(Touch2);
  Serial.println(touch2);

  if (touch2 < 40)
  {
    if (b == false)
    {
      digitalWrite(LED2, HIGH);
      Serial.println("light 2 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay2on");
      b = true;
      delay(300);
    }
    else if (b == true)
    {
      digitalWrite(LED2, LOW);
      Serial.println("light 2 ON from touch sensor");
      client.publish("esp/testStatus", "#relay2off");
      b = false;
      delay(300);
    }
  }

  touch3 = touchRead(Touch3);
  Serial.println(touch3);

  if (touch3 < 40)
  {
    if ( c == false)
    {
      digitalWrite(LED3, HIGH);
      Serial.println("light 3 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay3on");
      c = true;
      delay(300);
    }
    else if (c == true)
    {
      digitalWrite(LED3, LOW);
      Serial.println("light 3 ON from touch sensor");
      client.publish("esp/testStatus", "#relay3off");
      c = false;
      delay(300);
    }
  }

  touch4 = touchRead(Touch4);
  Serial.println(touch4);

  if (touch4 < 40)
  {
    if (d == false)
    {
      digitalWrite(LED4, HIGH);
      Serial.println("light 4 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay4on");
      d = true;
      delay(300);
    }
    else if (d == true)
    {
      digitalWrite(LED4, LOW);
      Serial.println("light 4 ON from touch sensor");
      client.publish("esp/testStatus", "#relay4off");
      d = false;
      delay(300);
    }
  }

  touch5 = touchRead(Touch5);
  Serial.println(touch5);

  if (touch5 < 40)
  {
    if (e == false)
    {
      digitalWrite(LED5, HIGH);
      Serial.println("light 5 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay5on");
      e = true;
      delay(300);
    }
    else if (e == true)
    {
      digitalWrite(LED5, LOW);
      Serial.println("light 5 ON from touch sensor");
      client.publish("esp/testStatus", "#relay5off");
      e = false;
      delay(300);
    }
  }

  touch6 = touchRead(Touch6);
  Serial.println(touch6);

  if (touch6 < 40)
  {
    if ( f == false)
    {
      digitalWrite(LED6, HIGH);
      Serial.println("light 6 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay6on");
      f = true;
      delay(300);
    }
    else if (f == true)
    {
      digitalWrite(LED6, LOW);
      Serial.println("light 6 ON from touch sensor");
      client.publish("esp/testStatus", "#relay6off");
      f = false;
      delay(300);
    }
  }

  touch7 = touchRead(Touch7);
  Serial.println(touch7);

  if (touch7 < 40)
  {
    if (g == false)
    {
      digitalWrite(LED7, HIGH);
      Serial.println("light 7 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay7on");
      g = true;
      delay(300);
    }
    else if (g == true)
    {
      digitalWrite(LED7, LOW);
      Serial.println("light 7 ON from touch sensor");
      client.publish("esp/testStatus", "#relay7off");
      g = false;
      delay(300);
    }
  }

  touch8 = touchRead(Touch8);
  Serial.println(touch8);

  if (touch8 < 40)
  {
    if (h == false)
    {
      digitalWrite(LED8, HIGH);
      Serial.println("light 8 OFF from touch sensor");
      client.publish("esp/testStatus", "#relay8on");
      h = true;
      delay(300);
    }
    else if (h == true)
    {
      digitalWrite(LED8, LOW);
      Serial.println("light 8 ON from touch sensor");
      client.publish("esp/testStatus", "#relay8off");
      h = false;
      delay(300);
    }
  }
}
