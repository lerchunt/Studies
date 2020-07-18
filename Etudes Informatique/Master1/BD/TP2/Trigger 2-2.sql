create or replace trigger Q2_2
before insert or update of noCage on LesAnimaux
for each row
Declare
fct varchar(20);
begin
	select fonction into fct from LesCages where nocage = :new.nocage;
	if fct != :new.fonction_cage then raise_application_error(-20001, 'cage incompatible');
	end if;
end;
