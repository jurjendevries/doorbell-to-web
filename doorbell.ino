/**
 * This is a script that triggers a script that sends a notification when someone at the door pressed thet door bell.
 * 
 * It uses the onboard RGB LED as status display:
 *  - Red = Waiting to be pressed
 *  - Green = Making HTTP request
 *  - Blue = Finished HTTP request
 * 
 * Hardware:
 *  - Normally-off momentary button
 *  - Spark Core
 * 
 * Setup:
 *  - Connect one pin of the button to GND
 *  - Connect the other pin of the button to the desired digital pin on the Spark Core, in this case D0 or change the pinDoorbutton.
 * 
 * Script configuration:
 * - Change "byte server" to the IP address of your web server
 * - Change "/sub-directory/" in the line "client.println("GET /sub-directory/ HTTP/1.0");" to the path from within your HTML root where you will place the index.php script.
 * - Change "www.your-webserver-domain.tld" in the line "client.println("Host: www.your-webserver-domain.tld");" to your domain name.
 *
 * Sources I used:
 * https://community.spark.io/t/doorbell-to-sms/3349 (Mostly this script is reused. Thanks a lot to wgbartley)
 * https://community.spark.io/t/how-to-open-a-url-with-spark-core/2800/4
 * http://docs.spark.io/firmware/#communication-tcpclient
 * http://docs.spark.io/firmware/#constants-input-output-input-pullup-input-pulldown
 **/
 
int millLast = 0;                    // Last time (in millis()) the doorbell was pressed
int pinDoorbutton = D0;                // Button pin
int millDelay = 15000;               // How much time to wait until we allow another doorbell "ring" again

TCPClient client;
byte server[] = { 123, 123, 123, 123 }; // IP address of your web server

void setup() {
    pinMode(pinDoorbutton, INPUT_PULLUP);
    RGB.control(true);
}
 
void loop() {
    if(digitalRead(pinDoorbutton)==LOW)
        dingdong();
    else
        RGB.color(255, 0, 0);
}
 
 
void dingdong() {
    if(millLast==0 || (millLast+millDelay)<millis()) {
        millLast = millis();
        
        RGB.color(0, 255, 0);
           delay(1000);
  // or you can use DHCP for autoomatic IP address configuration.
  // Ethernet.begin(mac);
  Serial.begin(9600);
  Serial.println("connecting...");

  if (client.connect(server, 80))
  {
    Serial.println("connected");
    client.println("GET /sub-directory/ HTTP/1.0");
    client.println("Host: www.your-webserver-domain.tld");
    client.println("Content-Length: 0");
    client.println();
    delay(100);
    client.flush();
    delay(100);
    client.stop();
    delay(250);
  }
  else
  {
    Serial.println("connection failed");
  }

  RGB.color(0, 0, 255);
  delay(1000);
    }
}
