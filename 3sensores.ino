//3 sensores CÓDIGO FINAL
/*
 * Program to interface FCT3065-XY Optical Mouse
 * Sensor with Arduino.
 * 
 * This code detects when mouse is moved and also
 * prints the change in x direction and change in y
 * direction in the serial monitor.
 * 
 * Author: Vineet Sukhthanker
 * Date: 6 October 2020
 * Edited: Laura Patiño
 * Date: 2024
 *
 */
#include <Arduino.h>

// Direcciones de los registros desde el datasheet
#define PROD_ID1 0x00
#define PROD_ID2 0x01
#define MOTION_STATUS 0X02
#define DEL_X 0x03
#define DEL_Y 0x04
#define OP_MODE 0x05
#define CONF 0x06
#define IMG_QUALITY 0x07
#define OP_STATE 0x08
#define W_PROTECT 0x09
#define SLEEP1_SET 0x0A
#define ENTER_TIME 0x0B
#define SLEEP2_SET 0x0C
#define IMG_THRESHOLD 0x0D
#define IMG_RECOG 0x0E

// Pines para los sensores
const int SCLK1 = 21, SDIO1 = 20; // Sensor 1
const int SCLK2 = 13, SDIO2 = 12; // Sensor 2
const int SCLK3 = 5, SDIO3 = 4; // Sesnsor 3

byte noSleep = 0xA0; // Configuración para desactivar el modo sueño
bool sensor1Ready = false;
bool sensor2Ready = false;
bool sensor3Ready = false;
int sensorNumber;

double cx, cy;
long x1, y1; // Variables para el sensor 1
long x2, y2; // Variables para el sensor 2
long x3, y3; // Variables para el sensor 3
const double D = 5900;
const double L = 5315;


void setup() {
  Serial.begin(115200);
  
  // Inicializa el sensor 1
  while (!sensor1Ready) {
    sensor1Ready = deviceInit(SCLK1, SDIO1);
    if (sensor1Ready) {
      Serial.println("Sensor 1 inicializado correctamente.");
    } else {
      delay(50); // Espera antes de reintentar
    }
  }
  // Ajusta la posición de x para el sensor 1
  x1 = 0 + (D / 2);
  y1 = 0;
  
  // Inicializa el sensor 2
  while (!sensor2Ready) {
    sensor2Ready = deviceInit(SCLK2, SDIO2);
    if (sensor2Ready) {
      Serial.println("Sensor 2 inicializado correctamente.");
    } else {
      delay(50); // Espera antes de reintentar
    }
  }
  // Ajusta la posición de x para el sensor 2
  x2 = 0 - (D / 2);
  y2 = 0;

  // Inicializa el sensor 3
  while (!sensor3Ready) {
    sensor3Ready = deviceInit(SCLK3, SDIO3);
    if (sensor3Ready) {
      Serial.println("Sensor 3 inicializado correctamente.");
    } else {
      delay(50); // Espera antes de reintentar
    }
  }
  // Ajusta la posición de x para el sensor 3
  x3 = 0;
  y3 = 0 + L;
}

void loop() {
  
  if (!sensor1Ready || !sensor2Ready || !sensor3Ready) {
    return; // Espera hasta que todos los sensores estén listos
  }

  // Procesa y muestra datos para todos los sensores una vez que ambos estén listos
  processSensorData(1, SCLK1, SDIO1, x1);
  processSensorData(2, SCLK2, SDIO2, x2);
  processSensorData(3, SCLK3, SDIO3, x3);
}

bool deviceInit(int SCLK, int SDIO) {
  pinMode(SCLK, OUTPUT);
  pinMode(SDIO, OUTPUT);
  digitalWrite(SCLK, HIGH);
  digitalWrite(SCLK, LOW);
  delayMicroseconds(2); // tRESYNC según datasheet
  digitalWrite(SCLK, HIGH);
  delay(320); // tSIWTT según datasheet
  writeRegister(OP_MODE, noSleep, SCLK, SDIO); // Desactiva el modo sueño
  byte prodId = readRegister(PROD_ID1, SCLK, SDIO);
  if (prodId == 0x31) {
    return true; // Dispositivo inicializado correctamente
  } else {
    return false; // Dispositivo no reconocido
  }
}

void processSensorData(int sensorNumber, int SCLK, int SDIO, long &x) {
  int motion = readRegister(MOTION_STATUS, SCLK, SDIO);
  if (motion == 0x81) {
    int delta_x = (int8_t)readRegister(DEL_X, SCLK, SDIO);
    int delta_y = (int8_t)readRegister(DEL_Y, SCLK, SDIO);
    if (sensorNumber == 1) {
      x1 += delta_x; // Actualiza la posición acumulativa global para el sensor 1
      y1 += delta_y; // Actualiza la posición acumulativa global para el sensor 1
      cx = -0.0254 * x1;
      cy = -0.0254 * y1;
      
    } 
    if (sensorNumber == 2) {
      x2 += delta_x * 1.744; // Actualiza la posición acumulativa global para el sensor 2
      y2 += delta_y * 3.01; // Actualiza la posición acumulativa global para el sensor 2
      cx = (-0.0254 * x2);
      cy = (-0.0254 * y2) ;
      
    }
     if (sensorNumber == 3) {
      x3 += delta_x; // Actualiza la posición acumulativa global para el sensor 3
      y3 += delta_y; // Actualiza la posición acumulativa global para el sensor 3
      cx = -0.0254 * x3;
      cy = -0.0254 * y3;
      
    } 
    
    Serial.print(sensorNumber);
    Serial.print(",");
    Serial.print(cx);
    Serial.print(",");
    Serial.print(cy);
    Serial.print("\n");
  }
}

byte readRegister(byte address, int SCLK, int SDIO) {
  pinMode(SDIO, OUTPUT);
  digitalWrite(SDIO, LOW);
  for (byte bit = 0x80; bit; bit >>= 1) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, address & bit ? HIGH : LOW);
    digitalWrite(SCLK, HIGH);
  }
  pinMode(SDIO, INPUT);
  byte result = 0;
  for (byte bit = 0x80; bit; bit >>= 1) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SCLK, HIGH);
    if (digitalRead(SDIO)) {
      result |= bit;
    }
  }
  return result;
}

void writeRegister(byte address, byte data, int SCLK, int SDIO) {
  address |= 0x80; // MSB = 1 para indicar escritura
  pinMode(SDIO, OUTPUT);
  digitalWrite(SDIO, LOW);
  for (byte bit = 0x80; bit; bit >>= 1) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, address & bit ? HIGH : LOW);
    digitalWrite(SCLK, HIGH);
  }
  for (byte bit = 0x80; bit; bit >>= 1) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, data & bit ? HIGH : LOW);
    digitalWrite(SCLK, HIGH);
  }
}

