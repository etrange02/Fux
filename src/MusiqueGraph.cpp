/***************************************************************
 * Name:      MusiqueGraph.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-11-04
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/MusiqueGraph.h"

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

static MusiqueGraph* instanceMusiqueGraph = NULL;

/**
 * Constructeur
 * @param Parent la classe parente de cette instance
 * @param args les arguments à appliquer à la fenêtre
 */
MusiqueGraph::MusiqueGraph(wxWindow *Parent, int *args) : wxGLCanvas(Parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)//wxPanel(Parent)
{
    instanceMusiqueGraph = this;
    m_musique = Musique::Get();
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
    m_fond.R = 0; m_fond.V = 0; m_fond.B = 0;
    m_barre.R = 0; m_barre.V = 0; m_barre.B = 255;
    m_police.R = 255; m_police.V = 0; m_police.B = 255;
    m_haut.R = 255; m_haut.V = 0; m_haut.B = 0;
    m_miSup.R = 0; m_miSup.V = 255; m_miSup.B = 0;
    m_doubleBarre = false;
    m_miInf.R = 0; m_miInf.V = 0; m_miInf.B = 0;
    m_bas.R = 0; m_bas.V = 0; m_bas.B = 0;
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
 * Retourne l'instance de la classe MusiqueGraph
 * @return l'instance
 */
MusiqueGraph* MusiqueGraph::Get()
{    return instanceMusiqueGraph;}

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
    glClearColor(m_fond.R/255.0, m_fond.V/255.0, m_fond.B/255.0, 1);

    if (m_musique->IsContainingMus())
    {
        register unsigned int i = 0;
        if (m_musique->GetLecture())
        {
            register unsigned int spec = 0, retard = 0;
            Couleur couleur = {0, 0, 0};

            m_musique->RemplirSpectre(spectrum, m_largeur_tab);
            glBegin(GL_LINES);
            for (i = 0; i < m_largeur_tab-1; i++)
            {
                spec = (unsigned int)(spectrum[i]*10*m_sizer_h);
                if (spec > (unsigned int) m_sizer_h -19)
                    spec = m_sizer_h -19;

                if (m_doubleBarre)
                {
                    glColor3ub(m_miSup.R, m_miSup.V, m_miSup.B);
                    glVertex2i(i+1+retard, m_moitEcran);
                    couleur = CouleurExtrem(spec, m_sizer_h, HAUT_SUP);
                    glColor3ub(couleur.R, couleur.V, couleur.B);
                    glVertex2i(i+1+retard, m_moitEcran + spec/2);
                    //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19-spec)/2, 1, spec/2), m_miSup, CouleurExtrem(spec, m_sizer_h, HAUT_SUP), wxNORTH);

                    glColor3ub(m_miInf.R, m_miInf.V, m_miInf.B);
                    glVertex2i(i+1+retard, m_moitEcran);
                    couleur = CouleurExtrem(spec, m_sizer_h, BAS_INF);
                    glColor3ub(couleur.R, couleur.V, couleur.B);
                    glVertex2i(i+1+retard, m_moitEcran - spec/2);
                    //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19)/2, 1, spec/2), m_miInf, CouleurExtrem(spec, m_sizer_h, BAS_INF), wxSOUTH);
                }
                else
                {
                    glColor3ub(m_miSup.R, m_miSup.V, m_miSup.B);
                    glVertex2i(i+1+retard, 19);//-1, -1);
                    couleur = CouleurExtrem(spec, m_sizer_h);
                    glColor3ub(couleur.R, couleur.V, couleur.B);
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
                            glColor3ub(m_miSup.R, m_miSup.V, m_miSup.B);
                            glVertex2i(i+1+retard, m_moitEcran);
                            couleur = CouleurExtrem(spec, m_sizer_h, HAUT_SUP);
                            glColor3ub(couleur.R, couleur.V, couleur.B);
                            glVertex2i(i+1+retard, m_moitEcran + spec/2);
                            //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19-spec)/2, 1, spec/2), m_miSup, CouleurExtrem(spec, m_sizer_h, HAUT_SUP), wxNORTH);

                            glColor3ub(m_miInf.R, m_miInf.V, m_miInf.B);
                            glVertex2i(i+1+retard, m_moitEcran);
                            couleur = CouleurExtrem(spec, m_sizer_h, BAS_INF);
                            glColor3ub(couleur.R, couleur.V, couleur.B);
                            glVertex2i(i+1+retard, m_moitEcran - spec/2 -1);
                            //Dc.GradientFillLinear(wxRect(i + retard, (m_sizer_h-19)/2, 1, spec/2), m_miInf, CouleurExtrem(spec, m_sizer_h, BAS_INF), wxSOUTH);
                        }
                        else
                        {
                            glColor3ub(m_miSup.R, m_miSup.V, m_miSup.B);
                            glVertex2i(i+1+retard, 19);
                            couleur = CouleurExtrem(spec, m_sizer_h);
                            glColor3ub(couleur.R, couleur.V, couleur.B);
                            glVertex2i(i+1+retard, spec + 19);
                            //Dc.GradientFillLinear(wxRect(i + retard, m_sizer_h-19-spec, 1, spec), m_miSup, CouleurExtrem(spec, m_sizer_h), wxNORTH);
                        }
                    }
                }
            }
            glEnd();
        }

        // Un test à faire sur l'état de Musique
        int largeur = m_musique->GetTpsActuel()*m_sizer_w/m_musique->GetDureeMS();
        glBegin(GL_QUADS);
            glColor4ub(m_barre.R, m_barre.V, m_barre.B, 255);
            glVertex2i(0, 0);
            glVertex2i(0, 19);
            glVertex2i(largeur, 19);
            glVertex2i(largeur, 0);
        glEnd();

        glColor4ub(m_police.R, m_police.V, m_police.B, 255);
        m_imageText->Affiche();

        if (ScreenToClient(wxGetMousePosition()).y >= m_sizer_h-19 && ScreenToClient(wxGetMousePosition()).x >= 0 && ScreenToClient(wxGetMousePosition()).x <= m_sizer_w+30)
        {
            int point = ScreenToClient(wxGetMousePosition()).x, tot = (point*m_musique->GetDureeMS())/(1024*m_sizer_w);
            wxString duree = wxString::Format(_T("%d:%2d/%d:%2d"), m_musique->GetDUREETpsActuel().minute, m_musique->GetDUREETpsActuel().seconde, m_musique->GetDUREEDuree().minute, m_musique->GetDUREEDuree().seconde);
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
    unsigned int r = 0, v = 0, b = 0;
    if (niveau == HAUT_SUP)
    {
        if (m_haut.R == m_miSup.R)
            r = m_haut.R;
        else if (m_haut.R > m_miSup.R)
            r = 255*hauteur/(sizer_h-19);
        else
            r = 255-255*hauteur/(sizer_h-19);

        if (m_haut.V == m_miSup.V)
            v = m_haut.V;
        else if (m_haut.V > m_miSup.V)
            v = 255*hauteur/(sizer_h-19);
        else
            v = 255-255*hauteur/(sizer_h-19);

        if (m_haut.B == m_miSup.B)
            b = m_haut.B;
        else if (m_haut.B > m_miSup.B)
            b = 255*hauteur/(sizer_h-19);
        else
            b = 255-255*hauteur/(sizer_h-19);
    }
    else if (niveau == BAS_INF)
    {
        if (m_miInf.R == m_bas.R)
            r = m_miInf.R;
        else if (m_miInf.R > m_bas.R)
            r = 255-255*hauteur/(sizer_h-19);
        else
            r = 255*hauteur/(sizer_h-19);

        if (m_miInf.V == m_bas.V)
            v = m_miInf.V;
        else if (m_miInf.V > m_bas.V)
            v = 255-255*hauteur/(sizer_h-19);
        else
            v = 255*hauteur/(sizer_h-19);

        if (m_miInf.B == m_bas.B)
            b = m_miInf.B;
        else if (m_miInf.B > m_bas.B)
            b = 255-255*hauteur/(sizer_h-19);
        else
            b = 255*hauteur/(sizer_h-19);
    }
    Couleur retour = {r, v, b};
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
        m_musique->SetPositionMS(msposition);
    }
}

/**
 * Modifie les couleurs de la fenêtre
 * @param fond
 * @param barre
 */
void MusiqueGraph::AffecteCouleurs(Couleur fond, Couleur barre, Couleur police, Couleur haut, Couleur miSup, bool doubleBarre, Couleur miInf, Couleur bas)
{
    m_fond = fond; m_barre = barre; m_police = police;
    m_haut = haut; m_miSup = miSup;
    m_doubleBarre = doubleBarre;
    m_miInf = miInf; m_bas = bas;
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



