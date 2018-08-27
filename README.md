# Zappy

Le Zappy est un projet Epitech consistant au développement d'un jeu en réseau.  
Plusieurs équipes doivent s'affronter sur un terrain contenant des ressources.
L'équipe gagnante est celle avec au moins 6 joueurs qui ont atteint le niveau maximal.  
Ce sont des I.A qui composent les équipes et incarnent les joueurs.

* **Le serveur** a entièrement été développé en C avec les librairies du système Linux.  
* **Les I.A** ont été développées avec Python 3.  
* **Le client graphique** a été créé avec Unity et est compatible sur Windows, Linux et MacOs

## Utilisation

### Lacement du serveur

Après avoir cloné le projet, exécutez la commande ```make``` pour installer le serveur.

Une fois installé, lancez le serveur avec la commande:

```
./zappy_server -p [PORT] -x [WIDTH] -y [HEIGHT] -n [TEAMS] -c [NB_CLIENTS] -f [FREQ]
```

* [PORT]: Port de connexion vers le serveur.

* [WIDTH]: Largeur du terrain.

* [HEIGHT]: Hauteur du terrain.

* [TEAMS]: Noms des différentes équipes qui pourront s'affronter (séparés par des espaces).

* [NB_CLIENTS]: Nombre de joueurs max par équipe.

* [FREQ]: Réciproque du temps pour l'exécution d'actions.

### Lancement de l'I.A

Pour lancer l'I.A, exécutez la commande suivante:

```
./zappy_ai -p [PORT] -n [TEAM] -h [HOST]
```

* [PORT]: Port de connexion vers le serveur.

* [TEAM]: Nom de l'équipe du joueur.

* [HOST]: Adresse du serveur sur lequel se connecter.

### Lancement du client graphique

Pour lancer le client graphique, il faut exécuter le programme correspondant à votre système d'exploitation:

* Linux: ```./ZappyLinux/ZappyLinux.x86_64```
* Windows: vous devez dézziper le fichier **ZappyWindows.zip**, ensuite vous pourrez exécuter: ```./ZappyWIndows/ZappyWIndows.exe```
* MacOs: vous devez dézziper le fichier **ZappyMac.app.zip**, ensuite vous pourrez exécuter: ```./ZappyMac.app```

## Trailer
[![Regarder le trailer](https://img.youtube.com/vi/1ZO8L_PyjQo/0.jpg)](https://www.youtube.com/watch?v=1ZO8L_PyjQo)

## Auteurs

* [Lucas Le Ray](https://github.com/LucasLeRay)
* Roméo Nahon
* Nicolas Laurent
* Nathan Douillet
* Eliott Legal
* Mathieu Rabissoni
