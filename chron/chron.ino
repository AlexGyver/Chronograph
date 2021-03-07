/*
Created 2015
by AlexGyver
AlexGyver Home Labs Inc.
*/

int gap1=2;        //2 цифровой пин для первого датчика
int gap2=3;       //3 цифровой пин для второго датчика
int initial=0;    //первый запуск
int n=1;            //номер выстрела
float velocity, energy;    //переменная для хранения скорости
float mass=0.00035;       //масса снаряда в килограммах
float length=0.148;       //расстояние между датчиками в метрах
volatile int flag1,flag2;    //флажки для хранения состояния пролетания пулей датчиков     
volatile unsigned long mark1, mark2;    //отметки времени прохождения пулей датчиков
void setup()
{
 pinMode(gap1, INPUT); //Настраиваем контакт 2
 pinMode(gap2, INPUT); //Настраиваем контакт 3
 Serial.begin(9600);    //открываем COM порт
 attachInterrupt(1,start,RISING);     //прерывание при прохождении первого датчика
 attachInterrupt(0,finish,RISING);      //прерывание при прохождении второго датчика
}
void start() 
{
  mark1=micros();
  flag1=1;       //прошли первый датчик, время запомнили
}
void finish() 
{
  mark2=micros();
  flag2=1;         //прошли второй датчик, время запомнили
}
void loop() 
{
  if (initial==0) {
   flag1=0;
   flag2=0;
   Serial.println("System is ready, just pull the f*ckin trigger!");   //уведомление о том, что хрон готов к работе. Вылезает при включении
   Serial.println(" ");
   initial=1;
  }
 if (micros()-mark1>1000000 && flag1==1) {       // (если пуля прошла первый датчик) И (прошла уже 1 секунда, а второй датчик не тронут)
    Serial.println("FAIL");                        //выдаёт FAIL через 1 секунду, если пуля прошла через первый датчик, а через второй нет
    flag1=0;
    flag2=0;
  }
 if (flag2==1 && flag1==1) {                           //(если пуля прошла оба датчика)
    velocity=(1000000*(length)/(mark2-mark1));     //вычисление скорости
    energy=velocity*velocity*mass/2;              //вычисление энергии
    Serial.print("Shot ");                        
    Serial.println(n);                                 //вывод номера выстрела
    Serial.print("Speed: ");    
    Serial.println(velocity);                          //вывод скорости в COM
    Serial.print("Energy: ");    
    Serial.println(energy);                          //вывод энергии в COM
    Serial.println(" "); 
    flag1=0;
    flag2=0;
    n++;                                      //номер выстрела +1
 }
 delayMicroseconds(10);    //задержка для стабильности
}
