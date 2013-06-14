/***************************************************************
 * Name:      PreferenceSon.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-12-14
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/PreferenceSon.h"

/**
 * @class PrefSon
 * @brief Interface représentant différents volumes sonores - Passer les fichiers au format XML
 */

BEGIN_EVENT_TABLE(PrefSon, wxScrolledWindow)
    EVT_RADIOBOX(ID_APP_PREF_SON_CHOIX, PrefSon::Son_RadioModif_Nouveau)
    EVT_CHOICE(ID_APP_PREF_SON_LISTE_MODIF, PrefSon::Son_ModifOuvrirFichier)
    EVT_BUTTON(ID_APP_PREF_SON_ENREGISTRER, PrefSon::Son_Bouton_Enregistrer)
    EVT_BUTTON(ID_APP_PREF_SON_ANNULER, PrefSon::Son_Bouton_Annuler)
    EVT_BUTTON(ID_APP_PREF_SON_APPLIQUER, PrefSon::Son_Bouton_Appliquer)
    EVT_BUTTON(ID_APP_PREF_SON_SUPPRIMER, PrefSon::Son_Bouton_Supprimer)
    EVT_BUTTON(ID_APP_PREF_SON_ACTUEL, PrefSon::Son_Bouton_Actuel)
    EVT_TEXT(ID_APP_PREF_SON_BOITE, PrefSon::BoiteNouveauModifiee)
END_EVENT_TABLE()


/**
 * Constructeur
 */
PrefSon::PrefSon()
{}

/**
 * Constructeur
 * @param Parent un pointeur sur la fenêtre parente
 */
PrefSon::PrefSon(wxWindow *Parent) : wxScrolledWindow(Parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL | wxHSCROLL)
{}

/**
 * Destructeur
 */
PrefSon::~PrefSon()
{}

/**
 * Crée les différents éléments graphique du panel et les place dessus.
 */
void PrefSon::Creer()
{
    SetScrollbars(20, 20, 50, 50);

    m_sizer1V = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer1V);

    //Choix sous forme de bouton radio
    wxString proposition[2]; proposition[0] = _("Nouveau"); proposition[1] = _("Modifier");
    m_choix = new wxRadioBox(this, ID_APP_PREF_SON_CHOIX, _("Mon choix"), wxDefaultPosition, wxDefaultSize, 2, proposition, 1, wxRA_SPECIFY_ROWS);
    m_sizer1V->Add(m_choix, 0, wxALL | wxSHAPED, 5);

    m_listeModif = new wxChoice(this, ID_APP_PREF_SON_LISTE_MODIF);//Liste déroulante
    m_sizer1V->Add(m_listeModif, 0, wxALL | wxSHAPED, 5);
    CreerListe(m_listeModif);//Listage

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);//Tableau des données
    m_sizer1V->Add(m_sizer2H, 0, wxALL | wxEXPAND, 5);
    m_sizerNewModif = new wxStaticBoxSizer(wxVERTICAL, this, _("Nouveau"));
    m_sizerActuel = new wxStaticBoxSizer(wxVERTICAL, this, _("Valeurs actuelles"));
    m_sizer2H->Add(m_sizerNewModif, 0, wxALL | wxEXPAND, 5);
    m_sizer2H->Add(m_sizerActuel, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 5);

    wxStaticText* TextNom = new wxStaticText[2];
    TextNom[0].Create(this, wxID_ANY, _("Nom")); TextNom[1].Create(this, wxID_ANY, _("Nom"));
    wxStaticText* TextVolume = new wxStaticText[2];
    TextVolume[0].Create(this, wxID_ANY, _("Volume")); TextVolume[1].Create(this, wxID_ANY, _("Volume"));
    wxStaticText* TextVolumePC = new wxStaticText[2];
    TextVolumePC[0].Create(this, wxID_ANY, _("Volume PC")); TextVolumePC[1].Create(this, wxID_ANY, _("Volume PC"));


 //////////////Partie Modification de jeu//////////////////////
    m_sizerNewModifTAB = new wxFlexGridSizer(3, 2, 5, 5);//Suite des cases contenant des valeurs modifiables
    m_sizerNewModif->Add(m_sizerNewModifTAB, 0, wxALL | wxEXPAND, 5);

    m_boiteNomMod = new wxTextCtrl(this, ID_APP_PREF_SON_BOITE, _T(""));
    m_boiteVolMod = new wxSpinCtrl(this, wxID_ANY, _T(""));
    m_boiteVolPCMod = new wxSpinCtrl(this, wxID_ANY, _T(""));
    m_boiteVolPCMod->SetRange(-1, 100);

    m_sizerNewModifTAB->Add(&TextNom[0], 0, wxALL, 0);
    m_sizerNewModifTAB->Add(m_boiteNomMod, 0, wxALL | wxEXPAND, 0);
    m_sizerNewModifTAB->Add(&TextVolume[0], 0, wxALL, 0);
    m_sizerNewModifTAB->Add(m_boiteVolMod, 0, wxALL | wxEXPAND, 0);
    m_sizerNewModifTAB->Add(&TextVolumePC[0], 0, wxALL, 0);
    m_sizerNewModifTAB->Add(m_boiteVolPCMod, 0, wxALL | wxEXPAND, 0);

//////////////Partie Valeurs actuelles//////////////////////
    wxSizer *sizer4Actuel_NON_Modifiable = new wxFlexGridSizer(3, 2, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerActuel->Add(sizer4Actuel_NON_Modifiable, 0, wxALL | wxEXPAND, 5);

    m_boiteNomActuel = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_boiteVolActuel = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_boiteVolPCActuel = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_boiteNomActuel->ChangeValue(_("Jeu par défaut"));
    m_boiteVolActuel->ChangeValue(_T("100"));
    m_boiteVolPCActuel->ChangeValue(_T("-1"));

    sizer4Actuel_NON_Modifiable->Add(&TextNom[1], 0, wxALL, 0);
    sizer4Actuel_NON_Modifiable->Add(m_boiteNomActuel, 0, wxALL | wxEXPAND, 0);
    sizer4Actuel_NON_Modifiable->Add(&TextVolume[1], 0, wxALL, 0);
    sizer4Actuel_NON_Modifiable->Add(m_boiteVolActuel, 0, wxALL | wxEXPAND, 0);
    sizer4Actuel_NON_Modifiable->Add(&TextVolumePC[1], 0, wxALL, 0);
    sizer4Actuel_NON_Modifiable->Add(m_boiteVolPCActuel, 0, wxALL | wxEXPAND, 0);

//////////////Partie Création des boutons//////////////////////
    m_sizerBouton = new wxFlexGridSizer(1, 5, 5, 5);
    m_sizer1V->Add(m_sizerBouton, 0, wxUP | wxALIGN_BOTTOM, 5);

    wxButton *m_Bouton_Enregistrer = new wxButton(this, ID_APP_PREF_SON_ENREGISTRER, _("Enregistrer"));
    wxButton *m_Bouton_Annuler = new wxButton(this, ID_APP_PREF_SON_ANNULER, _("Annuler"));
    m_Bouton_Appliquer = new wxButton(this, ID_APP_PREF_SON_APPLIQUER, _("Appliquer"));
    m_Bouton_Supprimer = new wxButton(this, ID_APP_PREF_SON_SUPPRIMER, _("Supprimer"));
    wxButton *m_Bouton_Actuel = new wxButton(this, ID_APP_PREF_SON_ACTUEL, _("Actuel"));

    m_sizerBouton->Add(m_Bouton_Enregistrer, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Annuler, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Appliquer, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Supprimer, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Actuel, 0, wxALL | wxEXPAND, 5);

//////////////Partie Affectation valeurs//////////////////////
    m_listeModif->Enable(false);
    m_Bouton_Appliquer->Enable(false);
    m_Bouton_Supprimer->Enable(false);
    m_listeModif_Nouveau = NOUVEAU;
    m_sizer1V->Layout();
}

/**
 * Liste tous les éléments présent dans le dossier Son
 * @param liste élément graphique devant être mis à jour
 * @return le nombre d'éléments présent dans liste
 */
int PrefSon::CreerListe(wxChoice *liste)
{
    int nombre = 0;
    wxFile fichier;
    fichier.Create(Parametre::Get()->getRepertoireParametre(_T("Liste_Son.txt")), true);

    if (wxDir::Exists(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son"))))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son")));
        bool continuer = Repertoire.GetFirst(&copie, _T("*.sauve"), wxDIR_FILES);

        while (continuer)
        {
            fichier.Write(copie);
            fichier.Write(_T("\r\n"));
            nombre++;
            liste->Append(copie);
            continuer = Repertoire.GetNext(&copie);
        }
    }
    fichier.Close();
    return nombre;
}

/**
 * Évènement - Modifie l'accessibilité des élément graphique en fonction du mode création/modification
 */
void PrefSon::Son_RadioModif_Nouveau(wxCommandEvent &event)
{
    m_listeModif_Nouveau = event.GetInt();

    if (m_listeModif_Nouveau == MODIFIER)
    {
        m_listeModif->Enable(true);
        m_Bouton_Appliquer->Enable(true);
        m_Bouton_Supprimer->Enable(true);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Modifier"));
    }
    else if (m_listeModif_Nouveau == NOUVEAU)
    {
        m_listeModif->Enable(false);
        m_Bouton_Appliquer->Enable(false);
        m_Bouton_Supprimer->Enable(false);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Nouveau"));
    }
    m_boiteNomMod->Clear();
    m_boiteVolMod->SetValue(0);
    m_boiteVolPCMod->SetValue(0);
    m_sizer1V->Layout();
}

/**
 * Méthode pour un changement manuel
 * @param changement le mode utilisé
 * @see Couleur_RadioModif_Nouveau
 */
void PrefSon::Son_Modif_Nouveau(int changement)
{
    m_listeModif_Nouveau = changement;

    if (m_listeModif_Nouveau == MODIFIER)
    {
        m_listeModif->Enable(true);
        m_Bouton_Appliquer->Enable(true);
        m_Bouton_Supprimer->Enable(true);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Modifier"));
    }
    else if (m_listeModif_Nouveau == NOUVEAU)
    {
        m_listeModif->Enable(false);
        m_Bouton_Appliquer->Enable(false);
        m_Bouton_Supprimer->Enable(false);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Nouveau"));
    }
    m_boiteNomMod->Clear();
    m_boiteVolMod->SetValue(0);
    m_boiteVolPCMod->SetValue(0);
    m_sizer1V->Layout();
}

/**
 * Evènement - Appelé lors de la demande de lecture d'un fichier contenant des préférences
 */
void PrefSon::Son_ModifOuvrirFichier(wxCommandEvent &WXUNUSED(event))
{
    wxString nomFichier = m_listeModif->GetString(m_listeModif->GetCurrentSelection());

    wxTextFile fichier(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son"), nomFichier));
    fichier.Open();
    if (fichier.GetLine(0).IsSameAs(_T("#EXTSAUVE_S1")))
    {
        m_boiteNomMod->ChangeValue(fichier.GetLine(1));
        m_boiteVolMod->SetValue(fichier.GetLine(2));
        m_boiteVolPCMod->SetValue(fichier.GetLine(3));
    }
}

/**
 * Évènement - Enregistre dans un fichier les paramètres sélectionnés
 */
void PrefSon::Son_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event))
{
    if (!m_boiteNomMod->IsEmpty() && (m_listeModif_Nouveau == NOUVEAU || m_listeModif->GetCurrentSelection() != wxNOT_FOUND))
    {
        wxFile FichierListe;
        wxString chemin = Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son"), wxFileName::GetPathSeparator()), cheminFichier, nom = m_boiteNomMod->GetValue(), volume, volumePC;

        cheminFichier = chemin;
        chemin << nom << _T(".sauve");

        volume << m_boiteVolMod->GetValue();
        volumePC << m_boiteVolPCMod->GetValue();

        if (wxFileName::FileExists(chemin) && m_listeModif_Nouveau == NOUVEAU && !m_Bouton_Appliquer->IsEnabled())
        {
            wxMessageBox(_("Un fichier portant ce nom existe déjà !"), _("Erreur !"));
        }
        else
        {
            if (m_listeModif_Nouveau == MODIFIER)// && m_boiteNomMod->IsModified())// || (m_listeModif_Nouveau == NOUVEAU && m_Bouton_Appliquer->IsEnabled())
            {
                cheminFichier << m_listeModif->GetString(m_listeModif->GetCurrentSelection());
                wxRemoveFile(cheminFichier);
            }
            if (!FichierListe.Create(chemin, true))
            {
                wxMessageBox(_("Erreur dans le nom.\nVérifiez que vous utilisez des caractères autorisés."), _("Erreur"));
                return;
            }
            FichierListe.Write(_T("#EXTSAUVE_S1\r\n"));
            FichierListe.Write(nom + _T("\r\n"));
            //FichierListe.Write();
            FichierListe.Write(volume + _T("\r\n"));
            //FichierListe.Write("\r\n");
            FichierListe.Write(volumePC);
            FichierListe.Write(_T("\r\n0.5\r\n0.5"));
            FichierListe.Close();
            m_listeModif->Clear();
            CreerListe(m_listeModif);
            if (m_listeModif_Nouveau == MODIFIER)
                m_listeModif->SetStringSelection(nom + _T(".sauve"));
            else
                m_Bouton_Appliquer->Enable(true);
        }
    }
    else
        wxMessageBox(_("Vous devez renseigner tous les champs"), _("Erreur !"));
}

/**
 * Évènement - Remet toutes les valeurs avec leur valeur par défaut
 */
void PrefSon::Son_Bouton_Annuler(wxCommandEvent &WXUNUSED(event))
{
    m_listeModif->SetSelection(wxNOT_FOUND);
    m_boiteNomMod->Clear();
    m_boiteVolMod->SetValue(0);
    m_boiteVolPCMod->SetValue(0);
}

/**
 * Évènement - Applique les paramètres à la classe Musique et enregistre les données dans le fichier correspondant
 */
void PrefSon::Son_Bouton_Appliquer(wxCommandEvent &event)
{
    Son_Bouton_Enregistrer(event);

    if (!m_boiteNomMod->IsEmpty())
    {
        wxString nom = m_boiteNomMod->GetValue(), volume, volumePC;
        volume << m_boiteVolMod->GetValue();
        volumePC << m_boiteVolPCMod->GetValue();

        m_boiteNomActuel->ChangeValue(nom);
        m_boiteVolActuel->ChangeValue(volume);
        m_boiteVolPCActuel->ChangeValue(volumePC);

        m_listeModif->Clear();
        CreerListe(m_listeModif);
        if (m_listeModif_Nouveau == MODIFIER)
            m_listeModif->SetStringSelection(nom + _T(".sauve"));

        Musique::Get()->SetVolume(m_boiteVolMod->GetValue());
        SliderSon::Get()->SetValue(m_boiteVolMod->GetValue());
    }
}

/**
 * Évènement - Supprime le fichier sélectionné
 */
void PrefSon::Son_Bouton_Supprimer(wxCommandEvent &WXUNUSED(event))
{
    if (!wxRemoveFile(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son"), m_listeModif->GetString(m_listeModif->GetCurrentSelection()))))
        return;

    m_listeModif->Clear();
    CreerListe(m_listeModif);

    m_boiteNomMod->Clear();
    m_boiteVolMod->SetValue(0);
    m_boiteVolPCMod->SetValue(0);
}

/**
 * Évènement - Recopie les valeurs courantes dans le filtre sans l'enregistrer
 */
void PrefSon::Son_Bouton_Actuel(wxCommandEvent &WXUNUSED(event))
{
    m_boiteVolMod->SetValue(m_boiteVolActuel->GetValue());
    //Pas encore utilisable !
    //m_boiteVolPCMod->SetValue(m_boiteVolPCActuel->GetValue());
}

/**
 * Met le volume sonore actuel à jour
 * @param valeur la nouvelle valeur du volume sonore
 */
void PrefSon::SetValeurMusique(long valeur)
{
    wxString volume;
    volume << valeur;
    m_boiteVolActuel->ChangeValue(volume);
}

/**
 * Évènement - La modification du nom du filtre désactive le bouton "Appliquer"
 */
void PrefSon::BoiteNouveauModifiee(wxCommandEvent &WXUNUSED(event))
{
    //Désactive le bouton appliquer si le texte est modifié dans les condition suivantes
    if (m_listeModif_Nouveau == NOUVEAU && m_Bouton_Appliquer->IsEnabled())
        m_Bouton_Appliquer->Enable(false);
}

/**
 * Renvoie l'instance des radioBox "Mon choix". Ceci permet une sélection extérieure du mode d'utilisation
 * @return l'instance
 */
wxRadioBox* PrefSon::GetRadioBox()
{    return m_choix;}



