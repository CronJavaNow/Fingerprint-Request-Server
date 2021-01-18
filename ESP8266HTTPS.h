/* 
 *  create new tab in build named net.h and paste the functions or -
 *  - download net.h in your project root.
 *  
 *  #include "net.h" in sketch.ino
 *  
 *  !- make sure you set ssid and password -!
 *  
 *  Call connect_esp(); in setup
 *  Call https_call("api.github.com", 443, "/test", fingerprint)
 *  
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "ssid";
const char* password = "password";

void connect_esp() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void https_call(char* host, int port, char* url, char* fingerprint){
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET /") + url + "\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  
  client.stop();
}
