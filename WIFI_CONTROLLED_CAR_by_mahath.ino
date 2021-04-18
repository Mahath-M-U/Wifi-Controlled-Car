#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
const char* ssid="Ap";
const char* password;
String  data =""; 

int leftMotorForward = D3;    
int rightMotorForward = D4;  
int leftMotorBackward = D5;   
int rightMotorBackward = D6;
void MotorForward();
void MotorBackward(); 
void TurnLeft();
void TurnRight();
void MotorStop();

WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to HOTSPOT");
  Serial.println(ssid);
 
  WiFi.begin(ssid,password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request

    if (request.indexOf("/forward") > 0) 
 {
    MotorForward();
   
  }
  else if (request.indexOf("/backward") >0) 
{
    MotorBackward();
  }

  else if (request.indexOf("/left") > 0)
  {
    TurnLeft();
   
  }
  else if (request.indexOf("/right") >0) 
  {
    TurnRight();
   
  }
  else if (request.indexOf("/stop") >0) 
  {
    MotorStop();
   
  }
   client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head> <style>h1 { font-size: 1.7rem; margin-top: 1rem; background: #008A8A; color: #EBEBE9; padding: 0.5em 1em; border-radius: 3px; border-left: solid #70BCBC 20px; font-weight: 100; }button{ display: inline-block; height: 38px; padding: 0 25px; color:#fff; text-align: center; font-size: 11px; font-weight: 600; line-height: 38px; letter-spacing: .1rem;text-transform: uppercase; text-decoration: none; white-space: nowrap; background: #3FBEE9; border-radius: 4px; border: none; cursor: pointer; box-sizing: border-box; } button:hover{ background: #A6A6A6; }h2{ display: inline-block; height: 38px; padding: 0 20px; color:#4AB583; text-align: center; font-size: 12px; font-weight: 600; line-height: 38px; letter-spacing: .1rem;text-transform: uppercase; text-decoration: none; white-space: nowrap; background: #FED801; border-radius: 4px; border: none; cursor: pointer; box-sizing: border-box; } h2:hover{ background: #00FF00; } h3{ display: inline-block; height: 38px; padding: 0 8px; color:#4AB583; text-align: center; font-size: 11px; font-weight: 600; line-height: 38px; letter-spacing: .1rem;text-transform: uppercase; text-decoration: none; white-space: nowrap; background: #00FF00; border-radius: 4px; border: none; cursor: pointer; box-sizing: border-box; } h3:hover{ background: #FF0000; } </style> </head>>");
  client.println("<body bgcolor=#000000><h1 align= center><big>WiFi Controlled Car</big><sub><small><font>By Mahath M U</font></small></sub></h1><br><center><a href=\"/forward\"><h3><button>FORWARD</button></h3></a></center><br><a href=\"/left\"><font color=#000000><center></font><h3><button>LEFT</button></h3></a><font color=#000000>_____________<h2 align= center><a href=\"/stop\"><center><b><button>STOP</button></b></center></a></h2>____________</font><h3><a href=\"/right\"><button>RIGHT</button></a><br></h3><center><p><h3><a href=\"/backward\"><b><button>BACKWARD</button></b></a></h3></center></body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");



  // Wait until the client sends some data
}
void MotorForward(void)   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

void MotorBackward(void)   
{

  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}


void TurnLeft(void)   
{

  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}


void TurnRight(void)   
{

  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}


void MotorStop(void)   
{
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

 
