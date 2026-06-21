#include <stdio.h>

struct Item {
    char name[50];
    float price;
    int qty;
    float gst;
};

/* Function to take item input */
void inputItems(struct Item items[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("\nEnter item %d name: ", i + 1);
        scanf("%s", items[i].name);

        printf("Enter GST %% , Quantity , Unit Price: ");
        scanf("%f %d %f",
              &items[i].gst,
              &items[i].qty,
              &items[i].price);
    }
}

/* Function to calculate gross amount */
float calculateGross(struct Item item, float *cgst, float *sgst) {
    float itemValue = item.price * item.qty;

    *cgst = itemValue * (item.gst / 2) / 100;
    *sgst = itemValue * (item.gst / 2) / 100;

    return itemValue + *cgst + *sgst;
}

/* Function to print invoice on screen */
void printInvoice(struct Item items[], int n) {
    float grandTotal = 0;

    printf("\n======================== GST INVOICE ===========================\n");
    printf("SL  Item Name\tGST%%\tQty\tPrice\tCGST\tSGST\tGross\n");
    printf("----------------------------------------------------------------\n");

    int i;
    for (i = 0; i < n; i++) {
        float cgst, sgst;
        float gross = calculateGross(items[i], &cgst, &sgst);

        grandTotal += gross;

        printf("%d   %s\t%.0f\t%d\t%.2f\t%.2f\t%.2f\t%.2f\n",
               i + 1,
               items[i].name,
               items[i].gst,
               items[i].qty,
               items[i].price,
               cgst,
               sgst,
               gross);
    }

    printf("----------------------------------------------------------------\n");
    printf("GRAND TOTAL:\t\t\t\t\t%.2f\n", grandTotal);
    printf("================================================================\n");
}

/* Function to save invoice into file */
void saveInvoice(struct Item items[], int n) {
    FILE *fp = fopen("bill.txt", "w");

    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }

    float grandTotal = 0;

    fprintf(fp, "======================== GST INVOICE ===========================\n");
    fprintf(fp, "SL  Item Name\tGST%%\tQty\tPrice\tCGST\tSGST\tGross\n");
    fprintf(fp, "----------------------------------------------------------------\n");

    int i;
    for (i = 0; i < n; i++) {
        float cgst, sgst;
        float gross = calculateGross(items[i], &cgst, &sgst);

        grandTotal += gross;

        fprintf(fp, "%d   %s\t%.0f\t%d\t%.2f\t%.2f\t%.2f\t%.2f\n",
                i + 1,
                items[i].name,
                items[i].gst,
                items[i].qty,
                items[i].price,
                cgst,
                sgst,
                gross);
    }

    fprintf(fp, "----------------------------------------------------------------\n");
    fprintf(fp, "GRAND TOTAL:\t\t\t\t\t%.2f\n", grandTotal);
    fprintf(fp, "================================================================\n");

    fclose(fp);

    printf("\nBill saved successfully in bill.txt\n");
}

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];

    inputItems(items, n);

    printInvoice(items, n);

    saveInvoice(items, n);

    return 0;
}
