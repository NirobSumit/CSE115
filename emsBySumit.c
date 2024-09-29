#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h> // Added for getch
#include <ctype.h> // Added for strcasecmp

#define Employee struct emp

void about();
void logo();
void welcome();
void printChar(char ch, int n);
void printHead();
void add(FILE *fp);
FILE *del(FILE *fp);
void modify(FILE *fp);
void displayList(FILE *fp);
void searchRecord(FILE *fp);
void maleemp(FILE *fp);
void femaleemp(FILE *fp);
void frmdhaka(FILE *fp);
void frmors(FILE *fp);
void displaybasic(FILE *fp);
void basiccontact(FILE *fp);
void mainbr(FILE *fp);
void otherbr(FILE *fp);

struct emp
{
    int id;
    char name[100];
    char desgn[10];
    float sal;
    char gender[10];
    char branch[50];
    char psaddr[200];
    char prtaddr[200];
    char phone[15];
    char mail[20];
};

int getch() // Implementation of getch for macOS
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main()
{
    FILE *fp;
    Employee e;
    int option;
    char another;

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL)
    {
        if ((fp = fopen("employeeInfo.txt", "wb+")) == NULL)
        {
            printf("can't open file");
            return 0;
        }
    }
    char username[20], password[20];
    printHead();
    welcome();
login:

    printHead();
    printf("\n\n\n");
    printf("\n            Welcome to\n");
    printf("\nEmployee Management System (EMS) Portal\n");
    printf("\n   Please, Enter Your Login Information.");
    printf("\n\n          ----------");
    printf("\n\n");
    printf("\n\nUsername: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);


    if (((strcasecmp(username, "admin")) == 0) && ((strcasecmp(password, "pass") == 0)))
    {
        while (1)
        {
        menu:

            printHead();
            printf("\n\n");
            printf("\n    Main Menu\n");
            printf("---------------\n");
            printf("\n");

            printf("\n01. Add Employee");
            printf("\n02. Delete Employee");
            printf("\n03. Modify Employee");
            printf("\n04. Display Employee List");
            printf("\n05. Search Record");
            printf("\n06. Display Basic Info");

            printf("\n07. Display Basic Contact Info");
            printf("\n08. List of Male Employee");
            printf("\n09. List of Female Employee");
            printf("\n10. List of Employee from Dhaka");
            printf("\n11. List of Employee from Others District");
            printf("\n12. List of Employee of Main Branch");
            printf("\n13. List of Employee of Others Branch");
            printf("\n14. About");
            printf("\n00. EXIT");

            printf("\n\n\nEnter Your Option :--> ");
            scanf("%d", &option);
            
            switch (option)
            {
            case 0:
                exit(0);
                break;
            case 1:
                add(fp);
                break;
            case 2:
                fp = del(fp);
                break;
            case 3:
                modify(fp);
                break;
            case 4:
                displayList(fp);
                break;
            case 5:
                searchRecord(fp);
                break;
            case 6:
                displaybasic(fp);
                break; 
            case 7:
                basiccontact(fp);
                break;
            case 8:
                maleemp(fp);
                break;
            case 9:
                femaleemp(fp);
                break;
            case 10:
                frmdhaka(fp);
                break;
            case 11:
                frmors(fp);
                break;
            case 12:
                mainbr(fp);
                break;
            case 13:
                otherbr(fp);
                break;
            case 14:
                about();
                break;
            default:
                printf("\nYou Pressed wrong key");
                printf("\nTry Again.............");
                getch();
                goto menu;

            } 
        }
    }
    else
    {
        printf("\n\n\n\nLogin Failed!");
        printf("\nPlease, Try Again...");
        getch();
        goto login;
    }

    return 1;
}

//====Welcome Screen=====
void welcome()
{
    logo();
    // printf("\n\n\n\n\n[ [ [ WELCOME TO OUR EMPLOYEE MANAGEMENT SYSTEM ] ] ]\n\n\n\n\n\n\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}

//----printing character ch at n times ------

void printChar(char ch, int n)
{
    while (n--) 
    {
        putchar(ch);
    }
}

//-----Printing Head Line of the program -----

void printHead()
{

    printf("\n\n\n");
    printf("\n==================================================================");
    printf("\n==================================================================");
    printf("\n================ EMPLOYEE MANAGEMENT SYSTEM (EMS) ================");
    printf("\n==================================================================");
    printf("\n==================================================================");

}


// ==========ADDING NEW RECORD==========================

void add(FILE *fp)
{
    char another = 'y';
    Employee e;

    fseek(fp, 0, SEEK_END);
    while (another == 'y' || another == 'Y')
    {
   
        printHead();

        printf("\n\n  Add Employee\n");
        printf("        ----------------\n");
        printf("\nEnter ID Number: ");
        scanf("%d", &e.id);

        printf("\nEnter Full Name of Employee: ");
        fflush(stdin);
        fgets(e.name, 100, stdin); // fgets takes an extra \n character as input
        e.name[strlen(e.name) - 1] = '\0';

        printf("\nEnter Designation: ");
        fflush(stdin);
        fgets(e.desgn, 30, stdin); // fgets takes an extra \n character as input
        e.desgn[strlen(e.desgn) - 1] = '\0';

        printf("\nEnter Gender: ");
        fflush(stdin);
        fgets(e.gender, 10, stdin); // fgets takes an extra \n character as input
        e.gender[strlen(e.gender) - 1] = '\0';

        printf("\nEnter Branch: ");
        fflush(stdin);
        fgets(e.branch, 50, stdin);
        e.branch[strlen(e.branch) - 1] = '\0';

        printf("\nEnter Salary: ");
        scanf("%f", &e.sal);

        printf("\nEnter Present Address: ");
        fflush(stdin);
        fgets(e.psaddr, 200, stdin);
        e.psaddr[strlen(e.psaddr) - 1] = '\0';

        printf("\nEnter Permanant Address: ");
        fflush(stdin); 
        fgets(e.prtaddr, 200, stdin);
        e.prtaddr[strlen(e.prtaddr) - 1] = '\0';

        printf("\nEnter Phone: ");
        fflush(stdin);
        fgets(e.phone, 50, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';

        printf("\nEnter E-mail Address: ");
        fflush(stdin);
        fgets(e.mail, 30, stdin);
        e.mail[strlen(e.mail) - 1] = '\0';

        fwrite(&e, sizeof(e), 1, fp);

        printf("\n\nWant to enter another employee info (Y/N) ");
        fflush(stdin);
        another = getchar();
    } 
}

//===================DELETING A RECORD FROM LIST ============
FILE *del(FILE *fp)
{
    printHead();
    printf("\n\n  Delete Employee\n");
    printf("        ------------------\n");
    Employee e;
    int flag = 0, tempid, siz = sizeof(e);
    FILE *ft;

    if ((ft = fopen("temp.txt", "wb+")) == NULL) 
    {
        printf("\n\n !!! ERROR !!!\n");
     
        return fp;
    }

    printf("\n\n Enter ID number of Employee to Delete the Record");
    printf("\n\n ID No. : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    { 
        if (e.id == tempid)
        {
            flag = 1;
            printf("\nRecord Deleted for");
            printf("\n\n%s\n\n%s\n\n%d\n", e.name, e.branch, e.id);
            continue;
        }

        fwrite(&e, siz, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("employeeInfo.txt");
    rename("temp.txt", "employeeInfo.txt");

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) 
    {
        printf("ERROR");
        return NULL;
    }

    if (flag == 0)
        printf("\n\n\n\n     ERROR RECORD NOT FOUND!\n");

    printf("\n\n");
    printf("\n\n   Enter any keys to continue...");
    getch();
    return fp;
}

//===========MODIFY A RECORD ===========================

void modify(FILE *fp)
{
    printHead();
    printf("\nModify Employee\n");
    printf("      --------------------\n");
    Employee e;
    int i, flag = 0, tempid, siz = sizeof(e);
    float sal;

    printf("\n\nEnter ID Number of Employee to Modify the Record : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if (e.id == tempid)
        {
            flag = 1; 
            break;
        }
    }

    if (flag == 1)
    {
        fseek(fp, -siz, SEEK_CUR);
        printf("\n                    Record Found!\n");
        printf("\n            Enter New Data for the Record\n");
        printf(" -----------------------------------\n");

        printf("\nEnter ID number: ");
        scanf("%d", &e.id);

        printf("\nEnter Full Name of Employee: ");
        fflush(stdin);
        fgets(e.name, 100, stdin);         // fgets takes an extra \n character as input
        e.name[strlen(e.name) - 1] = '\0'; 

        printf("\nEnter Designation: ");
        fflush(stdin);
        fgets(e.desgn, 30, stdin); // fgets takes an extra \n character as input
        e.desgn[strlen(e.desgn) - 1] = '\0';

        printf("\nEnter Gender: ");
        fflush(stdin);
        fgets(e.gender, 10, stdin); // fgets takes an extra \n character as input
        e.gender[strlen(e.gender) - 1] = '\0';

        printf("\nEnter Branch: ");
        fflush(stdin);
        fgets(e.branch, 50, stdin); 
        e.branch[strlen(e.branch) - 1] = '\0';

        printf("\nEnter Salary: ");
        scanf("%f", &e.sal);

        printf("\nEnter Present Address: ");
        fflush(stdin);
        fgets(e.psaddr, 200, stdin);
        e.psaddr[strlen(e.psaddr) - 1] = '\0';

        printf("\nEnter Permanant Address: ");
        fflush(stdin);
        fgets(e.prtaddr, 200, stdin); 
        e.prtaddr[strlen(e.prtaddr) - 1] = '\0';

        printf("\nEnter Phone: ");
        fflush(stdin);
        fgets(e.phone, 50, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';

        printf("\nEnter E-mail: ");
        fflush(stdin);
        fgets(e.mail, 30, stdin);
        e.mail[strlen(e.mail) - 1] = '\0';

        fwrite(&e, sizeof(e), 1, fp); 
    }

    else
        printf("\n\n      ERROR, RECORD NOT FOUND!");

    printf("\n\n");
    printf("\n\n   Enter any keys to continue...");
    getch();
}

//====================DISPLAY THE LIST =================
void displayList(FILE *fp)
{
    printHead();
    printf("\n List of Employees\n");
    printf("      -----------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        printf("\n\nID : %d\n", e.id); 
        printf("\n\nNAME : %s", e.name);
        printf("\n\nDESIGNATION : %s", e.desgn);
        printf("\n\nGENDER : %s", e.gender);
        printf("\n\nBRANCH : %s", e.branch);
        printf("\n\nSALARY : %.2f", e.sal);
        printf("\n\nPRESENT ADDRESS : %s", e.psaddr);
        printf("\n\nPERMANANT ADDRESS : %s", e.prtaddr);
        printf("\n\nPHONE : %s", e.phone);
        printf("\n\nE-MAIL : %s\n", e.mail);
        printf("\n\n     ===============================================");
    }
    printf("\n\n\n");
    printf("\n\n     Enter any keys to continue...");
    getch();
}

//================SEARCH EMPLOYEE==
void searchRecord(FILE *fp) 
{
    int tempid, flag, siz, i;
    Employee e;
    char another = 'y';

    siz = sizeof(e);

    while (another == 'y' || another == 'Y')
    {
     
        printHead();
        printf("\nSearch Employee\n");
        printf("---------------------\n");
        printf("\n\n Enter ID Number of Employee to search the record : ");
        scanf("%d", &tempid);

        rewind(fp); 

        while ((fread(&e, siz, 1, fp)
        ) == 1)
        {
            if (e.id == tempid)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            printf("\nNAME : %s", e.name);
            printf("\n\nID : %d", e.id);
            printf("\n\nDESIGNATION : %s", e.desgn);
            printf("\n\nBRANCH : %s", e.branch); 
            printf("\n\nSALARY: %.2f", e.sal);
            printf("\n\nPRESENT ADDRESS : %s", e.psaddr);
            printf("\n\nPERMANANT ADDRESS : %s", e.prtaddr);
            printf("\n\nPHONE : %s", e.phone);
            printf("\n\nE-MAIL : %s\n", e.mail);

            printf("\n\n========================");

        }
        else
            printf("\n\n      ERROR, RECORD NOT FOUND!");

        printf("\n\nWant to enter another search (Y/N)");
        fflush(stdin); 
        another = getchar();
    }
}

//========================LIST OF MALE EMPLOYEE==
void maleemp(FILE *fp)
{
    printHead();
    printf("\n      List of Male Employee\n");
    printf("    -------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp); 

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if ((strcmp(e.gender, "Male") == 0) || (strcmp(e.gender, "male") == 0))
        {
            
            printf("\n\n      ID : %d", e.id);
            printf("\n\n      NAME : %s", e.name);
            printf("\n\n      DESIGNATION : %s", e.desgn);
            printf("\n\n      PHONE : %s\n", e.phone);
            printf("\n      ======================================");
        }
    }

    printf("\n");
    printf("\n\n           Enter any keys to continue...");
    getch();
}

//========================LIST OF FEMALE EMPLOYEE==

void femaleemp(FILE *fp)
{
    printHead();
    printf("\n      List of Female Employee\n");
    printf("    ---------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if ((strcmp(e.gender, "Female") == 0) || (strcmp(e.gender, "female") == 0))
        {
            printf("\n\n      ID : %d", e.id);
            printf("\n\n      NAME : %s", e.name);
            printf("\n\n      DESIGNATION : %s", e.desgn);
            printf("\n\n      PHONE : %s\n", e.phone);
            printf("\n      ======================================");
        }
    }
    printf("\n");
    printf("\n\n           Enter any keys to continue...");
    getch();
}

//========================LIST OF EMPLOYEE FROM DHAKA====

void frmdhaka(FILE *fp)
{
    printHead();
    printf("\n    List of Employee from Dhaka\n"); 
    printf("  -------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if ((strstr(e.prtaddr, "Dhaka") == 0) || (strstr(e.prtaddr, "dhaka") == 0) || (strstr(e.prtaddr, "DHAKA") == 0))
        {
            printf("\n\n      ID : %d", e.id);
            printf("\n\n      NAME : %s", e.name);
            printf("\n\n      DESIGNATION : %s", e.desgn);
            printf("\n\n      PHONE : %s", e.phone);
            printf("\n\n      E-MAIL : %s\n", e.mail);
            printf("\n      ======================================");
        }
    } 
    printf("\n");
    printf("\n\n           Enter any keys to continue...");
    getch();
}

//========================LIST OF EMPLOYEE FROM ORS DIST====

void frmors(FILE *fp)
{
    printHead();
    printf("\n       List of Employee from Others District\n");
    printf("     -----------------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if ((strstr(e.prtaddr, "Dhaka") == 1) && (strstr(e.prtaddr, "dhaka") == 1) && (strstr(e.prtaddr, "DHAKA") == 1))
        {
            printf("\n\n      ID : %d", e.id);
            printf("\n\n      NAME : %s", e.name);
            printf("\n\n      DESIGNATION : %s", e.desgn);
            printf("\n\n      PHONE : %s", e.phone);
            printf("\n\n      E-MAIL : %s\n", e.mail);
            printf("\n      ======================================");
        }
    }
    printf("\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}

//==============DISPLAY BASIC INFO LIST==

void displaybasic(FILE *fp)
{
    printHead(); 
    printf("\nDisplay Basic Information\n");
    printf("  -------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        printf("\n\n      ID : %d", e.id);
        printf("\n\n      NAME : %s", e.name);
        printf("\n\n      DESIGNATION : %s", e.desgn);
        printf("\n\n      GENDER : %s", e.gender);
        printf("\n\n      BRANCH : %s", e.branch);
        printf("\n\n      PHONE : %s", e.phone);
        printf("\n\n      E-MAIL : %s\n", e.mail);
        printf("\n      ======================================");
    }
    printf("\n");
    printf("\n\n           Enter any keys to continue...");
    getch();
}

//========BASIC CONTACT INFO LIST====

void basiccontact(FILE *fp)
{
    printHead();
    printf("\n     Basic Contact Information\n");
    printf("-------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        printf("\n\nID : %d", e.id);
        printf("\n\nNAME : %s", e.name);
        printf("\n\nDESIGNATION : %s", e.desgn);
        printf("\n\nPHONE : %s", e.phone);
        printf("\n\nE-MAIL : %s\n", e.mail);
        printf("\n      ======================================");
    }
    printf("\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}

//========================LIST OF EMPLOYEE OF MAIN BRANCH====

void mainbr(FILE *fp)
{
    printHead();
    printf("\n          List of Employee of Main Branch\n");
    printf("        -----------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1) 
    {
        if ((strcmp(e.branch, "Main") == 0) || (strcmp(e.prtaddr, "main") == 0) || (strcmp(e.prtaddr, "MAIN") == 0))
        {
            printf("\n\nID : %d", e.id);
            printf("\n\nNAME : %s", e.name);
            printf("\n\nDESIGNATION : %s", e.desgn); 
            printf("\n\nPHONE : %s", e.phone);
            printf("\n\nE-MAIL : %s\n", e.mail);
            printf("\n\n========================");
        }
    }
    printf("\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}

//========================LIST OF EMPLOYEE OF OTHRES BRANCH====

void otherbr(FILE *fp)
{
    printHead();
    printf("\n List of Employee of Other Branch\n"); 
    printf("--------------------------------------\n");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1)
    {
        if ((strcmp(e.branch, "Main") != 0) && (strcmp(e.prtaddr, "main") != 0) && (strcmp(e.prtaddr, "MAIN") != 0))
        {
            printf("\n\n      ID : %d", e.id);
            printf("\n\n      NAME : %s", e.name); 
            printf("\n\n      DESIGNATION : %s", e.desgn);
            printf("\n\n      PHONE : %s", e.phone);
            printf("\n\n      E-MAIL : %s\n", e.mail);
            printf("\n\n========================");
        }
    }
    printf("\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}


void about()
{

    printf("\n\n\n");
    printf("    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("    ::          Project Details & About Programmer          ::\n");
    printf("    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n");
    printf("    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("    ::                                        NORTH SOUTH UNIVERSITY                                  ::\n");
    printf("    ::                             Project Name : Employee Management System (EMS)                    ::\n");
    printf("    ::                           ---------------------------------------------------                  ::\n");
    printf("    ::                                                                                                ::\n");
    printf("    ::                                        ----------------------                                  ::\n");
    printf("    ::                                             Submitted By                                       ::\n");
    printf("    ::                                        ----------------------                                  ::\n");
    printf("    ::                                         Name : Sumit Saha                                      ::\n");
    printf("    ::                                        ID Number : 1931415042                                  ::\n");
    printf("    ::                                                                                                ::\n");
    printf("    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\nEnter any keys to continue...");
    getch();
}

void logo()
{
    printf("\n\n\n");
    printf("     ____ _  _ ___  _    ____ _   _ ____ ____\n");
    printf("     |___ |\\/| |__] |    |  |  \\_/  |___ |___\n");
    printf("     |___ |  | |    |___ |__|   |   |___ |___\n");
    printf(" _  _ ____ _  _ ____ ____ ____ _  _ ____ _  _ ___\n");
    printf(" |\\/| |__| |\\ | |__| | __ |___ |\\/| |___ |\\ |  |\n");
    printf(" |  | |  | | \\| |  | |__] |___ |  | |___ | \\|  | \n");
    printf("          ____ _   _ ____ ___ ____ _  _\n");
    printf("          [__   \\_/  [__   |  |___ |\\/|\n");
    printf("          ___]   |   ___]  |  |___ |  |\n");
    printf("\n\n\n");
}