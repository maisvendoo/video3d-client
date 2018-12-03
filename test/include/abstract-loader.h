#ifndef		ABSTRACT_LOADER_H
#define		ABSTRACT_LOADER_H

#include    <osg/Group>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum ReadResult
{
    FILE_READ_SUCCESS,
    FILE_NOT_FOUND,
    FILE_NOT_HANDLED
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class OSG_EXPORT AbstractLoader
{
public:

    ///
    AbstractLoader(std::string routeDir);

    /// Destructor
    virtual ~AbstractLoader() {}

    /// Get route scene group node
    virtual osg::Group *getRoot();

protected:

    /// Route directory
    std::string routeDir;

    osg::ref_ptr<osg::Group>    root;

    virtual ReadResult loadDataFile(const std::string &filepath) = 0;
};

#endif
