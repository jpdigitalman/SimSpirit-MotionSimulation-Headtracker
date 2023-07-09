enum BTNCOMMAND{
   LEFT_TURN,
   RIGHT_TURN,
   PAIR,
   BLE,
   NONE
} BUTTONCOMMAND;

#define bleServerName "MARKSIM_HT"

float temp;
float yaw;
float pitch;
float roll;

bool deviceConnected = false;
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 200;

int cmdBTN = -1;
void redLed(bool status);

#define I2C_SDA 19
#define I2C_SCL 18
#define Interrupt_Pin 17

bool proximityFound = false;
int proximity, proximity_old = -1;
bool nearToFar = true;

void SetupBoardDriver();
void SetupConnections();

String MAC;
String MAC_Hardware;
bool ht_paired = false;