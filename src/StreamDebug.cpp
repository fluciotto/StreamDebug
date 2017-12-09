#include "StreamDebug.h"

StreamDebug::StreamDebug(Stream* stream) {
	this->stream = stream;
}

StreamDebug::StreamDebug(Stream* stream, std::function<char*(char*)> f) {
	this->stream = stream;
	setPrefixFunction(f);
}

void StreamDebug::setPrefixFunction(std::function<char*(char*)> f) {
	prefixFunction = f;
}

void StreamDebug::d(const char* message, ...) {
	va_list args;
	va_start(args, message);
	this->println("DEBUG", message, args);
	va_end(args);
}

void StreamDebug::i(const char* message, ...) {
	va_list args;
	va_start(args, message);
	this->println("INFO", message, args);
	va_end(args);
}

void StreamDebug::w(const char* message, ...) {
	va_list args;
	va_start(args, message);
	this->println("WARNING", message, args);
	va_end(args);
}

void StreamDebug::e(const char* message, ...) {
	va_list args;
	va_start(args, message);
	this->println("ERROR", message, args);
	va_end(args);
}

void StreamDebug::println(const char* level, const char* message, va_list args) {
	char* fmt;
	unsigned char sizeOfChar = sizeof(char);
	if(prefixFunction) {
		char* buffer;
		prefixFunction(buffer);
		fmt = (char*) malloc((strlen(buffer) + 1 + strlen(message) + 1) * sizeOfChar);
		sprintf(fmt, "%s %s", buffer, message);
		free(buffer);
	}
	else {
		fmt = (char*) malloc((strlen(message) + 1) * sizeOfChar);
		strcpy(fmt, message);
	}
	// Compute output string
	char* out = (char*) malloc(1024 * sizeOfChar);
	memset(out, 0, 1024);
	vsnprintf(out, 1023, fmt, args);
	free(fmt);

	// Prefix message with level
	out = (char*) realloc(out, (strlen(level) + 1 + strlen(out) + 1) * sizeof(char));
	// Move <out>
	memmove(out + (strlen(level) + 1) * sizeOfChar, out, (strlen(out) + 1) * sizeOfChar);
	// Fill <out> start with tabs
	memset(out, 9, (strlen(level) + 1) * sizeOfChar);
	// Prepend level
	memcpy(out, level, strlen(level) * sizeOfChar);

	// Print the resulting string
	stream->println(out);
	free(out);
}
