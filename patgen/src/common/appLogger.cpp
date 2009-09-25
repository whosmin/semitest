#include "appLogger.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

AppLogForm::AppLogForm(){
    upperCasePrefix = true;
}
std::string AppLogForm::operator()(const log_message& message) const {
        std::ostringstream oss;
//        tm local = *(localtime(&message.time)); // dereference and assign
//        oss << std::setfill('0');
//        oss << (1900 + local.tm_year);
//        oss << "/" << std::setw(2) << local.tm_mon;
//        oss << "/" << std::setw(2) << local.tm_wday;
//        oss << " " << std::setw(2) << local.tm_hour;
//        oss << ":" << std::setw(2) << local.tm_min;
//        oss << ":" << std::setw(2) << local.tm_sec;
//        oss << std::setfill(' ');
//        oss << " " + message.log_name;
//        oss << " ";
//        oss << "{" + message.log_stream_name;
//        oss << "}";
//        oss << " " << message.text;

        string logStreamName = message.log_stream_name;
        to_upper(logStreamName);
        oss << std::setfill(' ');
        oss << logStreamName;
        oss << " : " << message.text;
        return  oss.str();
//        return message.text;
}

AppLogger::AppLogger(const std::string& name, std::ostream& os)
    : basic_logger(name, os)
    , debug ( "debug", name, writer, DEFAULT_LEVEL_DEBUG)
    , info  ( "info",  name, writer, DEFAULT_LEVEL_INFO)
    , warn  ( "warn",  name, writer, DEFAULT_LEVEL_WARN)
    , error ( "error", name, writer, DEFAULT_LEVEL_ERROR)
    , fatal ( "fatal", name, writer, DEFAULT_LEVEL_FATAL)
{
    set_log_form(&form);
}

AppLogger::~AppLogger(){}

void AppLogger::add_log_stream( log_stream* pStream) {
    log_stream* stream = stream_map[name];

    if(!stream)
    {
    	stream_map[name] = pStream;
    }
    else
    {
//        mod_log_stream(name, level);
        cerr << "log_stream already exists. " << endl;
    }

}

log_type<AppLogger> APP_LOGGER;

