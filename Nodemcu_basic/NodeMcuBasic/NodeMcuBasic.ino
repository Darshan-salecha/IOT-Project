#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
/* Set these to your desired credentials. */
const char *ssid = "Darshan"; //Enter your WIFI ssid
const char *password = "darshan@742"; //Enter your WIFI password
ESP8266WebServer server(80);
void handleRoot() {
 server.send(200, "text/html", "<center><h1>Hii Dear</h1><br><form action=\"/LED_BUILTIN_on\" method=\"get\" id=\"form1\"></form><button type=\"submit\" form=\"form1\" value=\"On\">On</button><form action=\"/LED_BUILTIN_off\" method=\"get\" id=\"form2\"></form><button type=\"submit\" form=\"form2\" value=\"Off\">Off</button></center>");
}
void handleSave() {
 if (server.arg("pass") != "") {
   Serial.println(server.arg("pass"));
 }
}
void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
 delay(3000);
 Serial.begin(115200);
 Serial.println();
 Serial.print("Configuring access point...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 server.on ( "/", handleRoot );
 server.on ("/save", handleSave);
 server.begin();
 Serial.println ( "HTTP server started" );
 server.on("/LED_BUILTIN_on", []() {
   digitalWrite(LED_BUILTIN, 0);
   Serial.println("on");
   handleRoot();
 });
 server.on("/LED_BUILTIN_off", []() {
   digitalWrite(LED_BUILTIN, 1);
   Serial.println("off");
   handleRoot();
 });
}
void loop() {
 server.handleClient();
} 
