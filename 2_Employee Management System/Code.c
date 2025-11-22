#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
    char name[20];
    char gender[10];
    int age;
    int eid;
    float salary;
    char mobile[15];
    char address[20];
};

typedef struct Employee Employee;
Employee emp;
FILE *fp, *ft;
int recsize = sizeof(Employee);

void insert_record()
{
    int flag = 0, id;

    printf("\n====================================================");
    printf("\n               INSERT EMPLOYEE RECORD");
    printf("\n====================================================");

    printf("\nEnter Employee ID (EID): ");
    scanf("%d", &id);

    rewind(fp);
    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (emp.eid == id)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        fseek(fp, 0, SEEK_END);

        emp.eid = id;
        printf("Enter Name: ");
        fflush(stdin);
        gets(emp.name);

        printf("Enter Gender: ");
        fflush(stdin);
        gets(emp.gender);

        printf("Enter Salary: ");
        scanf("%f", &emp.salary);

        printf("Enter Mobile Number: ");
        fflush(stdin);
        gets(emp.mobile);

        printf("Enter Address: ");
        fflush(stdin);
        gets(emp.address);

        fwrite(&emp, recsize, 1, fp);
        printf("\nRecord saved successfully!");
    }
    else
    {
        printf("\nSorry! Employee ID already exists.");
    }
}

void display_record()
{
    rewind(fp);
    printf("\n====================================================");
    printf("\n               EMPLOYEE RECORD LIST");
    printf("\n====================================================");
    printf("\nEID\tName\tGender\tSalary\tAddress\t\tMobile");
    printf("\n----------------------------------------------------");

    while (fread(&emp, recsize, 1, fp) == 1)
    {
        printf("\n%d\t%s\t%s\t%.0f\t%s\t%s", emp.eid, emp.name, emp.gender, emp.salary, emp.address, emp.mobile);
    }
    printf("\n----------------------------------------------------");
    printf("\nEnd of employee records.\n");
}

void search_record()
{
    char streid[15], str[15];
    int flag = 0;

    printf("\n====================================================");
    printf("\n                 SEARCH EMPLOYEE");
    printf("\n====================================================");
    printf("\nEnter Employee ID or Mobile Number: ");
    fflush(stdin);
    gets(str);

    rewind(fp);
    while (fread(&emp, recsize, 1, fp) == 1)
    {
        sprintf(streid, "%d", emp.eid);

        if (strcmp(emp.mobile, str) == 0 || strcmp(streid, str) == 0)
        {
            flag = 1;
            printf("\nEID\tName\tGender\tSalary\tAddress\t\tMobile");
            printf("\n----------------------------------------------------");
            printf("\n%d\t%s\t%s\t%.0f\t%s\t%s", emp.eid, emp.name, emp.gender, emp.salary, emp.address, emp.mobile);
            printf("\n----------------------------------------------------");
            printf("\nRecord found successfully!\n");
            break;
        }
    }

    if (flag == 0)
    {
        printf("\nSorry! Employee record not found.\n");
    }
}

void delete_record()
{
    int id, flag = 0;

    printf("\n====================================================");
    printf("\n                 DELETE EMPLOYEE");
    printf("\n====================================================");
    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &id);

    ft = fopen("temp.dat", "wb+");
    if (ft == NULL)
    {
        printf("\nError while creating temporary file.\n");
        exit(2);
    }

    rewind(fp);
    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (emp.eid != id)
        {
            fwrite(&emp, recsize, 1, ft);
        }
        else
        {
            flag = 1;
        }
    }

    fclose(ft);
    fclose(fp);
    remove("emp.dat");
    rename("temp.dat", "emp.dat");
    fp = fopen("emp.dat", "rb+");

    if (flag == 1)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nNo record found with the given Employee ID.\n");
}

void modify_record()
{
    int flag = 0, id;

    printf("\n====================================================");
    printf("\n                 MODIFY EMPLOYEE");
    printf("\n====================================================");
    printf("\nEnter Employee ID to modify: ");
    scanf("%d", &id);

    rewind(fp);

    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (id == emp.eid)
        {
            printf("\nEnter New EID: ");
            scanf("%d", &emp.eid);

            printf("Enter New Name: ");
            fflush(stdin);
            gets(emp.name);

            printf("Enter New Gender: ");
            fflush(stdin);
            gets(emp.gender);

            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);

            printf("Enter New Mobile Number: ");
            fflush(stdin);
            gets(emp.mobile);

            printf("Enter New Address: ");
            fflush(stdin);
            gets(emp.address);

            fseek(fp, -recsize, SEEK_CUR);
            fwrite(&emp, recsize, 1, fp);
            flag = 1;
            break;
        }
    }

    if (flag == 1)
        printf("\nRecord modified successfully!\n");
    else
        printf("\nEmployee ID not found.\n");
}

int main()
{
    int choice;

    printf("\n====================================================");
    printf("\n           EMPLOYEE MANAGEMENT SYSTEM");
    printf("\n====================================================");

    fp = fopen("emp.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nFile does not exist. Creating new file...");
        fp = fopen("emp.dat", "wb+");

        if (fp == NULL)
        {
            printf("\nError while creating file.");
            exit(0);
        }
        else
        {
            printf("\nFile created successfully.");
        }
    }
    else
    {
        printf("\nFile opened successfully.");
    }

    do
    {
        printf("\n\n====================================================");
        printf("\n                     MAIN MENU");
        printf("\n====================================================");
        printf("\n1. Insert Record");
        printf("\n2. Display All Records");
        printf("\n3. Search Record");
        printf("\n4. Delete Record");
        printf("\n5. Modify Record");
        printf("\n0. Exit");
        printf("\n----------------------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert_record();
            break;
        case 2:
            display_record();
            break;
        case 3:
            search_record();
            break;
        case 4:
            delete_record();
            break;
        case 5:
            modify_record();
            break;
        case 0:
            printf("\nExiting... Thank you for using the system!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please try again.");
            break;
        }
    } while (1);

    return 0;
}
