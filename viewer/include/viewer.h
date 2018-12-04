//------------------------------------------------------------------------------
//
//
//
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief
 * \copyright
 * \author
 * \date
 */

#ifndef     VIEWER_H
#define     VIEWER_H

#include    <osgViewer/Viewer>

#include    "settings.h"
#include    "command-line-parser.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RouteViewer : public osgViewer::Viewer
{
public:

    RouteViewer(int argc, char *argv[]);

    virtual ~RouteViewer();

    bool isReady() const;

protected:

    bool        is_ready;
    settings_t  settings;

    bool init(int argc, char *argv[]);   

    settings_t loadSettings(const std::string &cfg_path) const;

    void overrideSettingsByCommandLine(const cmd_line_t &cmd_line,
                                       settings_t settings);
};

#endif // VIEWER_H
