create or replace trigger Q2_3
before insert or update  of noCage on LesAnimaux
for each row
declare
nb_grd number(3)
begin
	select count(*) noCage into nb_grd from LesGardiens where noCage = :new.nocage;
	if(nb_grd =0) then raise_application_error(-20001, 'Il n y a pas de gardien a cette cage');
	end if;
end;
