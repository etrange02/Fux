#ifndef DUREE_H
#define DUREE_H

/**
 * @struct Duree
 * @brief Structure représentant le temps en minute, seconde, et la totalité en seconde
 */

class Duree
{
    public:
        Duree();
        virtual ~Duree();
        Duree& operator=(const Duree& other);
        unsigned int GetMinute();
        void SetMinute(unsigned int val);
        unsigned int GetSeconde();
        void SetSeconde(unsigned int val);
        unsigned int GetMSecondeTot();
        void SetMSecondeTot(unsigned int val);

    private:
        unsigned int m_minute; //!< Member variable "m_minute"
        unsigned int m_seconde; //!< Member variable "m_seconde"
        unsigned int m_msecondeTot; //!< Member variable "m_msecondeTot"
};

#endif // DUREE_H
