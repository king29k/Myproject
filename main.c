#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produits.h"
#include "statistiques.h"

void menu() {
    int choice;

    do {
        printf("\nMain Menu:\n");
        printf("1. Display products\n");
        printf("2. Add a product\n");
        printf("3. Modify a product\n");
        printf("4. Delete a product\n");
        printf("5. Search products\n");
        printf("6. Product statistics\n");
        printf("7. Export products\n");
        printf("8. Quit\n");

        // Input validation loop
        printf("Enter your choice: ");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 8) {
            printf("Invalid input. Please enter a number between 1 and 8: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        switch (choice) {
            case 1:
                displayProducts();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                modifyProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                searchProducts();
                break;
            case 6:
                productStatistics();
                break;
            case 7:
                exportProducts();
                break;
            case 8:
                printf("Goodbye!\n");
                break;
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
