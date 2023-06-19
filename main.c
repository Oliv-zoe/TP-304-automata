#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define m 50


int nbre_caracteres, nbre_automates;
// Automate ={sigma,etats,etat_initiale,etats_Finaux,transitions}
//Des transitions
typedef struct transition{
    char etiquette;
    int destination[m];
    int nbr_transition;
}transition;
//Des etats
typedef struct etat{
    int numero;
    transition transition[m];
}etat;
//L'Automate
typedef struct Automate{
    char sigma[m];
    int etat_initiale;
    int nbr_etat;
    etat etats[m];
    int nbr_ef;
    int finale[m];
}Automate;

Automate*creation_automate()
{
    Automate*a=(Automate*)malloc(sizeof(Automate));
    a->etat_initiale=-1;
    a->nbr_etat=-1;
    a->nbr_ef=-1;
    return (a);
}

void construct_automate(Automate*a)
{
    int i,j;
    char c;
    printf("( Nombre De Symbole De L'alphabet) = ");
    scanf("%d",&nbre_caracteres);
    c = getchar();
    printf("\n");
    printf("[Entrer Les Symboles De Sigma] \n");
        for(i=0; i<nbre_caracteres; i++){
        printf("Sigma[%d] =",i+1);
        scanf("%c",&a->sigma[i]);
        c=getchar();

    }

    printf("\n");
    printf("(Nombre etat) = ");
    scanf("%d",&a->nbr_etat);
    printf("\n");
    for(i=0; i<a->nbr_etat; i++)
    {
        a->etats[i].numero=i;
    }
    printf("(etat initiale) = ");
    scanf("%d",&a->etat_initiale);
    printf("\n");
    printf("(Nombre etats finaux) = ");

    scanf("%d",&a->nbr_ef);
    printf("\n");

    for(i=0; i<a->nbr_ef; i++)
    {
        printf("finale(%d) =",i+1);
        scanf("%d",&a->finale[i]);
        c=getchar();
    }
     printf("\n");
printf("(----------------------Les Transitions -----------------)");
printf("\n");
int k;
 for(i = 0; i < a->nbr_etat; i++)
 {
  for(j=0;j<nbre_caracteres;j++)
  {
     printf("(etat[%d])\n",a->etats[i].numero);
   printf("[Entrer Le nombre De Transition pour le symbole %c]=",a->sigma[j]);
   scanf("%d",&a->etats[i].transition[j].nbr_transition);
         c=getchar();
   if(a->etats[i].transition[j].nbr_transition>0){
    for(k = 0; k<a->etats[i].transition[j].nbr_transition; k++)
  {

   printf("T[%d,%c]=",a->etats[i].numero,a->sigma[j]);
   scanf("%d",&a->etats[i].transition[j].destination[k]);
         c=getchar();


  }
  }
  else
    a->etats[i].transition[j].destination[0]=-100;
  }
 }
}


// ***********************Fonction definition des automates*******************//


 Automate**definition_automates(){

    Automate**tab_automates = malloc(m * sizeof(Automate*));
    int i;
    printf("\n");
    printf("Avec combien d'automates voulez-vous travailler ? ");
    scanf("%d", &nbre_automates);
    for(i=0; i<nbre_automates; i++){
        tab_automates[i]=creation_automate();
        printf("NB : Les etats sont numerotes a partir de 0\n");
        printf("Construction de l'automate %d :", i+1);
        printf("\n\t");
        construct_automate(tab_automates[i]);
    }

    return(tab_automates);
}


int est_finale(Automate*a,int v)
{
int i;
int finale=0;
for(i=0;i<a->nbr_ef;i++)
{
    if(a->finale[i]==v)
        finale=1;
}
return (finale);
}
void reconnaissance_mots(Automate*a,char mots[])
{
    int i,j,k;
    i=0;
    k=0;
    int observe=1;
    int l=strlen(mots);
    while(i<l)
    {
        for(j=0;j<nbre_caracteres;j++)
        {
            if(mots[i]==a->sigma[j])
            {
                if(a->etats[k].transition[j].nbr_transition==0)

                {
                    printf("\n");

                    printf("Le Mots N'appartient Par Au Langage \n");
                    break;
                }
                else
                    k=a->etats[k].transition[j].destination[0];
            }
            else
                observe=0;
        }
        i++;
    }

    if( est_finale(a,k))
    {
        printf("\n");
        printf("[Le Mots est Reconnue Par L'Automate]\n");
    }
    else
    {
        printf("\n");
        printf("[Le Mots n'est pas Reconnue Par L'Automate]\n");
    }

printf("\n");
}
void affichage(Automate*a)
{
    int i,j,k;
    printf("[Alphabet] =");
    printf("{");

        printf("%s", a->sigma);

    //printf("%s",a->sigma);
    printf("}");
    printf("\n");
    printf("[Etat initiale] =");
    printf("%d",a->etat_initiale);
    printf("\n");
    printf("(Etats Finaux)");
    printf("{");
     for(i=0;i<a->nbr_ef;i++)
    {
         printf("%d,",a->finale[i]);
    }

    printf("}");
    printf("\n");
    printf("Nombre d'etat = [%d]",a->nbr_etat);

    for(i=0;i<a->nbr_etat;i++)
    {
        printf("\n");
        printf("etat(%d)\n",a->etats[i].numero);
        printf("\t");
        for(j=0;j<nbre_caracteres;j++)
        {

            if(a->etats[i].transition[j].nbr_transition!=0)
            {
                for(k=0;k<a->etats[i].transition[j].nbr_transition;k++){
                printf("T[%d,%c]=%d\n",a->etats[i].numero,a->sigma[j],a->etats[i].transition[j].destination[k]);

                }
            }

        }
    }
}
int is_complet(Automate *a)
{
    int c=1;
    int i,j;
    i=0;
    while(i<a->nbr_etat)
    {
        for(j=0; j<nbre_caracteres; j++)
        {
            if(a->etats[i].transition[j].nbr_transition==0)
                c=0;
        }
        i++;
    }

  return (c);
}
int   is_afd(Automate*a)
{
    int afd=1;
    int i,j;
    i=0;
    while(i<a->nbr_etat)
    {
        for(j=0; j<=nbre_caracteres; j++)
        {
            if(a->etats[i].transition[j].nbr_transition>=2)
                afd=0;
        }
        i++;
    }

  return (afd);

}
Automate*cloture_par_miroir(Automate*a)
{
    Automate*b=creation_automate();
    if(a->nbr_ef==1){
    strcpy(b->sigma,a->sigma);
    b->nbr_etat=a->nbr_etat;
    b->nbr_ef=1;
    b->etat_initiale=a->finale[0];
    b->finale[0]=a->etat_initiale;
    int i,j,k;
     for(i=0; i<a->nbr_etat; i++)
    {
        b->etats[i].numero=i;
    }
    for(i=0;i<a->nbr_etat;i++)
    {
        for(j=0;j<nbre_caracteres;j++)
        {
          b->etats[i].transition[j].nbr_transition=0;
        }
    }
    for(i=0;i<a->nbr_etat;i++)
    {
        for(j=0;j<nbre_caracteres;j++)
        {
            if(a->etats[i].transition[j].nbr_transition>0)
            {
                for(k=0;k<a->etats[i].transition[j].nbr_transition;k++)
                {
b->etats[a->etats[i].transition[j].destination[k]].transition[j].destination[b->etats[a->etats[i].transition[j].destination[k]].transition[j].nbr_transition]=a->etats[i].numero;
b->etats[a->etats[i].transition[j].destination[k]].transition[j].nbr_transition++;

                }
            }
        }
    }
    return b;
    }
    else{
        printf("[Miroir Impossible Automate Mal Definie]\n");
    }
}
void auto_complet(Automate*a)
{
    int i,j;
    a->nbr_etat=a->nbr_etat+1;
    for(i=0; i<a->nbr_etat; i++)
    {
        for(j=0; j<nbre_caracteres; j++)
        {
            if(a->etats[i].transition[j].nbr_transition==0)
            {
                a->etats[i].transition[j].destination[0]=a->nbr_etat-1;
                a->etats[i].transition[j].nbr_transition++;
            }

        }

    }

    a->etats[a->nbr_etat-1].numero=a->nbr_etat-1;
    for(j=0; j<nbre_caracteres; j++)
    {
        a->etats[a->nbr_etat].transition[j].destination[0]=a->nbr_etat;
        a->etats[i].transition[j].nbr_transition++;
    }

}

//*********************Cloture par complementaire********************
Automate*complementaire(Automate*a){
    int i,j,k=0;
    Automate*b=creation_automate();

    b = a;
    b->nbr_ef = a->nbr_etat - a->nbr_ef;
    for(i=0; i< a->nbr_ef; i++){
        b->finale[i]= 0;
    }
    for(i=0; i< b->nbr_etat; i++){                         // les etats non finaux deviennent finaux
        for(j=0; j< a->nbr_ef; j++){
            if(b->etats[i].numero != a->finale[j]){
                b->finale[k]= b->etats[i].numero;
                k++;
            }
        }
    }

    return(b);
}



// ****************Main fonction**********************//


int main()
{
    printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\t@\t\t\t\t\t\t\t\t\t@\n");
    printf("\t@\t\t\tBIENVENU DANS AUTOMATEK\t\t\t\t@\n");
    printf("\t@\t\t\t\t*********\t\t\t\t@\n");
    printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\tVOTRE MENU\n");
    printf("\n");
    printf("\t\t1.Verifier si un automate est un AFD/AFN\n");
    printf("\t\t2.Reconnaissance De Mots\n");
    printf("\t\t3.Verifier si un automate est un Complet\n");
    printf("\t\t4.Completion D'un Automate\n");
    printf("\t\t5.Cloture Par miroir\n");
    printf("\t\t6.Complementaire de l'automate\n");

    Automate**tableau_autom=definition_automates();
    Automate*a ;
    Automate*b;
    a=tableau_autom[0];

char c;
int choix;
int choix_automate, choix_automate1, choix_automate2;
int i, booleen;
   char chaine[m];
printf("\n");
printf("\n");
printf("***********************Operations sur les automates**************************\n");

        printf("\n");
        do
    {
        printf("\n");
        printf("\t\t\t\t\tVOTRE MENU\n");
        printf("\n");
        printf("1.Verifier si un automate est un AFD/AFN\n");
        printf("2.Reconnaissance De Mots\n");
        printf("3.Verifier si un automate est un Complet\n");
        printf("4.Completion D'un Automate\n");
        printf("5.Cloture Par miroir\n");
        printf("6.Complementaire de l'automate\n");
        printf("7.Quitter\n");
        printf("\nFaites un choix?\n\n");
        scanf("%d", &choix);
        switch(choix)
        {
        case 1:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("%d", a->nbr_etat);
            printf("\n");
            affichage(a);
    if(is_afd(a))
    {
        printf("\n");

        printf("C'Est Un AFD\n ");

    }
    else
    {
         /*printf("\n");
         i=0;
         booleen=FALSE;
         while( i<nbre_caracteres && booleen == FALSE)
         {
             if(a->sigma[i] == '@')
             {
                 booleen = TRUE;
             }
             i++;
         }
         if(booleen==TRUE)
            {
                printf("C'est Un @-AFN\n");
            }
         else
            {
             printf("C'est Un AFN \n");
                }*/
     printf("C'est Un AFN \n");
    }

            break;
        case 2:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("\n");
            affichage(a);
            printf("\n");
            printf("Entrer le Mots  :\n ");
        scanf("%s", chaine);
        c=getchar();
        reconnaissance_mots(a,chaine);
            break;
        case 3:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("\n");
            affichage(a);
            printf("\n");
                 if(is_complet(a))
    {
        printf("\n");

        printf("[Cet Automate Est Complet]\n ");

    }
    else
    {
         printf("\n");

        printf("[Cet Automate est Pas Complet] \n");

    }

            break;
        case 4:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("\n");
            affichage(a);
    if(is_complet(a)==0){
            auto_complet(a);}
            printf("\n");
            printf("[Automates Complet]\n");
            affichage(a);
            break;
        case 5:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("\n");
            affichage(a);
            printf("\n");
            printf("\n");
            printf("[Automates Miroir]\n");
            b=cloture_par_miroir(a);
            affichage(b);
            break;
        case 6:
            printf("Sur quel automate voulez-vous effectuer votre operation?");
            printf("\nAutomate numero :");
            scanf("%d", &choix_automate);
            a=tableau_autom[choix_automate-1];
            printf("\n");
            printf("voici L'automate\n");
            printf("\n");
            affichage(a);
        if(is_complet(a)==1){
            b=complementaire(a);}
         else{
            printf("Condition de base non verifiee!!\n");
            printf("Cet Automate n'est pas Complet\n");
            printf("Completion de l'automate\n");
            auto_complet(a);
            b=complementaire(a);
            }
            printf("\n");
            printf("[Automate Complementaire]\n");
            affichage(b);
            break;
        case 7:
            printf("Exit\n");
            break;
        }
        }while(choix!=7);




    printf("\n");


    return 0;
}
