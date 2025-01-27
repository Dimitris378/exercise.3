#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "eshop.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

// Συνάρτηση για την αποστολή παραγγελίας
void send_order(int sock, int product_id) {
    write(sock, &product_id, sizeof(product_id)); // Αποστολή παραγγελίας
    char response[200];
    read(sock, response, sizeof(response)); // Λήψη απάντησης από server
    printf("Server response: %s\n", response);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;

    // Δημιουργία socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση διεύθυνσης του server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Σύνδεση με τον server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Τυχαία παραγγελία
    int product_id = rand() % 20; // Επιλογή τυχαίου προϊόντος
    printf("Placing order for product %d...\n", product_id);

    send_order(sock, product_id); // Αποστολή παραγγελίας στον server

    close(sock); // Κλείσιμο σύνδεσης
    return 0;
}
