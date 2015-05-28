#ifndef MUSIQUEGRAPH_H_INCLUDED
#define MUSIQUEGRAPH_H_INCLUDED

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "Classes.h"
#include "Define.h"
#include "widgets/SliderSon.h"
#include "settings/Couleur.h"

extern const wxEventType wxEVT_MUSIQUE_SUPPRESSION;

class ImageText;

namespace gui
{
    namespace music
    {
        class MusiqueGraph : public wxGLCanvas
        {
            public:
                MusiqueGraph(wxWindow *Parent, int *args);
                virtual ~MusiqueGraph();
                static MusiqueGraph* Get();

                virtual void OnIdle();
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

            private:
                Couleur m_fond;
                Couleur m_barre;
                Couleur m_police;
                Couleur m_haut;
                Couleur m_miSup;
                Couleur m_miInf;
                Couleur m_bas;
                float *spectrum;//puissance de 2, 64 à 8192
                float m_intervalle;
                int m_epaisseurSpectre;
                int m_sizer_w;
                int m_sizer_h;
                unsigned int m_largeur_tab;
                unsigned int m_bandeRestante;
                unsigned int m_moitEcran;
                bool m_doubleBarre;
                wxGLContext *m_context;
                ImageText *m_imageText;
                ImageText *m_imageTemps;

            DECLARE_EVENT_TABLE()
        };
    }
}

#endif // MUSIQUEGRAPH_H_INCLUDED
