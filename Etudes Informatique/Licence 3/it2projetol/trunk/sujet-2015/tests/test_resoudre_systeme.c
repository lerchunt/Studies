#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_resoudre_systeme(){
  int result = 1;
  
  int n = 4;
  Rationnel *** systeme = malloc((n+1)*sizeof(Rationnel **));
  for (int i=0;i<=n;i++)
    systeme[i] = malloc(n*sizeof(Rationnel *));
  
  systeme[0][1] = Lettre('a');
  systeme[0][3] = Lettre('b');
  systeme[1][2] = Lettre('b');
  systeme[1][3] = Lettre('a');
  systeme[2][2] = Union(Lettre('a'),Lettre('b'));
  systeme[2][4] = Epsilon();
  systeme[3][3] = Lettre('a');
  systeme[3][4] = Epsilon();

  print_systeme(systeme,n);

  printf("Tentative de résolution du système...\n");
  Systeme sys = resoudre_systeme(systeme,n);
  
  print_systeme(sys,n);
  
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_resoudre_systeme() )
    return 1; 
   
  return 0;
}
