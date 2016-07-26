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

Le but de la base de données est de conserver des informations sur des chansons :
- titre
- interprète(s)
- albums et/ou single
- un lien remix/reprise/live-original
- année du titre
- année de l'album/single
- genres

La définition de titre est très précise et doit répondre à : où, quand, qui.
L'identification d'un titre sera faite à partir de MusicBrainz, qui fournit un UID.

La base a aussi vocation à posséder une compétence réseau. Lorsque plusieurs
applications se retrouvent dans le même réseau local, elles échangent leurs données.
Le but est de permettre par la suite de pouvoir récupérer un titre sur un autre
poste à la demande de l'utilisateur.
Il faut donc stocker pour un titre :
- ses localisations
- l'hôte.
Plusieurs chemins possibles pour un titre (C:\path1, C:\path2, D:...)
Note:
Il est possible qu'il n'y ait pas de localisation pour un titre. Bien que ça puisse paraitre
évident, j'ai un objectif d'information auprès de l'utilisateur. Par exemple fournir le
nom de l'artiste original d'un titre dont on ne dispose que du remix.

Priorité à la recherche, au détriment de l'insertion. L'insertion sera volontairement
ralenti à cause des serveurs utilisés.

Le schéma actuel est très fortement basé sur celui de MusicBrainz car il répond à beaucoup
de mes objectifs.
J'hésite sur la présence ou non de certaines informations comme le nom et le nom de scène
d'un artiste ou encore la position d'un titre dans un album.
*/

