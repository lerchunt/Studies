Systeme systeme(Automate *automate)
{
    /
    printf("c'est bon");
    int nb=taille_ensemble(get_etats(automate));
    int nb_lettre=taille_ensemble(get_alphabet(automate));
    
    Systeme sys = malloc(sizeof(Rationnel **)*(nb+1));
    int i,j,k;
    for(i=1;i<=nb;i++)
        sys[i]=malloc(sizeof(Rationnel *)*nb);
    printf("c'est bon");
    //le systeme a nb lignes, et nb+1 colonne
    if(nb_lettre>=0)
        if(nb!=0){
            
            Ensemble_iterateur it= premier_iterateur_ensemble(get_alphabet(automate));
            Ensemble_iterateur it_lettre= premier_iterateur_ensemble(get_etats(automate));
            Ensemble_iterateur it_general=premier_iterateur_ensemble(get_alphabet(automate));
            int nb_lettre=taille_ensemble(get_alphabet(automate));
            printf("c'est bon");
            for(i=1;i<=nb;i++){ //pour chaque etat
                for(j=1;j<=nb;j++){ //on verifie s'il y a transition vers les autres états
                    for(k=1;k<=nb_lettre;k++){ //pour chaque lettre
                        if (est_une_transition_de_l_automate(automate,get_element(it),get_element(it_lettre),get_element(it_general))==1){
                            
                            //remplir au bon endroit
                            sys[i][j]=Lettre(get_element(it_lettre)); // affectation de la lettre
                            
                            printf("c'est bon");
                            it_general= iterateur_suivant_ensemble(it_general);
                        }
                        it_lettre= iterateur_suivant_ensemble(it_lettre); // lettre suivante
                    }
                    it_general=	premier_iterateur_ensemble(get_alphabet(automate));
                    
                }
                
                if(est_un_etat_final_de_l_automate(automate,get_element(it))==1)
                    sys[i][nb+1]= Epsilon();
                it= iterateur_suivant_ensemble(it);
            }
        }
    //pour chaque état
    //pour chaque transition de cet état syst[etat_actuel][n-ième transition]=lettre puis Etat d'arrivée de la transition
    
    
    return sys;
}