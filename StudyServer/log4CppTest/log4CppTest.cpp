// log4CppTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <log4cpp/Appender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/BasicConfigurator.hh>


int main()
{
	log4cpp::BasicConfigurator::configure();

	LOG4CPP_LOGGER("WorldServer");
	LOG4CPP_INFO(logger, "hahah");
	LOG4CPP_CRIT(logger, "critical");
	LOG4CPP_WARN(logger, "warn");


	log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
	log4cpp::Category::getRoot().getAppender()->setLayout(layout);

	layout->setConversionPattern("[%p]%d{%d %b %Y %H:%M:%S.%l} %m %n ");
	logger.error("error");
	logger.crit("critical");

	LOG4CPP_INFO(logger, "hahah");
	LOG4CPP_CRIT(logger, "critical");
	LOG4CPP_WARN(logger, "warn");

	log4cpp::Category::shutdown();

    return 0;
}

