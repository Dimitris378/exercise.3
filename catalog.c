struct Product {
    char description[100];
    float price;
    int item_count;
};
struct Product catalog[20];

int server_socket = socket(AF_INET, SOCK_STREAM, 0);
if (server_socket < 0) {
    perror("Socket creation failed");
    exit(1);
}

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(12345);  
server_addr.sin_addr.s_addr = INADDR_ANY;

if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    exit(1);
}

if (listen(server_socket, 5) < 0) {
    perror("Listen failed");
    exit(1);
}
int client_socket = accept(server_socket, NULL, NULL);
if (client_socket < 0) {
    perror("Accept failed");
    exit(1);
}


int product_index;
read(client_socket, &product_index, sizeof(int));


if (catalog[product_index].item_count > 0) {
    write(client_socket, "Order successful", 17);
    catalog[product_index].item_count--; 
} else {
    write(client_socket, "Product not available", 21);
}

close(client_socket);
sleep(1);  // 1 δευτερόλεπτο καθυστέρησης
int client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket < 0) {
    perror("Socket creation failed");
    exit(1);
}

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(12345);  
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    exit(1);
}
int product_index = rand() % 20;  
write(client_socket, &product_index, sizeof(int));
char response[256];
read(client_socket, response, sizeof(response));
printf("Server response: %s\n", response);

for (int i = 0; i < 5; i++) {
    pid_t pid = fork();
    if (pid == 0) {
        // Κώδικας πελάτη
        for (int j = 0; j < 10; j++) {
            // Στείλτε παραγγελία και περιμένετε απάντηση
            sleep(1);  // Αναμονή 1 δευτερολέπτου μεταξύ παραγγελιών
        }
        exit(0);
    }
}
