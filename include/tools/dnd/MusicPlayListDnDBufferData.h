#ifndef MUSICPLAYLISTDNDBUFFERDATA_H
#define MUSICPLAYLISTDNDBUFFERDATA_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/dataobj.h>
#include "DnDListeFichier.h"

class MusicPlayListDnDBufferData : public wxDataObjectSimple
{
   public:
      MusicPlayListDnDBufferData(DnDListeFichier* dndtransfile = 0);
      virtual ~MusicPlayListDnDBufferData();

      virtual size_t GetDataSize() const;
      virtual bool GetDataHere(void* buf) const;
      virtual bool SetData(size_t len, const void* buf);
      DnDListeFichier* GetTransFile();

   private:
      DnDListeFichier* m_DndNomObjet;
};

#endif // MUSICPLAYLISTDNDBUFFERDATA_H
