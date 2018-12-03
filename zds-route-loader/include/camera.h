//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef     CAMERA_H
#define     CAMERA_H

#include    <osgGA/GUIEventAdapter>
#include    <osgGA/GUIActionAdapter>
#include    <osgViewer/Viewer>

#include    "trajectory.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RailwayManipulator : public osgGA::GUIEventHandler
{
public:

    RailwayManipulator(TrainTrajectory *train_traj);

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:

    osg::ref_ptr<TrainTrajectory>   train_traj;
    double                          ref_time;
    double                          _startTime;
    traj_element_t                  traj_element;
    osg::Matrix                     matrix;

    void moveCamera(const traj_element_t &traj_element, osgViewer::Viewer *viewer);
};

#endif // CAMERA_H
