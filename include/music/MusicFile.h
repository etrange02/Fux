#ifndef MUSICFILE_H
#define MUSICFILE_H


class MusicFile
{
    public:
        /** Default constructor */
        MusicFile();
        /** Default destructor */
        virtual ~MusicFile();

        virtual void process() = 0;
};

#endif // MUSICFILE_H
