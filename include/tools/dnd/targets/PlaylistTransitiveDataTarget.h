#ifndef PLAYLISTTRANSITIVEDATATARGET_H
#define PLAYLISTTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class PlaylistTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            PlaylistTransitiveDataTarget(DroppedMarkedLineListCtrl& source, const bool isAssociatedToPlayListCtrl);
            /** Default destructor */
            virtual ~PlaylistTransitiveDataTarget();
            virtual wxDragResult OnDragOver(wxCoord, wxCoord, wxDragResult);

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);
            virtual void doCutProcessing(TransitiveData& transitiveData, const long position);

        private:
            const bool m_isAssociatedToPlayListCtrl;
    };
}

#endif // PLAYLISTTRANSITIVEDATATARGET_H
