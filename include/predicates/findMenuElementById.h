#ifndef FINDMENUELEMENTBYID_H
#define FINDMENUELEMENTBYID_H

class MenuElement;

class findMenuElementById
{
    public:
        /** Default constructor */
        findMenuElementById(const int id);
        /** Default destructor */
        virtual ~findMenuElementById();

        bool operator()(const MenuElement& element);

    private:
        const int m_id;
};

#endif // FINDMENUELEMENTBYID_H
