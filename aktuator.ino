
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//setting timer kirim data
unsigned long previousMillis = 0;    // Stores last time temperature was published
const long interval = 5000;

//data kirim
int count = 0;
//data terima
String pesan="";
void setup() {
  Serial.begin(115200);
  pinMode(15,OUTPUT); //pin RELAY

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  //cek data pada buffer bluetooth
  if (SerialBT.available()){
    char pesanMasuk = SerialBT.read();
    if (pesanMasuk != '\n'){
      pesan += String(pesanMasuk);}
    else{
      pesan = "";}
    Serial.write(pesanMasuk);  
  }
  //cek pesan yang diterima oleh ESP32
  if (pesan =="mati"){
    digitalWrite(15, HIGH);
    Serial.println("mati");}
    
  else if (pesan =="nyala"){
    digitalWrite(15, LOW);
    Serial.println("nyala");
   }
  delay(100);
 }
