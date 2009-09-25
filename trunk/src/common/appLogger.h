#ifndef __LOG_STREAM_H__
#define __LOG_STREAM_H__

#include <string>
#include <boost/logger/log.hpp>

using namespace std;
using namespace boost::logger;

class AppLogForm : public log_form {
public:
    AppLogForm();
    virtual ~AppLogForm(){}
    std::string operator()(const log_message& message) const;

    bool upperCasePrefix;
};

class AppLogger : public basic_logger
{
	friend class log_type<AppLogger>;
	
private:
    AppLogForm form;

protected:
	AppLogger(const std::string& name, std::ostream& os);
	~AppLogger();


public:

    virtual void add_log_stream( log_stream* pStream);

	log_stream debug;
	log_stream info;
	log_stream warn;
	log_stream error;
	log_stream fatal;	
};

extern log_type<AppLogger> APP_LOGGER;


#endif

