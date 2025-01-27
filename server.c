#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "eshop.h"

#define PORT 8080 // Θύρα που θα ακούει ο server

// Δομή για το προϊόν
struct Product {
    char description[100];
    float price;
    int item_count;
};

// Κατάλογος προϊόντων
struct Product catalog[20];

// Συνάρτηση για αρχικοποίηση του καταλόγου
void initialize_catalog() {
    for (int i = 0; i < 20; i++) {
        snprintf(catalog[i].description, sizeof(catalog[i].description), "Product %d", i+1);
        catalog[i].price = (float)(rand() % 100 + 10);  // Τυχαία τιμή για το προϊόν
        catalog[i].item_count = 2; // Κάθε προϊόν έχει 2 διαθέσιμα τεμάχια
    }
}

// Συνάρτηση για την επεξεργασία της παραγγελίας
void process_order(int client_sock, int product_id) {
    if (product_id < 0 || product_id >= 20) {
        write(client_sock, "Invalid product ID", 18);
        return;
    }

    struct Product *product = &catalog[product_id];

    if (product->item_count > 0) {
        product->item_count--; // Αφαίρεση ενός προϊόντος
        float total = product->price; // Υπολογισμός τιμής παραγγελίας
        char message[200];
        snprintf(message, sizeof(message), "Order successful! Product: %s, Price: %.2f, Remaining stock: %d", 
                 product->description, total, product->item_count);
        write(client_sock, message, strlen(message) + 1);
    } else {
        write(client_sock, "Product out of stock", 21);
    }
}

// Κύρια συνάρτηση του server
int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Δημιουργία socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση διεύθυνσης του server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Ανάθεση της διεύθυνσης στο socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Αναμονή για σύνδεση
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
    initialize_catalog(); // Αρχικοποιούμε τον κατάλογο προϊόντων

    // Σύνδεση με πελάτη
    while ((client_sock = accept(server_fd, (struct sockaddr*)&client_addr, &client_len)) >= 0) {
        printf("Client connected\n");
        
        int product_id;
        read(client_sock, &product_id, sizeof(product_id)); // Λήψη παραγγελίας από πελάτη
        process_order(client_sock, product_id); // Επεξεργασία παραγγελίας

        close(client_sock); // Κλείσιμο σύνδεσης με τον πελάτη
    }

    close(server_fd);
    return 0;
}
