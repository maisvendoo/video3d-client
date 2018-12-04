#ifndef     COMMAND_LINE_PARSER_H
#define     COMMAND_LINE_PARSER_H

#include    <osg/ArgumentParser>

#include    <sstream>

#include    "cmd-line.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class CommandLineParser
{
public:

    CommandLineParser(int argc, char *argv[]);

    virtual ~CommandLineParser();

    cmd_line_t getCommadLine() const;

protected:

    cmd_line_t cmd_line;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template <class T>
bool getValue(const std::string &str, T &value)
{
    std::istringstream ss(str);

    try
    {
        ss >> value;
    }
    catch (std::exception)
    {
        return false;
    }

    return true;
}

#endif
