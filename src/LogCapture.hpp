#pragma once

#include "LogLevel.hpp"
#include "LogMessage.hpp"

#include <sstream>

class LogCapture {
public:
	// Constructeur pour capturer le niveau de log
	LogCapture(LogLevel level) :
	    m_Level(level), m_location(std::source_location::current()), m_Timestamp(std::chrono::system_clock::now()) {
	}

	// Destructeur pour envoyer le log automatiquement quand l'objet est détruit
	~LogCapture();

	// Surcharge de l'opérateur << pour capturer les messages
	template<typename T>
	LogCapture& operator<<(const T& message) {
		m_Stream << message;
		return *this;
	}

private:
	LogLevel m_Level;
	std::ostringstream m_Stream;
	std::source_location m_location;
	std::chrono::system_clock::time_point m_Timestamp;
};