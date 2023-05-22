/*
Una blockchain es una cadena de bloques, donde cada bloque contiene transacciones que se han realizado.
Cada transaccion posee un monto (entero), un emisor, un receptor y un identificador. Cada bloque posee un limite de transacciones.
Ademas, en este caso, cada transaccion tendra un monto maximo, las transacciones que superen ese monto
se deben dividir en transacciones mas pequeñas que no superen el monto maximo, siempre teniendo en cuenta
el limite de transacciones por bloque.

Por otro lado, tener en cuenta que se puede querer modificar el formato del emisor y receptor (ej. pasar
a minisculas, pasar a mayusculas, etc.)

Se pide implementar las estructuras y funciones necesarias para poder crear una blockchain.
La funcion se debe llamar create_blockchain() y recibe:
- senders: Un puntero a strings (punteros de tipo char) con los emisores
- receivers: Un puntero a strings (punteros de tipo char) con los receptores
- amounts: Un puntero a enteros con los montos
- transactions: La cantidad de transacciones (coincide con el largo de los arrays anteriores)
- transactions_per_block: La cantidad maxima de transacciones por bloque
- max_transaction_amount: El monto maximo por transaccion

Como identificador de una transaccion (tx) utilizar el indice de la tx en el array de transacciones.

A su vez, se debe implementar la funcion free_blockchain() que recibe la blockchain y libera toda la memoria reservada.

Consideraciones:
- Guiarse por el programa de prueba y ejemplos para ver las estructuras y sus campos/propiedades
- La blockchain no debe tener bloques vacios pero puede tener transacciones vacias (que su monto sea 0)
- La blockchain no tiene un limite de bloques y puede crecer indefinidamente
- Si el monto de una transaccion es negativo, no se debe agregar a la blockchain
- En caso de que una transaccion supere el monto maximo, se debe dividir en transacciones mas pequeñas, todas asociadas al mismo identificador
- Si se llega al limite de transacciones por bloque, se debe crear un nuevo bloque
- Utilizar typedef's para las estructuras
- Modularizar siempre que se pueda
- Utilizar los tipos de datos (ej. unsigned int, size_t, etc.) y modificadores (ej. const, static, etc.) adecuados
- Evaluar cuando se debe usar memoria dinamica, que funcion y liberar todo lo reservado (con la funcion free_blockchain())
- En caso de necesitarlo, guiarse por las estructuras provistas

Ejemplos:
- Input:
    senders: ["A", "B", "C"]
    receivers: ["D", "E", "F"]
    amounts: [100, 200, 300]
    transactions: 3
    transactions_per_block: 2
    max_transaction_amount: 150
- Output:
    blockchain (size: 3):
        - bloque 1 (size: 2, amount: 250): tx (id: 0, amount: 100, sender: A, receiver: D), tx (id: 1, amount: 150, sender: B, receiver: E)
        - bloque 2 (size: 2, amount: 200): tx (id: 1, amount: 50, sender: B, receiver: E), tx (id: 2, amount: 150, sender: C, receiver: F)
        - bloque 3 (size: 1, amount: 150): tx (id: 2, amount: 150, sender: C, receiver: F)

- Input:
    idem anterior pero con transactions_per_block: 1
- Output:
    blockchain (size: 5):
        - bloque 1 (size: 1, amount: 100): tx (id: 0, amount: 100, sender: A, receiver: D)
        - bloque 2 (size: 1, amount: 150): tx (id: 1, amount: 150, sender: B, receiver: E)
        - bloque 3 (size: 1, amount: 50): tx (id: 1, amount: 50, sender: B, receiver: E)
        - bloque 4 (size: 1, amount: 150): tx (id: 2, amount: 150, sender: C, receiver: F)
        - bloque 5 (size: 1, amount: 150): tx (id: 2, amount: 150, sender: C, receiver: F)

- Input:
    idem primer ejemplo pero con transactions_per_block: 2 y max_transaction_amount: 60
- Output:
    blockchain (size: 6):
        - bloque 1 (size: 2, amount: 100): tx (id: 0, amount: 60, sender: A, receiver: D), tx (id: 0, amount: 40, sender: A, receiver: D)
        - bloque 2 (size: 2, amount: 120): tx (id: 1, amount: 60, sender: B, receiver: E), tx (id: 1, amount: 60, sender: B, receiver: E)
        - bloque 3 (size: 2, amount: 80): tx (id: 1, amount: 60, sender: B, receiver: E), tx (id: 1, amount: 20, sender: B, receiver: E)
        - bloque 4 (size: 2, amount: 120): tx (id: 2, amount: 60, sender: C, receiver: F), tx (id: 2, amount: 60, sender: C, receiver: F)
        - bloque 5 (size: 2, amount: 120): tx (id: 2, amount: 60, sender: C, receiver: F), tx (id: 2, amount: 60, sender: C, receiver: F)
        - bloque 6 (size: 1, amount: 60): tx (id: 2, amount: 60, sender: C, receiver: F)

- Input:
    idem primer ejemplo pero con transactions_per_block: 2 y max_transaction_amount: 450
- Output:
    blockchain (size: 2):
        - bloque 1 (size: 2, amount: 300): tx (id: 0, amount: 100, sender: A, receiver: D), tx (id: 1, amount: 200, sender: B, receiver: E)
        - bloque 2 (size: 1, amount: 300): tx (id: 2, amount: 300, sender: C, receiver: F)

- Input:
    idem primer ejemplo pero amounts: [0, 4, -9]
- Output:
    blockchain (size: 1):
        - bloque 1 (size: 2, amount: 4): tx (id: 0, amount: 0, sender: A, receiver: D), tx (id: 1, amount: 4, sender: B, receiver: E)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BLOCK_SIZE 100                    // cantidad de bloque a reservar para memoria dinamica

typedef struct
{
    int id;                               // identificador de la transaccion
    int amount;                           // monto de la transaccion
    char *sender;                         // emisor de la transaccion
    char *receiver;                       // receptor de la transaccion
} S_Transaction;

typedef struct
{
    S_Transaction *transactions;          // transacciones del bloque
    unsigned int size;                    // cantidad de transacciones en el bloque
    unsigned int amount;                  // monto total de las transacciones para el bloque
} S_Block;

typedef struct
{
    S_Block *blocks;                      // bloques de la blockchain
    unsigned int transactions_per_block;  // cantidad maxima de transacciones por bloque
    unsigned int max_transaction_amount;  // monto maximo por transaccion
    unsigned int size;                    // cantidad de bloques
} S_Blockchain;

void free_blockchain(S_Blockchain *blockchain)
{
    for(int i = 0; i < blockchain->size; i++) {
        for(int j = 0; j < blockchain->blocks[i].size; j++) {
            free(blockchain->blocks[i].transactions[j].sender);
            free(blockchain->blocks[i].transactions[j].receiver);
        }
        free(blockchain->blocks[i].transactions);
    }
    free(blockchain->blocks);
    free(blockchain);
    return;
}

static void insert_into_blocks(S_Blockchain * blockchain, const int current_transaction_amount, int id, const char * sender, const char * reciever) {
    S_Transaction * current_transaction_aux = &blockchain->blocks[blockchain->size - 1].transactions[blockchain->blocks[blockchain->size -1].size];
    current_transaction_aux->id = id;
    current_transaction_aux->amount = current_transaction_amount;
    current_transaction_aux->sender = malloc((strlen(sender) + 1) * sizeof(char));
    strcpy(current_transaction_aux->sender, sender);
    current_transaction_aux->receiver = malloc((strlen(reciever) + 1) * sizeof(char));
    strcpy(current_transaction_aux->receiver, reciever);


    blockchain->blocks[blockchain->size - 1].amount += current_transaction_amount;
    blockchain->blocks[blockchain->size - 1].size++;
}

static void resize_blocks(S_Blockchain * blockchain) {
    if(blockchain->size % BLOCK_SIZE == 0) {
        blockchain->blocks = realloc(blockchain->blocks, (blockchain->size + BLOCK_SIZE) * sizeof(S_Block));
    }

    blockchain->blocks[blockchain->size].size = 0;
    blockchain->blocks[blockchain->size].amount = 0;
    blockchain->blocks[blockchain->size].transactions = malloc(blockchain->transactions_per_block * sizeof(S_Transaction));
    blockchain->size++;
}

static int need_more_blocks(S_Blockchain * blockchain) {
    return blockchain->blocks[blockchain->size - 1].size == blockchain->transactions_per_block;
}

S_Blockchain *create_blockchain(const char **senders, const char **receivers, const int *amounts, unsigned int transactions, unsigned int transactions_per_block, unsigned int max_transaction_amount)
{
    S_Blockchain * blockchain = malloc(sizeof(S_Blockchain));

    blockchain->transactions_per_block = transactions_per_block;
    blockchain->max_transaction_amount = max_transaction_amount;
    blockchain->blocks = NULL;
    blockchain->size = 0;

    for(int i = 0; i < transactions; i++) {
        if(blockchain->size == 0 || need_more_blocks(blockchain)) {
            resize_blocks(blockchain);
        }
        if(amounts[i] >= 0) {
            int remaining_amount = amounts[i];
            do {
                int current_transaction_amount = max_transaction_amount > remaining_amount ? remaining_amount: max_transaction_amount;

                insert_into_blocks(blockchain, current_transaction_amount, i, senders[i], receivers[i]);

                remaining_amount -= current_transaction_amount;
                if(remaining_amount > 0  && need_more_blocks(blockchain)) {
                    resize_blocks(blockchain);
                }
            } while(remaining_amount > 0);
        }
    }

    if(blockchain->blocks[blockchain->size - 1].size == 0) {
        free(blockchain->blocks[blockchain->size - 1].transactions);
        blockchain->size--;
    }

    if(blockchain->blocks[blockchain->size - 1].size != blockchain->transactions_per_block) {
        blockchain->blocks[blockchain->size -1].transactions = realloc(blockchain->blocks[blockchain->size -1].transactions, blockchain->blocks[blockchain->size - 1].size * sizeof(S_Transaction));
    }

    blockchain->blocks = realloc(blockchain->blocks, (blockchain->size) * sizeof(S_Block));
    return blockchain;
}

int main()
{
    S_Blockchain *blockchain;
    unsigned int transactions;
    unsigned int transactions_per_block;
    unsigned int max_transaction_amount;

    // Ejemplo 1
    const char * senders1[3] = {"A", "B", "C"};
    const char * receivers1[3] = {"D", "E", "F"};
    const int amounts1[3] = {100, 200, 300};
    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 150;

    blockchain = create_blockchain(senders1, receivers1, amounts1, transactions, transactions_per_block, max_transaction_amount);

    assert(blockchain->size == 3);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 150);

    assert(blockchain->blocks[0].size == 2);
    assert(blockchain->blocks[0].amount == 250);

    assert(blockchain->blocks[0].transactions[0].id == 0);
    assert(blockchain->blocks[0].transactions[0].amount == 100);
    assert(strcmp(blockchain->blocks[0].transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks[0].transactions[1].id == 1);
    assert(blockchain->blocks[0].transactions[1].amount == 150);
    assert(strcmp(blockchain->blocks[0].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[1].size == 2);
    assert(blockchain->blocks[1].amount == 200);

    assert(blockchain->blocks[1].transactions[0].id == 1);
    assert(blockchain->blocks[1].transactions[0].amount == 50);
    assert(strcmp(blockchain->blocks[1].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[0].receiver, "E") == 0);


    assert(blockchain->blocks[1].transactions[1].id == 2);
    assert(blockchain->blocks[1].transactions[1].amount == 150);
    assert(strcmp(blockchain->blocks[1].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[2].size == 1);
    assert(blockchain->blocks[2].amount == 150);

    assert(blockchain->blocks[2].transactions[0].id == 2);
    assert(blockchain->blocks[2].transactions[0].amount == 150);
    assert(strcmp(blockchain->blocks[2].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[0].receiver, "F") == 0);

    free_blockchain(blockchain);

    // Ejemplo 3
    const char *senders3[3] = {"A", "B", "C"};
    const char *receivers3[3] = {"D", "E", "F"};
    const int amounts3[3] = {100, 200, 300};
    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 60;

    blockchain = create_blockchain(senders3, receivers3, amounts3, transactions, transactions_per_block, max_transaction_amount);
    assert(blockchain->size == 6);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 60);

    assert(blockchain->blocks[0].size == 2);
    assert(blockchain->blocks[0].amount == 100);

    assert(blockchain->blocks[0].transactions[0].id == 0);
    assert(blockchain->blocks[0].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[0].transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks[0].transactions[1].id == 0);
    assert(blockchain->blocks[0].transactions[1].amount == 40);
    assert(strcmp(blockchain->blocks[0].transactions[1].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[1].receiver, "D") == 0);

    assert(blockchain->blocks[1].size == 2);
    assert(blockchain->blocks[1].amount == 120);

    assert(blockchain->blocks[1].transactions[0].id == 1);
    assert(blockchain->blocks[1].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[1].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[0].receiver, "E") == 0);


    assert(blockchain->blocks[1].transactions[1].id == 1);
    assert(blockchain->blocks[1].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[1].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[2].size == 2);
    assert(blockchain->blocks[2].amount == 80);

    assert(blockchain->blocks[2].transactions[0].id == 1);
    assert(blockchain->blocks[2].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[2].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[0].receiver, "E") == 0);

    assert(blockchain->blocks[2].transactions[1].id == 1);
    assert(blockchain->blocks[2].transactions[1].amount == 20);
    assert(strcmp(blockchain->blocks[2].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[3].size == 2);
    assert(blockchain->blocks[3].amount == 120);

    assert(blockchain->blocks[3].transactions[0].id == 2);
    assert(blockchain->blocks[3].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[3].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[3].transactions[0].receiver, "F") == 0);

    assert(blockchain->blocks[3].transactions[1].id == 2);
    assert(blockchain->blocks[3].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[3].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[3].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[4].size == 2);
    assert(blockchain->blocks[4].amount == 120);

    assert(blockchain->blocks[4].transactions[0].id == 2);
    assert(blockchain->blocks[4].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[4].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[4].transactions[0].receiver, "F") == 0);

    assert(blockchain->blocks[4].transactions[1].id == 2);
    assert(blockchain->blocks[4].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[4].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[4].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[5].size == 1);
    assert(blockchain->blocks[5].amount == 60);

    assert(blockchain->blocks[5].transactions[0].id == 2);
    assert(blockchain->blocks[5].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[5].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[5].transactions[0].receiver, "F") == 0);

    free_blockchain(blockchain);

    // Ejemplo 5
    const char *senders5[3] = {"A", "B", "C"};
    const char *receivers5[3] = {"D", "E", "F"};
    const int amounts5[3] = {0, 4, -9};

    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 150;

    blockchain = create_blockchain(senders5, receivers5, amounts5, transactions, transactions_per_block, max_transaction_amount);
    assert(blockchain->size == 1);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 150);

    assert(blockchain->blocks->size == 2);
    assert(blockchain->blocks->amount == 4);

    assert(blockchain->blocks->transactions[0].id == 0);
    assert(blockchain->blocks->transactions[0].amount == 0);
    assert(strcmp(blockchain->blocks->transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks->transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks->transactions[1].id == 1);
    assert(blockchain->blocks->transactions[1].amount == 4);
    assert(strcmp(blockchain->blocks->transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks->transactions[1].receiver, "E") == 0);

    free_blockchain(blockchain);

    puts("OK!");
    return 0;
}
