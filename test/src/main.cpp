#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<RoutePath> routePath = new RoutePath("../routes/Moskow-Vjazma/route1.trk");
    osg::Vec3 pos = routePath->getPosition(10000.0f);

    model_info_t model_info;
    model_info.filepath = "../data/park_pass.dmd";
    model_info.texture_path = "../data/park.tga";

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(createLODNode(model_info));

    root->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    root->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}


