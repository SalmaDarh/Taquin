#include <stdio.h>
#include <stdlib.h>
typedef struct etat{
int table[3][3];
int g;
}Etat;

typedef struct noeud{
struct noeud *suivant;
Etat etat;
}Noeud;

typedef struct liste
{
    Noeud *sommet;
}Liste;
Liste NoeudsDejaTraites, listeNoeuds;

void Inserer(Etat e, Liste *L)
{
    Noeud *nouveau=malloc(sizeof(*nouveau));
    nouveau->etat=e;
    nouveau->suivant=L->sommet;
    L->sommet=nouveau;

}

Etat Extraire(Liste *L)
{
    Etat e;
    e=L->sommet->etat;
    L->sommet=L->sommet->suivant;
    return e;
}
int Vide(Liste L)
{
    return (L.sommet==NULL);
}

int Appartient(Etat e, Liste L)
{
    Noeud *ptr=malloc(sizeof(*ptr));

    for (ptr=L.sommet;ptr!=NULL;ptr=ptr->suivant)
    {

        int k=0;
        for(int i=0;i<=2;i++)
        {
            for(int j=0;j<=2;j++)
            {

                 if(ptr->etat.table[i][j]==e.table[i][j]) k++ ;
            }
        }

        if (k==9) return 1;

    }
    return 0;
}
int h(Etat et,Etat etatFinal)
{
    int H=0;
    for (int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
           if (et.table[i][j]!=etatFinal.table[i][j]) H++;
        }
    }
    return H;
}
int etatSolution(Etat etat,Etat etatFinal)
{
    if (h(etat,etatFinal)==0 )return 1;
    return 0;
}


void Afficher(Etat et)
{
    printf("\t\t\t\t ______ ______ ______\n");
    for(int i=0;i<=2;i++)
    {
      if(et.table[i][0]!=0 && et.table[i][1]!=0 && et.table[i][2]!=0)
      {
            printf("\t\t\t\t|      |      |      |\n");
            printf("\t\t\t\t|  %d   |  %d   |  %d   |\n",et.table[i][0],et.table[i][1],et.table[i][2]);
            printf("\t\t\t\t|______|______|______|\n");
      }
      if(et.table[i][0]==0)
      {
            printf("\t\t\t\t|      |      |      |\n");
            printf("\t\t\t\t|      |  %d   |  %d   |\n",et.table[i][1],et.table[i][2]);
            printf("\t\t\t\t|______|______|______|\n");
      }
      if(et.table[i][1]==0)
      {
            printf("\t\t\t\t|      |      |      |\n");
            printf("\t\t\t\t|  %d   |      |  %d   |\n",et.table[i][0],et.table[i][2]);
            printf("\t\t\t\t|______|______|______|\n");
      }
      if(et.table[i][2]==0)
      {
            printf("\t\t\t\t|      |      |      |\n");
            printf("\t\t\t\t|  %d   |  %d   |      |\n",et.table[i][0],et.table[i][1]);
            printf("\t\t\t\t|______|______|______|\n");
      }


    }

}
int RD(Etat e,Liste *L0)
{

    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            if (e.table[i][j]==0)
            {
                if(j!=2)
                {
                    e.table[i][j]=e.table[i][j+1];
                    e.table[i][j+1]=0;
                    e.g++;
                    if(!Appartient(e,NoeudsDejaTraites))
                    Inserer(e,L0);
                    return 1;

                }
            }

        }
    }
return 0;

}
int RG(Etat e,Liste *L0)
{

    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            if (e.table[i][j]==0)
            {
                if(j!=0)
                {
                    e.table[i][j]=e.table[i][j-1];
                    e.table[i][j-1]=0;
                    e.g++;
                    if(!Appartient(e,NoeudsDejaTraites))
                    Inserer(e,L0);
                   return 1;
                }

            }
        }
    }
return 0;
}
int RH(Etat e,Liste *L0)
{

    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            if (e.table[i][j]==0)
            {
                if(i!=0)
                {
                    e.table[i][j]=e.table[i-1][j];
                    e.table[i-1][j]=0;
                    e.g++;
                    if(!Appartient(e,NoeudsDejaTraites))
                    Inserer(e,L0);
                    return 1;
                }
            }
        }
    }
return 0;
}
int RB(Etat e,Liste *L0)
{
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            if (e.table[i][j]==0)
            {
                 if(i!=2)
                {
                    e.table[i][j]=e.table[i+1][j];
                    e.table[i+1][j]=0;
                    e.g++;
                    if(!Appartient(e,NoeudsDejaTraites)) Inserer(e,L0);
                    return 1;

                }
            }
        }
    }
return 0;

}
void genereSuccesseurs(Etat etat,Liste *L)
{
    //on insere ds la liste des successeurs
    RD(etat,L);
    RG(etat,L);
    RH(etat,L);
    RB(etat,L);


}

int n=0;
void RechercheAEtoile(Etat etatInitial,Etat etatFinal,void genereSuccesseurs())
{
    listeNoeuds.sommet=NULL;
    Inserer(etatInitial,&listeNoeuds);
    NoeudsDejaTraites.sommet=NULL;
    Etat etatCourant;
    Liste listeSuccesseurs;
    while (!Vide(listeNoeuds))
    {
        etatCourant=Extraire(&listeNoeuds);
        if(etatSolution(etatCourant,etatFinal))
        {
            printf("Succes! Arret sur l'etat :%d \n",n);
            Afficher(etatCourant);
            exit(0);

        }
        else
        {
            listeSuccesseurs.sommet=NULL;
            Afficher(etatCourant);
            printf("\n\n\t\t\t\t\t   | \n");
            printf("\t\t\t\t\t   | \n");
            printf("\t\t\t\t\t\  \\|/ \n");
            printf("\t\t\t\t\t\   V \n");
            genereSuccesseurs(etatCourant,&listeSuccesseurs);
            n++;
            printf("\n\n");
            int f1,f2;
            Inserer(listeSuccesseurs.sommet->etat,&listeNoeuds);
            for(Noeud *n=listeSuccesseurs.sommet;n->suivant!=NULL;n=n->suivant)
            {
                f1=n->etat.g+h(n->etat,etatFinal);
                f2=n->suivant->etat.g+h(n->suivant->etat,etatFinal);
                if (f2<f1)
                    Inserer(n->suivant->etat,&listeNoeuds);
            }

            Inserer(etatCourant,&NoeudsDejaTraites);
        }

    }
    puts("Pas de solution\n");
}
void messageDaccueil(void)
{

    printf("\t\t#######  #######  #######  #     #  #######  #     #\n");
    printf("\t\t   #     #     #  #     #  #     #     #     ##    #\n");
    printf("\t\t   #     #######  #     #  #     #     #     # ##  #\n");
    printf("\t\t   #     #     #  #   # #  #     #     #     #  ## #\n");
    printf("\t\t   #     #     #  #######  #######  #######  #    ##\n");
    printf("\t\t                         #                          \n");
    printf("\n\n\tBonjour! Bienvenue sur ce chercheur de chemin optimal du jeu du taquin \n\n");

}
int menu(void)
{
    int choix=0;
    printf("Si vous souhaitez entrer un etat initial et chercher le chemin optimalpour un etat final donnee tapez 1\n\nsi vous souhaitez voir la solution pour un etat qu'on propose tapez 2\n\n");
    scanf("%d",&choix);
    while (choix!=1 && choix!=2)
    {
        printf("Veuillez entrez un choix valide : \n");
        fflush(stdin);
        scanf("%d",&choix);
    }
    return choix;
}


int main()
{
    messageDaccueil();
    int a;
    a=menu();
    while(a!=0)
    {
        if (a==2)
        {
            Etat etatIn={{{2,8,3},{1,6,4},{7,0,5}},0};
            Etat etatFin={{{1,2,3},{8,0,4},{7,6,5}},0};
            RechercheAEtoile(etatIn,etatFin,genereSuccesseurs);

        }
        if (a==1)
        {
            int tabi[3][3];
            int tabf[3][3];
            printf("Veuillez entrer l'etat initial : (Marquez une unique case vide par le chiffre 0)\n");
            for(int i=1;i<=3;i++)
            {
                printf("entrez la ligne %d un a un (des chiffres de 1 a 8):\n ",i);
                scanf("%d",&tabi[i-1][0]);
                scanf("%d",&tabi[i-1][1]);
                scanf("%d",&tabi[i-1][2]);
            }
            printf("Veuillez entrer l'etat final :(Marquez une unique case vide par le chiffre 0)\n");
            for(int i=1;i<=3;i++)
            {
                printf("entrez la ligne %d un a un (des chiffres de 1 a 8):\n ",i);
                scanf("%d",&tabf[i-1][0]);
                scanf("%d",&tabf[i-1][1]);
                scanf("%d",&tabf[i-1][2]);
            }
            Etat etatIn={{{tabi[0][0],tabi[0][1],tabi[0][2]},{tabi[1][0],tabi[1][1],tabi[1][2]},{tabi[2][0],tabi[2][1],tabi[2][2]}},0};
            Etat etatFin={{{tabf[0][0],tabf[0][1],tabf[0][2]},{tabf[1][0],tabf[1][1],tabf[1][2]},{tabf[2][0],tabf[2][1],tabf[2][2]}},0};
            RechercheAEtoile(etatIn,etatFin,genereSuccesseurs);
            a=menu();
        }



    }

    return 0;
}
