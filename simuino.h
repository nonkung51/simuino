void debug(char *msg);
void runMode();
void runStep(int dir);
void openCommand();
void iDelay(int ms);
void show(WINDOW *win);
void putMsg(const char *message);
void showError(const char *m, int value);
void saveConfig();
void resetFile(const char *filename);
void logFile(char *m);
void wLog(const char *p, int value1, int value2);
void unoInfo();
void wLogChar(const char *p, const char *value1, int value2);
void showSerial(const char *m, int newLine);
void getString(char *in, char *out);
void readSketchInfo();
void initSim();
void resetSim();
void unimplemented(const char *f);
void readConfig();
void runLoop();
void runAll();
void readSimulation(char *fileName);
void showScenario(char *fileName);
void readMsg(char *fileName);
void init();
void loadSketch(char sketch[]);
void pinMode(int pin,int mode);
void digitalWrite(int pin,int value);
void analogReference(char type[]);
void analogWrite(int pin,int value); 
void tone(int pin, unsigned int freq);
void tone(int pin, unsigned int freq, unsigned long duration);
void noTone(int pin);
void shiftOut(int dataPin, int clockPin, int bitOrder, int value);
void delay(int ms);
void delayMicroseconds(int us);
void test_math();
void test_trigonometry();
void randomSeed(int seed);
void attachInterrupt(int interrupt,void(*func)(),int mode);
void detachInterrupt(int interrupt);
void interrupts();
void noInterrupts();

