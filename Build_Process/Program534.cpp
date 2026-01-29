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
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

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
//  Function Name   :   InitialiseSuperBlock
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

int main()
{
    char str[80] = {'\0'};
    char Command[4][20];
    int iCount = 0;

    StartAuxillaryDataInitialisation();

    printf("----------------------------------------------------------\n");
    printf("------------Marvellous CVFS started succesfully-----------\n");
    printf("----------------------------------------------------------\n");

    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\n Marvellous CVFS >");
        fgets(str,sizeof(str),stdin);
        //scanf("%s", str);
        
    }

    return 0;
}