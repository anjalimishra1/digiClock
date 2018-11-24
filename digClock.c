#include <LiquidCrystal.h>
#include "TimerOne.h"
#define RightBtn  1
#define UpBtn     2
#define DownBtn   3
#define LeftBtn   4
#define SelBtn 5
#define NoBtn   0
int buttonselected = 0;

// **************************************//
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int key_adc0  = 0;
int key_adc1  = 0;
int key_adc2  = 0;
int key_adc3  = 0;
int key_adc4  = 0;
int key_adc5  = 0;
int thesec = 0;
int thesec2 = 0;
int minute = 0;
int minute2 = 0;
int hour = 1;
int hour2 = 0;
bool backlightstatus = true;
bool semicol = true;
bool ampm = true;


void setup() {
  //initialize serial port
  Serial.begin(9600);
  //initialize the custom characters
  lcdcharinitiate();
  //initiate timer1 with 1 sec delay
  Timer1.initialize(1000000);
  //add the function that will be run every 1 sec
  Timer1.attachInterrupt(thedisplayfunction);
  lcd.clear();
  theclock();
}
//*************************************************//
//checking if buuton is pressed and do its function
void loop()
{
  int theinput = read_LCD_buttons();
  if(theinput == RightBtn && buttonselected != RightBtn)
  {
    buttonselected = RightBtn;
    minute++;
    if(minute > 9)
    {
      minute=0;
      minute2++;
      if(minute2 > 5)
      {
        minute2 =0;
      }
    }
  }
  else if(theinput == LeftBtn && buttonselected != LeftBtn)
  {
    buttonselected = LeftBtn;
    hour++;
          if(hour > 9 && hour2 == 0)
          {
            hour = 0;
            hour2++;
            if(hour2 >1)
            {
              hour2 = 0;
            }
          }
          if(hour > 2 && hour2 == 1)
          {
            hour = 1;
            hour2++;
            if(hour2 >1)
            {
              hour2 = 0;
              ampm=!ampm;
            }
          }
  }
  else if(theinput == SelBtn && buttonselected != SelBtn)
  {
    buttonselected = SelBtn;
    backlightstatus = !backlightstatus;
    if(backlightstatus)
    {
        digitalWrite(10,LOW);  
    }
    else
    {
        digitalWrite(10,HIGH);
    }
  }
  else if(theinput == NoBtn && buttonselected != NoBtn)
  {
    buttonselected = NoBtn;
  }
  delay(200);
}
//***************************//
//get which button is pressed
int read_LCD_buttons()
{
  key_adc0 = analogRead(0);      // read the value from the sensor
  //  when read are centered at values: 0, 144, 329, 504, 741
  
  if (key_adc0 > 1000) return NoBtn; 
  if (key_adc0 < 50)   return RightBtn;
  if (key_adc0 < 150)  return UpBtn;
  if (key_adc0 < 300)  return DownBtn;
  if (key_adc0 < 450)  return LeftBtn;
  if (key_adc0 < 700)  return SelBtn;
  return NoBtn;  // when all others fail, return this...
}
//the clock timer call function
void thedisplayfunction()
{ 
  semicol=!semicol;
  thesec++;
  if(thesec > 9)
  {
    thesec=0;
    thesec2++;
    if(thesec2 > 5)
    {
      thesec2 = 0;
      minute++;
      if(minute > 9)
      {
        minute=0;
        minute2++;
        if(minute2 > 5)
        {
          minute2 =0;
          hour++;
          if(hour > 9 && hour2 == 0)
          {
            hour = 0;
            hour2++;
            if(hour2 >1)
            {
              hour2 = 0;
            }
          }
          if(hour > 2 && hour2 == 1)
          {
            hour = 1;
            hour2++;
            if(hour2 >1)
            {
              hour2 = 0;
              ampm=!ampm;
            }
          }
        }
      }
    }
  }
  theclock();
}
//************************************************//
//print the value of the varaiable in its position
void theclock()
{
  numberprinter(minute,12);
  numberprinter(minute2,8);
  numberprinter(hour,4);
  numberprinter(hour2,0);
  if(ampm)
  {
    lcdam(15);
  }
  else
  {
    lcdpm(15);
  }
  if(semicol)
  {
    lcdnumbersemicolon(7);
  }
  else
  {
    lcdnumbersemicolonoff(7);
  }
}
//************************************************************//
//find the needed characer and added it to the needed position
void numberprinter(int num , int pos)
{
  if(num == 0)
  {
    lcdnumber0(pos);
  }
  if(num == 1)
  {
    lcdnumber1(pos);
  }
  if(num == 2)
  {
    lcdnumber2(pos);
  }
  if(num == 3)
  {
    lcdnumber3(pos);
  }
  if(num == 4)
  {
    lcdnumber4(pos);
  }
  if(num == 5)
  {
    lcdnumber5(pos);
  }
  if(num == 6)
  {
    lcdnumber6(pos);
  }
  if(num == 7)
  {
    lcdnumber7(pos);
  }
  if(num == 8)
  {
    lcdnumber8(pos);
  }
  if(num == 9)
  {
    lcdnumber9(pos);
  }
}
//*********************************//
//initiate the lcd custom charcters
void lcdcharinitiate()
{
    byte C0[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00};
    byte C1[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x1F};
    byte C2[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
    byte C3[8] = {0x00,0x00,0x0E,0x0A,0x0A,0x0E,0x00,0x00};
    
    lcd.createChar(0 , C0);
    lcd.createChar(1 , C1);
    lcd.createChar(2 , C2);
    lcd.createChar(3 , C3);
    lcd.begin(16 , 2);

}
//****************************//
//lcd draw character functions
void lcdnumber0(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber1(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(32));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(2));
}
void lcdnumber2(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(2));
}
void lcdnumber3(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber4(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(32));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(32));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber5(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber6(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber7(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(32));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(0));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber8(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumber9(int PosStart)
{
    lcd.setCursor(PosStart+0,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+1,0);
    lcd.write(byte(1));
    lcd.setCursor(PosStart+2,0);
    lcd.write(byte(255));
    lcd.setCursor(PosStart+0,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+1,1);
    lcd.write(byte(2));
    lcd.setCursor(PosStart+2,1);
    lcd.write(byte(255));
}
void lcdnumbersemicolon(int PosStart)
{
  lcd.setCursor(PosStart+0,0);
  lcd.write(byte(3));
  lcd.setCursor(PosStart+0,1);
  lcd.write(byte(3));
}
void lcdnumbersemicolonoff(int PosStart)
{
  lcd.setCursor(PosStart+0,0);
  lcd.write(byte(32));
  lcd.setCursor(PosStart+0,1);
  lcd.write(byte(32));
}
void lcdam(int PosStart)
{
  lcd.setCursor(PosStart+0,0);
  lcd.write(byte(97));
  lcd.setCursor(PosStart+0,1);
  lcd.write(byte(109));
}
void lcdpm(int PosStart)
{
  lcd.setCursor(PosStart+0,0);
  lcd.write(byte(112));
  lcd.setCursor(PosStart+0,1);
  lcd.write(byte(109));
}
//***************************************************************//
//the function recive time from pc by the application using serial

void serialEvent() {
  while (Serial.available()) {
    // get the stringdate:
    String time = Serial.readString();
    if(time[6] == 'A')
    {
      ampm = true;
    }
    else
    {
      ampm = false;
    }
    thesec = (int)time[5]-48;
    thesec2 = (int)time[4]-48;
    minute = (int)time[3]-48;
    minute2 = (int)time[2]-48;
    hour = (int)time[1]-48;
    hour2 = (int)time[0]-48;
  }
}