#ifndef MUSICMANAGERSWITCHER_H
#define MUSICMANAGERSWITCHER_H

#include "IMusicManager.h"
#include "MusicManagerDefaultDecorator.h"
#include "MusicManagerSearchDecorator.h"
#include "MusicManager.h"

class MusicManagerSwitcher
{
    public:
        static IMusicManager& get();
        static IMusicManager& getSearch();
        static void deleteInstance();


    private:
        /** Default constructor */
        MusicManagerSwitcher();
        /** Default destructor */
        virtual ~MusicManagerSwitcher();

        static MusicManagerSwitcher& getInstance();
        IMusicManager& getDefaultDecorator();
        IMusicManager& getSearchDecorator();

    private:
        MusicManager m_musicManager;
        MusicManagerDefaultDecorator m_defaultDecorator;
        MusicManagerSearchDecorator  m_searchDecorator;
};

#endif // MUSICMANAGERSWITCHER_H
