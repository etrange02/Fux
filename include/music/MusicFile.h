#ifndef MUSICFILE_H
#define MUSICFILE_H


namespace music
{
    class MusicFile
    {
        public:
            virtual ~MusicFile() {}
            virtual void process() = 0;
    };
}

#endif // MUSICFILE_H
