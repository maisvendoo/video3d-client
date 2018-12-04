#include    "viewer.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RouteViewer::RouteViewer(int argc, char *argv[]) : osgViewer::Viewer ()
{
    init(argc, argv);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RouteViewer::~RouteViewer()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::init(int argc, char *argv[])
{
    FileSystem &fs = FileSystem::getInstance();
    std::string routeDir = fs.getRouteRootDir();

    cmd_line_t cmd_line = parseCommandLine(argc, argv);

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
cmd_line_t RouteViewer::parseCommandLine(int argc, char *argv[]) const
{
    cmd_line_t cmd_line;

    osg::ArgumentParser args(&argc, argv);

    args.read("--route", cmd_line.routeDir);

    return cmd_line;
}
