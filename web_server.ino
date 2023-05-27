#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elsif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "board not supported"
#endif

#define LED1 2
//#define LED2 16


char webpage [] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<title>Online HTML Editor</title>

<head>
</head>
<center>
  <body>
    <h1>Online HTML Editor</h1>
    <h3>led 1</h3>
     <button onclick="window.location ='https://'+location.hostname+'/led1/on'"> ON </button>
     <button onclick="window.location ='https://'+location.hostname+'/led1/off'"> OFF </button>
    <h3>led 2</h3>
    
<button onclick="window.location ='https://'+location.hostname+'/led2/on'"> ON </button> 
<button onclick="window.location ='https://'+location.hostname+'/led2/off'"> OFF </button>

</body>  
</center>


</html>

)=====";


#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

AsyncWebServer Server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
 // pinMode(LED2,OUTPUT);
  WiFi.softAP("techiesms", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP"))
  { //esp.local/
    Serial.println("MDNS responder started");
  }

  Server.on("/", [](AsyncWebServerRequest * request)
  {  
    
    request->send_P(200, "text/html", webpage);
  });

  Server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,HIGH);
   // String message = "Welcome to page1"; 
   request->send_P(200, "text/html", webpage);
  });

Server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,LOW);
   // String message = "Welcome to page1"; 
   request->send_P(200, "text/html", webpage);
  });

// Server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest * request)
//  { 
//    digitalWrite(LED2,HIGH);
//   // String message = "Welcome to page1"; 
//   request->send_P(200, "text/html", webpage);
//  });

//Server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest * request)
//  { 
//    digitalWrite(LED2,LOW);
//   // String message = "Welcome to page1"; 
//   request->send_P(200, "text/html", webpage);
//  });
  Server.onNotFound(notFound);

  Server.begin();  // it will start webserver

  //MDNS.begin("dengutha");
}


void loop(void)
{
  //MDNS.update();
}
