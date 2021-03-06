#ifndef DIRECTSHOWFRAMEGRABBER_H
#define DIRECTSHOWFRAMEGRABBER_H

#include "AbstractFrameGrabber.h"

class DirectshowFrameGrabberPrivate;

class DirectshowFrameGrabber : public AbstractFrameGrabber
{
public:
    DirectshowFrameGrabber();
    ~DirectshowFrameGrabber();
    virtual bool open(const std::string& fileName);
    virtual bool seek(int64_t time);
    virtual AbstractVideoFrame* grabCurrentFrame();
    virtual int64_t duration();
    virtual void abort();
protected:
    int64_t duration_;
protected:
  DirectshowFrameGrabberPrivate * const d_ptr;
};

#endif // DIRECTSHOWFRAMEGRABBER_H
