#include <WiFi.h>
#include <HTTPClient.h>
#include "../include/global_variables.h"
#include "../include/defs.h"
#include <WiFiUdp.h>
WiFiUDP udp;

// Replace with your network credentials
const char *ssid = "ground-station";
const char *key = "password";

HTTPClient http;

// Your IP address or domain name with URL path
const char *serverURL = "http://192.168.4.1/data";

// Variable to store the HTTP request
String header;
String data;

unsigned long currentMillis;
unsigned long previousMillis = 0;
const long interval = 500;

void setup()
{
  Serial.begin(115200);

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.begin(ssid, key);
  udp.begin(PORT);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting...");
    delay(200);
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connected to Wi-Fi...");
}

void loop()
{

  currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {

      // print the received signal strength if connected
      long rssi = WiFi.RSSI();
      Serial.print("RSSI:");
      Serial.print(rssi);
      Serial.println();
      previousMillis = currentMillis;
      int size = udp.parsePacket();
      if (size == 0)
        return;
      Serial.print("Received Packet Size is : ");
      Serial.println(size);
      char buffer[255];

      int len = udp.read(buffer, strlen(buffer));
      if (len > 0)
      {
        buffer[len] = '\0';
      }

      Serial.println(buffer);

      // data = HTTPGetRequest(serverURL);

      // Serial.println(data);
    }
  }
}

String HTTPGetRequest(const char *server_name)
{
  WiFiClient client;
  HTTPClient http;

  // IP address with path
  http.begin(client, server_name);

  // send HTTP POST request from server to client
  int http_response_code = http.GET();

  String payload = "--";

  if (http_response_code > 0)
  {
    //    Serial.print("HTTP response code:");Serial.print(http_response_code);
    payload = http.getString();
  }
  else
  {
    // print error code. logging file can be done here. Send this code to python and create a logger file
    Serial.print("Error code: ");
    Serial.println(http_response_code);
  }

  // free hardware resources being used
  http.end();

  // return the fetched data
  return payload;
}
