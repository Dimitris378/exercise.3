# Ονόματα των αρχείων πηγαίου κώδικα
SRC = server.c client.c
# Ονόματα των αρχείων αντικειμένων
OBJ = server.o client.o
# Όνομα εκτελέσιμου αρχείου για τον server και τον client
EXEC_SERVER = server
EXEC_CLIENT = client

# Ορισμός του compiler
CC = gcc
CFLAGS = -Wall -g  # Ενεργοποίηση όλων των προειδοποιήσεων και debugging symbols

# Κανόνας για την κατασκευή του server
$(EXEC_SERVER): server.o
	$(CC) -o $(EXEC_SERVER) server.o $(CFLAGS)

# Κανόνας για την κατασκευή του client
$(EXEC_CLIENT): client.o
	$(CC) -o $(EXEC_CLIENT) client.o $(CFLAGS)

# Κανόνας για την κατασκευή των αντικειμένων από τα αρχεία πηγαίου κώδικα
server.o: server.c
	$(CC) -c server.c $(CFLAGS)

client.o: client.c
	$(CC) -c client.c $(CFLAGS)

# Καθαρισμός των αντικειμένων και εκτελέσιμων αρχείων
clean:
	rm -f $(OBJ) $(EXEC_SERVER) $(EXEC_CLIENT)

# Ειδικός κανόνας για το πρόγραμμα
all: $(EXEC_SERVER) $(EXEC_CLIENT)
