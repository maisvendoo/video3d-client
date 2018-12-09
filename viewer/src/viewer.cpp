#include    "viewer.h"

#include    <osg/BlendFunc>
#include    <osg/CullFace>
#include    <osg/GraphicsContext>

#include    "filesystem.h"
#include    "config-reader.h"

#include    <sstream>
#include    <fstream>

#include    "abstract-loader.h"
#include    "lighting.h"
#include    "motion-blur.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RouteViewer::RouteViewer(int argc, char *argv[])
  : is_ready(false)
{
    is_ready = init(argc, argv);
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
bool RouteViewer::isReady() const
{
    return is_ready;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int RouteViewer::run()
{
    return viewer.run();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::init(int argc, char *argv[])
{
    FileSystem &fs = FileSystem::getInstance();

    // Read settings from config file
    settings = loadSettings(fs.getConfigDir() + fs.separator() + "settings.xml");

    // Parse command line
    CommandLineParser parser(argc, argv);
    cmd_line_t cmd_line = parser.getCommadLine();
    overrideSettingsByCommandLine(cmd_line, settings);    

    // Load selected route
    if (!loadRoute(cmd_line.route_dir.value))
        return false;

    // Init graphical engine settings
    if (!initEngineSettings(root.get()))
        return false;

    // Init display settings
    if (!initDisplay(&viewer, settings))
        return false;

    // Init motion blur
    if (!initMotionBlurEffect(&viewer, settings))
        return false;

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
settings_t RouteViewer::loadSettings(const std::string &cfg_path) const
{
    settings_t settings;

    ConfigReader cfg(cfg_path);

    if (cfg.isOpenned())
    {
        std::string secName = "Viewer";

        cfg.getValue(secName, "HostAddress", settings.host_addr);
        cfg.getValue(secName, "Port", settings.port);
        cfg.getValue(secName, "Width", settings.width);
        cfg.getValue(secName, "Height", settings.height);
        cfg.getValue(secName, "FullScreen", settings.fullscreen);
        cfg.getValue(secName, "LocalMode", settings.localmode);
    }

    return settings;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RouteViewer::overrideSettingsByCommandLine(const cmd_line_t &cmd_line,
                                                settings_t settings)
{
    if (cmd_line.host_addr.is_present)
        settings.host_addr = cmd_line.host_addr.value;

    if (cmd_line.port.is_present)
        settings.port = cmd_line.port.value;

    if (cmd_line.width.is_present)
        settings.width = cmd_line.width.value;

    if (cmd_line.height.is_present)
        settings.height = cmd_line.height.value;

    if (cmd_line.fullscreen.is_present)
        settings.fullscreen = cmd_line.fullscreen.value;

    if (cmd_line.localmode.is_present)
        settings.localmode = cmd_line.localmode.value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::loadRoute(const std::string &routeDir)
{
    if (routeDir.empty())
        return false;

    FileSystem &fs = FileSystem::getInstance();
    std::string routeType = osgDB::findDataFile(routeDir + fs.separator() + "route-type");

    if (routeType.empty())
        return false;

    std::ifstream stream(routeType);

    if (!stream.is_open())
        return false;

    std::string routeExt = "";
    stream >> routeExt;

    if (routeExt.empty())
        return false;

    std::string routeLoaderPlugin = routeExt + "-route-loader";

    osg::ref_ptr<RouteLoader> loader = loadRouteLoader("../plugins", routeLoaderPlugin);

    if (!loader.valid())
        return false;

    loader->load(routeDir);
    root = loader->getRoot();

    viewer.addEventHandler(loader->getCameraEventHandler(1, 3.0f));

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::initEngineSettings(osg::Group *root)
{
    if (root == nullptr)
        return false;

    // Common graphics settings
    osg::StateSet *stateset = root->getOrCreateStateSet();
    osg::BlendFunc *blendFunc = new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    stateset->setAttributeAndModes(blendFunc);
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    stateset->setMode(GL_ALPHA, osg::StateAttribute::ON);
    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    stateset->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

    osg::ref_ptr<osg::CullFace> cull = new osg::CullFace;
    cull->setMode(osg::CullFace::BACK);
    stateset->setAttributeAndModes(cull.get(), osg::StateAttribute::ON);

    // Set lighting
    initEnvironmentLight(root,
                         osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f),
                         1.0f,
                         0.0f,
                         90.0f);

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::initDisplay(osgViewer::Viewer *viewer,
                              const settings_t &settings)
{
    if (viewer == nullptr)
        return false;

    viewer->setSceneData(root.get());
    viewer->getCamera()->setClearColor(osg::Vec4(0.63f, 0.80f, 0.97f, 1.0f));
    viewer->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    viewer->getCamera()->setAllowEventFocus(false);

    if (settings.fullscreen)
        viewer->setUpViewOnSingleScreen(0);

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RouteViewer::initMotionBlurEffect(osgViewer::Viewer *viewer,
                                       const settings_t &settings)
{
    (void) settings;

    if (viewer == nullptr)
        return false;

    osg::DisplaySettings::instance()->setMinimumNumAccumBits(8, 8, 8, 8);
    viewer->realize();

    osgViewer::Viewer::Windows windows;
    viewer->getWindows(windows);

    for (auto it = windows.begin(); it != windows.end(); ++it)
        (*it)->add(new MotionBlurOperation(0.1));

    return true;
}