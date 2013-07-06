/***************************************************************
 * Name:      MusiqueGraph.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-11-04
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/MusiqueGraph.h"

/**
 * @class MusiqueGraph
 * @brief Panel affichant le graph, la barre de temps et le titre de la chanson.
 */

const wxEventType wxEVT_MUSIQUE_SUPPRESSION = wxNewEventType();

BEGIN_EVENT_TABLE(MusiqueGraph, wxGLCanvas)
    EVT_PAINT(MusiqueGraph::OnPaint)
    EVT_ERASE_BACKGROUND(MusiqueGraph::OnEraseBackground)
    EVT_LEFT_DOWN(MusiqueGraph::PlacerChanson)
    EVT_KEY_DOWN(MusiqueGraph::OnToucheDown)
    EVT_SIZE(MusiqueGraph::Sizer_Size)
    EVT_MOUSE_EVENTS(MusiqueGraph::MouseEvents)
END_EVENT_TABLE()

static MusiqueGraph* s_instanceMusiqueGraph = NULL;

/**
 * Constructeur.
 * @param Parent la classe parente de cette instance
 * @param args les arguments à appliquer à la fenêtre
 */
MusiqueGraph::MusiqueGraph(wxWindow *Parent, int *args) : wxGLCanvas(Parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)//wxPanel(Parent)
{
    s_instanceMusiqueGraph = this;
    m_context = new wxGLContext(this);
       // m_context->SetCurrent(this);
    //wxGLCanvas::SetCurrent(*m_context);
    this->SetCurrent(*m_context);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_imageText = new ImageText;
    m_imageTemps = new ImageText;

    m_epaisseurSpectre = 512;
    m_sizer_h = 275;
    m_sizer_w = 512;
    m_largeur_tab = 512;
    m_bandeRestante = 0;
    m_intervalle = 0;
    m_moitEcran = 246;
    m_fond.SetRGB(0, 0, 0);
    m_barre.SetRGB(0, 0, 255);
    m_police.SetRGB(255, 0, 255);
    m_haut.SetRGB(255, 0, 0);
    m_miSup.SetRGB(0, 255, 0);
    m_doubleBarre = false;
    m_miInf.SetRGB(0, 0, 0);
    m_bas.SetRGB(0, 0, 0);
    spectrum = NULL;
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

/**
 * Destructeur
 */
MusiqueGraph::~MusiqueGraph()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("MusiqueGraph::~MusiqueGraph - fin"));
    #endif
    delete m_imageText;
    delete m_context;

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("MusiqueGraph::~MusiqueGraph - fin2"));
    #endif
}

/**
 * Retourne l'instance de la classe MusiqueGraph. Attention, l'instance n'est pas créée ici !
 * @return l'instance
 */
MusiqueGraph* MusiqueGraph::Get()
{    return s_instanceMusiqueGraph;}

/**
 * Redéfinition de OnIdle
 */
void MusiqueGraph::OnIdle()
{    Refresh();}

/**
 * Redéfinition de OnPaint
 */
void MusiqueGraph::OnPaint(wxPaintEvent&)
{
    if (!IsShown())
        return;

    wxGLCanvas::SetCurrent(*m_context);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    wxPaintDC(this);//Permet un arrêt rapide et non unblocage de la fenêtre

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_fond.GetRed()/255.0, m_fond.GetGreen()/255.0, m_fond.GetBlue()/255.0, 1);

    if (Musique::Get()->IsContainingMus())
    {
        register unsigned int i = 0;
        if (Musique::Get()->GetLecture())
        {
            register unsigned int spec = 0, retard = 0;
            Couleur couleur;

            Musique::Get()->RemplirSpectre(spectrum, m_largeur_tab);
            glBegin(GL_LINES);
            for (i = 0; i < m_largeur_tab-1; i++)
            {
                spec = (unsigned int)(spectrum[i]*10*m_sizer_h);
                if (spec > (unsigned int) m_sizer_h -19)
                    spec = m_sizer_h -19;

                if (m_doubleBarre)
                {
                    glColor3ub(m_miSup.GetRed(), m_miSup.GetGreen(), m_miSup.GetBlue());
                    glVertex2i(i+1+retard, m_moitEcran);
                    couleur = CouleurExtrem(spec, m_sizer_h, HAUT_SUP);
                    glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                    glVertex2i(i+1+retard, m_moitEcran + spec/2);
                    //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19-spec)/2, 1, spec/2), m_miSup, CouleurExtrem(spec, m_sizer_h, HAUT_SUP), wxNORTH);

                    glColor3ub(m_miInf.GetRed(), m_miInf.GetGreen(), m_miInf.GetBlue());
                    glVertex2i(i+1+retard, m_moitEcran);
                    couleur = CouleurExtrem(spec, m_sizer_h, BAS_INF);
                    glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                    glVertex2i(i+1+retard, m_moitEcran - spec/2);
                    //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19)/2, 1, spec/2), m_miInf, CouleurExtrem(spec, m_sizer_h, BAS_INF), wxSOUTH);
                }
                else
                {
                    glColor3ub(m_miSup.GetRed(), m_miSup.GetGreen(), m_miSup.GetBlue());
                    glVertex2i(i+1+retard, 19);//-1, -1);
                    couleur = CouleurExtrem(spec, m_sizer_h);
                    glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                    glVertex2i(i+1+retard, spec + 19);
                    //Dc.GradientFillLinear(wxRect(i + retard, m_sizer_h-19-spec, 1, spec), m_miSup, CouleurExtrem(spec, m_sizer_h), wxNORTH);
                }

                if (m_intervalle != 0 && retard < m_bandeRestante && i+retard >= m_intervalle*(retard +1))
                {
                    retard++;
                    if (spec != 0)
                    {
                        if (spec == 1 || spec == 2 || spec == 3);
                        else if (spec < (unsigned int) m_sizer_h - 19)
                            spec -= 1;
                        /*else if (spec < 0)
                            spec +=1;*/

                        if (m_doubleBarre)
                        {
                            glColor3ub(m_miSup.GetRed(), m_miSup.GetGreen(), m_miSup.GetBlue());
                            glVertex2i(i+1+retard, m_moitEcran);
                            couleur = CouleurExtrem(spec, m_sizer_h, HAUT_SUP);
                            glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                            glVertex2i(i+1+retard, m_moitEcran + spec/2);
                            //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19-spec)/2, 1, spec/2), m_miSup, CouleurExtrem(spec, m_sizer_h, HAUT_SUP), wxNORTH);

                            glColor3ub(m_miInf.GetRed(), m_miInf.GetGreen(), m_miInf.GetBlue());
                            glVertex2i(i+1+retard, m_moitEcran);
                            couleur = CouleurExtrem(spec, m_sizer_h, BAS_INF);
                            glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                            glVertex2i(i+1+retard, m_moitEcran - spec/2 -1);
                            //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19)/2, 1, spec/2), m_miInf, CouleurExtrem(spec, m_sizer_h, BAS_INF), wxSOUTH);
                        }
                        else
                        {
                            glColor3ub(m_miSup.GetRed(), m_miSup.GetGreen(), m_miSup.GetBlue());
                            glVertex2i(i+1+retard, 19);
                            couleur = CouleurExtrem(spec, m_sizer_h);
                            glColor3ub(couleur.GetRed(), couleur.GetGreen(), couleur.GetBlue());
                            glVertex2i(i+1+retard, spec + 19);
                            //Dc.GradientFillLinear(wxRect(i + retard, m_sizer_h-19-spec, 1, spec), m_miSup, CouleurExtrem(spec, m_sizer_h), wxNORTH);
                        }
                    }
                }
            }
            glEnd();
        }

        // Un test à faire sur l'état de Musique
        int largeur = Musique::Get()->GetTpsActuel()*m_sizer_w/Musique::Get()->GetDureeMS();
        glBegin(GL_QUADS);
            glColor4ub(m_barre.GetRed(), m_barre.GetGreen(), m_barre.GetBlue(), 255);
            glVertex2i(0, 0);
            glVertex2i(0, 19);
            glVertex2i(largeur, 19);
            glVertex2i(largeur, 0);
        glEnd();

        glColor4ub(m_police.GetRed(), m_police.GetGreen(), m_police.GetBlue(), 255);
        m_imageText->Affiche();

        if (ScreenToClient(wxGetMousePosition()).y >= m_sizer_h-19 && ScreenToClient(wxGetMousePosition()).x >= 0 && ScreenToClient(wxGetMousePosition()).x <= m_sizer_w+30)
        {
            int point = ScreenToClient(wxGetMousePosition()).x, tot = (point*Musique::Get()->GetDureeMS())/(1024*m_sizer_w);
            wxString duree = wxString::Format(_T("%d:%2d/%d:%2d"), Musique::Get()->GetDUREETpsActuel().GetMinute(), Musique::Get()->GetDUREETpsActuel().GetSeconde(), Musique::Get()->GetDUREEDuree().GetMinute(), Musique::Get()->GetDUREEDuree().GetSeconde());
            wxString tps = wxString::Format(_T("%d:%2d"), tot/60, tot%60);
            for (i = 0; i<duree.length(); i++)
                if (duree[i] == ' ')
                    duree[i] = '0';
            for (i = 0; i<tps.length(); i++)
                if (tps[i] == ' ')
                    tps[i] = '0';

            m_imageTemps->Creer(tps, duree);
            m_imageTemps->Affiche(point);
        }
    }

    SwapBuffers();// Dessine !
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Redéfinition empêche l'effacement
 */
void MusiqueGraph::OnEraseBackground(wxEraseEvent&)
{}

/**
 * Inutilisé
 */
void MusiqueGraph::GetCouleurNom(Couleur **fond, Couleur **barre, Couleur **police, Couleur **haut, Couleur **miSup, bool **doubleBarre, Couleur **miInf, Couleur **bas)
{
    *fond = &m_fond;
    *barre = &m_barre;
    *police = &m_police;
    *haut = &m_haut;
    *miSup = &m_miSup;
    *doubleBarre = &m_doubleBarre;
    *miInf = &m_miInf;
    *bas = &m_bas;
}

/**
 * Retourne la couleur d'une extrémité en fonction de la hauteur de la colonne
 * @param hauteur la hauteur de la colonne à colorer
 * @param sizer_h la hauteur de l'écran
 * @param niveau la partie du graphe concernée (partie supérieure ou inférieure)
 * @return la couleur
 */
Couleur MusiqueGraph::CouleurExtrem(int hauteur, int sizer_h, e_GraphPosition niveau)
{
    Couleur retour;
    if (niveau == HAUT_SUP)
    {
        if (m_haut.GetRed() == m_miSup.GetRed())
            retour.SetRed(m_haut.GetRed());
        else if (m_haut.GetRed() > m_miSup.GetRed())
            retour.SetRed(255*hauteur/(sizer_h-19));
        else
            retour.SetRed(255-255*hauteur/(sizer_h-19));

        if (m_haut.GetGreen() == m_miSup.GetGreen())
            retour.SetGreen(m_haut.GetGreen());
        else if (m_haut.GetGreen() > m_miSup.GetGreen())
            retour.SetGreen(255*hauteur/(sizer_h-19));
        else
            retour.SetGreen(255-255*hauteur/(sizer_h-19));

        if (m_haut.GetBlue() == m_miSup.GetBlue())
            retour.SetBlue(m_haut.GetBlue());
        else if (m_haut.GetBlue() > m_miSup.GetBlue())
            retour.SetBlue(255*hauteur/(sizer_h-19));
        else
            retour.SetBlue(255-255*hauteur/(sizer_h-19));
    }
    else if (niveau == BAS_INF)
    {
        if (m_miInf.GetRed() == m_bas.GetRed())
            retour.SetRed(m_miInf.GetRed());
        else if (m_miInf.GetRed() > m_bas.GetRed())
            retour.SetRed(255-255*hauteur/(sizer_h-19));
        else
            retour.SetRed(255*hauteur/(sizer_h-19));

        if (m_miInf.GetGreen() == m_bas.GetGreen())
            retour.SetGreen(m_miInf.GetGreen());
        else if (m_miInf.GetGreen() > m_bas.GetGreen())
            retour.SetGreen(255-255*hauteur/(sizer_h-19));
        else
            retour.SetGreen(255*hauteur/(sizer_h-19));

        if (m_miInf.GetBlue() == m_bas.GetBlue())
            retour.SetBlue(m_miInf.GetBlue());
        else if (m_miInf.GetBlue() > m_bas.GetBlue())
            retour.SetBlue(255-255*hauteur/(sizer_h-19));
        else
            retour.SetBlue(255*hauteur/(sizer_h-19));
    }
    return retour;
}

/**
 * Redéfinie les valeurs à prendre en compte en fonction de la taille de la fenêtre
 */
void MusiqueGraph::Sizer_Size(wxSizeEvent &event)
{
    if (spectrum)
        delete[] spectrum;
    /*m_sizer_h = GetContainingSizer()->GetSize().GetHeight();
    m_sizer_w = GetContainingSizer()->GetSize().GetWidth();*/
    m_sizer_h = event.GetSize().GetHeight();
    m_sizer_w = event.GetSize().GetWidth();

    glViewport(0, 0, m_sizer_w, m_sizer_h);//Zone définie sur tout l'écran
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, m_sizer_w, 0, m_sizer_h);//Modifie l'échelle
    //La zone de l'écran va de 1 à 512 !!
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    if (m_sizer_w >= 512 && m_sizer_w < 1024)
        m_largeur_tab = 512;
    else if (m_sizer_w < 2048)
        m_largeur_tab = 1024;
    else if (m_sizer_w < 4096)
        m_largeur_tab = 2048;
    else if (m_sizer_w < 8192)
        m_largeur_tab = 4096;
    else
        m_largeur_tab = 8192;

    m_bandeRestante = m_sizer_w - m_largeur_tab;
    if (m_bandeRestante != 0)
        m_intervalle = m_sizer_w/(m_bandeRestante+1);

    m_moitEcran = (m_sizer_h-19)/2 +19;
    spectrum = new float[m_largeur_tab];
    TitreChange();
}

/**
 * Lors d'un appuie sur l'écran, déplace le curseur de lecture en fonction du clic effectué
 * @param event
 */
void MusiqueGraph::PlacerChanson(wxMouseEvent &event)
{
    wxClientDC DC(this);
    wxPoint position = event.GetLogicalPosition(DC);

    if (position.y > m_sizer_h -20)
    {
        int msposition = (position.x)*(Musique::Get()->GetDureeMS())/(m_sizer_w);
        Musique::Get()->SetPositionMS(msposition);
    }
}

/**
 * Modifie les couleurs de la fenêtre
 * @param fond
 * @param barre
 */
void MusiqueGraph::AffecteCouleurs(Couleur fond, Couleur barre, Couleur police, Couleur haut, Couleur miSup, bool doubleBarre, Couleur miInf, Couleur bas)
{
    m_fond = fond;
    m_barre = barre;
    m_police = police;
    m_haut = haut;
    m_miSup = miSup;
    m_doubleBarre = doubleBarre;
    m_miInf = miInf;
    m_bas = bas;
}

/**
 * Évènement clavier
 */
void MusiqueGraph::OnToucheDown(wxKeyEvent &event)
{
    if (event.GetKeyCode() == 'P')
    {
        if (Musique::Get()->GetLecture())
            Musique::Get()->SetPause(true);
        else if (Musique::Get()->GetPause())
            Musique::Get()->SetPause(false);
        else
            Musique::Get()->ChangementChanson(IDENTIQUE);
    }
    else if (event.GetKeyCode() == 'S')
        Musique::Get()->SetStop();
    else if (event.GetKeyCode() == 'A')
        Musique::Get()->SetAleatoire(!Musique::Get()->GetAleatoire());
    else if (event.GetKeyCode() == '+' || event.GetKeyCode() == WXK_ADD || event.GetKeyCode() == WXK_NUMPAD_ADD)
        SliderSon::Get()->SonUp();
    else if (event.GetKeyCode() == '-' || event.GetKeyCode() == WXK_SUBTRACT || event.GetKeyCode() == WXK_NUMPAD_SUBTRACT || event.GetKeyCode() == '6')
        SliderSon::Get()->SonDown();
    else if (event.GetKeyCode() == WXK_RIGHT)
        Musique::Get()->ChangementChanson(SUIVANT);
    else if (event.GetKeyCode() == WXK_LEFT)
        Musique::Get()->ChangementChanson(PRECEDENT);
    else if (event.GetKeyCode() == WXK_DELETE)
    {
        wxCommandEvent evt(wxEVT_MUSIQUE_SUPPRESSION, GetId());
        GetParent()->GetEventHandler()->AddPendingEvent(evt);
    }
    else
        event.Skip();
}


/**
 * Modifie le texte affiché à l'écran indiquant le nom de la chanson
 */
void MusiqueGraph::TitreChange()
{   m_imageText->Creer(Musique::Get()->GetNomChanson(), m_largeur_tab, m_sizer_w);}

/**
 * Évènement clavier et souris simultané. Ctrl + utilisation de la molette, Alt +...
 */
void MusiqueGraph::MouseEvents(wxMouseEvent &event)
{
    if (event.ControlDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            Musique::Get()->ChangementChanson(SUIVANT);
        else
            Musique::Get()->ChangementChanson(PRECEDENT);
    }
    else if (event.AltDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            SliderSon::Get()->SonUp();
        else
            SliderSon::Get()->SonDown();
    }
    else
        event.Skip();
}



