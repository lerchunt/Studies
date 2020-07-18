	TP1:

Rakotomanga Mary-Andréa
Lerchundi Thomas

Compilation:

Le lancement de make check à partir du répertoire compile et lance à la suite les différents exercices. Par défaut nous avons mis l'argument à 10 pour le nombre de processus à executer.
Vous pouvez cependant changer cet argument en lançant les executable un par un avec :
./[nom de l'executable] n

Remarques:

Exercice 1:

Nous avons choisi une structure de telle sorte que le processus père crée n-1 fils.

Exercice 2:

Nous créons de la même manières les processus fils, et c'est aussi le père qui crée les n tubes. Ainsi les fils peuvent utiliser les différents tubes. Nous prennont soin de fermer les tubes qui n'ont pas d'utilité pour chaque processus. La plus grande valeur se transmet alors d'un processus à l'autre jusqu'à revenir au père.

Exercice 3:

Nous reprenons le principe de l'Exercice 2. Une fois que la valeur maximale est arrivée au processus père, nous reprennons le même principe de propagation sans tirer une autre valeur aléatoire. Ainsi, l'ensemble des processus a connaissance du vainqueur.
En pratique cette solution semble fonctionner, mais nous n'avons pas la certitude que cette solution soit correcte. En effet, nous ne comprenons pas qu'il n'y ait pas de conflit au niveau des communications entre les tubes.

Exercice 4:

Le processus père crée le segment de mémoire partagée pour ensuite se l'attacher. La création des fils se fait à la suite, afin que ces derniers aient aussi accès à ce segment. Chaque processus vérifie s'il ecrit dans le segment.
Une fois que tous les processus ont fini leur execution, la zone mémoire contient la valeur maximale que l'on affiche.
Nous rencontrons une erreur au moment de la libération de la zone mémoire causée à l'appel de la fonction handle_error("shmctl",cr) pour un "argument invalide".

