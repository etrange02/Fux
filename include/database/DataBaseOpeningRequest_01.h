#ifndef DATABASEOPENINGREQUEST_01_H
#define DATABASEOPENINGREQUEST_01_H

#include "tools/database/requests/DataBaseOpeningRequest.h"

class wxSQLite3Database;

/**
 * Name space of database tools
 */
namespace database
{
    class DataBaseOpeningRequest_01 : public tools::database::DataBaseOpeningRequest
    {
        public:
            /** Default constructor */
            DataBaseOpeningRequest_01(const wxString& filename);
            /** Default destructor */
            virtual ~DataBaseOpeningRequest_01();

        protected:
            virtual int updateTables(wxSQLite3Database& database, int currentVersion);

        private:
    };
}

#endif // DATABASEOPENINGREQUEST_01_H

/**

Le but de la base de donn�es est de conserver des informations sur des chansons :
- titre
- interpr�te(s)
- albums et/ou single
- un lien remix/reprise/live-original
- ann�e du titre
- ann�e de l'album/single
- genres

La d�finition de titre est tr�s pr�cise et doit r�pondre � : o�, quand, qui.
L'identification d'un titre sera faite � partir de MusicBrainz, qui fournit un UID.

La base a aussi vocation � poss�der une comp�tence r�seau. Lorsque plusieurs
applications se retrouvent dans le m�me r�seau local, elles �changent leurs donn�es.
Le but est de permettre par la suite de pouvoir r�cup�rer un titre sur un autre
poste � la demande de l'utilisateur.
Il faut donc stocker pour un titre :
- ses localisations
- l'h�te.
Plusieurs chemins possibles pour un titre (C:\path1, C:\path2, D:...)
Note:
Il est possible qu'il n'y ait pas de localisation pour un titre. Bien que �a puisse paraitre
�vident, j'ai un objectif d'information aupr�s de l'utilisateur. Par exemple fournir le
nom de l'artiste original d'un titre dont on ne dispose que du remix.

Priorit� � la recherche, au d�triment de l'insertion. L'insertion sera volontairement
ralenti � cause des serveurs utilis�s.

Le sch�ma actuel est tr�s fortement bas� sur celui de MusicBrainz car il r�pond � beaucoup
de mes objectifs.
J'h�site sur la pr�sence ou non de certaines informations comme le nom et le nom de sc�ne
d'un artiste ou encore la position d'un titre dans un album.
*/

