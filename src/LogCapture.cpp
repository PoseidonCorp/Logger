#include "LogCapture.hpp"

#include "OwnLogger.hpp"

LogCapture::~LogCapture() {
	m_Stream << '\n';

	auto logMessage = std::make_unique<LogMessage>(m_Level,
	                                               std::move(m_Timestamp), // Utilise std::move pour l'argument timestamp
	                                               std::move(m_location), // Utilise std::move pour l'argument location
	                                               std::move(m_Stream.str()) // Utilise std::move pour la chaîne
	);

	// Appeler la méthode via le pointeur de fonction membre
	((*logger).*logger->m_console_logger)(std::move(logMessage));
}