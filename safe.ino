//아두이노 금고 코드

//모듈 불러오기
#include<LiquidCrystal_I2C.h>
#include<Keypad.h>
#include<Servo.h>               

//세팅
LiquidCrystal_I2C lcd(0x27,20,4);
int buzzer=12;
int tru=0;
int count= 0;
char PW[4]={'1','2','3','4'};
const byte ROWS=4;
const byte COLS=4;
byte rowPins[ROWS]={9,8,7,6};
byte colPins[COLS]={5,4,3,2};

char keys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Servo myservo;
Keypad keypad=Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
  lcd.init();
  lcd.backlight();
  myservo.attach(11);
}

//키보드 비번 확인 및 동작 제어
void loop(){
  char key=keypad.getKey();
  if (key)
  {
    lcd.setCursor(0,0);
    lcd.print(key);
      if(key==PW[count])
      {
        count++;
        tru++;
      }
      else if(key!=PW[count])
      {
        count++;
      }
      if(key=='#')
       re();
      if(count==4)
      {
        if(tru==4)
          Su();
        else
          Fa();
        tru=0;
        count=0;
      }
  }
}

//비번이 맞았을 때
void Su()
{
  lcd.setCursor(0,1);
  myservo.write(0);
  lcd.print("Hello! Master!");

}
//비번이 틀렸을 때
void Fa()
{
  lcd.setCursor(0,1);
  myservo.write(90);
  lcd.print("wrong!!");
  tone(buzzer,500,1000);
}
//다시 시작 버튼이 눌렸을 때 
void re()
{
  lcd.setCursor(0,1);
  tru=0;
  count=0;
  lcd.print("reset");
  myservo.write(90);
}
