#ifndef ESHOP_H
#define ESHOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>

// Μέγιστος αριθμός προϊόντων στον κατάλογο
#define MAX_PRODUCTS 20
// Μέγιστος αριθμός πελατών
#define MAX_CLIENTS 5

// Δομή για το προϊόν
typedef struct {
    char description[256];  // Περιγραφή προϊόντος
    float price;            // Τιμή προϊόντος
    int item_count;         // Διαθέσιμα τεμάχια
} Product;

// Δομή για το αίτημα παραγγελίας του πελάτη
typedef struct {
    int client_id;          // ID πελάτη
    int product_id;         // ID προϊόντος που ζητήθηκε
    int quantity;           // Ποσότητα προϊόντος
} OrderRequest;

// Πίνακας με τα προϊόντα στον κατάλογο
extern Product catalog[MAX_PRODUCTS];

// Δηλώσεις συναρτήσεων

// Συνάρτηση για την αρχικοποίηση του server
int initialize_server(int port);

// Συνάρτηση για την επικοινωνία με τον πελάτη (εξυπηρέτηση παραγγελίας)
void handle_client(int client_socket);

// Συνάρτηση για τη διαχείριση της παραγγελίας (έλεγχος διαθεσιμότητας, εκτέλεση παραγγελίας)
void process_order(int client_socket, OrderRequest order);

// Συνάρτηση για την ενημέρωση του πελάτη σχετικά με την κατάσταση της παραγγελίας
void send_order_status(int client_socket, const char* message);

// Συνάρτηση για την ενημέρωση των στοιχείων του καταλόγου προϊόντων
void update_catalog(int product_id, int quantity);

// Συνάρτηση για την παραγωγή της συγκεντρωτικής αναφοράς
void generate_report();

// Συνάρτηση για τον client (παράγει παραγγελίες και επικοινωνεί με τον server)
void *client_function(void *arg);

// Συνάρτηση για τη σύνδεση του πελάτη με τον server
int connect_to_server(const char *server_ip, int server_port);

// Συνάρτηση για την εκτέλεση παραγγελίας (προαιρετικό αν θέλεις να το σπάσεις σε ξεχωριστές συναρτήσεις)
void make_order(int product_id, int quantity, int client_socket);

// Συνάρτηση για τη διαχείριση της επικοινωνίας (είσοδος και έξοδος μηνυμάτων)
void communicate_with_server(int client_socket, const char *message);

// Συνάρτηση για την κλείσιμο της σύνδεσης
void close_connection(int socket);

#endif  // ESHOP_H
