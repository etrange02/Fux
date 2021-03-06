/***************************************************************
 * Name:      ImagePochetteMusique.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-09-01
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/

#include "../../../include/gui/widgets/ImagePochetteMusique.h"

/**
 * @class ImagePochetteMusique
 * @brief Composant affichant une image, acceptant le Drag & Drop, et ouvre le navigateur de fichier pour changer l'image ; lors de tout changement, la fenêtre parente peut en être informée.
 */

BEGIN_EVENT_TABLE(ImagePochetteMusique, wxStaticBitmap)
    EVT_LEFT_DCLICK(ImagePochetteMusique::EvtSouris)
END_EVENT_TABLE()

const wxEventType wxEVT_IMAGE_SELECTION = wxNewEventType();

/**
 * Constructeur
 * @param Parent la fenêtre parente
 * @param id l'identifiant de l'instance
 * @param label un wxBitmap à modifier
 * @param warnParent si vrai, le parent est averti des modifications de l'image
 */
ImagePochetteMusique::ImagePochetteMusique(wxWindow* parent, wxWindowID id, const int width, const int height, bool warnParent) :
    m_modif(false),
    m_warnParent(warnParent),
    m_width(width),
    m_height(height),
    m_defaultBitmap(wxImage(m_width, m_height))
{
    wxStaticBitmap::Create(parent, id, m_defaultBitmap, wxPoint(), wxSize(m_width, m_height));
    SetDropTarget(new DropFichierImagePochetteMusique(this));
}

/**
 * Desctructeur
 */
ImagePochetteMusique::~ImagePochetteMusique()
{}

/**
 * Si affiche vaut vrai, l'image est affiché sinon, elle est effacée
 * @param affiche vrai si l'on veut prendre une l'image en mémoire
 * @return vrai si l'affiche a pu se faire
 */
bool ImagePochetteMusique::AfficheImage(bool affiche)
{
    if (affiche && m_image.IsOk())
    {
        SetBitmap(wxBitmap(m_image.Scale(m_width, m_height)));
        return true;
    }
    else
    {
        m_image.Destroy();
        SetBitmap(m_defaultBitmap);
        return false;
    }
}

/**
 * Retourne l'image
 * @return l'image
 */
wxImage& ImagePochetteMusique::GetImage()
{    return m_image;}

/**
 * Modifie l'image courante sans modifier l'affichage
 * @param image la nouvelle image
 */
void ImagePochetteMusique::SetImage(wxImage& image)
{
    m_image = image;
}

/**
 * Évènement - Affiche une boîte de dialogue pour sélectionner une nouvelle image. L'affichage n'est pas rafraichi.
 */
void ImagePochetteMusique::EvtSouris(wxMouseEvent &WXUNUSED(event))
{
    wxFileDialog navig(NULL, _("Choisissez une image"), wxStandardPaths::Get().GetDocumentsDir(), _T(""), _T("Image (*.jpg;*.jpeg)|*.jpg;*.jpeg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    int ouvert = navig.ShowModal();

    if (ouvert == wxID_OK)
        LectureImageEvent(navig.GetPath());
}

/**
 * Lit une image se trouvant à l'adresse chaine. Affichage non rafraichi
 * @param chaine le nom complet de l'image
 */
void ImagePochetteMusique::LectureImageEvent(wxString chaine)
{
    if (m_image.LoadFile(chaine))
    {
        if (m_warnParent)
        {
            wxCommandEvent evt(wxEVT_IMAGE_SELECTION, GetId());
            evt.SetString(chaine);
            GetParent()->GetEventHandler()->AddPendingEvent(evt);
        }
        m_modif = AfficheImage(true);
    }
}

/**
 * Test si l'image a été modifiée après sa création
 * @return true si une modification a eu lieu.
 */
bool ImagePochetteMusique::IsModified()
{
    return m_modif;
}


