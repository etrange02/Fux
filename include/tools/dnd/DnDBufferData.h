#ifndef DNDBUFFERDATA_H
#define DNDBUFFERDATA_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/dataobj.h>
#include "DnDListeFichier.h"

class DnDBufferData : public wxDataObjectSimple
{
   public:
      DnDBufferData(DnDListeFichier* dndtransfile = 0);
      virtual ~DnDBufferData();

      virtual size_t GetDataSize() const;
      virtual bool GetDataHere(void* buf) const;
      virtual bool SetData(size_t len, const void* buf);
      DnDListeFichier* GetTransFile();

   private:
      DnDListeFichier* m_DndNomObjet;
};

#endif // DNDBUFFERDATA_H
