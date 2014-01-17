#include <Adafruit_PN532.h>

#define SCK  (2)
#define MOSI (3)
#define SS   (4)
#define MISO (5)

#define MAX_RX 64

#define AUTHA 0x60

Adafruit_PN532 nfc(SCK, MISO, MOSI, SS);

static uint8_t rx[MAX_RX];
static uint8_t rxSize;
static uint8_t *tx;
static uint8_t txSize = 0;

static uint8_t nonce[] = {0x60, 0x30, 0x76, 0x4a};

static boolean doLoop = true;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  memset(rx, 0, MAX_RX);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

  nfc.SetParity(true);
  nfc.SetCRC(true);
  nfc.SetParameters(PARAM_AUTO_ATR_RES);

  Serial.println("Setting PN53x to target mode!");

  //expect 4 bytes (auth a)
  rxSize = 4;
  if (!nfc.TgInitAsTarget(rx, rxSize)) {
    Serial.println("Timeout before target init\n");
  }
  nfc.TgResponseToInitiator(nonce, 2);
  //nfc.SetCRC(false);
  //nfc.SetParity(false);
  uint8_t test = 0;
  nfc.ReadRegister(0x63, 0x3a, &test);
  Serial.println(test, HEX);
  nfc.GetFIFOBuffer();
  //nfc.TgGetInitiatorCommand(rx, 8);
  //nfc.TgResponseToInitiator(at, 2);
}


void loop(void) {
}

