/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/



//ELF : C:\Users\acer\AppData\Local\Temp\arduino_build_140348

//MQQT section==================================================================
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "BD-E1001";
const char* password = "87654321";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

//END OF MQTT SECTION==================================================================

//DISPLAY SECTION==================================================================

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//END OF DISPLAY SECTION==================================================================

//GRAIN128 SECTION==================================================================
#include "grain128aead-v2_opt.h"
#include "api.h"

#define MAX_MESSAGE_LENGTH      32
#define MAX_ASSOCIATED_DATA_LENGTH  32

 
  bool flag = false;
//SET_LOOP_TASK_STACK_SIZE(16*1024); // 16KB
//unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
//END OF GRAIN128 SECTION==================================================================

// RTOS===============================
TaskHandle_t Task1;
TaskHandle_t Task2;

void display_oled(char* msg){
  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 10);       // set position to display
  oled.println(msg); // set text
  oled.display();      
}

void call_grain(unsigned char* ct,unsigned long long clen){

    unsigned char msg2[MAX_MESSAGE_LENGTH];
   // unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
    unsigned long long mlen2;
    unsigned long long mlen = 8;
    unsigned long long adlen = 9;
  
   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    //447737B558296DE2AAD7034FE454C35 (unused)
    //84DAC2CC7598D9E96E71CA06F454F2B16( 2 hex)
      crypto_aead_decrypt(msg2,&mlen2,NULL,ct,clen,ad,adlen,nonce,key);
        for (int i = 0; i<mlen2;i++){
                    Serial.println(char(msg2[i]));
                }
       char *buff_msg = reinterpret_cast<char*>(msg2);
       display_oled(buff_msg);
    //unlockVariable();
   // vTaskSuspend(Task1);
    // display_oled((msg2);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void strToBin(byte bin[], char const str[]) { //parsing array of hex menjadi 2 group of hex
  for (size_t i = 0; str[i] and str[i + 1]; i += 2) {
    char slice[] = {0, 0, 0};
    strncpy(slice, str + i, 2);
    bin[i / 2] = strtol(slice, nullptr, 16);
  }
}

void callback(char* topic, byte* payload, unsigned int length_data) {

//  memset(ct,0,MAX_MESSAGE_LENGTH + CRYPTO_ABYTES);
  //unsigned char* ptr = msg;
  byte msg[length_data];
  char buff[length_data];
  //msg[0] = '\0';
  oled.clearDisplay(); // clear display
  Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length_data; i++) {
    buff[i]=(char)payload[i];
  }
  strToBin(msg,buff);
  Serial.println(length_data/2);
  call_grain(msg,length_data/2);
 // Serial.println("[APP] Free memory: " + String(esp_get_free_heap_size()) + " bytes");
 // unlockVariable();
 // vTaskDelay(100);
 // vTaskResume(Task1);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("main/testing_kiwi_27", "device ready");
      // ... and resubscribe
      client.subscribe("main/testing_kiwi_27");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200); 
//OLED
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); //bagin oled
  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display
  
//MQQT
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

//Task1code: blinks an LED every 1000 ms




void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
 client.loop();

}
