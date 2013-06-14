#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <wx/wx.h>
#include <wx/timer.h>
#include "Musique.h"
#include "MusiqueGraph.h"


class TimerGraph : public wxTimer
{
    public:
        TimerGraph();
        virtual ~TimerGraph();
        virtual void Notify();

    protected:
};

#endif // TIMER_H_INCLUDED
