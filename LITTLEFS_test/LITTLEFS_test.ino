#include <LITTLEFS.h>
#include <FS.h>

void setup(){
  Serial.begin(9600);

  LITTLEFS.begin(true);
  fs::File file = LITTLEFS.open("/pontos.txt", FILE_WRITE);
  LITTLEFS.open()
}

void loop() {}