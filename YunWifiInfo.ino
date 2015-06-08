/*
  Arduino Yun Wifi-info
  2015-06-08 v1.0 - Initial release.
  2015-06-08 v1.1 - Update Gateway to return IP and not the name.
 
 */
#include <Process.h>

#define LEDPIN      13

long DELAYTIME = 10000;
String VersionNumber = "1.0";

void setup() {
  Serial.begin(9600);  // initialize serial communication
  while (!Serial);     // do nothing until the serial monitor is opened

  Serial.println("Starting YunWifiInfo v" + VersionNumber + "\n");
  Bridge.begin();  // make contact with the linux processor
}

void loop() {
  // put your main code here, to run repeatedly:
  Process wifiInfo;  // initialize a new process

  Serial.print("======== ");
  // Return Year-month-dateOfMonth"T"time
  wifiInfo.runShellCommand("/bin/date +%Y-%m-%dT%T");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  
  Serial.println("Scanning for AP (Access Points) that are broadcasting.");  
  wifiInfo.runShellCommand("/usr/sbin/iwlist wlan0 scan | /bin/grep ESSI | /usr/bin/sort");  // command you want to run

  // while there's any characters coming back from the
  // process, print them to the serial monitor:
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  Serial.println();
  
  Serial.println("Getting Wifi configuration Information.");  
  // Get the wireless configuration
  wifiInfo.runShellCommand("/usr/sbin/iwconfig wlan0 > /tmp/tmp.winfo");
  // Get the Internet Configuration
  wifiInfo.runShellCommand("/sbin/ifconfig wlan0 >> /tmp/tmp.winfo");
  // Extract the App we are connected to
  wifiInfo.runShellCommand("/bin/grep 'SSID'  /tmp/tmp.winfo");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  //Serial.println();
  
  // Get what mode we are in
  wifiInfo.runShellCommand("/bin/grep  'Mode'  /tmp/tmp.winfo");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  //Serial.println();
  
  // Get our Internet Address
  wifiInfo.runShellCommand("/bin/grep  'inet addr'  /tmp/tmp.winfo");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  //Serial.println();

  // Get the Quality of our connection
  wifiInfo.runShellCommand("/bin/grep  'Quality'  /tmp/tmp.winfo");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  Serial.println();
  
  // Get the default gateway we are using
  wifiInfo.runShellCommand("/sbin/route -n | /bin/grep UG | /usr/bin/awk '{print $2}'");
  Serial.print("Gateway: ");
  while (wifiInfo.available() > 0) {
    char c = wifiInfo.read();
    Serial.print(c);
  }
  Serial.println();
 

  delay(DELAYTIME);
}

