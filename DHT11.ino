#include <Blynk.h>
#define BLYNK_TEMPLATE_ID "TMPL60HzHxrGa"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "-UAC_SDOujUwTPqwWyIBSkHWbZrm5wRS"
#define BLYNK_PRINT SwSerial



#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;

#define DHTPIN 2
#define DHTTYPE DHT11

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  // Generate random temperature value 10.0 to 30.0 (for example)
  h = dht.readHumidity();
  t = dht.readTemperature();
 

  // Send it to the server
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
}

void setup()
{
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  sendSensor();
}
