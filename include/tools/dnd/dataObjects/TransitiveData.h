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

            void doPaste();
            virtual bool isSameKind() const = 0;
            virtual void doCopy() = 0;
            virtual void doCut() = 0;
            virtual const wxString getName() const = 0;

        protected:
        private:
    };
}

#endif // TRANSITIVEDATA_H
