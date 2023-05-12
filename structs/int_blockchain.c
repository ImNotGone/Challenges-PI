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
- La blockchain no debe tener bloques vacios pero puede tener transacciones vacias (que su monto sea 0)
- La blockchain no tiene un limite de bloques y puede crecer indefinidamente
- Si el monto de una transaccion es negativo, no se debe agregar a la blockchain
- En caso de que una transaccion supere el monto maximo, se debe dividir en transacciones mas pequeñas, todas asociadas al mismo identificador
- Si se llega al limite de transacciones por bloque, se debe crear un nuevo bloque
- Utilizar typedef's para las estructuras
- Modularizar siempre que se pueda
- Utilizar los tipos de datos (ej. unsigned int, size_t, etc.) y modificadores (ej. const, static, etc.) adecuados
- Evaluar cuando se debe usar memoria dinamica, que funcion y liberar todo lo reservado (con la funcion free_blockchain())

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
    blockchain (size: 5):
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

#define BLOCK_SIZE 100

/* DEJAR LAS ESTRUCTURAS A MODO DE APOYO */
typedef struct
{
    int id;
    int amount;
    char *sender;
    char *receiver;
} S_Transaction;

typedef struct
{
    S_Transaction *transactions;
    unsigned int size;
    unsigned int amount;
} S_Block;

typedef struct
{
    S_Block *blocks;
    unsigned int transactions_per_block;
    unsigned int max_transaction_amount;
    unsigned int size;
} S_Blockchain;

/* ESTO LO TIENEN QUE IMPLEMENTAR ELLOS */
void free_blockchain(S_Blockchain *blockchain)
{
    // liberar cada bloque
    for (unsigned int i = 0; i < blockchain->size; i++)
    {
        for (unsigned int j = 0; j < blockchain->blocks[i].size; j++)
        {
            free(blockchain->blocks[i].transactions[j].sender);
            free(blockchain->blocks[i].transactions[j].receiver);
        }
        free(blockchain->blocks[i].transactions);
    }

    // liberar los bloques y la blockchain
    free(blockchain->blocks);
    free(blockchain);
}

static S_Transaction create_transaction(int id, int amount, const char *sender, const char *receiver)
{
    S_Transaction tx = {.id = id, .amount = amount};
    tx.sender = malloc(strlen(sender) + 1);
    strcpy(tx.sender, sender);

    tx.receiver = malloc(strlen(receiver) + 1);
    strcpy(tx.receiver, receiver);

    return tx;
}

static S_Block create_block(unsigned int transactions_per_block)
{
    S_Block block = {.size = 0, .amount = 0};
    block.transactions = calloc(transactions_per_block, sizeof(S_Transaction));
    return block;
}

static char reached_current_block_limits(S_Blockchain *blockchain)
{
    return blockchain->blocks[blockchain->size - 1].size == blockchain->transactions_per_block;
}

static void expand_blockchain(S_Blockchain *blockchain)
{
    // agregar mas espacio a la blockchain si es necesario
    if (blockchain->size % BLOCK_SIZE == 0)
    {
        blockchain->blocks = realloc(blockchain->blocks, (blockchain->size + BLOCK_SIZE) * sizeof(S_Block));
    }

    // inicializar el nuevo bloque
    blockchain->blocks[blockchain->size] = create_block(blockchain->transactions_per_block);
    blockchain->size++;
}

S_Blockchain *create_blockchain(const char **senders, const char **receivers, const int *amounts, unsigned int transactions, unsigned int transactions_per_block, unsigned int max_transaction_amount)
{
    // crear la blockchain base
    S_Blockchain *blockchain = calloc(1, sizeof(S_Blockchain));
    blockchain->transactions_per_block = transactions_per_block;
    blockchain->max_transaction_amount = max_transaction_amount;

    // iterar por cada transaccion
    for (unsigned int i = 0; i < transactions; i++)
    {
        // si estoy en el principio o se llego a los limites dentro del bloque actual, expandir
        if (blockchain->size == 0 || reached_current_block_limits(blockchain))
        {
            expand_blockchain(blockchain);
        }

        // insertar la tx en la blockchain solo si el monto es valido
        if (amounts[i] >= 0)
        {
            int remaining_amount = amounts[i];
            do
            {
                // obtener el monto de la tx
                int amount = remaining_amount > blockchain->max_transaction_amount ? blockchain->max_transaction_amount : remaining_amount;
                remaining_amount -= amount;

                // crear la tx
                blockchain->blocks[blockchain->size - 1].transactions[blockchain->blocks[blockchain->size - 1].size] = create_transaction(i, amount, senders[i], receivers[i]);
                blockchain->blocks[blockchain->size - 1].size++;
                blockchain->blocks[blockchain->size - 1].amount += amount;

                /*
                ------------------------------ UNA ALTERNATIVA ------------------------------
                  S_Block *current_block = &blockchain->blocks[blockchain->size - 1];
                  current_block->transactions[current_block->size] = create_transaction(i, amount, senders[i], receivers[i]);
                  current_block->size++;
                  current_block->amount += amount;
                -----------------------------------------------------------------------------
                */

                // si se llego a los limites dentro del bloque actual y aun queda monto, expandir
                if (remaining_amount > 0 && reached_current_block_limits(blockchain))
                {
                    expand_blockchain(blockchain);
                }
            } while (remaining_amount > 0);
        }
    }

    /* 
        verificar si el ultimo bloque esta vacio (se pudo haber creado por el expand_blockchain() de 
            if (blockchain->size == 0 || reached_current_block_limits(blockchain))
    */
    if (blockchain->blocks[blockchain->size - 1].size == 0)
    {
        free(blockchain->blocks[blockchain->size - 1].transactions);
        blockchain->size--;
    }

    // reallocar el ultimo bloque para que no queden transacciones vacias
    blockchain->blocks[blockchain->size - 1].transactions = realloc(blockchain->blocks[blockchain->size - 1].transactions, blockchain->blocks[blockchain->size - 1].size * sizeof(S_Transaction));

    // reallocar los bloques para que no queden espacios vacios
    blockchain->blocks = realloc(blockchain->blocks, blockchain->size * sizeof(S_Block));

    return blockchain;
}

int main()
{
    const char *senders[3] = {"A", "B", "C"};
    const char *receivers[3] = {"D", "E", "F"};
    const int amounts[3] = {0, 4, -9};
    unsigned int transactions = 3;
    unsigned int transactions_per_block = 2;
    unsigned int max_transaction_amount = 150;

    S_Blockchain *blockchain = create_blockchain(senders, receivers, amounts, transactions, transactions_per_block, max_transaction_amount);

    printf("blockchain (size: %d):\n", blockchain->size);
    for (unsigned int i = 0; i < blockchain->size; i++)
    {
        printf("\t- bloque %d (size: %d, amount: %d): ", i + 1, blockchain->blocks[i].size, blockchain->blocks[i].amount);
        for (unsigned int j = 0; j < blockchain->blocks[i].size; j++)
        {
            printf("tx (id: %d, amount: %d, sender: %s, receiver: %s), ", blockchain->blocks[i].transactions[j].id, blockchain->blocks[i].transactions[j].amount, blockchain->blocks[i].transactions[j].sender, blockchain->blocks[i].transactions[j].receiver);
        }
        printf("\n");
    }

    free_blockchain(blockchain);

    return 0;
}