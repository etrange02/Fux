#ifndef MUSICLIST_H_INCLUDED
#define MUSICLIST_H_INCLUDED

#include <wx/wx.h>
#include <vector>

#include <wx/dir.h>

#include "Define.h"
#include "Music.h"
#include "Factory.h"
#include "tools/dir_traverser/ISearchTraversable.h"
#include "tools/dir_traverser/Search.h"
#include "settings/Parametre.h"

extern const wxEventType wxEVT_FUX_MUSICLIST_LIST_UPDATE;
extern const wxEventType wxEVT_FUX_MUSICLIST_LIST_LINE_DELETED;

namespace music
{
    class MusicList : public ISearchTraversable
    {
        public:
            MusicList();
            virtual ~MusicList();

            std::vector<Music*>& getCollection() const;

            bool empty() const;
            size_t size() const;

            void parseDirectory(const wxString& dirname, bool recursive);
            void clear();
            void addLines(const wxArrayString& pathArray);
            virtual void addUnknownKindLine(const wxString& path);
            virtual void addFileLine(const wxString& path);
            virtual void addDirLine(const wxString& path);
            void importFileContent(const wxString& filename);

            wxString getNameAtPosition(long position);
            long getPositionInList(const wxString& filename, long position = -1);
            long getPositionInList(const IMusic* music);
            void removeLine(size_t position);
            void removeLines(wxArrayString& filenameArray);
            void exchangeLine(const wxString& filename1, const wxString& filename2);
            //void moveLines
            void insertLines(const wxArrayString& filenameArray, long position);

            void setParent(wxWindow *parent);
            wxWindow *getParent() const;
            void sendMusicListUpdatedEvent();

            bool isSendEventWhenAdding() const;
            void setSendEventWhenAdding(bool send);


        protected:
            void initialize();
            void parseDirectoryRecursively(const wxString& dirname);
            void parseDirectoryWithoutRecurs(const wxString& dirname);

            void sendMusicListLineDeleted(const int position);

        private:
            std::vector<Music*> *m_musicList;
            wxWindow *m_parent;
            bool m_sendEventWhenAdding;
    };
}

#endif // MUSICLIST_H_INCLUDED
