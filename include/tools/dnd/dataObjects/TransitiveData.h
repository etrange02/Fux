#ifndef TRANSITIVEDATA_H
#define TRANSITIVEDATA_H

#include <wx/wx.h>

namespace dragAndDrop
{
    class TransitiveData
    {
        public:
            /** Default constructor */
            TransitiveData();
            /** Default destructor */
            virtual ~TransitiveData();

            void displayName() const;
            void setCopy(const bool copy);
            bool isCopy() const;

            virtual void doCopy() = 0;
            virtual void doCut() = 0;
            virtual const wxString getName() const = 0;

            virtual wxArrayString getFilenames() const = 0;
            virtual bool isContainerFileKind() const;
            virtual bool isPlaylistKind() const;
            virtual bool isDirKind() const;
            virtual bool isEmpty() const = 0;

        protected:
        private:
            bool m_isCopy;
    };
}

#endif // TRANSITIVEDATA_H
