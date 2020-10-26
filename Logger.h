/* Logging singleton modeled after syslog severity levels. Currently, no
   differentiation (aside from the message prefix) is made between severity
   levels, beyond filtering against the current logger state, except that any
   message at or above "ERROR" will also throw a runtime error.
*/

#include <iostream>
#include <stdexcept>
#include <string>

#ifndef LOGGER_H
#define LOGGER_H

enum SysLogSeverity {
    SLS_DEBUG,
    SLS_INFORMATIONAL,
    SLS_NOTICE,
    SLS_WARNING,
    SLS_ERROR,
    SLS_CRITICAL,
    SLS_ALERT,
    SLS_EMERGENCY
};

class Logger {
public:
    void debug(std::string msg) {
        if (SLS_DEBUG < this->level) { return; }
        this->dest << "DEBUG: " << msg << std::endl;
    }

    void informational(std::string msg) {
        if (SLS_INFORMATIONAL < this->level) { return; }
        this->dest << "INFORMATIONAL: " << msg << std::endl;
    }

    void notice(std::string msg) {
        if (SLS_NOTICE < this->level) { return; }
        this->dest << "NOTICE: " << msg << std::endl;
    }

    void warning(std::string msg) {
        if (SLS_WARNING < this->level) { return; }
        this->dest << "WARNING: " << msg << std::endl;
    }
    
    void error(std::string msg) {
        if (SLS_ERROR < this->level) { return; }
        this->dest << "ERROR: " << msg << std::endl;
        throw std::runtime_error(msg);
    }
    
    void critical(std::string msg) {
        if (SLS_CRITICAL < this->level) { return; }
        this->dest << "CRITICAL: " << msg << std::endl;
        throw std::runtime_error(msg);
    }
    
    void alert(std::string msg) {
        if (SLS_ALERT < this->level) { return; }
        this->dest << "ALERT: " << msg << std::endl;
        throw std::runtime_error(msg);
    }
    
    void emergency(std::string msg) {
        if (SLS_EMERGENCY < this->level) { return; }
        this->dest << "EMERGENCY: " << msg << std::endl;
        throw std::runtime_error(msg);
    }
protected:
    SysLogSeverity level = SLS_DEBUG; // anything below this number will be ignored
    std::ostream& dest = std::cout; // by default, goes to STDOUT
private:
};

static Logger LOGGER;

#endif
