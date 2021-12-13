#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct iteams
{
    char iteam[20];
    float price;
    int qty;
};
struct orders
{
    char date[50];
    char customer[50];
    int numofitems;
    struct iteams itm[50];
};
//function to generatem  the bills
void generatethebillheader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t     KGF.Restaurant\n");
    printf("\t----------------------");
    printf("\nDate:%s", date);
    printf("\nInvoice to: %s", name);
    printf("\n");
    printf("----------------------------------------------------\n");
    printf("Iteams\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------------------\n");
    printf("\n\n");
}
void generatebillbody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generatbillflooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandtTotal = netTotal + 2 * cgst;
    printf("---------------------------------------------------\n");
    printf("Sub Total \t\t\t%.2f\n", total);
    printf("Discount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total \t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandtTotal);
    printf("\n---------------------------------------------------\n");
}

int main()
{
    int opt, n;
    float total;
    struct orders order;
    struct orders ord;
    char saveBill = 'y';
    FILE *fp;

    //dashbord
    printf("\t==================HOTEL KGF====================\n");
    printf("Please enter the prefered opeartion\n");
    printf("\n\t 1. generate the Invoice");
    printf("\n\t 2.Show all Invoices");
    printf("\n\t 3.search Invoice");
    printf("\n\t 4.Exit\n\n");
    printf("\n\nYour choice :\t");

    scanf("%d", &opt);
    fgetc(stdin);
    switch (opt)
    {
    case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer) - 1] = 0;
        strcpy(ord.date, __DATE__);
        printf("Please enter the number of items:\t");
        scanf("%d", &n);
        ord.numofitems = n;
        for (int i = 0; i < n; i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d :\t", i + 1);
            fgets(ord.itm[i].iteam, 20, stdin);
            ord.itm[i].iteam[strlen(ord.itm[i].iteam) - 1] = 0;
            printf("\nPlease enter the quantity :\t");
            scanf("%d", &ord.itm[i].qty);
            printf("\n Please enter the unit price :\t");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }
        generatethebillheader(ord.customer, ord.date);
        for (int i = 0; i < ord.numofitems; i++)
        {
            generatebillbody(ord.itm[i].iteam, ord.itm[i].qty, ord.itm[i].price);
        }
        generatbillflooter(total);
        printf("\n Do you want to save the invoice[y/n]:\t");
        scanf("%s", &saveBill);
        if (saveBill == 'y')
        {
            fp = fopen("RestaurantBill.dat", "a+");
            fwrite(&ord, sizeof(struct orders), 1, fp);
            if (fwrite != 0)
            {
                printf("\nSuccessfully saved\n\n");
            }
            else
            {
                printf("\n Somthing went wrong , the file havent saved");
            }
            fclose(fp);
        }
        break;
    case 2:
        system("clear");
        fp = fopen("RestaurantBill.dat", "r");
        printf("\n    *******Your privious bills*******\n");
        while (fread(&order, sizeof(struct orders), 1, fp))
            ;
        {
            float tot = 0;
            generatethebillheader(order.customer, order.date);
            for (int i = 0; i <order.numofitems; i++)
            {
                generatebillbody(order.itm[i].iteam,order.itm[i].qty ,order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generatbillflooter(tot);
        }
        fclose(fp);
        break;
    }
}