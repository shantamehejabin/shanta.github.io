#include<stdio.h>
#include<stdlib.h>
void heading();
void mainmenu();
void addbook();
void booklist();
void search();
void edit();
void deletebook();
struct Book_info{
    int id;
    char name[10];
    char author[10];
    int quantity;
    int rack;
};
struct Book_info a;

FILE *file;

int main()
{
    heading();
}
void mainmenu()
{   int num;
    system("cls");
    printf("\n\n \t\t\t\t\t <========   Main Menu  ========>\n");
    printf("\n\n \t\t\t\t\t 1. Add Book \n");
    printf(" \t\t\t\t\t 2. View Book list \n");
    printf(" \t\t\t\t\t 3. Search Book \n");
    printf(" \t\t\t\t\t 4. Edit Book\n");
    printf(" \t\t\t\t\t 5. Delete Book\n");
    printf(" \t\t\t\t\t 6. Exit \n\n");

    printf(" \t\t\t\t\t**********************************\n");
    printf(" \t\t\t\t\t Enter your choice: ");
    scanf("%d",&num);

    switch(num){
        case 1:
            addbook();
            break;
        case 2:
            booklist();
            break;
        case 3:
            search();
            break;
        case 4:
            edit();
            break;
        case 5:
             deletebook();
            break;
        case 6:
            printf("\n\t\t\t\t\t Thank You.......<3\n ");
            exit(0);
        default:
            printf("\n \t\t\t\t Invalid Choice...\n");
            printf("\n \t\t\t\t Try Agian...");

            fflush(stdin);
            getchar();
            mainmenu();
    }

}
void addbook()
{
    system("cls");
    int d,count = 0;

    printf("\n\n\t\t *****************Add Book******************\n\n");

    file = fopen("book.text","ab+");

    printf("\t\t Enter Book ID: ");
    scanf("%d",&d);

    rewind(file);
    while(fread(&a, sizeof(a), 1, file) == 1){

        if(d == a.id){
            printf("\n\n\t\t This Book is Already in Libaray....");
            count = 1;
        }
    }
    if(count == 1){

        fflush(stdin);
        getchar();
        mainmenu();
    }
    a.id = d;

    printf("\n\t\t Enter Book Name: ");
    fflush(stdin);
    gets(a.name);

    printf("\t\t Enter Author: ");
    fflush(stdin);
    gets(a.author);

    printf("\t\t Enter quantity: ");
    fflush(stdin);
    scanf("%d", &a.quantity);

    printf("\t\t Enter Rack: ");
    fflush(stdin);
    scanf("%d", &a.rack);

    fseek( file, 0, SEEK_END );
    fwrite(&a, sizeof(a), 1, file);

    fclose(file);

    printf("\n\n\t\t Book added Sucessfully! ");

    fflush(stdin);
    getchar();

    mainmenu();
}
void booklist()
{
    system("cls");
    printf("\n\n\t\t\t\t***************Book List****************\n\n");
   printf("\t\t%-10s %-30s %-20s %-10s %-30s \n\n", "ID", "Book Name", "Author", "Quantity", "Rack no");


   file = fopen("book.text","rb");

   while(fread(&a, sizeof(a), 1, file) == 1)
   {
        printf("\t\t%-10d %-30s %-20s %-10d %-30d\n", a.id, a.name, a.author, a.quantity, a.rack);
   }
   fclose(file);
   printf("\n\n\t\t Press any key.....");
   fflush(stdin);
   getchar();

   mainmenu();
}
void search(){
    int id,count=0;

    system("cls");
    printf("\n\n\t\t***************Search Any Book****************\n\n");
    file = fopen("book.text","rb");

    printf("\n\t\t Enter ID: ");
    scanf("%d", &id);

    while(fread(&a,sizeof(a), 1 , file)==1 ){
        if( id == a.id){
            printf("\n\n\t\t Book is Found <3");
            printf("\n\n\t\t ID no: %d", a.id);
            printf("\n\t\t Book Name: %s", a.name);
            printf("\n\t\t Author Name: %s", a.author);
            printf("\n\t\t Quantity: %d", a.quantity);
            printf("\n\t\t Rack no: %d", a.rack);

            count=1;
        }
    }
    if(count == 0){
        printf("\n\n\t\t This Book is not Available now !");
    }
    printf("\n\n\t\t Press any key.....");
    fflush(stdin);
    getchar();

    mainmenu();
}
void edit(){
    int id,count=0;
    system("cls");
    printf("\n\n\t\t************Edit Book************\n\n");
    file = fopen("book.text","rb+");

    printf("\n\t\t Enter ID: ");
    scanf("%d",&id);

    while(fread(&a, sizeof(a),1,file)== 1)
    {
        if(id == a.id){

        printf("\n\t\t Book is here...\n");
        printf("\n\t\t ID: %d", a.id);
        printf("\n\t\t Enter New Name: ");
         scanf("%s",&a.name);
        printf("\n\t\t Enter New Author Name: ");
         scanf("%s",&a.author);
        printf("\n\t\t Enter New Quantity: ");
         scanf("%d",&a.quantity);
        printf("\n\t\t Enter New Rack no: ");
         scanf("%d",&a.rack);

        fseek(file, ftell(file)-sizeof(a), 0);

        fwrite(&a,sizeof(a),1,file);
        fclose(file);
         printf("\n\n\t\t Book edited Sucessfully! ");
        count++;
        }
    }
    if(count==0){
        printf("\n\t\tThis book not available :0");
    }
    fflush(stdin);
    getchar();

    mainmenu();

}

void deletebook()
{
     system("cls");
    int id,count = 0;

    printf("\n\n\t\t ************Delete Book*************\n\n");
    printf("\t\t Enter ID for Delete Book: ");
    scanf("%d",&id);
    FILE*ft;
    file = fopen("book.text","rb+");
    ft = fopen("temp.text","ab");


    while(fread(&a, sizeof(a), 1, file) == 1){

        if(id == a.id){
            printf("\n\n\t\t This Book is Available.");
            printf("\n\n\t\t Book Name: %s",a.name);
            printf("\n\n\t\t Rack no: %d",a.rack);
            count = 1;
        }
        else{
            fwrite(&a, sizeof(a), 1, ft);
        }
    }
        fclose(file);
        fclose(ft);

        remove("book.text");
        rename("temp.text", "book.text");

    if(count==0)
    {
       printf("\n\n\t\t This Book is not Available.");
    }
    else
    {
       printf("\n\t\tBook Deleted successfully ");
    }

    fflush(stdin);
    getchar();

    mainmenu();
}
void heading()
{
    system("cls");
    printf("\n\n\n\n \t\t\t\t\t *****////   WELCOME TO   /////*****");
    printf("\n\n\n\n \t\t\t\t **************Libaray Management System**************\n" );

    printf("\n \t\t\t Press any key to Enter....");

    fflush(stdin);
    getchar();

    mainmenu();
}
