#pragma once

#include "LogColor.hpp"
#include "LogLevel.hpp"
#include "LogMessage.hpp"

#include <array>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <source_location>
#include <sstream>
#include <windows.h>


#define ADD_COLOR_TO_STREAM(color) "\x1b[" << int(color) << "m"
#define RESET_STREAM_COLOR "\x1b[" << int(LogColor::RESET) << "m"
#define HEX_TO_UPPER(value) \
	"0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase

template<typename TP>
inline std::time_t to_time_t(TP tp) {
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
	return system_clock::to_time_t(sctp);
}

using LogMessagePtr = std::shared_ptr<LogMessage>;

class OwnLogger final {
public:
	OwnLogger(std::string consoleName, bool wine, bool inConsole = true, bool inFile = true, bool createBackup = true, std::string logFileName = "Log.txt");
	virtual ~OwnLogger();

	void init(std::filesystem::path folderPath, int alpha = 255, bool showDate = true, bool showFile = true);
	void destroy();

	void format_console_progress(std::string filled, std::string unfilled, int progress);
	void format_file(const LogMessagePtr msg);
	void format_console(const LogMessagePtr msg);
	void format_console_simple(const LogMessagePtr msg);

	OwnLogger& Log(const LogLevel level, std::source_location location = std::source_location::current());

	template<typename T>
	OwnLogger& operator<<(const T& message) {
		m_Stream << message; // Capture du message dans un flux
		return *this;
	}

	void Flush();

private:
	void create_backup(std::filesystem::path folderPath);

	void open_outstreams(std::filesystem::path folderPath);
	void close_outstreams();

	std::ostringstream m_Stream;

public:
	bool m_attach_console;
	bool write_in_file;
	bool should_create_backup;
	bool m_did_console_exist;
	bool show_date;
	bool show_file;
	bool simple_logger;
	std::string log_file_name;

	LogMessagePtr m_CurrentLogMessage;
	std::mutex m_Mutex;

	std::string m_console_title;
	DWORD m_original_console_mode;
	HANDLE m_console_handle;

	std::ofstream m_console_out;
	std::ofstream m_file_out;
};

#define LOG(level) logger->Log(level)
#define FLUSH_LOG() logger->Flush()

extern std::unique_ptr<OwnLogger> logger;
