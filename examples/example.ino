#include <StreamDebug.h>

StreamDebug* debug;
#define DEBUG(...)	debug->d(__VA_ARGS__)
#define INFO(...)   debug->i(__VA_ARGS__)
#define WARN(...)   debug->w(__VA_ARGS__)
#define ERROR(...)	debug->e(__VA_ARGS__)

void setup() {
	Serial.begin(115200);
	debug = new StreamDebug(&Serial);

	DEBUG("First debug message!");
  INFO("First info message!");
  WARN("First warn message!");
	ERROR("First error message!");
}

void loop() {
}
