#ifndef COULEUR_H
#define COULEUR_H

/**
 * @class Couleur
 * @brief Champs RVB
 */

class Couleur
{
    public:
        Couleur(unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0);
        virtual ~Couleur();
        unsigned int GetRed();
        void SetRed(unsigned int val);
        unsigned int GetBlue();
        void SetBlue(unsigned int val);
        unsigned int GetGreen();
        void SetGreen(unsigned int val);
        void SetRGB(unsigned int red, unsigned int green, unsigned int blue);

        //Couleur& operator=(const Couleur& other);
    private:
        unsigned int m_red;
        unsigned int m_green;
        unsigned int m_blue;
};

#endif // COULEUR_H
