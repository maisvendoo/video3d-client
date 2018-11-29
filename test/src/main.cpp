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

    osg::ref_ptr<RoutePath> routePath = new RoutePath(fs.getRouteRootDir() + fs.separator() + "route1.trk");

    osg::ref_ptr<osg::Group> track = routePath->getTrackLine(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

    //if (track.valid())
      //  root->addChild(track.get());

    float x = 400.0f;

    while (!viewer.done())
    {
        osg::Vec3 orth;
        osg::Vec3 pos = routePath->getPosition(x, orth) + osg::Vec3(0.0f, 0.0f, 3.0f);

        orth = orth *= (1 / orth.length());

        float angle = asinf(orth.x());

        osg::Matrix m = osg::Matrix::translate(pos *= -1.0f);
        m *= osg::Matrix::rotate(-osg::PI / 2, osg::Vec3(1.0f, 0.0f, 0.0f));
        m *= osg::Matrix::rotate(static_cast<double>(angle), osg::Vec3(0.0f, 1.0f, 0.0f));

        viewer.getCamera()->setViewMatrix(m);
        x += 1.0f;

        viewer.frame();
    }

    return 0;
}


