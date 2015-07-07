# IRC
Server and client IRC

RFC 1459 Compliant

Commandes client :

/server _host_[:_port_] : se connecte à un serveur

/nick _nickname_ : définit le surnom de l’utilisateur au sein du channel

/list [string] : liste les channels disponibles sur le serveur. N’affiche que les
channels contenant la chaîne "string" si celle-ci est spécifiée.

/join _channel_ : rejoint un channel sur le serveur

/part _channel_ : quitte le channel

/users : liste les utilisateurs connectés au channel (liste des nicknames bien
entendu)

_message_ : envoie un message à tous les utilisateurs connectés au channel.

/msg _nickname_ _message_ : envoie un message à un utilisateur spécifique

/send_file _nickname_ _file_ : envoie un fichier à un utilisateur.

/accept_file _nickname_ : accepte la réception d’un fichier en provenance
d’un utilisateur du channel.
