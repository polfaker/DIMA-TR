#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <Wire.h>
#include <SD.h>
#include <SPI.h>

File myFile;
float temperatura;
float pressio;
float altitud;

Adafruit_BMP280 bmp; // I2C Interface


void setup() {
  Serial.begin(9600);
  SD.begin(4);
  while(!Serial){
    ;
  }
  if(!SD.begin(4)){
    Serial.println("No s'ha iniciat la SD");
  }
  SD.open("/");
  
  if(SD.exists("Dades.txt")){
    Serial.println("S'ha trobat l'arxiu");
  }else{
    Serial.println("No s'ha trobat");
    
  }
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while(1);
  }
  delay(3000);

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    
}

void loop() {

    myFile = SD.open("Dades.txt");
    myFile;
    Serial.println();
    Serial.print(F("Temperature = "));
    temperatura=bmp.readTemperature();
    Serial.print(temperatura);
    Serial.println(" *C");
    if(myFile){
      Serial.print("Escribint a la SD...");
      myFile.print("Temperatura2: ");
      myFile.print(temperatura);
      myFile.println(" *C");
    }else{
      Serial.println("No s'ha pogut escriure");
    }
    
    Serial.println();
    Serial.print(F("Pressure = "));
    pressio=bmp.readPressure()/100;
    Serial.print(pressio); //displaying the Pressure in hPa, you can change the unit
    Serial.println(" hPa");
    if(myFile){
      Serial.print("Escribint a la SD...");
      myFile.print("Pressió2: ");
      myFile.print(pressio);
      myFile.println(" hPa");
    }else{
      Serial.println("No s'ha pogut escriure");
    }

    Serial.println();
    Serial.print(F("Approx altitude = "));
    altitud=bmp.readAltitude(1019.66);
    Serial.print(altitud); //The "1019.66" is the pressure(hPa) at sea level in day in your region
    Serial.println(" m");                    //If you don't know it, modify it until you get your current altitude
    if(myFile){
      Serial.print("Escribint a la SD...");
      myFile.print("Altitud2: ");
      myFile.print(altitud);
      myFile.println(" m");
    }else{
      Serial.print("No s'ha pogut escriure");
    }
    myFile.close();
    delay(3000);
}
