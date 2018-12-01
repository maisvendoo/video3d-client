//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef     TRAJECTORY_H
#define     TRAJECTORY_H

#include    <osg/Referenced>

#include    <string>

#include    "trajectory-element.h"
#include    "route-path.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TrainTrajectory : public osg::Referenced
{
public:

    TrainTrajectory(int direction,
                    float height);

    void update(const traj_element_t &traj_elem, const float &delta_time);

    osg::Vec3   getPosition() const;
    osg::Vec3   getAttitude() const;

private:

    int                         direction;
    float                       height;
    float                       init_yaw;
    osg::ref_ptr<RoutePath>     routePath;
    std::string                 routeDir;

    osg::Vec3                   position;
    osg::Vec3                   attitude;
};

#endif // TRAJECTORY_H
