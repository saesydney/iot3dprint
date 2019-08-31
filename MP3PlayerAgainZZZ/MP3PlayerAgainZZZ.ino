#include <SoftwareSerial.h>
#define ARDUINO_RX 3//should connect to TX of the Serial MP3 Player module 3
#define ARDUINO_TX 1//connect to RX of the module 1
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0} ;

#define CMD_PLAY_W_INDEX 0X03
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01
String fred = "7E 04 41 00 01 EF";
void setup() 
{
    mySerial.begin(9600);
          Serial.begin(9600);
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card 
      Serial.println("Selected TF Card."); 
      delay(200);//wait for 200ms
      sendCommand(CMD_PLAY_W_INDEX, 0X1E01);//play the first song with volume 30 class
      Serial.println("Sent play first song with Volume 30.");
}
String str;
void loop() {
if(Serial.available())
{
str = Serial.readStringUntil('\n');

if(str == "1")
{
  //mySerial.write (fred);
  mySerial.write ("7E 04 41 00 01 EF");
//sendCommand(CMD_PLAY_W_INDEX, 0X1E01);//play the first track
Serial.println("play the first track");
}

if(str == "2")
{
sendCommand(CMD_PLAY_W_VOL, 0X1E02);//play the second track with volume 30 class
Serial.println("Second sound track.");
}
if(str == "3")
{
sendCommand(CMD_PLAY_W_VOL, 0X1E03);//play the third track with volume 30 class
Serial.println("Third sound track.");
}
if(str == "4")
{
sendCommand(CMD_PLAY_W_VOL, 0X1E04);//play the forth track with volume 30 class
Serial.println("Forth sound track.");
}
if(str == "ps")
{
sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
Serial.println("Pause");
}
if(str == "pl")
{
sendCommand(CMD_PLAY, 0X0D);//play it again 
Serial.println("Play");
}
if(str == "pr")
{
sendCommand(CMD_PREVIOUS, 0X02);//play previous track
Serial.println("Playing previous track.");
}
if(str == "nx")
{
sendCommand(CMD_NEXT, 0X01);//play next track
Serial.println("Playing next track.");
}
 }
}

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte                    
  Send_buf[1] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; //
  Send_buf[3] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[4] = (int8_t)(dat >> 8);//datah
  Send_buf[5] = (int16_t)(dat); //datal
  Send_buf[6] = 0xef; //ending byte
  for(int8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]) ;
    Serial.println (Send_buf[i], HEX) ;
  }
}
