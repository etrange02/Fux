#ifndef EXPLORERFACTORY_H
#define EXPLORERFACTORY_H


/**
 * Explorer name space.
 */
namespace explorer
{
    class ExplorerManagerData;
    class DriveManagerState;
    class DefaultDriveManagerState;
    class DirDriveManagerState;
    class FileDriveManagerState;
    class PlaylistDriveManagerState;

    class ExplorerFactory
    {
        public:
            static DriveManagerState* createDefaultDriveManagerState (ExplorerManagerData& data, const bool initDragAndDrop);
            static DriveManagerState* createDirDriveManagerState     (ExplorerManagerData& data);
            static DriveManagerState* createFileDriveManagerState    (ExplorerManagerData& data);
            static DriveManagerState* createPlaylistDriveManagerState(ExplorerManagerData& data);

        protected:
        private:
            /** Default constructor */
            ExplorerFactory();
            /** Default destructor */
            virtual ~ExplorerFactory();
    };
}

#endif // EXPLORERFACTORY_H
