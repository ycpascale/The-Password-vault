#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"
#include <ncurses.h>

#define LEN 30

/**
*Vault data structure
**/
typedef struct vaultData
{
   char systDescriptor[30];
   char password[30];
}vaultData;

/**
*Master data structure
**/

typedef struct masterData
{
   char masterUsrname[30];
   char masterPsw[30];
}masterData;

/** Function which hashes the key to produce an index
*@return an integer
*@param size size of the hash table
*@param key which represents the alphanumeric string
**/
int myHashFunction(size_t tableSize, char* key);

/** Function to destroy and free data
*@param data pointer to a generic data that is to be freed
**/
void destroyData(void *data);

/** Function to print the data
*@param data pointer to a generic data that is to be printed
**/
void printData(void *toBePrinted);

/**Function to remove the null terminated
*@param string that may contains  the null terminated
**/
void removeTrailing(char * buf);

/**Function to open file for writing and reading
*@param string which is obtained from the commmand line
**/
FILE *openFile(char *fileName);

/**Function which counts the number of systems in the fileName
*@return integer which represents number of systems
*@param file pointer to a file to be read
**/
int numOfSystems(FILE* fptr);

/*Function which reads the file and store the data in the struct
@return a struct which contains the data which were in the file
*@param file pointer to the file to be used
*@param count integer that represents the number of systems
**/
vaultData *readFile(FILE* fptr, int count);

/**Function to update the password of one systems
*@pre Hash table must exist and have memory allocated to it
*@param hashtable pointer to hash table containing nodes
**/
void updateFunc(HTable *hashTabUpdate);

/**Function to retrieve the password  and system descriptorof one systems
*@pre Hash table must exist and have memory allocated to it
*@param hashtable pointer to hash table containing nodes
**/
void retrieveFunc(HTable *hashTabRet);

/**Function to delete the password and system descriptor of one systems
*@pre Hash table must exist and have memory allocated to it
*@param hashtable pointer to hash table containing nodes
**/
void deleteFunc(HTable *hashtabDel);

/**Function to update the password of one systems
*@pre Hash table must exist and have memory allocated to it
*@param hashtable pointer to hash table containing nodes
**/

FILE *transferData(HTable *hashT, int count, FILE *fptr);
