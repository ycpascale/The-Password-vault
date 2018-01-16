#include "func.h"

int myHashFunction(size_t tableSize, char* key)
{
   char tempStr[8];
   int i = 0;
   int sum = 0;

   strncpy(tempStr, key, 4);

   for (i= 0; i < 4; i++)
   {
       sum = sum + tempStr[i];
   }

   return (sum % (int)tableSize);
}

void destroyData(void *data)
{
  /* free(((vaultData*)data)->systDescriptor);
   free(((vaultData*)data)->password);*/
   free((vaultData*)data);
}

void printData(void *toBePrinted)
{
   vaultData * toPrint;

   if (toBePrinted != NULL)
   {
      toPrint = (vaultData*)toBePrinted;
      mvprintw(15, 0, "System descriptor: %s , Password: %s\n", toPrint->systDescriptor, toPrint->password);
      refresh();
      getch();
   }
   else
   {
      printw("Hash table was created and all parameter were set properly. Hash table is empty\n");
   }
}

void removeTrailing(char * buf)
{
   if (buf[strlen(buf) -1] == '\n')
   {
      buf[strlen(buf) - 1] = '\0';
   }
}

FILE *openFile(char *fileName)
{
   FILE* tempFile;

   tempFile = fopen(fileName, "ab+");

   if (tempFile == NULL)
   {
      tempFile = fopen("vault.db", "wb+");
   }

   return tempFile;
}

int numOfSystems(FILE* fptr)
{
   vaultData nSystems[100];
   int count = 0;
   int end = 0;
   int afterMasterData = 0;
   int i = 0;

   fseek(fptr, sizeof(masterData), SEEK_SET);
   afterMasterData = ftell(fptr);
   fseek(fptr, 0, SEEK_END);
   end = ftell(fptr);

   if (afterMasterData != end)
   {
      fseek(fptr, sizeof(masterData), SEEK_SET);
      while (count != end)
      {
         fread(&nSystems[i], sizeof(vaultData), 1, fptr);
         i++;
         count = ftell(fptr);
      }
      return i;
   }
   else
   {
      return 0;
   }
}

vaultData *readFile(FILE* fptr, int count)
{
   vaultData *tempData;
   int i = 0;

   tempData = malloc(sizeof(vaultData) * count);
   fseek(fptr, 0, SEEK_SET);

   for (i = 0; i < count; i++)
   {
      fread(&tempData[i], sizeof(vaultData), 1, fptr);
   }

   return tempData;
}

void deleteFunc(HTable *hashTabDel)
{
   char tempDescriptor[LEN];
   vaultData *tempGetData;

   printw("Enter system descriptor: ");
   getstr(tempDescriptor);
   removeTrailing(tempDescriptor);

   tempGetData = (vaultData*)lookupData(hashTabDel, tempDescriptor);
   if (tempGetData != NULL)
   {
      removeData(hashTabDel, tempDescriptor);
      printw("\n\nDeletion successful!");
      refresh();
      getch();
   }
   else
   {
      printw("\n\nSorry! The system descriptor cannot be found. Please try again!\n\n");
      refresh();
      getch();
      deleteFunc(hashTabDel);
   }

}

void retrieveFunc(HTable *hashTabRet)
{
   char tempDescriptor[LEN];
   vaultData *tempGetData;

   printw("Enter system descriptor to retrieve: ");
   getstr(tempDescriptor);
   removeTrailing(tempDescriptor);

   tempGetData = (vaultData*)lookupData(hashTabRet, tempDescriptor);
   if (tempGetData != NULL)
   {
      printw("\n");
      hashTabRet->printData((void*)tempGetData);
   }
   else
   {
      printw("\n\nSorry! This system descriptor cannot be found. Try again!\n\n");
      refresh();
      getch();
      retrieveFunc(hashTabRet);
   }
}

void updateFunc(HTable *hashTabUpdate)
{
   char tempDescriptor[LEN];
   char tempPsw[LEN];
   vaultData *tempGetData;

   printw("Enter the system descriptor which you want to change the password: ");
   getstr(tempDescriptor);
   removeTrailing(tempDescriptor);
   tempGetData = (vaultData*)lookupData(hashTabUpdate, tempDescriptor);
   if (tempGetData != NULL)
   {
    /*  printw("\nThis is the system descriptor for which you want to make changes!\n");
      hashTabUpdate->printData((void*)tempGetData);*/

      printw("Enter the new password: ");
      getstr(tempPsw);
      removeTrailing(tempPsw);

      removeData(hashTabUpdate, tempDescriptor);

      tempGetData = malloc(sizeof(vaultData));
      strncpy(tempGetData->systDescriptor, tempDescriptor, (strlen(tempDescriptor)+1));
      strncpy(tempGetData->password, tempPsw, (strlen(tempPsw)+1));
      insertData(hashTabUpdate, tempGetData->systDescriptor, (void*)tempGetData);

      tempGetData = (vaultData*)lookupData(hashTabUpdate, tempDescriptor);
      if (tempGetData != NULL)
      {
         printw("\n\nUpdated data\n");
         hashTabUpdate->printData((void*)tempGetData);
       }

       printw("\n\nSystem successfully updated\n");
       refresh();
       getch();

    }
    else
    {
       printw("\n\nSorry, this system descriptor cannot be found. Try again\n\n");
       refresh();
       getch();
       updateFunc(hashTabUpdate);
    }
}

FILE *transferData(HTable *hashT, int count, FILE* fptr)
{
   Node *tempNode;
   int i = 0;
   vaultData *temp;

   fseek(fptr, 0, SEEK_SET);

   for (i = 0; i < hashT->size; i++)
   {
      tempNode = hashT->table[i];

      while (tempNode != NULL)
      {
         temp = (vaultData*)lookupData(hashT, tempNode->key);
         mvprintw(15, 0, "zafr is %s %s", temp->systDescriptor, temp->password);
        // fwrite(&temp, sizeof(vaultData), 1, fptr);
         tempNode = tempNode->next;
      }
   }
   return fptr;
}
