Dourov Maxime
Delime Thibault
Chennaoui Marwa
[git](https://github.com/mux99/EPHEC-OS2)[^1], [video]()[^2]
# Rapport du projet OS 2 TI
## Introduction
Lors du cours de Système d’exploitation II, nous avons dû faire un travail en groupe de 3-4 ayant pour but de gérer un championnat de formule 1.
Ce projet devait être codé en langage de programmation C.
Il a donc fallu faire attention aux différentes particularités d’une course afin d’avoir : les voitures, les grands prix, les 2 différents types de week-ends:
- Les week-ends classiques, comportant séances d'essais, séances de qualifications et la course.
- Les week-ends spéciaux, qui sont presque identiques aux week-ends classiques mais comportent en plus une course sprint le samedi après-midi.

Les temps des voitures devait être générer aléatoirement.
Il était demandé d’utiliser de la mémoire partagée comme moyen de communication interprocessus.
Ainsi que d’utiliser les sémaphores pour synchroniser l’accès à la mémoire partagée.
Le programme devait avoir suffisament d'options pour simuler nimporte quel grand prix.

## Analyse du travail
### le “chef d’orchestre”
c’est la première partie du code à s'exécuter, il est responsable de la création et de l’initialisation de la mémoire partagée (nous reviendrons sur sa structure plus tard).
Il est répartit sur deux fichiers qui font ensemble appel a tout les autres.
le premier est ```main.c``` qui s'occupe de la création et initialisation de la mémoire partagée. Ainsi que la simulation d'un grand prix après l'autre.  
Le second est ```simulation_logic.h``` qui lui orchestre la simulation d'un grand prix de bout en bout. C'est ici que sont appelé les *simulateurs* et l'*afficheur*  

### les simulateurs
c’est un groupe de fonctions systématiquement appelé en tant que processus parallèle. Leur but est de simuler les différents aspects désirés des voitures sur le circuit. Il y en a une par activitée d'un Grand Prix et elle sont toutes situdée dans ```car_sim.h```.

Leurs but est de ce comporter comme une voiture sur le circuit. Il y a donc autant d'instances de ces fonctions qu'il y a de voitures sur le circuit.

Pour ce-faire, elles lisent et écrivent sur les segments de mémoire partagée. Bien sûr l’écriture est protégée par des sémaphores dans toutes les fonctions. Pour des raisons de timings il n’a pas été nécessaire d’implémenter les sémaphores ailleurs dans les autres fichiers du code.

### l’afficheur
C’est un groupe de fonctions (avec un seul point d’entrée) également toujours appelé comme processus parallèle, se trouvant dans ```display.h```. 

Son but est d’afficher le contenu de la mémoire partagée dans la console, sous format de tableau à deux entrée facile a lire.
La difficulté est que les données complètes d’un grand prix sont présentes en mémoire. L’une des variables des grands prix permet donc au programme principal de communiquer à l'afficheur quelle étape doit être affichée sans que celui-ci ne doivent être relancé à chaque étape (seulement a chaque grand prix).
Bien que les fonctions d’affichages soit très longues, c’est uniquement dû à tous les cas de figure a prendre en compte et à l'affichage des temps en minute seconde, milliseconde. Par exemple, tant qu’une voiture n’a pas fini son premier tour, on affiche des tirets à la place de son temps.
Cette complexité atteint son paroxysme pour le récap de fin de grand prix. puisque pour les qualifs trois cas existent en fonction de quand une voiture est qualifiée. A cela s'ajoute le sprint qui n’est pas toujours joué (par simplicité, la colonne est toujours présente). Ce qui passe déjà à 6 le nombre de lignes diférantes à crée dans le tableau.


### la mémoire partagée
**Nous utilisons trois zones de mémoire partagée:**
- Une liste de structures où chacune est un grand prix.
Ils contiennent donc le nom du GP, la longueur du circuit, le type de weekend, le nombre de tours pour le sprint et la course, ainsi que le numéro de l'activité en cours.
- une liste de structures où chacune est une voiture.
Elles contiennent donc, le numéro de la voiture, les points accumulés, le nom du pilote et de son équipe. ainsi que différents flags tels que [out] et [pit].
- La dernière est une grande liste d’entiers découpée en 14 segments qui vont stocker les données brutes du grand prix. Chaque segment est aussi long qu’il y a de voitures dans la course et ils sont délimité entre eux par le simbole définit par ```end```, par défaut ```-1```.

**Voici le détail des sement de la liste d'entiers:**
1. meilleur temps pour les tours d’essais
2. meilleur temps pour les qualifs 1
3. meilleur temps pour les qualifs 2
4. meilleur temps pour les qualifs 3
5. les positions de départ de la course (exception à l'ordre des voitures)
6. temps total du sprint
7. meilleur temps du sprint
8. temps total de la course
9. meilleur temps de la course
10. points gagnés (dans ce GP uniquement)
11. nombre de tours
12. meilleur temps du secteur 1
13. meilleur temps du secteur 2
14. meilleur temps du secteur 3

**Quelques précisions:**
-L’ordre des données dans chaque segment est très important. La raison est que l’ordre des voitures dans la liste de structure doit coïncider avec l’ordre des données, pour toujours être capable de relier une voiture à ces données.
-Le meilleur temps des tours d’essais est écrasé à chaque fois, donc on ne conserve que le dernier essai.
-Les positions de départ sont particulières puisque au lieu de stocker les positions des voitures, elle stocke les voitures aux positions. C’est-à-dire que pour chaque donnée dans l’ordre de lecture on obtient le numéro de la voiture (le numéro est la position dans la liste de structure, et non celui peint sur la voiture) a cette position sur la grille de départ. Cela facilite l’affichage.
-Il est également important de noter que les segments 11 à 14 sont réutilisés à chaque étape du GP (donc remis à zéro).
-Enfin a chaque grand prix, tout le segment de donée est remis a zéro. 

### Tri des résultats sans changer l'ordre en mémoire partagée.
Pour résoudre ce problème une solution légère mais complexe a été trouvée.
En effet, il serait facile de se dire qu’il suffit de faire une copie de la mémoire partagée et de trier la copie. Sauf que cela est gourmand en mémoire et demande de trier de manière identique un grand nombre de listes différentes. Voici donc la solution adoptée.

La fonction de tri de ce projet reçoit en paramètre la référence vers une liste d’entiers (dont la fin est délimitée par ```end```).
Elle va générer un liste de substitution qui contiendra dans l’ordre voulu pour l’affichage (les plus petits en premiers) les index des voitures dans la mémoire partagée. Ce qui permet, comme toutes les données sont correctement alignées en mémoire, d’afficher n'importe quelle donnée d’une voiture, à partir de ce seul numéro d’index.
Néanmoins, cela rend très complexe les fonctions d’affichage, qui doivent utiliser des instructions très longues pour accéder aux données voulues.


## Conclusion
Sauf oubli, toutes les fonctionnalitée demandée sont présantes dans le projet.


### Difficulté d'implémentation:
-Pour la lecture des ```CSV```, l’idée initiale était de les lire dans un ```char***```, ce qui ne causait que des problèmes. une solution plus simple a été adoptée.
-Pour la liste d’entiers en mémoire partagée, le plan initial était de stocker tous les gp simultanément. ce qui était impossible puisque dépassant la taille max d’un segment de mémoire partagée (32 Mb).
-Pour permettre la sauvegarde sur fichier la solution du moindre effort a été adoptée mais elle n’est pas optimale:
La fonction d’affichage est rappelée et capturée dans un fichier. Le problème est que l’implémentation est majoritairement composée de code recyclé du projet de l'année dernière.
-l’accès aux données (```int```) en mémoire partagée est sub optimal. Actuellement tous les accès contiennent une forme ou l’autre du code suivant: ```([numéro du segment]*([nombre de voiture]+1))+I```
Bien sûr le remplacement par des variables a été tenté mais comme seul ce système semble ne pas cracher, c’est celui qui reste.

### Difficultée de groupe:
Par rapport au groupe, à part Maxime, nous n’étions pas à chaque fois présents lors des cours. Nous avons un discord pour communiquer mais la communication n’était pas bonne du tout. On aurait dû faire des réunions hebdomadaires afin de mieux se tenir à jour.
*note de max: je ne suis pas allé vers les membre de mon groupe pour les tenir informé de mon avancement*


### Évolutions futures de l’application
- Simplifier les fonctions d’affichage. Elles sont actuellement extrêmement complexes. La longueur du fichier parle pour elle même.
- De la couleur dans l’affichage, pas le temps de trouver comment on fait (la méthode de python ne marche pas).
- Corriger le seul bug connu. (très compliqué)
Avec le fonctionnement actuel de l’affichage. Dans les phase 2 et 3 des qualifs, il n’est pas possible de garantir que pendant la brève période où certains ont fini leurs premier tours et d'autres non. Certains noms dans le classement peuvent apparaître deux fois et d'autres pas du tout. Le problème se résorbe dès que toutes les voitures qui participent ont fait leurs premier tours.
Le problème vient du fait que pour ces affichage en particulier, trois jeux de "tri" sont utilisé mais seuls deux d'antre eux sont garanti sans doublons. Aucune solution simple ou élégante ne permet de corriger ce défaut.

### Conclusion personnelle
**Delime Thibault**
Si je dois retenir une leçon de ce projet c’est qu’il ne faut pas prendre de retard et toujours se tenir informé de ce qu’il se fait au sein du groupe. Car sans ça il est très difficile de revenir à la hauteur de ceux qui n’ont pas eu ce retard. J’aurais également dû demander + d’information et me rendre plus disponible.

**Dourov Maxime**
Ce projet était une exploration intéressante dans la façon dont les langages façonnent la méthode de pensée et l'approche pour résoudre les problèmes.
Tout au long de ce projet je me suis heurté aux limites de C dans mon élan pour faire *“comme je l’ai toujours fait”*. J’ai donc acquis une nouvelle perspective sur la façon d’adapter son raisonnement au langage et pas le langage au raisonnement.

**Chennaoui Marwa**
```[aux abonnés absente]```

[^1]: https://github.com/mux99/EPHEC-OS2
[^2]: