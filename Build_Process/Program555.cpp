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
//      User Define Macros for error handdling
//
///////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

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
    char Information[100];
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
    int FreeInodes;
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
typedef FileTable* PFILETABLE;

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
    superobj.FreeInodes = MAXINODE;

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
        newn = (PINODE)malloc(sizeof(INODE));

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
    strcpy(bootobj.Information, "Booting process of Marvellous CVFS is Done.");

    printf("%s\n", bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary Data Initialise Succesfully\n");
}

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
    printf("-----------------------------------------------------------\n");
    printf("---------------- Marvellous CVFS Help Page ----------------\n");
    printf("-----------------------------------------------------------\n");


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
        printf("About : It is used to display manual page\n");
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
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("no manual entry for %s\n",Name);
    }
}

//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   IsFileExist
//  Description     :   It is use to check wheter file is already existvor not
//  Input           :   It accept file name
//  Output          :   It return the true or false
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   16/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
                    char *name      // File name
               )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }
    return bFlag;
}


//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   CreateFile
//  Description     :   It is use to create new regular file
//  Input           :   It accept file name and permission
//  Output          :   It return the file descriptor
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   16/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,         //  name of new file
                    int permission      //  permission for that file
               )
{
    PINODE temp = head;
    int i = 0;

    printf("Total Number of inodes remainig : %d\n",superobj.FreeInodes);

    // if name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the inodes are Full.
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // If file is already exist
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("There is no inode\n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT entry
    // Note : 0,1,2 are Reserved
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is full
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise File table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect file table with inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;
    
    // Allocate memory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    superobj.FreeInodes--;
    
    return i;       // File descriptor
}

//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   LsFile
//  Description     :   It is use to list all files
//  Input           :   Nothing
//  Output          :   Nothing
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   16/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

void LsFile()
{
    PINODE temp = head;

    printf("----------------------------------------------------------\n");
    printf("-------------Marvellous CVFS Files Information------------\n");
    printf("----------------------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp-> FileType != 0)
        {
           printf("%d\t%s\t%d\n",temp->InodeNumber, temp->FileName, temp->ActualFileSize);
        }
        temp = temp->next;
    }

    printf("----------------------------------------------------------\n");
}

//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   UnlinkFile
//  Description     :   It is use to delete the file
//  Input           :   File Name
//  Output          :   Nothing
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   22/01/2026
//
///////////////////////////////////////////////////////////////////////////////////


int UnlinkFile(
                char *name
               )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExist(name) == false)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    //Travel the UFDT
    for(i = 0; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName,name) == 0)
            {
                // Deallocate memory of Buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer = NULL;

                //Reset All Values of inode
                //Dont deallocate memory of inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                
                memset(uareaobj.UFDT[i]->ptrinode->FileName, '\0', sizeof(uareaobj.UFDT[i]->ptrinode->FileName));

                // Deallocate memory of File_Table
                free(uareaobj.UFDT[i]);

                // set NULL to UFDT 
                uareaobj.UFDT[i] = NULL;

                // Increment Freeinodes count
                superobj.FreeInodes++;
                
                break;
            }   // End of if
        }       // End of if
    }           // End of For
    return EXECUTE_SUCCESS;

}               // End of Function


//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   WriteFile
//  Description     :   It is use to Write the Data into the file
//  Input           :   File Descriptor
//                      Address of Buffer whitch contain data
//                      Size of Data that we want to write
//  Output          :   Number of bytes succesfully return
//  Author          :   Satyajeet Manohar Ghule
//  Date            :   22/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

int WriteFile(
                int fd,
                char *data,
                int size
              )
{
    printf("File descriptor : %d\n", fd);
    printf("Data that we want to erite : %s\n",data);
    printf("Number of bytes that we wants to write : %d\n",size);

    //Invalid FD
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Fd points to NULL
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // There is no permission to write
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficient Space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    //Write the Data into the file
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset, data, size);

    // Update the write of set
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size; 

    // Upadate the actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}


///////////////////////////////////////////////////////////////////////////
//
//      Entry Point Function of the Project
//
///////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    char InputBuffer[MAXFILESIZE] = {'\0'};

    int iCount = 0;
    int iRet = 0;

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
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated Resources\n");

                break;
            }
            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                LsFile();
            }
            // Marvellous CVFS : > help
            else if(strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
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
            // Marvellous CVFS : > man ls
            if(strcmp("man", Command[0]) == 0)
            {
                ManPageDiplay(Command[1]);
            }
            // Marvellous CVFS : > unlink Demo.txt
            if(strcmp("unlink", Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error :  Invalid Parameter\n");
                }

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to delete as there is no such file\n");
                }

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("File gets Succesfully Deleted\n");
                }
            }
            // Marvellous CVFS : > Write 2
            else if(strcmp("write",Command[0]) == 0)
            {
                printf("Enter the data that you want to write : \n");
                fgets(InputBuffer, MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]), InputBuffer,strlen(InputBuffer)-1);
            }
            if(iRet == ERR_INVALID_PARAMETER)
            {
                printf("Error : Invalid Parameter\n");
            }
            else if(iRet == ERR_FILE_NOT_EXIST)
            {
                printf("Error : There is no such file\n");
            }
            else if(iRet == ERR_PERMISSION_DENIED)
            {
                printf("Error : Unable to writw as there is no permission.\n");
            }
            else if(iRet == ERR_INSUFFICIENT_SPACE)
            {
                printf("Error : Unable to write as there is no space\n");
            }
            else
            {
                printf("There is no such command\n");
            }
        }// End of Else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat Ganesh.txt 3
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create the file as parameters are invalid\n");
                    printf("Please refer man page\n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no inode\n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file becouse the file is already present\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file\n");
                    printf("Max opened files limit reached\n");
                }

                printf("File gets succesfully created with FD  %d\n",iRet);
            }
            else
            {
                printf("There is No such Command.\n");
            }
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