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

    //viewer.getDatabasePager()->setTargetMaximumNumberOfPageLOD(1);

    viewer.setSceneData(root.get());
    viewer.getCamera()->setClearColor(osg::Vec4(0.63f, 0.80f, 0.97f, 1.0f));

    viewer.getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    viewer.setUpViewOnSingleScreen(0);

    float dir = 1.0f;
    float x = 400.0f;

    osg::ref_ptr<RoutePath> routePath;
    float psi = 0.0f;

    if (dir > 0.0f)
        routePath = new RoutePath(fs.getRouteRootDir() + fs.separator() + "route1.trk");
    else
    {
        routePath = new RoutePath(fs.getRouteRootDir() + fs.separator() + "route2.trk");
        psi = osg::PIf;
    }

    while (!viewer.done())
    {
        osg::Vec3 attitude;
        osg::Vec3 pos = routePath->getPosition(x, attitude) + osg::Vec3(0.0f, 0.0f, 3.0f);

        osg::Matrix m = osg::Matrix::translate(pos *= -1.0f);
        m *= osg::Matrix::rotate(-osg::PI / 2 + attitude.x(), osg::Vec3(1.0f, 0.0f, 0.0f));

        m *= osg::Matrix::rotate(static_cast<double>(attitude.z() + psi), osg::Vec3(0.0f, 1.0f, 0.0f));

        viewer.getCamera()->setViewMatrix(m);

        x += 1.0f * dir;

        viewer.frame();
    }

    return 0;
}


