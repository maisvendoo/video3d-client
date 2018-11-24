#ifndef     ROUTE_PATH_H
#define     ROUTE_PATH_H

#include    <fstream>

#include    <osg/Referenced>
#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

#include    "track.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RoutePath : public osg::Referenced
{
public:

    /// Default constructor
    RoutePath() {}
    /// Constructor with automatic track loading
    RoutePath(const std::string &track_file_path);
    /// Destructor
    ~RoutePath() {}

    osg::Vec3 getPosition(float railway_coord);
    osg::Vec3 getPosition(float railway_coord, osg::Vec3 &orth);

protected:

    std::vector<track_t>    track_data;

    bool load(const std::string &track_file_path);

    bool load(std::istream &stream);

    std::string getLine(std::istream &stream) const;

    track_t findTrack(float railway_coord);
};

#endif // ROUTE_PATH_H
