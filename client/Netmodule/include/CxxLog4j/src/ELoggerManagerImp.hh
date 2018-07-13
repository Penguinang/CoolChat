/*
 * ELoggerManagerImp.hh
 *
 *  Created on: 2014-6-23
 *      Author: cxxjava@163.com
 */

#ifndef ELOGGERMANAGERIMP_HH_
#define ELOGGERMANAGERIMP_HH_

#include "Efc.hh"
#include "./EConfiguration.hh"
#include "../inc/ELogger.hh"
#include "../inc/ELoggerManager.hh"

namespace efc {
namespace log {

class ELoggerManagerImp {
public:
	~ELoggerManagerImp();
	ELoggerManagerImp();

	void reset(const char* config);
	void flushConfig();

	sp<ELogger> getLogger(const char* name);
	ECollection<sp<ELogger> >* getLoggers();

	void remove(const char* name);

	sp<EConfiguration> getCurrentConfigure();

private:
	sp<ELogger> rootLogger;
	EConcurrentHashMap<EString, ELogger>* loggers;

	sp<EConfiguration> configuration;

	EFile* configFile;
	llong lastModified;

	EReentrantLock flushLock;
};

extern ELoggerManagerImp* getLoggerManagerImp();

} /* namespace log */
} /* namespace efc */
#endif /* ELOGGERMANAGERIMP_HH_ */
