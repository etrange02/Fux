#ifndef DRIVEMANAGERLISTELEMENT_H
#define DRIVEMANAGERLISTELEMENT_H

#include <wx/wx.h>

class DriveManagerListElement
{
    public:
        /** Default constructor */
        DriveManagerListElement();
        /** Default destructor */
        virtual ~DriveManagerListElement();

        const wxString& getFilename() const;
        void setFilename(const wxString& filename);

    protected:
    private:
        wxString m_filename;
        /// play list ??
        /// pointer, reference
};

#endif // DRIVEMANAGERLISTELEMENT_H
