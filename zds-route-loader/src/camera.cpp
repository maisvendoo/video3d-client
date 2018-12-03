#include    "camera.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RailwayManipulator::RailwayManipulator(TrainTrajectory *train_traj)
    : train_traj(train_traj)
    , ref_time(0.0)
    , _startTime(0.0)

{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RailwayManipulator::handle(const osgGA::GUIEventAdapter &ea,
                                osgGA::GUIActionAdapter &aa)
{
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::FRAME:
    {
        osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer *>(&aa);

        if (!viewer)
            break;

        double time = viewer->getFrameStamp()->getReferenceTime();
        double delta_time = time - _startTime;
        ref_time += delta_time;
        _startTime = time;

        moveCamera(traj_element, viewer);

        break;
    }

    case osgGA::GUIEventAdapter::USER:
    {

        break;
    }

    default:

        break;
    }

    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RailwayManipulator::moveCamera(const traj_element_t &traj_element,
                                    osgViewer::Viewer *viewer)
{
    train_traj->update(traj_element, static_cast<float>(ref_time));

    osg::Vec3 position = train_traj->getPosition();
    osg::Vec3 attitude = train_traj->getAttitude();

    matrix = osg::Matrix::translate(position *= -1.0f);
    matrix *= osg::Matrix::rotate(static_cast<double>(attitude.x()), osg::Vec3(1.0f, 0.0f, 0.0f));
    matrix *= osg::Matrix::rotate(static_cast<double>(attitude.z()), osg::Vec3(0.0f, 1.0f, 0.0f));

    viewer->getCamera()->setViewMatrix(matrix);
}
