#ifndef MUSICMANAGERSEARCHDECORATOR_H
#define MUSICMANAGERSEARCHDECORATOR_H

#include "AbstractMusicManagerDecorator.h"
#include "MusicManager.h"

namespace music
{
    class MusicManagerSearchDecorator : public AbstractMusicManagerDecorator
    {
        public:
            /** Default constructor */
            MusicManagerSearchDecorator(MusicManager& musicManager);
            /** Default destructor */
            virtual ~MusicManagerSearchDecorator();

            virtual MusicCollection& getMusics();
            virtual size_t getCurrentMusicPosition();
            virtual void moveIntTitlesAt(const wxArrayString& titles, size_t position);
            virtual void moveTitlesAt(const MusicCollection& titles, size_t position);
            virtual void placeStringTitlesAt(const wxArrayString& titles, size_t position);
            virtual void deleteTitleAt(size_t position);
            virtual void deleteTitleAt(const std::vector<unsigned long>& positions);
            virtual bool playMusicAt(long position);
            virtual void updateMusicContent(const size_t position, Music* music);
            virtual int  getDeletedLine(DeletedLines& deletedLines);
            virtual void convertPositionsToTransitiveData(const std::vector<unsigned long>& positions, dragAndDrop::PlaylistTransitiveData& transitiveData);
    };
}

#endif // MUSICMANAGERSEARCHDECORATOR_H
