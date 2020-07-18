#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_systeme(){
  int result = 1;
  
   Rationnel * rat;
   rat = expression_to_rationnel("(a.b)*.a");
   numeroter_rationnel(rat);
   Automate * automate = Glushkov(rat);
   
   print_automate(automate);

   Systeme sys = systeme(automate);

   printf("\n");
   print_systeme(sys,taille_ensemble(automate->etats));
   printf("\n");
  
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_systeme() )
    return 1; 
   
  return 0;
}
