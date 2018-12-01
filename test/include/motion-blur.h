//------------------------------------------------------------------------------
//
//
//
//
//------------------------------------------------------------------------------
#ifndef     MOTION_BLUR_H
#define     MOTION_BLUR_H

#include    <osg/Object>
#include    <osgUtil/Optimizer>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MotionBlurOperation : public osg::Operation
{
public:

    MotionBlurOperation(double persistence)
        : osg::Referenced(true)
        , osg::Operation("MotionBlur", true)
        , _cleared(false)
        , _persistence(persistence)
    {

    }

    virtual void operator() (osg::Object *object);

protected:

    bool _cleared;
    double _persistence;
    double _t0;
};

#endif // MOTION_BLUR_H
