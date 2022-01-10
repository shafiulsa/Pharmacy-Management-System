#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct medi
{
    int serial;
    char name[20];
    int price;
};

void addmedi();
void displayAll();
void del();
void search();
void rremove();
void delete();

char mygetch();

char fname[] = {"mydb.dat"};



int main()
{
    int ch;

    while (1)
    {
        system("clear"); 
        int n;
        printf("~~~~~~~~~~~~~~~~~~~~~~~~Pharmacy Management System~~~~~~~~~~~~~~~~~\n\n");
               
        int ch;
        printf("1. Add medicine\n\n");
        printf("2. Search medicine\n\n");
        printf("3. Display All medicine\n\n");
        printf("4. Delete  medicinen\n\n");
        printf("0. Exit\n\n");

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

        printf("\nPlease enter your Choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            addmedi();
            break;;

        case 2:
            search();
            break;

        case 3:
            displayAll();
            break;


        case 4:
            delete();
            break;
        case 0:
            exit(0);
        }
        mygetch();
    }

    return 0;
}
     
void addmedi()
{
    FILE *fp;
    struct medi t1;

    fp = fopen(fname, "ab");

    printf("\nEnter serial no:");
    scanf("%d", &t1.serial);
    printf("\nEnter name: of medicine :");
    scanf("%s", t1.name);
    printf("\nEnter price:");
    scanf("%d", &t1.price);
    fwrite(&t1, sizeof(t1), 1, fp);

    fclose(fp);
    printf("\n \n medicine added successfully!!!\n ");
    printf("\npress any key to go to main manue \n");

}
void delete(){
    printf("1.deleter one medicine \n");
    printf("2.delete all medicine\n");
    printf("enter your choice\n");
    int n;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
         del();
        break;
    case 2:
          rremove();
          break;
    }
    // printf("\npress any key to go to main manue \n");
}
void rremove()
{
    FILE *fp, *fp1;
    struct medi t;

    char name[20];
    char val[20];

    printf("\nDo you want to make copy of it (Y/N):");
    scanf("%s", val);

    if (strcmp(val, "Y") == 0)
    {

        printf("\nEnter the New File Name:");
        fflush(stdin);
        scanf("%[^\n]", name);

        fp = fopen(name, "wb");
        fp1 = fopen(fname, "rb");

        while (1)
        {
            fread(&t, sizeof(t), 1, fp1);

            if (feof(fp1))
            {
                break;
            }
            fwrite(&t, sizeof(t), 1, fp);
        }

        fclose(fp);
        fclose(fp1);

        remove(fname);

        strcpy(fname, name);
        
    }
    else
    {
        remove(fname);
    }
    printf("\npress any key to go to main manue \n");
}


void del()
{
    FILE *fp, *fp1;
    struct medi t, t1;
    int id, found = 0, count = 0;

    fp = fopen(fname, "rb");
    fp1 = fopen("temp.dat", "wb");

    printf("\nEnter the serial no you want to Delete:");
    scanf("%d", &id);

    while (1)
    {
        fread(&t, sizeof(t), 1, fp);

        if (feof(fp))
        {
            break;
        }
        if (t.serial == id)
        {
            found = 1;
        }
        else
        {
            fwrite(&t, sizeof(t), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if (found == 0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        fp = fopen(fname, "wb");
        fp1 = fopen("temp.dat", "rb");

        while (1)
        {
            fread(&t, sizeof(t), 1, fp1);

            if (feof(fp1))
            {
                break;
            }
            fwrite(&t, sizeof(t), 1, fp);
        }
    }
    fclose(fp);
    fclose(fp1);
    printf("\n \n medicine delete successfully!!!\n ");
    printf("\npress any key to go to main manue \n");
}

void search()
{
    FILE *fp;
    struct medi t;
    int found = 0;
    char name[20];

    fp = fopen(fname, "rb");

    printf("\nEnter the medicine Name:");
    scanf("%s", &name);

    while (1)
    {
        fread(&t, sizeof(t), 1, fp);

        if (feof(fp))
        {
            break;
        }
        if (strcmp(name, t.name) == 0)
        {
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            printf("\t\t medicine Details of %d\n\n", t.serial);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

            printf("Medicine_Name\tmedicine_price\n\n");

            printf("%s\t\t", t.name);
            printf("%d\t\t\n\n", t.price);

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            found=1;
        }
       
    }
    if (found == 0)
    {
        printf("\nSorry No Record Found");
    }
    fclose(fp);
    printf("\npress any key to go to main manue \n");
}
void displayAll()
{
    FILE *fp;
    struct medi t;

    fp = fopen(fname, "rb");

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t All Medicine Details\n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    printf("\nserial_no\tName\t\t price\n\n");

    while (1)
    {
        fread(&t, sizeof(t), 1, fp);

        if (feof(fp))
        {
            break;
        }
        printf("%d\t\t", t.serial);
        printf("%s\t\t", t.name);
        printf("%d\t\t\n\n", t.price);
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    fclose(fp);
    printf("\npress any key to go to main manue \n");
}


char mygetch()
{
    char val;
    char rel;

    scanf("%c", &val);
    scanf("%c", &rel);
    return (val);
}

