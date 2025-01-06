#include <SPI.h>
#include <RCSwitch.h>
#include <RH_ASK.h>
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<ESP8266HTTPClient.h>

ESP8266WebServer server(80);
IPAddress local_IP(192,168,1,150);
IPAddress subnet(255,255,255,0);

RCSwitch mySwitch = RCSwitch();
String sending = "";
String ROO = "<!DOCTYPE html> <html> <head> <meta http-equiv=\"refresh\" content=\"1\"> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>RF Hacker BabakStars</title> </head> <body style=\"background-color:rgb(142, 142, 142)\"><h2 style=\"color:white;\">Babak Stars</h2><br> ";
int j = 0, i = 0;

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(D1);

  pinMode(D4,OUTPUT);
  digitalWrite(D4,0);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,local_IP,subnet);
  WiFi.softAP("BabakStars","123456789");
  server.on("/",Root);
  server.on("/SET",SET);
  server.begin();
}

void loop() {
  server.handleClient();
  digitalWrite(D4,0);
  delay(95);
  while (mySwitch.available()) {
    i++;
    String ii = String(i);
    //Serial.print("433MHz: ");
    //Serial.println( mySwitch.getReceivedValue() );
    sending ="<a id=\"433tag"+ii+"\" href=\"#\" onclick=\"var cc = document.getElementById(this.id).text; location.replace('http://192.168.1.150/SET?password='+cc);\" style=\"background-color: red; font-size: 24px;\">"+ String(mySwitch.getReceivedValue()) + " </a><a style=\"background-color: red; font-size: 24px;\">_____ 433MHz</a> <br>";
    
    //server.send(200,"text/plain",sening);
    mySwitch.resetAvailable();
    ROO += sending ;
  }
  
  digitalWrite(D4,1);
  delay(95);
  while (mySwitch.available()) {
    j++;
    String jj = String(j);
    //Serial.print("315MHz: ");
    //Serial.println( mySwitch.getReceivedValue() );
    sending = "<a href=\"#\" id=\"mytag"+jj+"\" onclick=\"var cc = document.getElementById(this.id).text; location.replace('http://192.168.1.150/SET?password='+cc);\" style=\"background-color: yellow; font-size: 24px;\">"+ String(mySwitch.getReceivedValue()) + " </a><a style=\"background-color: yellow; font-size: 24px;\">_____ 315MHz</a> <br>";
    
    //.send(200,"text/plain",sening);
    mySwitch.resetAvailable();

    ROO += sending ;
  }
   ROO +=" </body>  </html>";
  
}

void Root() {
  server.send(200,"text/html",ROO);

}

void SET() {
  String pass = server.arg("password");
  Serial.println(pass);
  mySwitch.enableTransmit(D6);
  mySwitch.send(pass.toInt(), 24);
  delay(500);
  server.send(200,"text/html","<a href=\"http://192.168.1.150/\">Back To Home</a>");
  
}
