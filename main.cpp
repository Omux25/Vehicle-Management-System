#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct InfoVehicule{
    char matricule[20];
    char marque[20];
    char modele[20];
    int annee;
    int nbViolations;
} infoVehicule;

typedef struct Vehicule{
    struct InfoVehicule *data;
    struct Vehicule *next;
    struct Vehicule *prev;
} vehicule;

void clear();
void attente();
void menuPrincipal(vehicule **head);
void gestionVehicules(vehicule **head);
void Ajout_vehicule(vehicule **head);
void modification_vehicule(vehicule *head, char *matricule);
void Suppression_Vehicule(vehicule **head);
vehicule *Creer_vehicule();
vehicule *Ajout_debut(vehicule *head);
vehicule *Ajout_fin(vehicule *head);
vehicule *Ajout_Apres_Vehicule(vehicule *head, char *matricule);
vehicule* SupprimerDebut(vehicule *head);
vehicule* SupprimerFin(vehicule *head);
vehicule* SupprimerApresVehicule(vehicule *head, char *matricule);
void Afficher_vehicules(vehicule *head);
void Liberer_liste(vehicule *head);
void Rechercher_Vehicule(vehicule *head);
void Suivi_Infractions(vehicule *head, int threshold);
void Ajouter_Violation(vehicule *head, char *matricule);
int compare_annee(const void *a, const void *b);
int compare_nbViolations(const void *a, const void *b);
void Trier_Vehicules(vehicule **head, int critere);

int main(){
    vehicule *head = NULL;
    menuPrincipal(&head);
    Liberer_liste(head);
    return 0;
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        if (!isatty(STDOUT_FILENO)) return;
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

void attente() {
    printf("\nAppuyez sur Entree pour continuer...");
    getchar();
}

void menuPrincipal(vehicule **head){
    int n;
    do {
        clear();
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("|                                          |\n");
        printf("|              Menu Principal              |\n");
        printf("|                                          |\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("1. Gestion des vehicules\n");
        printf("2. Quitter\n");
        printf("Choisir une option : ");
        scanf("%d", &n);
        getchar();
        switch (n){
            case 1:
                gestionVehicules(head);
                break;
            case 2:
                printf("Fermeture du programme...\n");
                break;
            default:
                printf("Erreur! Option non valable\n");
                attente();
                break;
        }
    } while (n != 2);
}

void gestionVehicules(vehicule **head){
    int n;
    while(1){
        clear();
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("|                                          |\n");
        printf("|          Gestion des vehicules           |\n");
        printf("|                                          |\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("1. Ajout d'un vehicule\n");
        printf("2. Modification d'un vehicule\n");
        printf("3. Suppression d'un vehicule\n");
        printf("4. Recherche d'un vehicule\n");
        printf("5. Afficher les vehicules\n");
        printf("6. Option de tri\n");
        printf("7. Suivi des infractions repetees\n");
        printf("8. Ajouter une infraction\n");
        printf("9. Retour au menu principal\n");
        printf("Choisir une option : ");
        scanf("%d",&n);
        getchar(); 
        switch (n){
            case 1:
                Ajout_vehicule(head);
                break;
            case 2:
                {
                    char tmpMat[20];
                    printf("Entrez une matricule : ");
                    scanf("%19s", tmpMat);
                    getchar();
                    modification_vehicule(*head, tmpMat);
                }
                break; 
            case 3:
                Suppression_Vehicule(head);
                break;
            case 4:
                Rechercher_Vehicule(*head);
                break;
            case 5:
                Afficher_vehicules(*head);
                attente();
                break;   
            case 6:
                {
                    int critere;
                    do {
                        printf("Choisir le critere de tri (1: Annee, 2: Nombre d'infractions) : ");
                        scanf("%d", &critere);
                        getchar();
                        if (critere != 1 && critere != 2){
                            printf("Erreur. Option Non Valable.\n");
                            attente();
                        }
                    } while (critere != 1 && critere != 2);
                    Trier_Vehicules(head, critere);
                    Afficher_vehicules(*head);
                    attente();
                }
                break;
            case 7:
                {
                    int threshold;
                    printf("Entrez le seuil d'infractions : ");
                    scanf("%d", &threshold);
                    getchar();
                    Suivi_Infractions(*head, threshold);
                    attente();
                }
                break;
            case 8:
                {
                    char violMat[20];
                    printf("Entrez le matricule du vehicule : ");
                    scanf("%19s", violMat);
                    getchar();
                    Ajouter_Violation(*head, violMat);
                    attente();
                }
                break;
            case 9:
                return;
            default:
                printf("Erreur! Option non valide.\n");
                attente();
                break;
        }
    }
}

void Ajout_vehicule(vehicule **head){
    int n;
    while(1){
        clear();
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("|                                          |\n");
        printf("|            Ajout d'un vehicule           |\n");
        printf("|                                          |\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("1. Ajout debut\n");
        printf("2. Ajout fin\n");
        printf("3. Ajout apres un vehicule specifique\n");
        printf("4. Retour\n");
        printf("Choisir une option : ");
        scanf("%d", &n);
        getchar();
        switch (n){
            case 1:
                *head = Ajout_debut(*head);
                printf("Vehicule ajoute avec succes.\n");
                attente();
                break;
            case 2:
                *head = Ajout_fin(*head);
                printf("Vehicule ajoute avec succes.\n");
                attente();
                break;
            case 3:
                {
                    char tmpMat[20];
                    printf("Entrez une matricule : ");
                    scanf("%19s", tmpMat);
                    getchar();
                    *head = Ajout_Apres_Vehicule(*head, tmpMat);
                    attente();
                }
                break;
            case 4:
                return;
            default:
                printf("Erreur! Option non valide.\n");
                attente();
                break;
        }
    }
}

void modification_vehicule(vehicule *head, char *matricule){
    vehicule *current = head;
    while(current && strcmp(current->data->matricule, matricule) != 0){
        current = current->next;
    }
    if (current){
        int n;
        while(1){
            clear();
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
            printf("|                                          |\n");
            printf("|           Type de modification           |\n");
            printf("|                                          |\n");
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
            printf("Matricule actuel : %s\n", current->data->matricule);
            printf("1. Modifier le matricule\n");
            printf("2. Modifier la Marque\n");
            printf("3. Modifier le Modele\n");
            printf("4. Modifier l'annee\n");
            printf("5. Retour\n");
            printf("Choisir une option : ");
            scanf("%d", &n);
            getchar();
            switch (n){
                case 1:
                    printf("Entrer le nouvelle matricule : ");
                    scanf("%19s", current->data->matricule);
                    getchar();
                    break;
                case 2:
                    printf("Entrer la nouvelle marque : ");
                    scanf("%19s", current->data->marque);
                    getchar();
                    break;
                case 3:
                    printf("Entrer le nouveau modele : ");
                    scanf("%19s", current->data->modele);
                    getchar();
                    break;
                case 4:
                    printf("Entrer la nouvelle annee : ");
                    scanf("%d", &current->data->annee);
                    getchar();
                    break;
                case 5:
                    return;
                default:
                    printf("Erreur! Option non valide.\n");
                    attente();
                    break;
            }
        }
    } else {
        printf("Erreur! Vehicle non trouve.\n");
        attente();
    }
}

void Suppression_Vehicule(vehicule **head){
    int n;
    while(1){
        clear();
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("|                                          |\n");
        printf("|           Type de suppression            |\n");
        printf("|                                          |\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("1. Suppression au debut\n");
        printf("2. Suppression a la fin \n");
        printf("3. Suppression apres un vehicule specifique\n");
        printf("4. Retour\n");
        printf("Choisir une option : ");
        scanf("%d", &n);
        getchar();
        switch (n){
            case 1:
                *head = SupprimerDebut(*head);
                attente();
                break;
            case 2:
                *head = SupprimerFin(*head);
                attente();
                break;
            case 3:
                {
                    char tmpMat[20];
                    printf("Entrez une matricule : ");
                    scanf("%19s", tmpMat);
                    getchar();
                    *head = SupprimerApresVehicule(*head, tmpMat);
                    attente();
                }
                break;
            case 4:
                return;
            default:
                printf("Erreur! Option non valide.\n");
                attente();
                break;
        }
    }
}

vehicule *Creer_vehicule(){
    vehicule* newVehicule = (vehicule*)malloc(sizeof(vehicule));
    if (!newVehicule){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newVehicule->data = (infoVehicule*)malloc(sizeof(infoVehicule));
    if (!newVehicule->data){
        printf("Memory allocation failed.\n");
        free(newVehicule);
        exit(1);
    }
    printf("Entrer le matricule : ");
    scanf("%19s", newVehicule->data->matricule);
    getchar();
    printf("Entrer la marque : ");
    scanf("%19s", newVehicule->data->marque);
    getchar();
    printf("Entrer le modele : ");
    scanf("%19s", newVehicule->data->modele);
    getchar();
    printf("Entrer l'annee : ");
    scanf("%d", &newVehicule->data->annee);
    getchar();
    newVehicule->data->nbViolations = 0;
    newVehicule->prev = NULL;
    newVehicule->next = NULL;
    return newVehicule;
}

vehicule *Ajout_debut(vehicule *head){
    vehicule* newVehicule = Creer_vehicule();
    if (!head){
        return newVehicule;
    }
    newVehicule->next = head;
    head->prev = newVehicule;
    return newVehicule;
}

vehicule *Ajout_fin(vehicule *head){
    vehicule *newVehicule = Creer_vehicule();
    if (!head){
        return newVehicule;
    }
    vehicule *tmp = head;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = newVehicule;
    newVehicule->prev = tmp;
    return head;
}

vehicule *Ajout_Apres_Vehicule(vehicule *head, char *matricule){
    vehicule *current = head;
    while(current && strcmp(current->data->matricule, matricule) != 0){
        current = current->next;
    }
    if (current){
        vehicule *newVehicule = Creer_vehicule();
        newVehicule->prev = current;
        newVehicule->next = current->next;
        if(current->next){
            current->next->prev = newVehicule;
        }
        current->next = newVehicule;
    } else {
        printf("Erreur! il n'ya pas de vehicule avec ce matricule.\n");
    }
    return head;
}

vehicule* SupprimerDebut(vehicule *head){
    if (!head){
        printf("Erreur! La liste est vide.\n");
        return NULL;
    }
    vehicule *toDelete = head;
    head = head->next;
    if (head){
        head->prev = NULL;
    }
    free(toDelete->data);
    free(toDelete);
    printf("Vehicule supprime avec succes.\n");
    return head;
}

vehicule* SupprimerFin(vehicule *head){
    if (!head){
        printf("Erreur! La liste est vide.\n");
        return NULL;
    }
    if (!head->next){
        free(head->data);
        free(head);
        printf("Vehicule supprime avec succes.\n");
        return NULL;
    }
    vehicule *tmp = head;
    while(tmp->next->next){
        tmp = tmp->next;
    }
    vehicule *toDelete = tmp->next;
    tmp->next = NULL;
    free(toDelete->data);
    free(toDelete);
    printf("Vehicule supprime avec succes.\n");
    return head;
}

vehicule* SupprimerApresVehicule(vehicule *head, char *matricule){
    if (!head){
        printf("Erreur! La liste est vide.\n");
        return head;
    }
    vehicule *current = head;
    while(current && strcmp(current->data->matricule, matricule) != 0){
        current = current->next;
    }
    if (current && current->next){
        vehicule *toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete->next){
            toDelete->next->prev = current;
        }
        free(toDelete->data);
        free(toDelete);
        printf("Vehicule supprime avec succes.\n");
    } else {
        printf("Erreur! vehicule non trouve ou pas de vehicule suivant.\n");
    }
    return head;
}

void Afficher_vehicules(vehicule *head){
    if (!head){
        printf("Erreur! La liste est vide\n");
        return;
    }
    int i=1;
    vehicule *current = head;
    while(current){
        printf("|------------Vehicule no %d--------------|\n", i);
        printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
               current->data->matricule,
               current->data->marque,
               current->data->modele,
               current->data->annee,
               current->data->nbViolations);
        current = current->next;
        i++;
        printf("|----------------------------------------|\n");
    }
}

void Liberer_liste(vehicule *head){
    while(head){
        vehicule *tmp = head;
        head = head->next;
        if (tmp->data) free(tmp->data);
        free(tmp);
    }
}

void Rechercher_Vehicule(vehicule *head){
    int n;
    while(1){
        clear();
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("|                                          |\n");
        printf("|           Recherche de vehicule          |\n");
        printf("|                                          |\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("1. Par marque\n");
        printf("2. Par modele\n");
        printf("3. Par annee de fabrication\n");
        printf("4. Recherche avancee\n");
        printf("5. Retour\n");
        printf("Choisir une option : ");
        scanf("%d", &n);
        getchar();
        if (n == 5) return;
        if (n < 1 || n > 5){
            printf("Erreur! option non Valide.\n");
            attente();
            continue;
        }
        if (!head){
            printf("La liste est vide.\n");
            attente();
            continue;
        }
        vehicule *current = head;
        int found = 0;
        if (n == 1){
            char marque[20];
            printf("Entrez la marque : ");
            scanf("%19s", marque);
            getchar();
            while(current){
                if (strcasecmp(current->data->marque, marque) == 0){
                    printf("|------------Vehicule trouve!--------------|\n");
                    printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
                           current->data->matricule,
                           current->data->marque,
                           current->data->modele,
                           current->data->annee,
                           current->data->nbViolations);
                    found = 1;
                    printf("|------------------------------------------|\n");
                }
                current = current->next;
            }
        } else if (n == 2){
            char modele[20];
            printf("Entrez le modele : ");
            scanf("%19s", modele);
            getchar();
            while(current){
                if (strcasecmp(current->data->modele, modele) == 0){
                    printf("|------------Vehicule trouve!--------------|\n");
                    printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
                           current->data->matricule,
                           current->data->marque,
                           current->data->modele,
                           current->data->annee,
                           current->data->nbViolations);
                    found = 1;
                    printf("|------------------------------------------|\n");
                }
                current = current->next;
            }
        } else if (n == 3){
            int annee;
            printf("Entrez l'annee de fabrication : ");
            scanf("%d", &annee);
            getchar();
            while(current){
                if (current->data->annee == annee){
                    printf("|------------Vehicule trouve!--------------|\n");
                    printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
                           current->data->matricule,
                           current->data->marque,
                           current->data->modele,
                           current->data->annee,
                           current->data->nbViolations);
                    found = 1;
                    printf("|------------------------------------------|\n");
                }
                current = current->next;
            }
        } else if (n == 4){
            char marque[20] = "", modele[20] = "";
            int annee = -1;
            char buffer[50];
            
            printf("Entrez la marque (ou appuyez sur Entree pour ignorer) : ");
            fgets(buffer, sizeof(buffer), stdin);
            if(buffer[0] != '\n') {
                sscanf(buffer, "%19s", marque);
            }

            printf("Entrez le modele (ou appuyez sur Entree pour ignorer) : ");
            fgets(buffer, sizeof(buffer), stdin);
            if(buffer[0] != '\n') {
                sscanf(buffer, "%19s", modele);
            }

            printf("Entrez l'annee (ou -1 pour ignorer) : ");
            scanf("%d", &annee);
            getchar(); 

            while(current){
                int match = 0;
                int criteria = 0;

                if (marque[0]) {
                    criteria++;
                    if (strcasecmp(current->data->marque, marque) == 0) match++;
                }
                if (modele[0]) {
                    criteria++;
                    if (strcasecmp(current->data->modele, modele) == 0) match++;
                }
                if (annee != -1) {
                    criteria++;
                    if (current->data->annee == annee) match++;
                }

                if (criteria > 0 && match == criteria){
                    printf("|------------Vehicule trouve!--------------|\n");
                    printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
                           current->data->matricule,
                           current->data->marque,
                           current->data->modele,
                           current->data->annee,
                           current->data->nbViolations);
                    found = 1;
                    printf("|------------------------------------------|\n");
                }
                current = current->next;
            }
        }
        if (!found){
            printf("Aucun vehicule trouve.\n");
        }
        attente();
    }
}

void Suivi_Infractions(vehicule *head, int threshold){
    printf("Vehicules avec %d infractions ou plus:\n", threshold);
    vehicule *current = head;
    int found = 0;
    while(current){
        if (current->data->nbViolations >= threshold){
            printf("Matricule: %s, Marque: %s, Modele: %s, Annee: %d, Infractions: %d\n",
                   current->data->matricule,
                   current->data->marque,
                   current->data->modele,
                   current->data->annee,
                   current->data->nbViolations);
            found = 1;
        }
        current = current->next;
    }
    if (!found){
        printf("Aucun vehicule n'a %d infractions ou plus.\n", threshold);
    }
}

void Ajouter_Violation(vehicule *head, char *matricule){
    vehicule *current = head;
    while(current && strcmp(current->data->matricule, matricule) != 0){
        current = current->next;
    }
    if (current){
        current->data->nbViolations++;
        printf("Infraction ajoutee pour le vehicule %s. Total: %d\n", matricule, current->data->nbViolations);
    } else {
        printf("Vehicule non trouve.\n");
    }
}

int compare_annee(const void *a, const void *b){
    vehicule *va = *(vehicule **)a;
    vehicule *vb = *(vehicule **)b;
    return va->data->annee - vb->data->annee;
}

int compare_nbViolations(const void *a, const void *b){
    vehicule *va = *(vehicule **)a;
    vehicule *vb = *(vehicule **)b;
    return vb->data->nbViolations - va->data->nbViolations; 
}

void Trier_Vehicules(vehicule **head, int critere) {
    if (!*head) return;
    int n = 0;
    vehicule *current = *head;
    while (current) {
        n++;
        current = current->next;
    }
    vehicule **array = (vehicule **)malloc(n * sizeof(vehicule *));
    if (!array) {
        printf("Memory allocation failed.\n");
        return;
    }
    current = *head;
    for (int i = 0; i < n; i++) {
        array[i] = current;
        current = current->next;
    }
    if (critere == 1) {
        qsort(array, n, sizeof(vehicule *), compare_annee);
    } else if (critere == 2) {
        qsort(array, n, sizeof(vehicule *), compare_nbViolations);
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            array[i-1]->next = array[i];
            array[i]->prev = array[i-1];
        } else {
            array[i]->prev = NULL;
        }
        if (i == n-1) {
            array[i]->next = NULL;
        }
    }
    *head = array[0];
    free(array);
}
