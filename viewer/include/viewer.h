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

#include    "cmd-line.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RouteViewer : public osgViewer::Viewer
{
public:

    RouteViewer(int argc, char *argv[]);

    virtual ~RouteViewer();

protected:

    bool init(int argc, char *argv[]);

    cmd_line_t parseCommandLine(int argc, char *argv[]) const;
};

#endif // VIEWER_H
