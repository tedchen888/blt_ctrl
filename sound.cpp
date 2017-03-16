#include // 模拟救护车警笛
const int buzzer = 10;
void setup() {  // put your setup code here, to run once:  Serial.begin(9600);  pinMode(buzzer, OUTPUT);}
  
  void loop() {  // put your main code here, to run repeatedly:  static bool open = false;  if ( Serial.available() && Serial.read() == 'O' )  {    open = true;  }  if (open)  {    for (int i = 0; i<80; ++i)    {      digitalWrite(buzzer, HIGH);      delay(1);      digitalWrite(buzzer, LOW);      delay(1);    }   for (int i = 0; i<100; ++i)   {      digitalWrite(buzzer, HIGH);      delay(2);      digitalWrite(buzzer, LOW);      delay(2);    }}
}


