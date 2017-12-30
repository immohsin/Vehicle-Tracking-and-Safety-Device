#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <DHT.h>

SoftwareSerial gpsSerial(4, 3); // create gps sensor connection
TinyGPS gps; // create gps object

// variables for temp sensor
#define DHTPIN 2  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

//variables for gps
long lat,lon; // create variable for latitude and longitude object

// variables for smoke sendor
int smokeA0 = A0;
int sensorThres = 1300;

const int buzzer = 9;

//serial communication variables
char dataString[50] = {0};
int a =0; 


void setup() {
 gps_setup();
 humid_setup();
 smoke_setup();
 void buzz_setup();
}

void loop() {
 gps_loop();
  humid_loop();
   smoke_loop();
}









void humid_setup(){
  Serial.begin(9600);
  dht.begin();
}

void humid_loop(){

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 // Serial.print("Humidity: ");
  //Serial.println(h);
  //Serial.print(" %\t");
  //Serial.print("Temperature: ");
  //Serial.print(t);
  //Serial.print(" *C ");
  //Serial.print(f);
  //Serial.print(" *F\t");
  Serial.print("H:");
  Serial.println(hic);
  if(hic >= 27.0)
  {
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
  }
  else
  {
    noTone(buzzer);
  }
//  Serial.print("*C ");
//  Serial.print(hif);
//  Serial.println("*F");
  delay(100);
}













void smoke_setup()
{
   Serial.begin(9600);
}

void smoke_loop()
{
   float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024 *5.0;
  Serial.print("S:");
  Serial.println(sensorVoltage);
  //Serial.println(" V");

  if(sensorVoltage >= 1.40)
  {
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
  }
  else
  {
    noTone(buzzer);
  }
  delay(100);
}












void gps_setup()
{
   // Open serial communications and wait for port to open:
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void gps_loop()
{
while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
   // Serial.print("Position: ");
    Serial.print("l:");
    Serial.println(lat);
    //Serial.print(" ");// print latitude
    Serial.print("L:");
    Serial.println(lon); // print longitude
   }
  }
}



void buzz_setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

