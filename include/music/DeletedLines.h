#ifndef DELETEDLINES_H
#define DELETEDLINES_H

namespace music
{
    class DeletedLines
    {
        public:
            /** Default constructor */
            DeletedLines();
            /** Default constructor */
            DeletedLines(const long position, const long positionInSearch);
            /** Default destructor */
            virtual ~DeletedLines();

            void setPosition(const long position);
            void setPositionInSearch(const long position);
            long getPosition() const;
            long getPositionInSearch() const;

        private:
            long m_position;
            long m_positionInSearch;
    };

}

#endif // DELETEDLINES_H
