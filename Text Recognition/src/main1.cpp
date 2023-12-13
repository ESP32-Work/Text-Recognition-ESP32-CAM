// /****************************************************************************************************************************************************
//  *  TITLE: HOW TO BUILD A $9 RSTP VIDEO STREAMER: Using The ESP-32 CAM Board || Arduino IDE - DIY #14
//  *  DESCRIPTION: This sketch creates a video streamer than uses RTSP. You can configure it to either connect to an existing WiFi network or to create
//  *  a new access point that you can connect to, in order to stream the video feed.
//  *
//  *  By Frenoy Osburn
//  *  YouTube Video: https://youtu.be/1xZ-0UGiUsY
//  *  BnBe Post: https://www.bitsnblobs.com/rtsp-video-streamer---esp32
//  ****************************************************************************************************************************************************/

//   /********************************************************************************************************************
//  *  Board Settings:
//  *  Board: "ESP32 Wrover Module"
//  *  Upload Speed: "921600"
//  *  Flash Frequency: "80MHz"
//  *  Flash Mode: "QIO"
//  *  Partition Scheme: "Hue APP (3MB No OTA/1MB SPIFFS)"
//  *  Core Debug Level: "None"
//  *  COM Port: Depends *On Your System*
//  *********************************************************************************************************************/
 
// #include "OV2640.h"
// #include <WiFi.h>
// #include <WebServer.h>
// #include <WiFiClient.h>
// #include <SPI.h>
// #include <Wire.h>
// #include "SimStreamer.h"
// #include "OV2640Streamer.h"
// #include "CRtspSession.h"

// //#define ENABLE_OLED //if want use oled ,turn on thi macro
// #define SOFTAP_MODE // If you want to run our own softap turn this on
// #define ENABLE_WEBSERVER
// #define ENABLE_RTSPSERVER

// #ifdef ENABLE_OLED
// #include "SSD1306.h"
// #define OLED_ADDRESS 0x3c
// #define I2C_SDA 14
// #define I2C_SCL 13
// SSD1306Wire display(OLED_ADDRESS, I2C_SDA, I2C_SCL, GEOMETRY_128_32);
// bool hasDisplay; // we probe for the device at runtime
// #endif

// // Select camera model
// //#define CAMERA_MODEL_WROVER_KIT
// //#define CAMERA_MODEL_ESP_EYE
// //#define CAMERA_MODEL_M5STACK_PSRAM
// //#define CAMERA_MODEL_M5STACK_WIDE
// #define CAMERA_MODEL_AI_THINKER

// #include "camera_pins.h"

// OV2640 cam;

// #ifdef ENABLE_WEBSERVER
// WebServer server(80);
// #endif

// #ifdef ENABLE_RTSPSERVER
// WiFiServer rtspServer(8554);
// #endif


// #ifdef SOFTAP_MODE
// IPAddress apIP = IPAddress(192, 168, 1, 1);
// #else
// #include "wifikeys.h"
// #endif

// #ifdef ENABLE_WEBSERVER
// void handle_jpg_stream(void)
// {
//     WiFiClient client = server.client();
//     String response = "HTTP/1.1 200 OK\r\n";
//     response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
//     server.sendContent(response);

//     while (1)
//     {
//         cam.run();
//         if (!client.connected())
//             break;
//         response = "--frame\r\n";
//         response += "Content-Type: image/jpeg\r\n\r\n";
//         server.sendContent(response);

//         client.write((char *)cam.getfb(), cam.getSize());
//         server.sendContent("\r\n");
//         if (!client.connected())
//             break;
//     }
// }

// void handle_jpg(void)
// {
//     WiFiClient client = server.client();

//     cam.run();
//     if (!client.connected())
//     {
//         return;
//     }
//     String response = "HTTP/1.1 200 OK\r\n";
//     response += "Content-disposition: inline; filename=capture.jpg\r\n";
//     response += "Content-type: image/jpeg\r\n\r\n";
//     server.sendContent(response);
//     client.write((char *)cam.getfb(), cam.getSize());
// }

// void handleNotFound()
// {
//     String message = "Server is running!\n\n";
//     message += "URI: ";
//     message += server.uri();
//     message += "\nMethod: ";
//     message += (server.method() == HTTP_GET) ? "GET" : "POST";
//     message += "\nArguments: ";
//     message += server.args();
//     message += "\n";
//     server.send(200, "text/plain", message);
// }
// #endif

// void lcdMessage(String msg)
// {
//   #ifdef ENABLE_OLED
//     if(hasDisplay) {
//         display.clear();
//         display.drawString(128 / 2, 32 / 2, msg);
//         display.display();
//     }
//   #endif
// }

// void setup()
// {
//   #ifdef ENABLE_OLED
//     hasDisplay = display.init();
//     if(hasDisplay) {
//         display.flipScreenVertically();
//         display.setFont(ArialMT_Plain_16);
//         display.setTextAlignment(TEXT_ALIGN_CENTER);
//     }
//   #endif
//     lcdMessage("booting");

//     Serial.begin(115200);
//     //while (!Serial);            //wait for serial connection. 

//     camera_config_t config;
//     config.ledc_channel = LEDC_CHANNEL_0;
//     config.ledc_timer = LEDC_TIMER_0;
//     config.pin_d0 = Y2_GPIO_NUM;
//     config.pin_d1 = Y3_GPIO_NUM;
//     config.pin_d2 = Y4_GPIO_NUM;
//     config.pin_d3 = Y5_GPIO_NUM;
//     config.pin_d4 = Y6_GPIO_NUM;
//     config.pin_d5 = Y7_GPIO_NUM;
//     config.pin_d6 = Y8_GPIO_NUM;
//     config.pin_d7 = Y9_GPIO_NUM;
//     config.pin_xclk = XCLK_GPIO_NUM;
//     config.pin_pclk = PCLK_GPIO_NUM;
//     config.pin_vsync = VSYNC_GPIO_NUM;
//     config.pin_href = HREF_GPIO_NUM;
//     config.pin_sscb_sda = SIOD_GPIO_NUM;
//     config.pin_sscb_scl = SIOC_GPIO_NUM;
//     config.pin_pwdn = PWDN_GPIO_NUM;
//     config.pin_reset = RESET_GPIO_NUM;
//     config.xclk_freq_hz = 20000000;
//     config.pixel_format = PIXFORMAT_JPEG;
//     config.frame_size = FRAMESIZE_SVGA;
//     config.jpeg_quality = 12; 
//     config.fb_count = 2;       
  
//     #if defined(CAMERA_MODEL_ESP_EYE)
//       pinMode(13, INPUT_PULLUP);
//       pinMode(14, INPUT_PULLUP);
//     #endif
  
//     cam.init(config);
    
//     IPAddress ip;

// #ifdef SOFTAP_MODE
//     const char *hostname = "devcam";
//    // WiFi.hostname(hostname); // FIXME - find out why undefined
//     lcdMessage("starting softAP");
//     WiFi.mode(WIFI_AP);
    
//     bool result = WiFi.softAP(hostname, "12345678", 1, 0);
//     delay(2000);
//     WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    
//     if (!result)
//     {
//         Serial.println("AP Config failed.");
//         return;
//     }
//     else
//     {
//         Serial.println("AP Config Success.");
//         Serial.print("AP MAC: ");
//         Serial.println(WiFi.softAPmacAddress());

//         ip = WiFi.softAPIP();

//         Serial.print("Stream Link: rtsp://");
//         Serial.print(ip);
//         Serial.println(":8554/mjpeg/1");
//     }
// #else
//     lcdMessage(String("join ") + ssid);
//     WiFi.mode(WIFI_STA);
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(F("."));
//     }
//     ip = WiFi.localIP();
//     Serial.println(F("WiFi connected"));
//     Serial.println("");
//     Serial.println(ip);
//     Serial.print("Stream Link: rtsp://");
//     Serial.print(ip);
//     Serial.println(":8554/mjpeg/1");
// #endif

//     lcdMessage(ip.toString());

// #ifdef ENABLE_WEBSERVER
//     server.on("/", HTTP_GET, handle_jpg_stream);
//     server.on("/jpg", HTTP_GET, handle_jpg);
//     server.onNotFound(handleNotFound);
//     server.begin();
// #endif

// #ifdef ENABLE_RTSPSERVER
//     rtspServer.begin();
// #endif
// }

// CStreamer *streamer;
// CRtspSession *session;
// WiFiClient client; // FIXME, support multiple clients

// void loop()
// {
// #ifdef ENABLE_WEBSERVER
//     server.handleClient();
// #endif

// #ifdef ENABLE_RTSPSERVER
//     uint32_t msecPerFrame = 100;
//     static uint32_t lastimage = millis();

//     // If we have an active client connection, just service that until gone
//     // (FIXME - support multiple simultaneous clients)
//     if(session) {
//         session->handleRequests(0); // we don't use a timeout here,
//         // instead we send only if we have new enough frames

//         uint32_t now = millis();
//         if(now > lastimage + msecPerFrame || now < lastimage) { // handle clock rollover
//             session->broadcastCurrentFrame(now);
//             lastimage = now;

//             // check if we are overrunning our max frame rate
//             now = millis();
//             if(now > lastimage + msecPerFrame)
//                 printf("warning exceeding max frame rate of %d ms\n", now - lastimage);
//         }

//         if(session->m_stopped) {
//             delete session;
//             delete streamer;
//             session = NULL;
//             streamer = NULL;
//         }
//     }
//     else {
//         client = rtspServer.accept();

//         if(client) {
//             //streamer = new SimStreamer(&client, true);             // our streamer for UDP/TCP based RTP transport
//             streamer = new OV2640Streamer(&client, cam);             // our streamer for UDP/TCP based RTP transport

//             session = new CRtspSession(&client, streamer); // our threads RTSP session and state
//         }
//     }
// #endif
// }
