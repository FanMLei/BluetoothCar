#include"SR04.h"
#include<LiquidCrystal_I2C.h>
#include"MsTimer2.h"
#include <Servo.h>
#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
LiquidCrystal_I2C lcd(0x27,16,2); 
Servo myservo;  
int pos ,velocity ,control,c;               
long distance = sr04.Distance(); 

void Init()
{
  pos = 90 ; 
  velocity = 155 ;
  c = 1 ; 
  lcd.init();  
  lcd.backlight();              
}

void go(int a ,int b , int c , int d)
{
  digitalWrite( 4 , a);
  digitalWrite( 5 , b);
  digitalWrite( 6 , c);
  digitalWrite( 7 , d);
  analogWrite (11 , velocity);
  analogWrite (3  , velocity);
}

void Adjust()
{
  switch(control)
  {
    case'7': velocity-=10 ; break ;
    case'9': velocity+=10 ; break ;
  }
  if( velocity >255 )
    velocity = 255 ;
  if( velocity <155 )
    velocity = 155 ;
}

void Display()
{ 
     lcd.clear();//清屏
     lcd.setCursor(0,0);//光标从这里开始
     lcd.print("Distance=");
     lcd.print(distance);
     lcd.print("cm");
     delay(1000);
}

void Control()
{
  if(Serial.available())

    control=Serial.read();

 
}

void Auto()                   //壁障主函数
{
  if(control==1)
    c = 1 ;
  go(0,0,0,0,0,0,0,0);
  velocity = 155 ; 
}

void Manual()                //
{
  switch(control)
    {
      case'1': c = 1 ;break;
      case'3': c = 0 ;break;
      case'2': {go(1,0,1,0);break;}
      case'8': {go(0,1,0,1);break;}
      case'4': {go(1,0,0,1);break;}
      case'6': {go(0,1,1,0);break;}
      case'5': {go(0,0,0,0);break;} 
    }   
}
void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);                    //定义舵机接口
  Init();
}

void loop() {  
   if(Serial.available())
    control=Serial.read();
    Manual();
}
