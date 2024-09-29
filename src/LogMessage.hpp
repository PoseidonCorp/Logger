#pragma once

#include "LogLevel.hpp"

#include <source_location>
#include <string>

class LogMessage {
public:
	LogMessage(const LogLevel level, std::chrono::system_clock::time_point&& timestamp, std::source_location&& location, std::string&& message) :
	    m_Level(level), m_Timestamp(timestamp), m_Location(location), m_Message(message) {
	}
	virtual ~LogMessage() = default;

	const LogLevel& Level() const {
		return m_Level;
	}
	const std::source_location& Location() const {
		return m_Location;
	}
	const std::string& Message() const {
		return m_Message;
	}
	const std::chrono::system_clock::time_point& Timestamp() const {
		return m_Timestamp;
	}

private:
	const LogLevel m_Level;
	const std::chrono::system_clock::time_point m_Timestamp;
	const std::source_location m_Location;
	const std::string m_Message;
};