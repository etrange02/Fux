/***************************************************************
 * Name:      MusicFileWriter.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileWriter.h"

using namespace TagLib;

MusicFileWriter::MusicFileWriter(const Music& src, Music& dst) :
    m_musicSrc(src),
    m_musicDst(dst)
{
}

MusicFileWriter::~MusicFileWriter()
{
}

void MusicFileWriter::process()
{
    fillData();
    saveImage();
    renameFile();
}

void MusicFileWriter::fillData()
{
//    wxString tempo = fichierTAG;
//    wxString art = m_BoiteArtiste->GetValue();
//    for (unsigned int j = 0; j < art.length(); j++)
//    {
//        if (art[j] == '/')
//            art[j] = ';';
//    }
//    m_ObjetTAG.tag()->setArtist(TagLib::String(art.fn_str()));//Artiste
//    m_ObjetTAG.tag()->setAlbum(TagLib::String(m_BoiteAlbum->GetValue().fn_str()));//Album
//    m_ObjetTAG.tag()->setTitle(TagLib::String(m_BoiteTitre->GetValue().fn_str()));//Titre
//    m_ObjetTAG.tag()->setYear(m_BoiteAnnee->GetValue());//Année
//    if (m_BoiteGenre->GetValue().IsSameAs(_T("Other")) || m_BoiteGenre->GetValue().IsSameAs(_T("Inconnu")))
//        m_ObjetTAG.tag()->setGenre("");//Genre
//    else
//        m_ObjetTAG.tag()->setGenre(TagLib::String(m_BoiteGenre->GetValue().fn_str()));//Genre
//    m_ObjetTAG.save();
//    m_ObjetTAG = TagLib::FileRef(_T(""));
//
//    int i = tempo.Find(wxFileName::GetPathSeparator(), true);
//    tempo = tempo.Left(i);
//    tempo << wxFileName::GetPathSeparator() << m_BoiteNom->GetValue();//Nom du fichier
//    if (fichierTAG != tempo)
//    {
//        if (wxRenameFile(fichierTAG, tempo, true))
//            FichierListe::Get()->EchangeNom(fichierTAG, tempo);
//        else
//            wxMessageBox(_("Erreur dans le nom.\nVérifiez que vous utilisez des caractères autorisés."), _("Erreur"));
//    }
}

void MusicFileWriter::saveImage()
{

}

void MusicFileWriter::renameFile()
{

}

