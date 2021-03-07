/*
Created 2015
by AlexGyver
AlexGyver Home Labs Inc.
*/

void setup()
{
	Serial.begin(9600);    //открываем порт
}
void loop() 
{
	Serial.print("LOL");  
	Serial.println(analogRead(6));      //подключаем от подстроечного к 6 аналоговому пину, выводим значение в COM
	delay(100);                      //задержка
}
