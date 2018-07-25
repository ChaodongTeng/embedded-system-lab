char input;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial2.begin(38400);

USART1->US_MR|=US_MR_CHMODE_LOCAL_LOOPBACK;
Serial2.print("HELLO");
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial2.available()>0){
input=Serial2.read();
//Serial2.available();
//write("HELLO")
//Serial.print("HELLO");
//Serial.print(Serial2);
Serial.print(input);}
}
