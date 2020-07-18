========================================================
=====     TP Cryptographie : Reseau de Feistel     =====
====  Binome : Paul ESMIEU & Hitinui ROBERT (S4p2C)  ===
========================================================

Quelques informations :
-----------------------------
Vous pouvez compiler le programme avec la ligne de commande suivante :
g++ feistel.cc -o feistel

Les fichiers devant avoir un format particulier (composés exactement de
32 ou 64 caractères dont uniquement des 0 et des 1), nous vous fournissons 
3 ensembles de fichiers de tests.

Exemple d'utilisation :
---------------------
> cat mess1.txt
1000000000000000000000000000000000000000000000000000000000000001
> ./feistel mess1.txt cle1.txt > chiffre1.txt
1101101101100000000000000000000001101101001100000000000000000001
> ./feistel chiffre1.txt cle1.txt
1000000000000000000000000000000000000000000000000000000000000001

On retrouve bien notre message de départ.
