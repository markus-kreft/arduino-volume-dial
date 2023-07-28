#include <HID-Project.h>
#include <HID-Settings.h>


int rawValue = 0;
int oldValue = 0;
int set = 0;
int is = 0;
int diff = 0;


void setup() {
  // Serial.begin(9600);

  // Set volume to 0
  for (int i=0; i<100; i++) {
    Consumer.write(MEDIA_VOLUME_DOWN);
    delay(2);
  }
}


void loop() {
  // read input twice
  rawValue = analogRead(A0);
  rawValue = analogRead(A0);
  // ignore bad hop-on region of a pot by removing 8 values at both extremes
  rawValue = constrain(rawValue, 8, 1015);
  // add some deadband
  if (rawValue < (oldValue - 4) || rawValue > (oldValue + 4)) {
    // convert to percentage
    set = map(rawValue, 8, 1015, 0, 100);
    oldValue = rawValue;
  }

  diff = set - is;

  // Serial.print("Set: ");
  // Serial.print(set);
  // Serial.print(" Is: ");
  // Serial.print(is);
  // Serial.print(" ");
  // Serial.println(diff);

  if (diff < 0) {
    // Serial.println("DOWN");
    Consumer.write(MEDIA_VOLUME_DOWN);
    is--;
  } else if (diff > 0) {
    // Serial.println("UP");
    Consumer.write(MEDIA_VOLUME_UP);
    is++;
  }
  delay(10);
}
