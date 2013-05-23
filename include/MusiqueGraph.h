#ifndef MUSIQUEGRAPH_H_INCLUDED
#define MUSIQUEGRAPH_H_INCLUDED

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <wx/dir.h>
#include "Musique.h"
#include "ImageText.h"
#include "Define.h"
#include "SliderSon.h"

class Musique;

extern const wxEventType wxEVT_MUSIQUE_SUPPRESSION;

class MusiqueGraph : public wxGLCanvas
{
    public:
        MusiqueGraph(wxWindow *Parent, int *args);
        virtual ~MusiqueGraph();
        static MusiqueGraph* Get();

        void OnIdle();
        Couleur CouleurExtrem(int, int, e_GraphPosition niveau = HAUT_SUP);
        void Sizer_Size(wxSizeEvent &event);
        void PlacerChanson(wxMouseEvent&);
        void AffecteCouleurs(Couleur, Couleur, Couleur, Couleur, Couleur, bool, Couleur, Couleur);
        void GetCouleurNom(Couleur**, Couleur**, Couleur**, Couleur**, Couleur**, bool**, Couleur**, Couleur**);
        void OnToucheDown(wxKeyEvent&);
        void OnPaint(wxPaintEvent&);
        void OnEraseBackground(wxEraseEvent&);
        void TitreChange();
        void MouseEvents(wxMouseEvent&);

    protected:
        Musique *m_musique;

        float *spectrum, m_intervalle;
        int m_epaisseurSpectre, m_sizer_w, m_sizer_h;//puissance de 2, 64 à 8192
        unsigned int m_largeur_tab, m_bandeRestante, m_moitEcran;
        bool m_doubleBarre;
        Couleur m_fond, m_barre, m_police, m_haut, m_miSup, m_miInf, m_bas;
        wxGLContext *m_context;
        ImageText *m_imageText, *m_imageTemps;

        DECLARE_EVENT_TABLE()
};

#endif // MUSIQUEGRAPH_H_INCLUDED
