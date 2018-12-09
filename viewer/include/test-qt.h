#ifndef TESTQT_H
#define TESTQT_H

#include    <QObject>
#include    <osgGA/GUIEventHandler>
#include    <iostream>

class Sender : public QObject, public osgGA::GUIEventHandler
{
    Q_OBJECT

public:

    Sender() : QObject(), osgGA::GUIEventHandler(), a(0)
    {

    }

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
    {
        switch (ea.getEventType())
        {
        case osgGA::GUIEventAdapter::FRAME:

            emit sendNumber(a);
            a++;

            break;

        default:

            break;
        }

        return false;
    }

signals:

    void sendNumber(int num);

private:

    int a;
};

class Resiever : public QObject
{
    Q_OBJECT

public:

    Resiever()
    {

    }

public slots:

    void resieveNum(int num)
    {
        std::cout << num << std::endl;
    }
};

#endif // TESTQT_H
