#ifndef DIRFILEMANAGERDATA_H
#define DIRFILEMANAGERDATA_H


/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileManagerData
        {
            public:
                /** Default constructor */
                DirFileManagerData();
                /** Default destructor */
                virtual ~DirFileManagerData();

                bool isRecursive() const;
                void setRecursive(bool recursive);
                bool isRecursiveAsked() const;
                void setRecursiveAsked();

            protected:
            private:
                bool m_recurseHasBeenAsked;
                bool m_recursive;
        };
    }
}

#endif // DIRFILEMANAGERDATA_H
