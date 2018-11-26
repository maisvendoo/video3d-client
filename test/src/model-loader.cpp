#include    "model-loader.h"
#include    "texture-loader.h"

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info)
{
    std::string fileName = osgDB::findDataFile(model_info.filepath);

    if (fileName.empty())
        return nullptr;

    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->setFileName(0, fileName);
    pagedLOD->setRange(0, 0.0f, model_info.view_distance);

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);

    if (model_info.mipmap)
    {
        texture->setNumMipmapLevels(9);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    }

    texture->setUpdateCallback(new LoadTextureCallback(model_info.texture_path));
    texture->setResizeNonPowerOfTwoHint(false);
    texture->setUnRefImageDataAfterApply(true);

    pagedLOD->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    return pagedLOD.release();
}
