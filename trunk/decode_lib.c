/*  Simuino is a Arduino Simulator based on Servuino Engine
    Copyright (C) 2011  Benny Saxen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

//=====================================
// Functions
//=====================================


//------ Digital I/O -----------------------

void pinMode(int pin,int mode)
{
  char temp[120];

  currentPin = pin;

  if(mode == INPUT || mode == OUTPUT)
    {
      digitalMode[pin] = mode;
      wmove(uno,digPinRow[pin]-1,digPinCol[pin]);
      if(pin < 22)
	waddch(uno,ACS_VLINE);

      if(mode==INPUT)
	{
	  wmove(uno,digStatRow[pin],digStatCol[pin]);
	  strcpy(temp,textPinModeIn[pin]);
	  wprintw(uno,"In");
	  if(strstr(temp,"void"))
	    wLog1("pinMode IN",pin);
	  else
	    wLog1(temp,pin);
	}

      if(mode==OUTPUT)
	{
	  wmove(uno,digStatRow[pin],digStatCol[pin]-1);
	  strcpy(temp,textPinModeOut[pin]);
	  wprintw(uno,"Out");
	  if(strstr(temp,"void"))
	    wLog1("pinMode OUT",pin);
	  else
	    wLog1(temp,pin);
	}      
      show(uno);
    }
  else
    {
      showError("Unknown Pin Mode",mode);
    }
}

void digitalWrite(int pin,int value)
{
  char temp[120];

  currentPin = pin;
  if(digitalMode[pin] == OUTPUT)
    {
      currentValueD[pin] = value;

      wmove(uno,digPinRow[pin],digPinCol[pin]);
      if(value==HIGH)
	{
	  strcpy(temp,textDigitalWriteHigh[pin]);
	  waddch(uno,ACS_DIAMOND);
	  if(confLogLev > 0)
	    { 
	      if(strstr(temp,"void"))
		wLog1("digitalWrite HIGH",pin);
	      else
		wLog1(temp,pin);
	    }
	}
      if(value==LOW)
	{
	  strcpy(temp,textDigitalWriteLow[pin]);
	  waddch(uno,ACS_BULLET);
	  if(confLogLev > 0)
	    {
	      if(strstr(temp,"void"))
		wLog1("digitalWrite LOW",pin);
	      else
		wLog1(temp,pin);
	    }
	}
      wmove(uno,digActRow[pin],digActCol[pin]);
      wprintw(uno,"w");
      show(uno);
      iDelay(confDelay);
      if(value < 10)
	{
	  wmove(uno,digPinRow[pin],digPinCol[pin]);
	  wprintw(uno,"%1d",value);
	}
      else
	{
	  wmove(uno,digPinRow[pin],digPinCol[pin]-2);
	  wprintw(uno,"%3d",value);
	}
      wmove(uno,digActRow[pin],digActCol[pin]);
      wprintw(uno," ");
      show(uno);
    }
  else
    {
      showError("Wrong pin mode. Should be OUTPUT",pin);
      wLog("digitalWrite",pin,-1);
    }
}

int digitalRead(int pin)
{
  char temp[120];
  int value;


  currentPin = pin;
  if(digitalMode[pin] == INPUT)
    {
      value = g_value;
 
      currentValueD[pin] = value;

      strcpy(temp,textDigitalRead[pin]);
      if(confLogLev > 0)
	{
	  if(strstr(temp,"void"))
	    wLog2("digitalRead",pin,value);
	  else
	    wLog2(temp,pin,value);
	}

      wmove(uno,digActRow[pin],digActCol[pin]);
      wprintw(uno,"r");
      show(uno);
      iDelay(confDelay);
      if(value < 10)
	{
	  wmove(uno,digPinRow[pin],digPinCol[pin]);
	  wprintw(uno,"%1d",value);
	}
      else
	{
	  wmove(uno,digPinRow[pin],digPinCol[pin]-2);
	  wprintw(uno,"%3d",value);
	}
      wmove(uno,digActRow[pin],digActCol[pin]);
      wprintw(uno," ");
      show(uno);

    }
  else
    {
      showError("Wrong pin mode. Should be INPUT",pin);
      wLog("digitalRead",pin,value);

    }
  return(value);
}

//------ Analog I/O ------------------------

void analogReference(char type[])
{
  unimplemented("analogReference()");
  //DEFAULT, INTERNAL, INTERNAL1V1, INTERNAL2V56, or EXTERNAL
}

int analogRead(int pin)  // Values 0 to 1023
{

  int value;
  char temp[120];

  value = g_value;
  currentPin = pin;
  if(value > 1023 || value < 0)
    {
      sprintf(temp,"%d Analog pin=%d value out of range = %d",currentStep,pin,value);
      showError(temp,-1);
      value = 0;
    }

  currentValueA[pin] = value;  

  wmove(uno,ap,anaPinCol[pin]-3);
  wprintw(uno,"%4d",value);
  wmove(uno,ap-2,anaPinCol[pin]);
  wprintw(uno,"r");
  show(uno);

  strcpy(temp,textAnalogRead[pin]);
  if(confLogLev > 0)
    {
      if(strstr(temp,"void"))
	wLog2("analogRead",pin,value);
      else
	wLog2(temp,pin,value);
    }


  wmove(uno,ap-2,anaPinCol[pin]);
  wprintw(uno,"r");
  show(uno);
  iDelay(confDelay);
  wmove(uno,ap+1,anaPinCol[pin]);
  waddch(uno,ACS_VLINE);
  wmove(uno,ap+2,anaPinCol[pin]-1);
  wprintw(uno,"In");
  wmove(uno,ap-2,anaPinCol[pin]);
  wprintw(uno," ");
  show(uno);
  return(value); 
}

void analogWrite(int pin,int value) 
// Values 0 to 255   PWM: only pin 3,5,6,9,10,11
{
  char temp[120];
  currentPin = pin;

  if(value > 256 || value < 0)
    {
      sprintf(temp,"%d AnalogWrite pin=%d value out of range = %d",currentStep,pin,value);
      showError(temp,-1);
      value = 0;
    }

  wmove(uno,digPinRow[pin]-1,digPinCol[pin]);
  if(pin < 22)
    waddch(uno,ACS_VLINE);
  wmove(uno,digStatRow[pin],digStatCol[pin]-1);
  strcpy(temp,textPinModeOut[pin]);
  wprintw(uno,"PWM");

  currentValueD[pin] = value;
  wmove(uno,digPinRow[pin],digPinCol[pin]-2);
  wprintw(uno,"%3d",value);
  wmove(uno,digActRow[pin],digActCol[pin]);
  wprintw(uno,"a");
  show(uno);
  iDelay(confDelay);
  strcpy(temp,textAnalogWrite[pin]);
  if(strstr(temp,"void"))
    wLog2("analogWrite",pin,value);
  else
    wLog2(temp,pin,value);
  wmove(uno,digActRow[pin],digActCol[pin]);
  wprintw(uno," ");
  show(uno);
  return;
}

//------ Advanced I/O ----------------------
void tone(int pin, unsigned int freq)
{
  currentPin = pin;
  unimplemented("tone()");
}

void tone(int pin, unsigned int freq, unsigned long duration)
{
  currentPin = pin;
  unimplemented("tone()");
}

void noTone(int pin)
{
  currentPin = pin;
  unimplemented("noTone()");
}

void shiftOut(int dataPin, int clockPin, int bitOrder, int value)
{
  //bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST.
  unimplemented("shiftOut()");
}

unsigned long pulseIn(int pin, int value)
{
  currentPin = pin;
  unimplemented("pulseIn(int,int)");
}

unsigned long pulseIn(int pin, int value, unsigned long timeout)
{
  currentPin = pin;
  unimplemented("pulseIn(int,int,unsigned long)");
}

//------ Time ------------------------------

unsigned long millis()
{
  //unimplemented("millis()");
  return(currentStep*100);
}

unsigned long micros()
{
  //unimplemented("micros()");
  return(currentStep*100000);
}

void delay(int ms)
{
  wLog("delay",ms,-1);
}

void delayMicroseconds(int us)
{
  wLog("delayMicroseconds",us,-1);
}


//------ External Interrupts ---------------



void interrupt(char *m, int ir)
{
  int pin;

  pin = inrpt[ir];

  wLog(m,ir,-1);

  if(strstr(m,"RISING") != NULL)  currentValueD[pin] = 1;
  if(strstr(m,"FALLING") != NULL) currentValueD[pin] = 0;
  if(strstr(m,"CHANGE") != NULL)  currentValueD[pin] = 1;
  if(strstr(m,"LOW") != NULL)     currentValueD[pin] = 0;

  if(currentValueD[pin] > 1)currentValueD[pin] = 0;

  wmove(uno,dp,digPinCol[pin]);
  //wprintw(uno,"%1d",currentValueD[pin]);
  wprintw(uno,"*");
  wmove(uno,dp+2,digPinCol[pin]);
  wprintw(uno," ");
  show(uno);
}

void attachInterrupt(int interrupt,void(*func)(),int mode)
{
  int pin;

  interruptMode[interrupt] = mode;
  attached[interrupt] = YES;

  pin = inrpt[interrupt];
  digitalMode[pin] == INTERRUPT;

/*  if(interrupt == 0)
    {
      interrupt0 = func;
    }
  if(interrupt == 1)
    {
      interrupt1 = func;
    }
*/
  if(interrupt >= 0 && interrupt <= 5)
  { 
    if(mode==LOW)wLog("attachInterruptLOW",interrupt,-1);
    if(mode==RISING)wLog("attachInterruptRISING",interrupt,-1);
    if(mode==FALLING)wLog("attachInterruptFALLING",interrupt,-1);
    if(mode==CHANGE)wLog("attachInterruptCHANGE",interrupt,-1);
  }
  else
    showError("Unsupported interrupt number",interrupt);

  if(mode == RISING || mode == FALLING || mode == CHANGE || mode == LOW)
    {
      digitalMode[pin] = mode;
      wmove(uno,digPinRow[pin]-1,digPinCol[pin]);
      waddch(uno,ACS_VLINE);
      wmove(uno,digStatRow[pin],digStatCol[pin]);

      if(mode==RISING)
	{
	  wprintw(uno,"R");
	}

      if(mode==FALLING)
	{
	  wprintw(uno,"F");
	}      

      if(mode==CHANGE)
	{
	  wprintw(uno,"C");
	}   

      if(mode==LOW)
	{
	  wprintw(uno,"L");
	}      

      show(uno);
    }
  else
    {
      showError("Unknown Pin Mode",mode);
    }
}

//---------------------------------------------------
void detachInterrupt(int interrupt)
{
  attached[interrupt] = NO;
  
  if(interrupt != 0 && interrupt != 1)
    showError("Unsupported interrupt number",interrupt);
    
  wLog("detachInterrupt",interrupt,-1);
}

//------ Interrupts ------------------------
void interrupts()
{
  unimplemented("interrupts()");
}
void noInterrupts()
{
  unimplemented("noInterrupts()");
}
//------ Communication ---------------------
class serial {

 public:
  void begin(int baudRate);
  void end();
  int  available();
  int  read();
  int  peek();
  void flush();
  void print(int x);
  void print(int x,int base);
  void print(const char *p);
  void println();
  void println(int x);
  void println(int x,int base);
  void println(const char *p);
  void write(int p);
  void write(char *p);
  void write(char *p, int len);
};

serial Serial,Serial1,Serial2,Serial3;

void serial::begin(int baudRate) 
{
  baud = baudRate;
  digitalMode[0] = RX;
  digitalMode[1] = TX;
  serialMode = ON;
  wLog("serial:begin",baud,-1);
}

void serial::end() 
{
  digitalMode[0] = FREE;
  digitalMode[1] = FREE;
  serialMode = OFF;
  if(confLogLev > 2)
    {
      wLog("serial:end",-1,-1);
    }
}

int serial::available()  // returns the number of bytes available to read
{
  unimplemented("Serial.available");
  return(1);
}

int serial::read() // the first byte of incoming serial data available (or -1 if no data is available)
{
  unimplemented("Serial.read");
  return(-1);
}

int serial::peek() 
{
  return(-1);
}

void serial::flush() 
{
  showSerial("flush",1);
}

void serial::print(int x) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,0);
  wLog("serial:print",x,-1);
}

void serial::print(int x,int base) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,0);
  wLog("serial:print base",x,-1);
}

void serial::print(const char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,0);
  wLogChar("serial:print",p,-1);
}

void serial::println() 
{
  //sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println()",-1,-1);
}

void serial::println(int x) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println",x,-1);
}

void serial::println(int x, int base) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println base",x,-1);
}

void serial::println(const char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:println",p,-1);
}

void serial::write(int p) 
{
  sprintf(stemp,"%d",p);
  showSerial(stemp,1);
  wLog("serial:write(val)",p,-1);
}

void serial::write(char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:write(str)",p,-1);
}

void serial::write(char *p, int len) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:write(len)",p,-1);
}


//======================================================
// Ethernet Library
//======================================================

/* class Ethernet { */
/*  public: */
/*   void begin(int baudRate); */
/* }; */

/* void Ethernet::begin(char *mac,char *ip)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */
/* void Ethernet::begin(char *mac,char *ip,char *gateway)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */
/* void Ethernet::begin(char *mac,char *ip,char *gateway, char *subnet)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */

/* class Server { */
/*  public: */
/* begin() */
/* available() */
/* write() */
/* print() */
/* println() */
/* }; */

/* void Server::Server(int port)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.Server",port,-1); */
/* } */
/* void Server::begin()  */
/* { */
/*   if(confLogLev > 0)wLog("Server.begin",-1,-1); */
/* } */
/* Client Server::available()  */
/* { */
/*   Client x = Client(); */
/*   if(confLogLev > 0)wLog("Server.available",-1,-1); */
/*   return(x),  */
/* } */
/* void Server::write(char x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.write",-1,-1); */
/*   sprintf(stemp,"%c",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::write(int x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.write",-1,-1); */
/*   sprintf(stemp,"%d",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%c",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(int x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%d",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char *x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%s",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char x,char *base)  */
/* { */
/*   //BIN for binary (base 2)  */
 /*   //DEC for decimal (base 10) */
  /*   //OCT for octal (base 8) */
   /*   //HEX for hexadecimal (base 16) */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::print(int x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::print(char *x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println()  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"\n"); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(int x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char *x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(int x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char *x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */

    /* class Client { */
    /*  public: */
    /*   void begin(int baudRate); */
    /* connected() */
    /* connect() */
    /* write() */
    /* print() */
    /* println() */
    /* available() */
    /* read() */
    /* flush() */
    /* stop() */
    /* }; */

    /* void serial::print(int x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("serial print",x,-1); */
    /*   sprintf(stemp,"%d",x); */
    /*   strcat(serialBuffer,stemp); */
    /*   showSerial(); */
    /*   passTime(); */
    /* } */

    //====================================
    // End of file
    //====================================