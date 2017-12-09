#ifndef __STREAM_DEBUG_H__

#define __STREAM_DEBUG_H__

#include "Particle.h"

class StreamDebug {
	private:
		Stream* stream;
		std::function<char*(char*)> prefixFunction;
		void println(const char* level, const char* format, va_list args);
	public:
		enum LEVEL { DEBUG, INFO, WARNING, ERROR };
		StreamDebug(Stream* stream);
		StreamDebug(Stream* stream, std::function<char*(char*)> f);
		void setPrefixFunction(std::function<char*(char*)> f);
		void d(const char* format, ...);
		void i(const char* format, ...);
		void w(const char* format, ...);
		void e(const char* format, ...);
};

#endif
