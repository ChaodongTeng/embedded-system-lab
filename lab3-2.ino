 #define  XTC    TC1       // TC number
   #define  XCHAN  1         // TC channel
   #define  XID    ID_TC4    // Instance ID
   
   void setup(){
     Serial.begin(9600);
     
     pmc_set_writeprotect(false);
     pmc_enable_periph_clk(XID);
     TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
     TC_Start(XTC, XCHAN);
     
   }
     void sprint(char *s) {
     Serial.print(s);
    }
    
    void fprint(double f) {
      Serial.println(f);
    }
   void loop(){
    sprint("HELLO");
     Serial.println((double)TC_ReadCV(XTC, XCHAN)/8400/128, DEC);
     TC_Stop(XTC,XCHAN);
     TC_Start(XTC,XCHAN);
     double f=1.2;
     fprint(f);
     Serial.println((double)TC_ReadCV(XTC, XCHAN)/8400/128, DEC);
     TC_Stop(XTC,XCHAN);
     TC_Start(XTC,XCHAN);
     
   }
