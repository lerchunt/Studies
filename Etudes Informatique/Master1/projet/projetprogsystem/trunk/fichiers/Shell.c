/* Construction des arbres représentant des commandes */

#include "Shell.h"

//#include <argz.h>
//#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netinet/in.h>
//#include <assert.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
/*
 * Construit une expression à partir de sous-expressions
 */

Expression *ConstruireNoeud (expr_t type, Expression *g, Expression *d, char **args)
{
  Expression *e;
     
  if ((e = (Expression *)malloc(sizeof(Expression))) == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  e->type   = type;
  e->gauche = g;
  e->droite = d;
  e->arguments = args;
  return e;
} /* ConstruireNoeud */



/*
 * Renvoie la longueur d'une liste d'arguments
 */
int LongueurListe(char **l)
{
  char **p;
  for (p=l; *p != NULL; p++)
    ;
  return p-l;
} /* LongueurListe */



/*
 * Renvoie une liste d'arguments, la première case étant initialisée à NULL, la
 * liste pouvant contenir NB_ARGS arguments (plus le pointeur NULL de fin de
 * liste)
 */
char **InitialiserListeArguments (void)
{
  char **l;
  
  l = (char **) (calloc (NB_ARGS+1, sizeof (char *)));
  *l = NULL;
  return l;
} /* InitialiserListeArguments */



/*
 * Ajoute en fin de liste le nouvel argument et renvoie la liste résultante
 */
char **AjouterArg (char **Liste, char *Arg)
{
  char **l;
  
  l = Liste + LongueurListe (Liste);
  *l = (char *) (malloc (1+strlen (Arg)));
  strcpy (*l++, Arg);
  *l = NULL;
  return Liste;
} /* AjouterArg */



/*
 * Fonction appelée lorsque l'utilisateur tape "".
 */
void EndOfFile (void)
{
  exit (0);
} /* EndOfFile */

/*
 * Appelée par yyparse() sur erreur syntaxique
 */
void yyerror (char *s)
{
   fprintf(stderr, "%s\n", s);
}

/*
*fonction executant une commande simple
*/
int commandeSimple(char **command){
  pid_t pid=fork();
  int status;
  int a;
 
  if(pid==0)
          a=execvp(command[0],command);
  else
    wait(&status);
  if(WEXITSTATUS(a)== -1)
    printf("some error is occured in that shell command");
  if (WEXITSTATUS(status) == 127)
    printf("That shell command is not found\n");
  printf("Code de retour : %d \n", WEXITSTATUS(status));
  return WEXITSTATUS(status);


}
int ret=-2;//variable globale pour les fonctions sequences
/*
*fonction executant une commande sequence
*/

void commandSequence(Expression *e){
	if(e->type==SIMPLE)
		commandeSimple(e->arguments);
	if(e->gauche!=NULL)
		commandSequence(e->gauche);
	if(e->droite!=NULL)
		commandSequence(e->droite);
}
/*
*fonction executant une commande sequence_ET
commande2 s'exécute ssi le code de sortie de commande1 vaut 0. De même commande3 s'exécute ssi le code de sortie de commande2 vaut 0
*/
void  commandSequence_ET(Expression *e,Expression* filsGauche,Expression *filsDroit){
  if(e->type==SIMPLE){
    if(e==filsGauche)
      ret=commandeSimple(e->arguments);
    else
      if(ret==0)
        ret=commandeSimple(e->arguments);    
  }
  if(e->gauche!=NULL){
    filsGauche=e->gauche;
    commandSequence_ET(e->gauche,filsGauche,filsDroit);
  }
  if(e->droite!=NULL){
    printf("droit\n");//ce printf est necessaire sinon le programme change donc à revoir
    filsDroit=e->droite;
    commandSequence_ET(e->droite,filsGauche,filsDroit);
      
  }
  
  
}
/*
commande exécutant une sequence ou
**  commande2 s'exécute ssi le code de sortie de commande1 est diffèrent de 0. De même commande3 s'exécute ssi le code de sortie de commande2 est diffèrent de 0. 
 */
void  commandSequence_OU(Expression *e,Expression* filsGauche,Expression *filsDroit){
  if(e->type==SIMPLE){
    if(e==filsGauche)
      ret=commandeSimple(e->arguments); 
    else
      if(ret!=0)
        ret=commandeSimple(e->arguments);     
  }
  if(e->gauche!=NULL){
    filsGauche=e->gauche;
    commandSequence_OU(e->gauche,filsGauche,filsDroit);
  }
  if(e->droite!=NULL){
      filsDroit=e->droite;
      commandSequence_OU(e->droite,filsGauche,filsDroit);
    }

}

void commandRedirEntree(Expression *e){
  int fd=open(e->arguments[0],O_RDONLY,0666);
  printf("e->arguments[0]=%s\n",e->arguments[0]);
  pid_t pid=fork();
  if(pid==0){
    dup2(fd,0);
    execvp(e->gauche->arguments[0],e->gauche->arguments);
    close(fd);
  }
  else{
    close(fd);
    wait(0);
  }
}

void commandPipe(Expression *e){
  if (e->gauche->type==PIPE){
    commandPipe(e->gauche);
  }
  int fd[2];
  pipe(fd);
  pid_t pid=fork();
  if (pid==0){
    dup2(fd[1],1);
    close(fd[0]);
    execvp(e->gauche->arguments[0],e->gauche->arguments);
    close(fd[1]);
  }else{
    if (e->droite->type==PIPE){
      commandPipe(e->droite);
    }
    pid_t pid2=fork();
    if(pid2==0){
      dup2(fd[0],0);
      close(fd[1]);
      execvp(e->droite->arguments[0],e->droite->arguments);
      close(fd[0]);
    }
  } 
  close(fd[1]);
  close(fd[0]);
  wait(0);
  wait(0);
}
void signal_callback_handler(int signum){
    
    printf("Caught signal SIGPIPE %d\n",signum);
}
void commandRedirection_O(Expression * e){
    printf("redirection sortie dans fichier \n");
    
    int fd[2];
    pipe(fd);
    signal(SIGPIPE, signal_callback_handler);
    
    pid_t pid= fork();
    if (pid==0){
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);
        
        execvp(e->gauche->arguments[0],e->gauche->arguments);
        
    }
    else{
        
        FILE * file= fopen(e->arguments[0],"w+" );
        char c;
        close(fd[1]);
        FILE * p= fdopen(fd[0],"r"); // convertit un fd en FILE * pour qu'il soit lu par fread
        while(fread(&c, sizeof(char),1,p)){
            fwrite(&c,sizeof(char),1, file);
        }
        close(fd[0]);
        fclose(file);
        fclose(p);
        wait(0);
    }
    
}
void commandRedirection_A(Expression * e){
    printf("redirection sortie dans fichier \n");
    
    int fd[2];
    pipe(fd);
    signal(SIGPIPE, signal_callback_handler);
    
    pid_t pid= fork();
    if (pid==0){
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);
        
        execvp(e->gauche->arguments[0],e->gauche->arguments);
        
    }
    else{
        
        FILE * file= fopen(e->arguments[0],"a" );
        char c;
        close(fd[1]);
        FILE * p= fdopen(fd[0],"r"); // convertit un fd en FILE * pour qu'il soit lu par fread
        while(fread(&c, sizeof(char),1,p)){
            fwrite(&c,sizeof(char),1, file);
        }
        close(fd[0]);
        fclose(file);
        fclose(p);
        wait(0);
    }
    
}
void commandRedirection_E(Expression * e){
    printf("redirection sortie dans fichier \n");
    
    int fd[2];
    pipe(fd);
    signal(SIGPIPE, signal_callback_handler);
    
    pid_t pid= fork();
    if (pid==0){
        dup2(fd[1],2);
        close(fd[0]);
        close(fd[1]);
        
        execvp(e->gauche->arguments[0],e->gauche->arguments);
        
    }
    else{
        
        FILE * file= fopen(e->arguments[0],"a" );
        char c;
        close(fd[1]);
        FILE * p= fdopen(fd[0],"r"); // convertit un fd en FILE * pour qu'il soit lu par fread
        while(fread(&c, sizeof(char),1,p)){
            fwrite(&c,sizeof(char),1, file);
        }
        close(fd[0]);
        fclose(file);
        fclose(p);
        wait(0);
    }
    
}

void
expression_free(Expression *e)
{
  if (e == NULL)
    return;
    
  expression_free(e->gauche);
  expression_free(e->droite);

  if (e->arguments != NULL)
    {
      for (int i = 0; e->arguments[i] != NULL; i++)
	free(e->arguments[i]);
      free(e->arguments);  
    }
  free(e);
}
/*
    Commande interne echo
    Ecrit sur la sortie standard son premier argument
 */
void cmd_echo(Expression *e)
{
    int w;
    w = write(STDOUT_FILENO,e->arguments[1],10);
}

/*
 commande interne exec
 Execute la commande passŽe en argument de exec (sans changer de PID)
 */
void cmd_exec(Expression *e){
            execlp("/bin/bash","bash","-c",e->arguments[1],0);
}
void cmd_exit(Expression *e){
    if(strcmp(e->arguments[0], "exit") == 0)
    exit(EXIT_SUCCESS);
}
void cmd_kill(Expression *e){
    if(strcmp(e->arguments[1], "-l") == 0){
        char cmd="cat /usr/include/sys/signal.h"
        execlp("/usr/include/sys/signal.h.");
        /*  afficher l'ensemble des signaux disponible dans la machine.
            Dispo dans /usr/include/sys/signal.h*/
    }
    else if(strcmp(e->arguments[1], "0") == 0)
        kill(getpid(),SIGTERM)
        /* */
    else if(strcmp(e->arguments[1], "-1") == 0)
    else
        kill(e->arguments[1],SIGTERM);
}
int
main (int argc, char **argv,char **envp) 
{
  while (1){
   	printf("%s >",envp[24]);  //envp[13]);
    
    if (yyparse () == 0) {
	
      /*--------------------------------------------------------------------------------------.
      | L'analyse de la ligne de commande est effectuée sans erreur.  La variable globale     |
      |       ExpressionAnalysee pointe sur un arbre représentant l'expression.  Le type      |
      |       "Expression" de l'arbre est décrit dans le fichier Shell.h. Il contient 4       |
      |       champs. Si e est du type Expression :					      |
      | 										      |
      | - e.type est un type d'expression, contenant une valeur définie par énumération dans  |

      |   Shell.h. Cette valeur peut être :					      	      |
      | 										      |
      |   - VIDE, commande vide								      |
      |   - SIMPLE, commande simple et ses arguments					      |
      |   - SEQUENCE, séquence (;) d'instructions					      |
      |   - SEQUENCE_ET, séquence conditionnelle (&&) d'instructions			      |
      |   - SEQUENCE_OU, séquence conditionnelle (||) d'instructions			      |
      |   - BG, tâche en arrière plan (&)						      |
      |   - PIPE, pipe (|).								      |
      |   - REDIRECTION_I, redirection de l'entrée (<)					      |
      |   - REDIRECTION_O, redirection de la sortie (>)					      |
      |   - REDIRECTION_A, redirection de la sortie en mode APPEND (>>).		      |
      |   - REDIRECTION_E, redirection de la sortie erreur,  	   			      |
      |   - REDIRECTION_EO, redirection des sorties erreur et standard.			      |
      | 										      |
      | - e.gauche et e.droite, de type Expression *, représentent une sous-expression gauche |
      |       et une sous-expression droite. Ces deux champs ne sont pas utilisés pour les    |
      |       types VIDE et SIMPLE. Pour les expressions réclamant deux sous-expressions      |
      |       (SEQUENCE, SEQUENCE_ET, SEQUENCE_OU, et PIPE) ces deux champs sont utilisés     |
      |       simultannément.  Pour les autres champs, seule l'expression gauche est	      |
      |       utilisée.									      |
      | 										      |
      | - e.arguments, de type char **, a deux interpretations :			      |
      | 										      |
      |      - si le type de la commande est simple, e.arguments pointe sur un tableau à la   |
      |       argv. (e.arguments)[0] est le nom de la commande, (e.arguments)[1] est le	      |
      |       premier argument, etc.							      |
      | 										      |
      |      - si le type de la commande est une redirection, (e.arguments)[0] est le nom du  |
      |       fichier vers lequel on redirige.						      |
      `--------------------------------------------------------------------------------------*/
      
      Expression *e =ExpressionAnalysee;
    
      switch(e->type){
      case(SIMPLE):

             // commandeSimple(e->arguments);
           //   else
                //  cmd_echo(e);
              
              cmd_kill(e);
              
	break;
      case(SEQUENCE):
	commandSequence(e);
	break;
      case(PIPE):
	commandPipe(e);
	break;
      case(SEQUENCE_ET):
	commandSequence_ET(e,e->gauche,e->droite);
	break;
      case(SEQUENCE_OU):
	commandSequence_OU(e,e->gauche,e->droite);
	break;
      case(REDIRECTION_I):
	commandRedirEntree(e);
	break;
      case(REDIRECTION_O):
    commandRedirection_O(e);
    break;
      case(REDIRECTION_A):
    commandRedirection_A(e);
    break;
      case(REDIRECTION_E):
    commandRedirection_E(e);
    break;
    
      }/*
      if(e->type == SIMPLE){ 
	commandeSimple(e->arguments);
	}
      if (e->type ==SEQUENCE){
	commandSequence(e);}

      if(e->type== SEQUENCE_ET){}
      if(e->type== SEQUENCE_OU){}
      if(e->type == BG){}							
      if(e->type == PIPE){
	commandPipe(e);
      }
      if(e->type == REDIRECTION_I){}
      if(e->type == REDIRECTION_O){}
      if(e->type == REDIRECTION_A){}
      if(e->type == REDIRECTION_E){}
      if(e->type == REDIRECTION_EO){}
       */


      fprintf (stderr,"Expression syntaxiquement correcte : ");
      fprintf (stderr,"[%s]\n", previous_command_line());
        if (e->type == SIMPLE)
        {
            printf("il s'agit d'une commande simple dont voici les arguments :\n");
            for(int i=0; e->arguments[i] != NULL;i++)
                printf("[%s]",e->arguments[i]);
            putchar('\n');
        }
        expression_free(e);
    }
    else {
      /* L'analyse de la ligne de commande a donné une erreur */
      fprintf (stderr,"Expression syntaxiquement incorrecte !\n");
      reset_command_line();
    }
  }
  return 0;
}
