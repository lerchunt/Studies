1) Création de la table

Select * from Comptes;

create table Comptes(NC integer,Nom varchar2(10),	Solde number,constraint SoldePositif check (solde>=0) deferrable);

EXERCICE 1

1.

insert into Comptes values (1, 'Paul', 1000);
insert into Comptes values (2, 'Paul', 3);

3.
rollback;

La table ne contient plus rien


EXERCICE 2

insert into Comptes values (1, 'Pierre', 1500);
insert into Comptes values (2, 'Pierre', 30);

commit;

Ce qui a été commit reste dans la base après le rollback


Exercice 4


SQL> insert into Comptes values (3,'Paul',300);

savepoint UnInsert;


insert into Comptes values (4, 'Paul', 4333);

rollback to UnInsert;

Enlève la derniere Paul;

Rollback enleve le dernier Paul


PARTIE 2

insert into Comptes values (3, 'Claude', 100);
insert into Comptes values (4, 'Henri', 200);


set constraint SoldePositif IMMEDIATE;

Update Comptes set Comptes.Solde=Solde+50 where Comptes.Nom='Henri';
Update Comptes set Comptes.Solde=Solde-150 where Comptes.Nom='Claude';

->check constraint (LERCHUNT.SOLDEPOSITIF) violated
Henri remis à 100

Delete From Comptes Where Nom in ('Claude','Henri');

Differé : passe au moment de l update

annulation remet Henri et claude à leurs valeurs initiales
Validation:
	SQL> commit;
	commit
	*
	ERROR at line 1:
	ORA-02091: transaction rolled back
	ORA-02290: check constraint (LERCHUNT.SOLDEPOSITIF) violated


Partie 3
Exercice 1
Update Comptes set Comptes.Solde=Solde+1000 where Comptes.NC='2';

Delete From Comptes Where Nom in ('Pierre');

S2 : Update Comptes set Comptes.Nom='Pierre';

Blocage!

Commit de S1 débloque S2;
Dans S2 :
SQL> Update Comptes set Comptes.Nom='Pierre';

	2 rows updated.

	SQL> Select * from Comptes;

        NC NOM             SOLDE
	---------- ---------- ----------
         3 Pierre            100
         4 Pierre            200

commit de S2

Dans S1:

	SQL> select * from Comptes;

		   NC NOM             SOLDE
	---------- ---------- ----------
		    3 Pierre            100
		    4 Pierre            200
On voit les modification apportée dans S2 dans S1.

	

***********EXERCICE 4*******************:


Création du Deadlock:

Etat initial de la table:
        NC NOM             SOLDE
---------- ---------- ----------
         3 Pierre            100
         4 Pierre            200

T1:SQL> update Comptes set Nom = 'thomas' where solde =100;
T2:SQL> update Comptes set Nom = 'lucas' where solde =200;
T1:SQL> Update Comptes set Nom='Renaud' where solde=200;
(T1 attend que T2 ait fini)
T2:SQL> update Comptes set Nom='Jaki' where solde=100;
T2 attend que T1 ait fini.

Voici l'affichage de oracle qui arrive dans le terminal de T1:
ERROR at line 1:
ORA-00060: deadlock detected while waiting for resource

