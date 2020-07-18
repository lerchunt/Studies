Precisions et Rappels pour la configuration Java 
------------------------------------------------

Le SGBD Oracle est installe sur le serveur im2ag-oracle.
Pour contourner certains problemes de reseau (configuration/filtrage),
le code java de ce TP devra etre compile et execute sur le meme serveur
que le SGBD (im2ag-oracle).

===============================================================================

Rappels sur la compilation et le lancement d'un programme Java

Dans ce TP, vous allez manipuler deux fichiers source Java :
LectureClavier.java (a utiliser tel quel) et Banque.java (a completer).

En compilant ces fichiers, vous allez creer deux fichiers 
(LectureClavier.class et Banque.class) dans le repertoire cible
(par defaut, ce repertoire correspond au repertoire courant).

Dans la suite, on supposera que les fichiers .java, .class et .jar sont stockes
dans le repertoire courant. 

1) Compiler LectureClavier.java :
javac LectureClavier.java
=> le fichier LectureClavier.class est cree dans le repertoire courant.
Si vous ne modifiez pas ce fichier, il n'est pas necessaire de le recompiler
a chaque fois.

2) Compiler Banque.java
La compilation de ce fichier necessite le fichier LectureClavier.class et
le pilote JDBC d'Oracle (contenu dans le fichier archive ojdbc6.jar,
a placer dans le repertoire cible).
Donc il faut soit configurer le(s) chemin(s) necessaire(s) via la variable
d'environnement CLASSPATH (voir ci-dessous), soit passer ces informations en
parametre de la commande de compilation avec l'option -classpath :

javac -classpath .:./ojdbc6.jar Banque.java

3) Lancer le programme
La classe qui contient le programme principal (main) est Banque.
Ici aussi, il faut preciser a la machine virtuelle Java ou sont les fichiers
.class et l'archive jar. On peut faire cela soit via la variable
d'environnement CLASSPATH (voir ci-dessous), soit passer ces informations via
l'option -cp :

java -cp .:./ojdbc6.jar Banque

===============================================================================

Modifier la variable d'environnement CLASSPATH :

1) Affichez le contenu de votre variable CLASSPATH avec la commande :
echo $CLASSPATH
S'il contient deja tous les chemins necessaires, passez a l'etape 5.

2) Verifiez le nom de votre shell en utilisant la commande :
echo $SHELL

3) Si votre shell est tcsh, utilisez la commande suivante pour ajouter les
chemins et jar necessaires a votre CLASSPATH :
setenv CLASSPATH $CLASSPATH:.:./ojdbc6.jar

Si votre shell est bash, utilisez la commande suivante pour ajouter les
chemins et jar necessaires a votre CLASSPATH :
export CLASSPATH=$CLASSPATH:.:./ojdbc6.jar

4) Verifiez que vos modifications ont bien ete prises en comptes.
Pour cela, affichez a nouveau le contenu du CLASSPATH :
echo $CLASSPATH

5) lancer ensuite les commandes dans le MEME shell :
javac LectureClavier.java
javac Banque.java
java Banque

===============================================================================

Variante 

On reprend l'exemple precedent mais dans ce cas, on souhaite
placer les fichiers .class et .jar dans le repertoire /home/toto/bin et utiliser
la variable d'environnement CLASSPATH.

Les commandes ci-dessous sont lancees a partir du repertoire /home/toto
(dans lequel sont stockes les fichiers LectureClavier.java et Banque.java) :

1) Si necessaire, mettre a jour le CLASSPATH pour qu'il contienne
le repertoire cible et l'archive jar.
Par exemple sous tcsh :
setenv CLASSPATH ${CLASSPATH}:/home/toto/bin:/home/toto/ojdbc14.jar

2) Compiler les fichiers :
L'option -d precise le repertoire cible :
javac -d /home/toto/bin LectureClavier.java
javac -d /home/toto/bin Banque.java

3) Lancer le programme :
java Banque
