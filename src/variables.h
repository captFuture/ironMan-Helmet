#define SERVO1PIN 22
#define SERVO2PIN 19
#define SERVO1POWERPIN 21
#define SERVO2POWERPIN 25

bool debug = true;
int SERVO1Current = 700;
int SERVO2Current = 2250;
int maxLoop = 1024;

long int smin1 = SERVO1Current ;
long int smax1 = SERVO2Current;
long int smin2 = SERVO1Current;
long int smax2 = SERVO2Current;
int pos1 = 0;
int pos2 = 0;
bool opened = false;
int ledNum = 0;

