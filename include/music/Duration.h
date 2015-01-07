#ifndef DURATION_H
#define DURATION_H

/**
 * @struct Duration
 * @brief Abstraction of music time in minute, second and full time in second
 */

class Duration
{
    public:
        Duration();
        virtual ~Duration();
        Duration& operator=(const Duration& other);
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
