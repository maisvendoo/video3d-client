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
class LoadTextureCallback : public osg::StateAttributeCallback
{
public:

    LoadTextureCallback(std::string texture_path) : texture_path(texture_path)
      , is_textured(false)
    {

    }

    virtual void operator() (osg::StateAttribute *, osg::NodeVisitor *);

protected:

    std::string texture_path;
    bool is_textured;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void LoadTextureCallback::operator()(osg::StateAttribute *sa, osg::NodeVisitor *nv)
{
    if (is_textured)
        return;

    if (texture_path.empty())
        return;

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(texture_path);

    if (image.valid())
    {
        osg::Texture2D *texture = static_cast<osg::Texture2D *>(sa);
        texture->setImage(image.get());
        is_textured = true;
    }
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


