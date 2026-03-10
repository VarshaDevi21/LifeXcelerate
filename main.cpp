#include <Arduino.h>
#include <BluetoothSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

BluetoothSerial SerialBT;

/* TFT PINS */
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/* Patient Details */
String patientName = "RARKIREN";
String age = "65";
String location = "Madurai";
String patientID = "5585";
String abnormality = "High Heart Rate & Low Oxygen";

/* OTP */
String receivedOTP = "";

void sendAlert()
{
  String message =
  "ALERT Name:" + patientName +
  " Age:" + age +
  " Location:" + location +
  " PatientID:" + patientID +
  " Abnormality:" + abnormality;

  SerialBT.println(message);

  Serial.println("ALERT SENT TO APP:");
  Serial.println(message);
}

void setup()
{
  Serial.begin(115200);

  SerialBT.begin("ESP32_ALERT_DEVICE");
  Serial.println("Bluetooth Started");

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10,30);
  tft.println("WELCOME");



  tft.setCursor(10,10);
  tft.println("HR:102");
 

  tft.setCursor(10,40);
  tft.println("SpO2:56");
  


  tft.setTextColor(ST77XX_RED);
  tft.setCursor(10,70);
  tft.println("ABNORMAL");

  delay(7000);

  tft.fillScreen(ST77XX_BLACK);
  delay(2000);
  tft.println("2310");



  sendAlert();  
   // Send alert once
}




/* CHECK OTP */
void checkOTP()
{
  if (SerialBT.available())
  {
    Serial.println("DATA RECEIVED");

    receivedOTP = SerialBT.readString();

    Serial.print("OTP RECEIVED: ");
    Serial.println(receivedOTP);

    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10,40);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_GREEN);
    tft.println("2310");
    delay(2000);
    tft.println(receivedOTP);
    
  }
}

void loop()
{
  static bool connected = false;

  if (SerialBT.hasClient())
  {
    if (!connected)
    {
      Serial.println("Phone Connected");
      connected = true;
     
      sendAlert(); 
      
        // send alert AFTER phone connects
    }
  }

  checkOTP();

  delay(6000);
}


  