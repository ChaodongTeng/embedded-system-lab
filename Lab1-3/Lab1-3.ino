#define piopinmask (1<<12)|(1<<13)
void setup() {
  // put your setup code here, to run once:
REG_PIOC_WPMR=0x50494F00;
REG_PIOC_PER=piopinmask;
REG_PIOC_OER=piopinmask;
REG_PIOC_PUER=piopinmask;
REG_PIOC_MDDR=piopinmask;
REG_PIOC_OWER=piopinmask;

}

void loop() {
  // put your main code here, to run repeatedly:
REG_PIOC_ODSR=(1<<12);
delay(1000);
REG_PIOC_ODSR=(1<<13);
delay(1000);

}
