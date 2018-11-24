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

    osg::ref_ptr<osg::MatrixTransform> trans1 = new osg::MatrixTransform;

    model_info_t model_info;
    model_info.filepath = routeDir + "/models/sky.dmd";
    model_info.texture_path = routeDir + "/textures/sky_day.bmp";
    model_info.view_distance = 10000.0f;

    osg::ref_ptr<osg::Node> sky = osgDB::readNodeFile(model_info.filepath);
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(model_info.texture_path);

    if (image.valid())
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D(image.get());
        sky->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    }

    trans1->addChild(sky.get());
    root->addChild(trans1.get());

    root->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    root->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.getCamera()->setClearColor(osg::Vec4(0.63f, 0.80f, 0.97f, 1.0f));

    osg::ref_ptr<RoutePath> routePath = new RoutePath(routeDir + "/route1.trk");
    float x = 400.0f;

    while (!viewer.done())
    {
        osg::Vec3 pos = routePath->getPosition(x) + osg::Vec3(0.0f, 0.0f, 3.0f);
        osg::Vec3 forward = routePath->getPosition(x + 0.01f) + osg::Vec3(0.0f, 0.0f, 3.0f);

        osg::Vec3 orth = forward - pos;
        orth = orth *= (1 / orth.length());

        float angle = asinf(orth.x());

        osg::Matrix m = osg::Matrix::translate(pos *= -1.0f);
        m *= osg::Matrix::rotate(-osg::PI / 2, osg::Vec3(1.0f, 0.0f, 0.0f));
        m *= osg::Matrix::rotate(angle, osg::Vec3(0.0f, 1.0f, 0.0f));

        trans1->setMatrix(osg::Matrix::translate(pos));
        viewer.getCamera()->setViewMatrix(m);
        x += 1.0f;

        viewer.frame();
    }

    return 0;
}


