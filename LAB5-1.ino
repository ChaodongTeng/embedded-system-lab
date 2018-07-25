volatile boolean l=1;
//#define XTC TC1    //NUMBER
//#define XCHAN 2    //channel
//#define XID ID_TC5 //ID
#define BITSPERCHAR 8
#define BAUD 9600
#define MCLK 84000000 
  int led = 13;
   /* UART FSM States */
   typedef enum
   {
     IDLE = 0U,
    START,
     BYTE,
     STOP,
   } UART_State_t;
   
   /* FSM variables */
   UART_State_t txState = IDLE; // State register
   unsigned char txBitn;        // Number of sent bits
   unsigned char txData;        // Current data register
   unsigned char txSym = 1;     // Bit to transmit
   unsigned char txStart = 0;   // 1 if UART is sending data, 0 if idle
   //unisgned char parity;
   void uart_state_machine()
   {
    digitalWrite(led,txSym);
     switch(txState)
     {
       case START:
         txSym = 0;
         txBitn = 0;
         txState = BYTE;
         break;
       case BYTE:
         txSym = txData & 0x01;
         txData = txData >> 1;
         txBitn++;
         txState = txBitn < BITSPERCHAR ? BYTE : STOP;
         break;
       case STOP:
         txData = 0;
         txSym = 1;
         txState = IDLE;
         txStart = 0;
         break;
       case IDLE:
         txSym = 1;
         if (txStart != 0)
           txState = START;
        break;
       default:
          break;
    }
   }
void uart_send_bit() {
     digitalWrite(led, txSym);
     uart_state_machine();
     delayMicroseconds((int)(1000000/BAUD));
   }
void TC7_Handler(){
TC_GetStatus(TC2,1);
uart_send_bit();




  
}

void setup() {
  pinMode(12,OUTPUT);
  pinMode(led,OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);

pmc_set_writeprotect(false);
pmc_enable_periph_clk(ID_TC7);
int tc_periods_ns=1000000000.0L/42000000.0L;
int baud_period_ns=1000000000.0L/BAUD;
int tc_periods_per_baud=4528;
TC_Configure(TC2, 1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;
TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;
TC_SetRC(TC2,1,tc_periods_per_baud);
TC_Start(TC2, 1);
NVIC_EnableIRQ(TC7_IRQn);
Serial1.begin(BAUD);
}



void loop() {
  char b = 0xaa;
     if (txStart == 0) {
       
       txData = b;
      txStart = 1;
}
do{
       uart_send_bit();
     } while(txState != IDLE);
     uart_send_bit();
delay(20);
if(Serial.available())
{
  b=Serial1.read();
  Serial.println(b,HEX);
  }

}





     

