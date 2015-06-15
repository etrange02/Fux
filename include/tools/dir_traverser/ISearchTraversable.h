#ifndef ISEARCHTRAVERSABLE_H_INCLUDED
#define ISEARCHTRAVERSABLE_H_INCLUDED

class ISearchTraversable
{
    public:
        virtual ~ISearchTraversable() {}
        virtual void addFileLine(const wxString& path) = 0;
};

#endif // ISEARCHTRAVERSABLE_H_INCLUDED
