#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    osg::ArgumentParser args(&argc, argv);
    std::string routeDir;
    args.read("--route", routeDir);

    FileSystem &fs = FileSystem::getInstance();
    fs.setRouteRootDir(routeDir);

    SceneLoader scnLoader(routeDir);    

    osg::ref_ptr<osg::Group> root = scnLoader.getRoot();

    root->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    root->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_ALPHA, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

    osg::ref_ptr<osg::CullFace> cull = new osg::CullFace;
    cull->setMode(osg::CullFace::BACK);
    root->getOrCreateStateSet()->setAttributeAndModes(cull, osg::StateAttribute::ON);

    initEnvironmentLight(root.get(),
                         osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f),
                         1.0f,
                         180.0f,
                         45.0f);

    osgViewer::Viewer viewer;    


    viewer.setSceneData(root.get());
    viewer.getCamera()->setClearColor(osg::Vec4(0.63f, 0.80f, 0.97f, 1.0f));

    viewer.getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    viewer.setUpViewOnSingleScreen(0);

    osg::ref_ptr<TrainTrajectory> train_traj = new TrainTrajectory(1.0f, 3.0f);
    viewer.getCamera()->setAllowEventFocus(false);
    viewer.addEventHandler(new RailwayManipulator(train_traj.get()));
    viewer.setThreadingModel(osgViewer::Viewer::AutomaticSelection);

    osg::DisplaySettings::instance()->setMinimumNumAccumBits(8, 8, 8, 8);
    viewer.realize();

    osgViewer::Viewer::Windows windows;
    viewer.getWindows(windows);

    for (auto it = windows.begin(); it != windows.end(); ++it)
    {
        (*it)->add(new MotionBlurOperation(0.1));
    }

    return viewer.run();
}


