#ifndef SLIDERSON_H
#define SLIDERSON_H

#include <wx/wx.h>
#include <wx/slider.h>
#include "Define.h"


class SliderSon : public wxSlider
{
    public:
        static SliderSon* Get();
        void SonUp();
        void SonDown();

    protected:
        SliderSon();
        /** Default destructor */
        virtual ~SliderSon();
};

#endif // SLIDERSON_H
