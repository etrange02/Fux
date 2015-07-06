#ifndef PLAYLISTTRANSITIVEDATATARGET_H
#define PLAYLISTTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class PlaylistTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            PlaylistTransitiveDataTarget();
            /** Default destructor */
            virtual ~PlaylistTransitiveDataTarget();
        protected:
        private:
    };
}

#endif // PLAYLISTTRANSITIVEDATATARGET_H
