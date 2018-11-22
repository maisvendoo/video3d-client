#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Node *createLODNode(const std::string &filepath)
{
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->setFileName(0, filepath);
    pagedLOD->setRange(0, 0.0f, 1000.0f);

    return pagedLOD.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> root = createLODNode("../data/park_pass.dmd");

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setWrap(osg::Texture2D::WRAP_R, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);
    texture->setUpdateCallback(new LoadTextureCallback("../data/park.tga"));

    root->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    root->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    root->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}


