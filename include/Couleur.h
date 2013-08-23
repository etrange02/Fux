#ifndef COULEUR_H
#define COULEUR_H

#include <wx/wx.h>
#include <wx/xml/xml.h>

class Couleur
{
    public:
        Couleur(unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, bool boolValue = false);
        Couleur(wxString chaine, bool boolValue);
        Couleur(wxXmlNode *node);
        virtual ~Couleur();
        void FromXMLNode(wxXmlNode *node);
        void FromString(wxString chaine, bool boolValue);
        unsigned int GetRed();
        bool GetBoolRed();
        void SetRed(unsigned int val);
        unsigned int GetBlue();
        bool GetBoolBlue();
        void SetBlue(unsigned int val);
        unsigned int GetGreen();
        bool GetBoolGreen();
        void SetGreen(unsigned int val);
        void SetRGB(unsigned int red, unsigned int green, unsigned int blue);
        void SetBoolRGB(bool red, bool green, bool blue);
        wxString ToString();
        wxString ToString(wxString mot);
        wxString ToBoolString();
        wxString ToBoolString(wxString mot);
        wxXmlNode* ToXMLNode(wxXmlNode *parent, wxString titre);

        //Couleur& operator=(const Couleur& other);
    private:
        unsigned int m_red;
        unsigned int m_green;
        unsigned int m_blue;
};

#endif // COULEUR_H
