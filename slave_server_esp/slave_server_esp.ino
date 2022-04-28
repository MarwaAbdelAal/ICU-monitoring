#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFiClient.h>


const char * username = "Mikasa";
const char * password = "mnnymnny";
//const char* username = "STUDBME2";
//const char* password = "BME2Stud";
//ESP8266WiFiMulti WiFiMulti;
int wifiCount;
String state;

WiFiClient client;
HTTPClient http;

void setup() {

  Serial.begin(9600);

  WiFi.begin(username, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    wifiCount++;
    if (wifiCount == 20) {
      wifiCount = 0;

    }
    Serial.print(".");
  }
  Serial.println("WiFi connected");

}

// habd function
//String httpGETRequest(const char* urlString){
String httpGETRequest(String urlString){
//  WiFiClient client;
//  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, urlString);

  // Send HTTP POST request
  int httpResponseCode = http.GET();
  Serial.println("fn ");
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    //    Serial.print("payload: ");
    //    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


void loop() {
  //  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
  //    dataFromSlave1 = Serial.read(); // Reads the data from the serial port and store it in dataFromSlave variable
  //    Serial.print("Current humidity = ");
  //    Serial.print(dataFromSlave1);
  //    Serial.print("%  ");
  //    dataFromSlave2 = Serial.read();
  //    Serial.print("temperature = ");
  //    Serial.print(dataFromSlave2);
  //    Serial.println("C  ");
  //  }


  //  int t = Serial.read();
  int t = Serial.read();
    Serial.print("t = ");
    Serial.println(t);
  //  delay(1000);
  int h = Serial.read();
  Serial.print("h = ");
  Serial.println(h);
  delay(1000);

  if (WiFi.status() == WL_CONNECTED) {

    //    String urlString = "http://127.28.133.54:8090/recieve_data?ID=" + String(1) + "&temp=" + String(t) + "&hum=" String(h) + "&";
    String urlString = "http://192.168.43.240:8090/recieve_data?ID=" + String(1) + "&temp=" + String(t) + "&hum=" + String(h) ;
//    String urlString = "http://192.168.43.140:8090/recieve_data?ID=" + String(1) + "&temp=" + String(5) + "&hum=" + String(4) ;
//    String urlString = "http://192.168.43.140:8090/recieve_data?ID=" + String(1);

    http.begin(client, urlString.c_str());
    // Your Domain name with URL path or IP address with path
    int httpResponseCode = http.GET();
//    Serial.print("httpResponseCode_sensors = ");
//    Serial.println(httpResponseCode);
    
    String payload = http.getString();
//    Serial.println(payload);
    // Free resources
    http.end();




//    String response;
//    String responseArr[2];
//
//    //    leds_url = "http://127.28.133.54:8090/leds";
//    String leds_url = "http://192.168.43.140:8090/leds";
//
//    response = httpGETRequest(leds_url);
//    Serial.print("httpResponseCode_leds = ");
//    Serial.println(response);
//    
//    JSONVar myObject = JSON.parse(response);
//
//    // JSON.typeof(jsonVar) can be used to get the type of the var
//    if (JSON.typeof(myObject) == "undefined") {
//      Serial.println("Parsing input failed!");
//      return;
//    }


    //  Serial.print("JSON object = ");
    //  Serial.println(myObject);

    //  Serial.print("mode = ");
    //  Serial.println(myObject[0]);
    //  Serial.print("dir = ");
    //  Serial.println(myObject[1]);

//    state = myObject[0];



  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
  //    Serial.print("dataFromMaster = ");
  //    Serial.println(dataFromMaster);
  //  Serial.println("from sensors ");
  //  Serial.print("t = ");
  //  Serial.println(t);
  //  Serial.print("h = ");
  //  Serial.println(h);

  //  Serial.write(1);
//  Serial.write(int(state));


  

  //  if ((WiFiMulti.run() == WL_CONNECTED)) {
  //    WiFiClient client;
  //    HTTPClient http;
  //    Serial.print("[HTTP] begin...\n");
  //    /* Make sure to replace the http by your API & replace the localhost by your IP address */
  //    if (http.begin(client, "http://127.28.133.54:8090/recieve_data?ID=" + String(1) + "&temp=" + String(t) + "&hum=" + String(h))) { // HTTP
  //      Serial.print("[HTTP] GET...\n");
  //      // start connection and send HTTP header
  //      int httpCode = http.GET();
  //      // httpCode will be negative on error
  //      if (httpCode > 0) {
  //        // HTTP header has been send and Server response header has been handled
  //        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  //        // file found at server
  //        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
  //          String payload = http.getString();
  //          Serial.println(payload);
  //        }
  //      } else {
  //        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  //      }
  //      http.end();
  //    } else {
  //      Serial.printf("[HTTP} Unable to connect\n");
  //    }
  //  }
  //  /* Another Calling For the Led Indicator API */
  //  if ((WiFiMulti.run() == WL_CONNECTED)) {
  //    WiFiClient client;
  //    HTTPClient http;
  //    Serial.print("[HTTP] begin...\n");
  //    if (http.begin(client, "http://127.28.133.54:8090/leds")) { // HTTP
  //      Serial.print("[HTTP] GET...\n");
  //      // start connection and send HTTP header
  //      int httpCode = http.GET();
  //      // httpCode will be negative on error
  //      if (httpCode > 0) {
  //        // HTTP header has been send and Server response header has been handled
  //        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  //        // file found at server
  //        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
  //          String payload = http.getString();
  //          Serial.write(int(payload));
  //          if (payload == "1") {
  //            digitalWrite(5, LOW);
  //            digitalWrite(4, HIGH);
  //          }
  //          else if (payload == "2"){
  //            digitalWrite(5, HIGH);
  //            digitalWrite(4, LOW);
  //          }
  ////          else if (payload == "3"){
  ////            digitalWrite(5, HIGH);
  ////            digitalWrite(4, HIGH);
  ////          }
  //          else {
  //            digitalWrite(5, LOW);
  //            digitalWrite(4, LOW);
  //          }
  //          Serial.println(payload);
  //        }
  //      } else {
  //        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  //      }
  //      http.end();
  //    } else {
  //      Serial.printf("[HTTP} Unable to connect\n");
  //    }
  //  }
  delay(1000);
}
