/*
 * Logger.h
 *
 *  Created on: Feb 22, 2019
 *      Author: check
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include "BaseLogger.h"
#include <string>


class ClLogger {
public:
	ClLogger(const std::string &sLoggerName);
	void info(const std::string &sMessage);
	void warn(const std::string &sMessage);
	void error(const std::string &sMessage);
	void debug(const std::string &sMessage);
private:
	const std::string m_sLoggerName;
};



#endif /* SRC_LOGGER_H_ */
