#pragma once

#include "LogLevel.hpp"

#include <source_location>
#include <string>

class LogMessage {
public:
	LogMessage(const LogLevel level, const std::chrono::system_clock::time_point& timestamp, const std::source_location& location) :
	    m_Level(level), m_Timestamp(timestamp), m_Location(location), m_Message("") {
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

	std::string m_Message;

private:
	const LogLevel m_Level;
	const std::chrono::system_clock::time_point m_Timestamp;
	const std::source_location m_Location;
};