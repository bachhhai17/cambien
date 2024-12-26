#define BLYNK_TEMPLATE_ID "TMPL6kwY-y_AW"
#define BLYNK_TEMPLATE_NAME "cambien"
#define BLYNK_AUTH_TOKEN "ltl1bUoUg7X75uqYYLaiWh0d8Arlf_0W"
//auth token và ID của tài khoản trên ứng dụng blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <string.h>
//sử dụng các thư viện để thực hiện chức năng qua các hàm của mỗi thư viện
#include "DHT.h"

//DHT define, chân out của dht nối vào D14 trên esp32
#define DHTTYPE DHT11
#define DHTPIN 14  
DHT dht(DHTPIN,DHTTYPE);

//Define LED, chân dương nối với D27 của esp
#define LED 27
WidgetLED LED_ON_APP(V2);
int button;

char auth[] = BLYNK_AUTH_TOKEN;

// tên và pass wifi để esp kết nối và đọc dữ liệu từ dht11
char ssid [] ="Thuy Nga";
char pass []="nga0936258058";

void setup(){

  //Debug console
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  dht.begin();
  // khởi tạo cho esp32 và cảm biến dht11
  Blynk.begin(auth,ssid,pass);// khởi tạo với 3  dòng auth ssid và pass như đã gán ở 3 dòng 22,25,26
}

BLYNK_WRITE(V3){
  button = param.asInt();
  if (button == 1){
    digitalWrite(LED,HIGH); 
    LED_ON_APP.on();
  } else {
    digitalWrite(LED,LOW);
    LED_ON_APP.off(); //dùng hàm digitalWrite để bật tắt đèn, nếu giá trị là 1 như đã cài trên app thì bật, không thì sẽ tắt
  }
}

void loop()
{
  Blynk.run();
  //đọc nhiệt độ
  float t= dht.readTemperature();
  //đọc độ ẩm
  float h = dht.readHumidity();
  //kiểm tra xem liệu độ ẩm và nhiệt độ đã được đọc hay chưa, nếu chưa thì in ra dòng 59 và lại trở về chạy từ đầu
  if(isnan(h) || isnan(t)){
    delay(500);
    Serial.println("Failed to read from DHT sensor!\n");
    return;
  }
//gán V0 cho nhiệt độ và V1 cho độ ẩm như đã set up trên app Blynk
  Blynk.virtualWrite(V0,t);
  Blynk.virtualWrite(V1,h);
//in ra và gửi thông tin về độ ẩm và nhiệt độ lên app blynk sau mỗi 2s
  Serial.print("\n");
  Serial.print("Humility: " + String(h) + "%");
  Serial.print("\t");
  Serial.print("Temperature: " + String(t) + "C");
  delay(2000);
}
