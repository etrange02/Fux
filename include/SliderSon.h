#ifndef SLIDERSON_H
#define SLIDERSON_H

#include <wx/wx.h>
#include <wx/slider.h>
#include "Define.h"


class SliderSon : public wxSlider
{
    public:
        /** Default constructor */
        SliderSon(wxWindow *Parent);
        /** Default destructor */
        virtual ~SliderSon();
        static SliderSon* Get();

        void SonUp();
        void SonDown();
};

#endif // SLIDERSON_H
