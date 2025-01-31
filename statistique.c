#include "statistiques.h"
#include "produits.h"

void searchProducts() {
    FILE *fichier = fopen("produits.csv", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char nom[50];
    float prixMin, prixMax;
    printf("Entrez le nom du produit à rechercher: ");
    scanf("%s", nom);
    printf("Entrez l'intervalle de prix (min max): ");
    scanf("%f %f", &prixMin, &prixMax);

    char ligne[100];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Produit p;
        sscanf(ligne, "%d,%s,%d,%f", &p.id, p.nom, &p.quantite, &p.prix);
        if (strcmp(p.nom, nom) == 0 && p.prix >= prixMin && p.prix <= prixMax) {
            printf("%s", ligne);
            trouve = 1;
        }
    }
    fclose(fichier);

    if (!trouve) {
        printf("Aucun produit trouvé.\n");
    }
}

void productStatistics() {
    FILE *fichier = fopen("produits.csv", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int nombreProduits = 0;
    int totalStock = 0;
    float prixTotal = 0.0;
    float prixMax = 0.0;
    char produitCher[50] = "None"; // Default value if no product exists

    char ligne[100];
    int id, quantite;
    char nom[50];
    float prix;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%d,%49[^,],%d,%f", &id, nom, &quantite, &prix) == 4) {
            nombreProduits++;
            totalStock += quantite;
            prixTotal += (prix * quantite); // Price should be multiplied by quantity

            if (prix > prixMax) {
                prixMax = prix;
                strcpy(produitCher, nom);
            }
        }
    }
    fclose(fichier);

    if (nombreProduits > 0) {
        float prixMoyen = prixTotal / totalStock; // Correct calculation
        printf("\n===== Product Statistics =====\n");
        printf("Total number of products: %d\n", nombreProduits);
        printf("Total stock: %d\n", totalStock);
        printf("Average price: %.2f\n", prixMoyen);
        printf("Most expensive product: %s (%.2f)\n", produitCher, prixMax);
        printf("==============================\n");
    } else {
        printf("No products found in the inventory.\n");
    }
}


void exportProducts() {
    FILE *fichier = fopen("produits.csv", "r");
    FILE *exportFichier = fopen("export.csv", "w");
    if (fichier == NULL || exportFichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char ligne[100];
    int id, quantite;
    char nom[50];
    float prix;

    // Write table header with fixed-width columns
    fprintf(exportFichier, "------------------------------------------\n");
    fprintf(exportFichier, "| %-5s | %-15s | %-10s | %-7s |\n", "ID", "Name", "Quantity", "Price");
    fprintf(exportFichier, "------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%d,%49[^,],%d,%f", &id, nom, &quantite, &prix) == 4) {
            if (quantite < 10) { // Export only products with low stock
                fprintf(exportFichier, "| %-5d | %-15s | %-10d | %-7.2f |\n", id, nom, quantite, prix);
            }
        }
    }

    fprintf(exportFichier, "------------------------------------------\n");

    fclose(fichier);
    fclose(exportFichier);
    printf("Produits exportés avec succès dans 'export.csv'.\n");
}
