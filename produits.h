#ifndef PRODUITS_H_INCLUDED
#define PRODUITS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nom[50];
    int quantite;
    float prix;
} Produit;

void displayProducts();
void addProduct();
void modifyProduct();
void deleteProduct();
void searchProducts();
void productStatistics();
void exportProducts();

#endif// PRODUITS_H_INCLUDED
