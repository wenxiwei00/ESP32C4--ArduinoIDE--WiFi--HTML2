#include "html510.h"
HTML510Server h(80);
#define LEDPIN 7

const char* ssid     = "xiwei"; 
const char* password = "123456789"; 


const char body[] PROGMEM = R"===(
 <!DOCTYPE html>  
 <html><body>        
 <h1>
 <a href="/H">Turn ON</a> LED.<br>
 <a href="/L">Turn OFF</a> LED.<br>
 </h1>
 </body></html>  
)===";

void handleRoot(){
  h.sendhtml(body);
}

void handleH(){
  digitalWrite(LEDPIN, HIGH);  // LED ON
  //neopixelWrite(2,20,0,0); // Red
  h.sendhtml(body);
}

void handleL(){
  digitalWrite(LEDPIN, LOW);  // LED ON
  //neopixelWrite(2,0, 20,0); // green
  h.sendhtml(body);
}

void setup() {
  //IPAddress myIP(192,168,4,2);
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);

  WiFi.softAP(ssid, password);
  //WiFi.config(myIP,IPAddress(192,168,1,1),IPAddress(255,255,255,0));
  //delay(1000);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address");
  Serial.println(IP);

  
  h.begin(); //attachHandler是用于将不同的URL路径和处理函数关联起来//找到URL发过来的是什么指令, （handleH/L/Root）并且进行对应的操作，最后返回一个html给客户端
  h.attachHandler("/H",handleH); //when user ask /H, call handleH
  h.attachHandler("/L",handleL); //when user ask /L, call handleL
  h.attachHandler("/ ",handleRoot); //call handleRoot. It is main default interface for users
}

void loop() {
  h.serve();
  delay(10);
}
