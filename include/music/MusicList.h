#ifndef MUSICLIST_H_INCLUDED
#define MUSICLIST_H_INCLUDED

#include <wx/wx.h>
#include <vector>

#include <wx/dir.h>

#include "../Define.h"
#include "Music.h"
#include "ChansonNomPos.h"
#include "Factory.h"
#include "../tools/dir_traverser/ISearchTraversable.h"
#include "../tools/dir_traverser/Search.h"
#include "../settings/Parametre.h"
#include "../tools/thread/ThreadManager.h"

extern const wxEventType wxEVT_FUX_MUSICLIST_LIST_UPDATE;

class MusicList : public ISearchTraversable
{
    public:
        MusicList();
        virtual ~MusicList();

        std::vector<Music*>& getCollection() const;

        bool empty() const;
        size_t size() const;

        void parseDirectory(wxString dirname, bool recursive);
        void clear();
        void addLines(wxArrayString *pathArray);
        virtual void addUnknownKindLine(wxString path);
        virtual void addFileLine(wxString path);
        virtual void addDirLine(wxString path);
        void importFileContent(wxString filename);

        wxString getNameAtPosition(long position);
        long getPositionInList(const wxString& filename, long position = -1);
        long getPositionInList(const Music* music);
        void removeLine(ChansonNomPos& title);
        void removeLine(size_t position);
        void removeLines(wxArrayString *filenameArray);
        void exchangeLine(wxString filename1, wxString filename2);
        //void moveLines
        void insertLines(wxArrayString *filenameArray, long position);

        void setParent(wxWindow *parent);
        wxWindow *getParent() const;
        void sendMusicListUpdatedEvent();


    protected:
        void initialize();
        void parseDirectoryRecursively(wxString dirname);
        void parseDirectoryWithoutRecurs(wxString dirname);

    private:
        std::vector<Music*> *m_musicList;
        wxWindow *m_parent;
};

#endif // MUSICLIST_H_INCLUDED
