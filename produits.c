#include "produits.h"

void displayProducts() {
    FILE *file = fopen("produits.csv", "r");
    if (file == NULL) {
        // If the file does not exist, create it
        file = fopen("produits.csv", "w");
        if (file == NULL) {
            perror("Error creating the file");
            return;
        }
        fclose(file);
        printf("File created successfully. No products available.\n");
        return;
    }

    printf("\n----------------------------------------------\n");
    printf("| %-5s | %-15s | %-10s | %-7s |\n", "ID", "Name", "Quantity", "Price");
    printf("----------------------------------------------\n");

    char line[100];
    int id, quantity;
    char name[50];
    float price;

    while (fgets(line, sizeof(line), file)) {
        // Parse CSV format: ID,Name,Quantity,Price
        sscanf(line, "%d,%49[^,],%d,%f", &id, name, &quantity, &price);

        // Print in table format
        printf("| %-5d | %-15s | %-10d | %-7.2f |\n", id, name, quantity, price);
    }

    printf("----------------------------------------------\n");

    fclose(file);
}


void addProduct() {
    FILE *file = fopen("produits.csv", "a");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    Produit p;
    printf("Enter the product name: ");
    scanf("%s", p.nom);
    printf("Enter the product quantity: ");
    scanf("%d", &p.quantite);
    printf("Enter the product price: ");
    scanf("%f", &p.prix);

    // Find the next available ID
    int nextId = 1;
    FILE *temp = fopen("produits.csv", "r");
    if (temp != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), temp)) {
            int id;
            sscanf(line, "%d", &id);
            if (id >= nextId) {
                nextId = id + 1;
            }
        }
        fclose(temp);
    }

    p.id = nextId;
    printf("The product ID is: %d\n", p.id);

    fprintf(file, "%d,%s,%d,%.2f\n", p.id, p.nom, p.quantite, p.prix);
    fclose(file);
}

void modifyProduct() {
    FILE *file = fopen("produits.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file == NULL || temp == NULL) {
        perror("Error opening the file");
        return;
    }

    int id;
    printf("Enter the ID of the product to modify: ");
    scanf("%d", &id);

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        Produit p;
        sscanf(line, "%d,%[^,],%d,%f", &p.id, p.nom, &p.quantite, &p.prix);
        if (p.id == id) {
            found = 1;
            printf("Enter the new product name: ");
            scanf("%s", p.nom);
            printf("Enter the new product quantity: ");
            scanf("%d", &p.quantite);
            printf("Enter the new product price: ");
            scanf("%f", &p.prix);
            fprintf(temp, "%d,%s,%d,%.2f\n", p.id, p.nom, p.quantite, p.prix);
        } else {
            fprintf(temp, "%s", line);
        }
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
    } else {
        remove("temp.csv");
        printf("Product not found.\n");
    }
}

void deleteProduct() {
    FILE *file = fopen("produits.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file == NULL || temp == NULL) {
        perror("Error opening the file");
        return;
    }

    int id;
    printf("Enter the ID of the product to delete: ");
    scanf("%d", &id);

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        Produit p;
        sscanf(line, "%d,%[^,],%d,%f", &p.id, p.nom, &p.quantite, &p.prix);
        if (p.id != id) {
            fprintf(temp, "%s", line);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
    } else {
        remove("temp.csv");
        printf("Product not found.\n");
    }
}
