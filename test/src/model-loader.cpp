#include    "model-loader.h"
#include    "texture-loader.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info)
{
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->setFileName(0, model_info.filepath);
    pagedLOD->setRange(0, 0.0f, model_info.view_distance);

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setWrap(osg::Texture2D::WRAP_R, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);
    texture->setUpdateCallback(new LoadTextureCallback(model_info.texture_path));
    texture->setResizeNonPowerOfTwoHint(false);
    texture->setUnRefImageDataAfterApply(true);

    pagedLOD->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    return pagedLOD.release();
}
