///////////////////////////////////////////////////////////////////////////
//
//      Header File Inclusion
//
///////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

///////////////////////////////////////////////////////////////////////////
//
//      User Define Macros
//
///////////////////////////////////////////////////////////////////////////

//  Maximum File size that we allowed in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

///////////////////////////////////////////////////////////////////////////
//
//     User Defiend Structures
//
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :       BootBlock
//  Description     :       Holds the information to boot the Operating  System
//
///////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Informathion[100];
};

///////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :       SuperInode
//  Description     :       Holds the information about the file System
//
///////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int ToatalInode;
    int FreeInode;
};

///////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :       Inode
//  Description     :       Holds the information about the file 
//
///////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode* PINODE;
typedef struct Inode** PPINODE;

///////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :       FileTable
//  Description     :       Holds the information about Opened File
//
///////////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

///////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :       UAREA
//  Description     :       Holds the information about process file
//
///////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

///////////////////////////////////////////////////////////////////////////////////
//
//  Globale Veriables of Objects used in the project
//
///////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   InitaliseUAREA
//  Description     :   It is used to initialise UAREA members
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;
    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Marvellous CVFS : UAREA gets initialise succesfully\n");
}


///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   InitialiseSuperBlock
//  Description     :   It is used to initialise Super block members
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.ToatalInode = MAXINODE;
    superobj.FreeInode = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialise succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   CreateDILB
//  Description     :   It is used to create Linked List of Inodes
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 0;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE) malloc(sizeof(INODE));

        strcpy(newn->FileName, "\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)        // LL is Empty
        {
            head = newn;
            temp = head;
        }
        else                    //LL contains atleast 1 Node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Marvellous CVFS : DILB created succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   StartAuxillaryDataInitialisation
//  Description     :   It is use to call at such function which are use to initialise 
//                      Auxillary Data
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Informathion, "Booting process of Marvellous CVFS is Done.");

    printf("%s\n", bootobj.Informathion);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary Data Initialise Succesfully\n");
}

///////////////////////////////////////////////////////////////////////////
//
//      Entry Point Function of the Project
//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   DisplayHelp
//  Description     :   It is use to Display the Help Page
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("----------------------------------------------------------\n");
    printf("----------------Marvellous CVFS Help Page-----------------\n");
    printf("----------------------------------------------------------\n");


    printf("man     :    It is use to Display Manual Page\n");
    printf("clear   :    It is used to clear the terminal\n");
    printf("creat   :    It is used to create new file\n");
    printf("wirte   :    It is used to write the into file\n");
    printf("read    :    It is used read the data from the file\n");
    printf("stat    :    It is used to display statistical information\n");
    printf("unlink  :    It is used to delete the file\n");
    printf("exit    :    It is use to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------\n");

}

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   ManPageDisplay
//  Description     :   It is use to Display the Man Page
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void ManPageDiplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man",Name) == 0)
    {
        printf("About : It is used to displayvmanual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if(strcmp("exit",Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
     else if(strcmp("clear",Name) == 0)
    {
        printf("About : It is used to c;ear the shell\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("no manual entry for %s\n",Name);
    }
}

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitialisation();

    printf("----------------------------------------------------------\n");
    printf("------------Marvellous CVFS started succesfully-----------\n");
    printf("----------------------------------------------------------\n");

    // Infinite Listening Shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s %s", Command[0], Command[1], Command[2], Command[3], Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the Resources\n");

                break;
            }
            else if(strcmp("ls",Command[0]) == 0)
            {
                printf("Inside ls\n");
            }
            else if(strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }
            else if(strcmp("clear",Command[0]) == 0)
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
        }// End of Else if 1
        else if(iCount == 2)
        {
            if(strcmp("man", Command[0]) == 0)
            {
                ManPageDiplay(Command[1]);
            }
        }// End of Else if 2
        else if(iCount == 3)
        {

        }// End of Else if 3
        else if(iCount == 4)
        {

        }// End of Else if 4
        else
        {
            printf("Command Not Found\n");
            printf("Please refer help option to get more information\n");
        }//End of Else

    }//End of While Loop

    return 0;
}// End of Main