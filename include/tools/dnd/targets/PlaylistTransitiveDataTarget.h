#ifndef PLAYLISTTRANSITIVEDATATARGET_H
#define PLAYLISTTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class PlaylistTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            PlaylistTransitiveDataTarget(const wxListCtrl& source);
            /** Default destructor */
            virtual ~PlaylistTransitiveDataTarget();

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);

        private:
    };
}

#endif // PLAYLISTTRANSITIVEDATATARGET_H
