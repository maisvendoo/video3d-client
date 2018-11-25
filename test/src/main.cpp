#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    osg::ArgumentParser args(&argc, argv);
    std::string routeDir;
    args.read("--route", routeDir);

    SceneLoader scnLoader(routeDir);    

    osg::ref_ptr<osg::Group> root = scnLoader.getRoot();    

    root->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    root->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    root->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

    osg::ref_ptr<osg::CullFace> cull = new osg::CullFace;
    cull->setMode(osg::CullFace::BACK);
    root->getOrCreateStateSet()->setAttributeAndModes(cull, osg::StateAttribute::ON);

    osg::ref_ptr<osg::Light> sun = new osg::Light;
    sun->setLightNum(0);
    sun->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));

    float alpha = osg::PIf / 2.0f;
    osg::Vec3 sunDir(0.0f, cosf(alpha), -sinf(alpha));
    sun->setDirection(sunDir);

    osg::ref_ptr<osg::LightSource> light0 = new osg::LightSource;
    light0->setLight(sun);

    root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    root->addChild(light0.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.getCamera()->setClearColor(osg::Vec4(0.63f, 0.80f, 0.97f, 1.0f));
    viewer.setUpViewOnSingleScreen(0);

    osg::ref_ptr<RoutePath> routePath = new RoutePath(routeDir + "/route1.trk");
    float x = 400.0f;

    while (!viewer.done())
    {
        osg::Vec3 pos = routePath->getPosition(x) + osg::Vec3(0.0f, 0.0f, 3.0f);
        osg::Vec3 forward = routePath->getPosition(x + 100.0f) + osg::Vec3(0.0f, 0.0f, 3.0f);

        osg::Vec3 orth = forward - pos;
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


