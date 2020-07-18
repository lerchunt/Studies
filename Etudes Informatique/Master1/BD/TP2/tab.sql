create or replace trigger Q2_1 
	after insert or delete
	on LesMaladies
	for each row
DECLARE
begin
	IF inserting then update LesAnimaux set NbMaladie= NbMaladie+1 Where NomA = :old.nomA;
	ELSIF deleting then update LesAnimaux set NbMaladie= NbMaladie -1 Where NomA= :old.nomA;
	end if;

end;
/
--:new.NomA	/* nouveau etat du tuple*/
--:old.nomM /*ancien etat du tuple*/
--show errors
