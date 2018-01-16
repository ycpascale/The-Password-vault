#include "func.h"
#include "HashTableAPI.h"


#define SIZE 100
#define LEN 30

int main(int argc, char* argv[])
{
   FILE *inFile = NULL;

   masterData tempData;
   masterData fileData;
   vaultData *data;
   vaultData *tempVaultData;
   char action = 'S';
   int systemCount = 0;
   HTable * hashTab;
   char tempDescriptor[LEN];
   char tempPsw[LEN];
   int i = 0;

   initscr();
   cbreak();

   inFile = openFile(argv[1]);

   fseek(inFile, 0, SEEK_END);
   if (ftell(inFile) == 0)
   {
      printw("WELCOME TO THE PASSWORD VAULT\n\n");
      printw("Enter your log in information: \n\n");
      printw("Username: ");
      getstr(tempData.masterUsrname);
      printw("Password: ");
      noecho();
      getstr(tempData.masterPsw);
      removeTrailing(tempData.masterUsrname);
      removeTrailing(tempData.masterPsw);
      refresh();

      fseek(inFile, 0, SEEK_SET);
      fwrite(&tempData, sizeof(masterData), 1 , inFile);

   }
   else
   {
      printw("WELCOME TO THE PASSWORD VAULT\n\n");
      printw("Enter your log in information: \n\n");
      printw("Username: ");
      getstr(tempData.masterUsrname);
      printw("Password: ");
      noecho();
      getstr(tempData.masterPsw);
      removeTrailing(tempData.masterUsrname);
      removeTrailing(tempData.masterPsw);

      fseek(inFile, 0, SEEK_SET);
      fread(&fileData, sizeof(masterData), 1, inFile);

      if (strcmp(tempData.masterUsrname, fileData.masterUsrname) == 0)
      {
         if (strcmp(tempData.masterPsw, fileData.masterPsw) == 0)
         {
            printw("\n------ Username and password correct -> ACCESS ALLOWES! ------\n");
            refresh();
            getch();
         }

      }
      else if (strcmp(tempData.masterUsrname, fileData.masterUsrname) != 0)
      {
         while (strcmp(tempData.masterUsrname, fileData.masterUsrname) != 0)
         {
            if (strcmp(tempData.masterPsw, fileData.masterPsw) != 0)
            {
            printw("Sorry! Wrong username or password. Please enter again\n\n");
            printw("Enter require information:\n");
            refresh();
            echo();
            printw("Username: ");
            getstr(tempData.masterUsrname);
            printf("Password: ");
            noecho();
            getstr(tempData.masterPsw);
            removeTrailing(tempData.masterUsrname);
            removeTrailing(tempData.masterPsw);
            }
         }
      }
   }

   fseek(inFile, sizeof(masterData), SEEK_SET);
   systemCount = numOfSystems(inFile);

   /*If file contains systems of username and their passwords*/
   if (systemCount != 0)
   {
      /*calling the function readFile where it reads the data and load it in the struct*/
      data = readFile(inFile, systemCount);

      /*This part we created the hash table and load the struct in the struct*/
      hashTab = createTable(SIZE, &myHashFunction, &destroyData, &printData);

     /*Insert all the systems stored in the file into the hash table...*/
      for (i = 0; i < systemCount; i++)
      {
         insertData(hashTab, data[i].systDescriptor, (void*)&data[i]);
      }
   }
   else
   {
       hashTab = createTable(SIZE, &myHashFunction, &destroyData, &printData);
   }

   while (action !=  'Q')
   {
      clear();
      echo();
      printw("\n\n~~~~~ WELCOME TO THE PASSWORD VAULT ~~~~~\n\n");
      printw("Choose the following options:\n\n");
      printw("Press A - To add a new system\n");
      printw("Press D - To delete a system\n");
      printw("Press R - To retrieve a sytem\n");
      printw("Press U - To update an existing system\n");
      printw("Press Q - If you don't want to make any changes and to quit\n\n");

      /*Asking the user what he would like to do*/
      printw("Action:");
      action = getch();
      refresh();

       /*Option to add a new set of username and psw*/
      if (action == 'A')
      {
          /*Make it into a function*/
          clear();
          printw("\n\n~~~ Adding a new system descriptor with its password~~~\n\n");
          printw("Enter system descriptor: ");
          getstr(tempDescriptor);
          removeTrailing(tempDescriptor);
          printw("Enter password: ");
          getstr(tempPsw);
          removeTrailing(tempPsw);
          printw("New set of system descriptor and password added");
          refresh();
          getch();

          tempVaultData = malloc(sizeof(vaultData));
          strncpy(tempVaultData->systDescriptor, tempDescriptor, (strlen(tempDescriptor)+1));
          strncpy(tempVaultData->password, tempPsw, (strlen(tempPsw)+1));
          insertData(hashTab, tempVaultData->systDescriptor, (void*)tempVaultData);
          systemCount = systemCount + 1;

      }
      else if (action == 'D')
      {
         clear();
         printw("\n~~~ Deleting a new system descriptor with its password~~~\n\n");
         deleteFunc(hashTab);
         systemCount = systemCount - 1;
      }
      else if (action == 'R')
      {
         clear();
         printw("\n~~~Retrieve a system descriptor with its password~~~\n\n");
         retrieveFunc(hashTab);

      }
      else if (action == 'U')
      {
         clear();
         printf("\n~~~Updating the password for a system descriptor~~~\n");
         updateFunc(hashTab);
         refresh();

      }
      else if (action != 'Q' && action != 'A' && action != 'R' && action != 'D' && action != 'U')
      {
         printw("Incorrect action! Try again!\n\n");
      }
      refresh();
   }

    clear();
    printf("Seg fault coming!!!!\n");
    refresh();
    getch();

   if (systemCount != 0)
   {

     inFile = transferData(hashTab, systemCount, inFile);
   }

   fclose(inFile);

    endwin();


   return 0;
}
