#ifndef PLAYLISTTRANSITIVEDATA_H
#define PLAYLISTTRANSITIVEDATA_H

#include "tools/dnd/sources/TransitiveData.h"
#include <memory>
#include "music/Music.h"

namespace dragAndDrop
{
    class PlaylistTransitiveData : public TransitiveData<std::shared_ptr<music::Music>>
    {
        public:
            /** Default constructor */
            PlaylistTransitiveData();
            /** Default destructor */
            virtual ~PlaylistTransitiveData();
            /** Copy constructor
             *  \param other Object to copy from
             */
            PlaylistTransitiveData(const PlaylistTransitiveData& other);
            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            PlaylistTransitiveData& operator=(const PlaylistTransitiveData& other);
        protected:
        private:
    };
}

#endif // PLAYLISTTRANSITIVEDATA_H
