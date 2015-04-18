#ifndef FINDMENUELEMENTBYID_H
#define FINDMENUELEMENTBYID_H

namespace explorer {
    class MenuElement;
}

class findMenuElementById
{
    public:
        /** Default constructor */
        findMenuElementById(const int id);
        /** Default destructor */
        virtual ~findMenuElementById();

        bool operator()(const ::explorer::MenuElement& element);

    private:
        const int m_id;
};

#endif // FINDMENUELEMENTBYID_H
