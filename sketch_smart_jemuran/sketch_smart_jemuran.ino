
// program jemuran pintar tugas IoT Design application
// 07 nov 2020 
// Mawaddi Rachman, Bilal, Frans


#include <SPI.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

#include <Servo.h>

#include "secrets.h"
#include "datetime_lib.h"

// Komponen payung jemuran
// Simulasi menggunakan servo
Servo tapServo;

// peta pin
int pinSensorHujan=4; //digital
int pinServo = 5; //digital
int pinAnalogHujan;

// blynk android app key
// auth key untuk koneksi dengan aplikasi blynk
// 1. download aplikasi dari playstore/appstore
// 2. buka aplikasi, buat akun.
// 3. buat project
// 4. nilai auth akan dikirim lewat email yang terdaftar

// WiFi credentials
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

const char *firebaseBasePath = "/smart-jemuran-test-2";

// Koneksi data ke Firebase database
FirebaseData firebaseData;

// NTPClient object
WiFiUDP ntpUdp;
NTPClient ntpClient(ntpUdp, "pool.ntp.org", 3600);

void setup()
{
  // initialize serial communication at 9600 bits
  Serial.begin(9600);

  delay(100);
  Serial.println("Connecting to WiFi");
  int status = WL_IDLE_STATUS;
  while(status != WL_CONNECTED) {
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // mulai koneksi ke firebase database
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, SECRET_SSID, SECRET_PASS);
  Firebase.reconnectWiFi(true);

  // mulai inisialisasi ntpClient
  ntpClient.begin();

  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +7 = 25200
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  ntpClient.setTimeOffset(25200);

  pinMode(pinSensorHujan, INPUT);
  tapServo.attach(pinServo);
}


/* Cara kerja sistem 
 *  bila hujan maka payung jemuran membuka        ==> jika nilaiHujan == 0 then pinServo diset 0 derajad
 *  bila tidak hujan maka payung jemuran menutup  ==> jika nilaiHujan == 1 then pinMotor diset 180 derajad
 */
void loop()
{
  String status;
  
  if(digitalRead(pinSensorHujan) == LOW) {
    tapServo.write(180);
    status = "HUJAN";
  } else {
    tapServo.write(0);
    status = "KERING";
  }

  // Kirim dan simpan data ke firebase database
  ntpClient.update();
  String iddate = getId(ntpClient);
  String dateTime = getCurrentDateTime(ntpClient);
  Serial.print("Datetime: ");
  Serial.println(dateTime);
  String jsonStr = "{\"id\":\""+ iddate + "\", \"date_time\":\"" + dateTime + "\", \"status\": \"" + status + "\"}";
  String apath = firebaseBasePath + String("/") + iddate;
  if(Firebase.setJSON(firebaseData, apath, jsonStr)) {
    Serial.println("Data is saved");
  } else {
    Serial.print("Failed to save: ");
    Serial.println(firebaseData.errorReason());
  }
  delay(4000);
}
