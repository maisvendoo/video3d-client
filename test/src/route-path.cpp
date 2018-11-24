#include    "route-path.h"
#include    "string-funcs.h"

#include    <sstream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RoutePath::RoutePath(const std::string &track_file_path)
{
    load(track_file_path);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 RoutePath::getPosition(float railway_coord)
{
    track_t track = findTrack(railway_coord);

    float motion = railway_coord - track.rail_coord;
    osg::Vec3 motion_vec = track.orth *= motion;
    osg::Vec3 pos = track.begin_point + motion_vec;

    return pos;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 RoutePath::getPosition(float railway_coord, osg::Vec3 &orth)
{
    track_t track = findTrack(railway_coord);

    float motion = railway_coord - track.rail_coord;
    osg::Vec3 motion_vec = track.orth *= motion;
    osg::Vec3 pos = track.begin_point + motion_vec;

    orth = track.orth;

    return pos;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RoutePath::load(const std::string &track_file_path)
{
    std::string ext = osgDB::getLowerCaseFileExtension(track_file_path);

    if (ext != "trk")
        return false;

    std::string fileName = osgDB::findDataFile(track_file_path);

    if (fileName.empty())
        return false;

    std::ifstream stream(fileName.c_str(), std::ios::in);

    if (!stream)
        return false;

    return load(stream);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RoutePath::load(std::istream &stream)
{
    float rail_coord = 0.0f;

    while (!stream.eof())
    {
        std::string line = getLine(stream);

        std::istringstream ss(line);

        track_t track;

        ss >> track.begin_point.x()
           >> track.begin_point.y()
           >> track.begin_point.z()
           >> track.end_point.x()
           >> track.end_point.y()
           >> track.end_point.z()
           >> track.prev_uid
           >> track.next_uid
           >> track.arrows
           >> track.voltage
           >> track.ordinate;

        osg::Vec3 dir_vector = track.end_point - track.begin_point;
        track.length = dir_vector.length();
        track.orth = dir_vector *= (1 / track.length);

        osg::Vec3 up(0, 0, 1);
        track.right = track.orth ^ up;
        track.right = track.right *= (1 / track.right.length());

        track.rail_coord = rail_coord;
        rail_coord += track.length;

        track_data.push_back(track);
    }

    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string RoutePath::getLine(std::istream &stream) const
{
    std::string line = "";
    std::getline(stream, line);
    std::string tmp = delete_symbol(line, '\r');
    tmp = delete_symbol(tmp, ';');
    std::replace(tmp.begin(), tmp.end(), ',', ' ');

    return tmp;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
track_t RoutePath::findTrack(float railway_coord)
{
    track_t track;

    size_t left_idx = 0;
    size_t right_idx = track_data.size() - 1;
    size_t idx = (left_idx + right_idx) / 2;

    while (idx != left_idx)
    {
        track = track_data.at(idx);

        if (railway_coord < track.rail_coord)
            right_idx = idx;
        else
            left_idx = idx;

        idx = (left_idx + right_idx) / 2;
    }

    return track;
}


