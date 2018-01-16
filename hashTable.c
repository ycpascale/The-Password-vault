#include "HashTableAPI.h"


Node *createNode(char* key, void* data)
{
    Node *newNode;

    newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    strcpy(newNode->key, key);
    newNode->data = data;

    return newNode;
}
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char* key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    HTable *newHtable;

    newHtable = malloc(sizeof(HTable));
    newHtable->table = malloc(sizeof(Node));
    newHtable->hashFunction = hashFunction;
    newHtable->destroyData = destroyData;
    newHtable->printData = printData;
    newHtable->size = size;

    return newHtable;

}

void destroyTable (HTable *hashTable)
{
    int i = 0;
    Node *tempNode;
    Node *deleteNode;

   if (hashTable == NULL)
   {
     return;
   }
   for (i= 0; i < hashTable->size; i++)
   {
       tempNode = hashTable->table[i];

       while (tempNode != NULL)
       {
           deleteNode = tempNode;
           tempNode = tempNode->next;
           hashTable->destroyData(deleteNode);
           free(deleteNode);
       }
   }

      free(hashTable->table);
      free(hashTable);

}
/* NOT DONEEE */

void insertData (HTable *hashTable, char* key, void *data)
{
    int index = 0;
    Node *tempNode;
    Node *newNode;

    if (hashTable != NULL)
    {
        newNode = createNode(key, data);

        index = hashTable->hashFunction(hashTable->size, key);

        if (hashTable->table[index] != NULL)
        {
           tempNode = hashTable->table[index];

           while (tempNode->next != NULL && (strcmp(tempNode->key,key) != 0))
           {
              tempNode = tempNode->next;
           }

           if (strcmp(tempNode->key, key) == 0)
           {
              tempNode->data = data;
           }
           else
           {
              tempNode->next = newNode;
           }
        }
        /*met head*/
        else
        {
              hashTable->table[index] = newNode;
        }
     }
}

void removeData(HTable *hashTable, char* key)
{
   int index = 0;
   Node *theNode;
   Node *prevNode;

   if (hashTable != NULL)
   {
      index = hashTable->hashFunction(hashTable->size, key);


   if (hashTable->table[index] != NULL)
   {
       theNode = hashTable->table[index];
       prevNode = NULL;

       while (strcmp(theNode->key, key) != 0)
       {
          prevNode = theNode;
          theNode = theNode->next;
       }

       if (strcmp(theNode->key,key) == 0)
       {
          if (prevNode == NULL)
          {
             hashTable->table[index] = theNode->next;
             hashTable->destroyData(theNode->data);
            /* free(theNode);*/
          }
          else
          {
             prevNode->next = theNode->next;
             hashTable->destroyData(theNode->data);
            /* free(theNode);*/
          }
       }
   }
 }
}

void *lookupData(HTable *hashTable, char* key)
{
   int index = 0;
   Node *tempNode;

   if (hashTable != NULL)
   {
      index = hashTable->hashFunction(hashTable->size, key);

      if (hashTable->table[index] == NULL)
      {
         return NULL;
      }

      tempNode = hashTable->table[index];

      while (tempNode != NULL)
      {
         if (strcmp(tempNode->key,key) == 0)
         {
            return (tempNode->data);
         }
         tempNode = tempNode->next;
      }

   }
   return NULL;
}
