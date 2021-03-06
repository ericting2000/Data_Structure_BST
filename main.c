#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.c"
#include "bst.h"

int main() {
    char option[2];
    node* root = NULL;
    printf("Please select the operation from below:\n");
    menu();
    while (scanf("%s", option) == 1) {
        if (strcmp("1", option) == 0) {
            char filename[50];
            system("clear");
            printf("Please insert the file name in this form : (XXX.txt)\n");
            scanf("%s", filename);
            root = import_file(filename, root);
            if (!root) {
                esc_to_exit();
                printf("Please select the operation from below:\n");
                menu();
                continue;
            }
            printf("File import successfully\n");
            esc_to_exit();
        }
        if (strcmp("2", option) == 0) {
            int k = 0;
            node* srch;
            char num[5];
            system("clear");
            printf("Please insert the product number you want to search:\n");
            scanf("%s", num);
            do {
                if (k == 0)
                    srch = search(root, num);
                else
                    srch = inorder_succ(root, srch->product_num);
                if (srch) {
                    printf("Here's your search result:\n");
                    printf("product_number     price     amount\n");
                    printf("     %s        |   %d    |    %d\n", srch->product_num, srch->price, srch->amount);
                    k = 1;
                } else if (!srch && k == 0) {
                    printf("The product you search for doesn't exist\n");
                    esc_to_exit();
                    break;
                } else {
                    printf("No more information is avalable to show\n");
                    esc_to_exit();
                    break;
                }
            } while (conti_show() == 1);
        }
        if (strcmp("3", option) == 0) {
            node* src;
            char p_num[5];
            int prz, amt;
            system("clear");
            printf("Please insert the product number and the amount you want to import:\n");
            scanf("%s%d", p_num, &amt);
            src = search(root, p_num);
            if (src) {
                src->amount += amt;
                printf("\n");
                printf("The data of this product has been updated, below is its information:\n");
                printf("product_number     price     amount\n");
                printf("     %s        |   %d    |    %d\n", src->product_num, src->price, src->amount);

            } else {
                printf("The product doesn't exist, please insert the price to complete importation\n");
                scanf("%d", &prz);
                printf("\n");
                root = insert(root, p_num, prz, amt);
                printf("Your importation has completed\n");
                printf("Below is its product information:\n");
                printf("product_number     price     amount\n");
                printf("     %s        |   %d    |    %d\n", p_num, prz, amt);
            }
            esc_to_exit();
        }
        if (strcmp("4", option) == 0) {
            node* src;
            char num[5];
            system("clear");
            printf("Please insert the product number you want to delete:\n");
            scanf("%s", num);
            src = search(root, num);
            if (src) {
                system("clear");
                printf("Below is the information that you chosen to delete:\n");
                printf("product_number     price     amount\n");
                printf("     %s        |   %d    |    %d\n", src->product_num, src->price, src->amount);
                root = del(root, num);
                printf("\n");
                printf("The product you selected has already been deleted\n");

            } else {
                printf("The product you choose doesn't exist, please check again\n");
            }
            esc_to_exit();
        }
        if (strcmp("5", option) == 0) {
            node* src;
            char p_num[5];
            int amt;
            system("clear");
            printf("Please insert the product number and the amount you want to export:\n");
            scanf("%s%d", p_num, &amt);
            src = search(root, p_num);
            if (src) {
                if (src->amount >= amt) {
                    src->amount -= amt;
                    printf("Your exportation has completed\n");
                } else
                    printf("The amount of product isn't enough for you to export\n");
                /*if (src->amount == 0) {
                    root = del(root, p_num);
                }*/
            } else
                printf("The product doesn't exist\n");
            esc_to_exit();
        }
        if (strcmp("6", option) == 0) {
            system("clear");
            printf("product_number     price     amount\n");
            inorder_pt(root);
            esc_to_exit();
        }
        if (strcmp("7", option) == 0) {
            system("clear");
            node* oldnode;
            int prz, amt;
            char o_num[5], n_num[5];
            printf("Please insert the product number you want to modify and its new number : (old, new)\n");
            scanf("%s%s", o_num, n_num);
            oldnode = search(root, o_num);
            if (!oldnode) {
                printf("The product you want to modify the number is not exist in database.\n");
                esc_to_exit();
            } else {
                prz = oldnode->price;
                amt = oldnode->amount;
                root = del(root, o_num);
                root = insert(root, n_num, prz, amt);
                system("clear");
                printf("The data of product %s has been midified\n", o_num);
                printf("Below is the new data:\n");
                printf("product_number     price     amount\n");
                printf("     %s        |   %d    |    %d\n", n_num, prz, amt);
                esc_to_exit();
            }
        }
        if (strcmp("8", option) == 0) {
            char flname[50];
            char t[3];
            system("clear");
            printf("Do you want to save the file before you quit?[y/n]\n");
            while (scanf("%s", t) == 1) {
                system("clear");
                if (strcmp(t, "y") == 0) {
                    printf("Please insert the file name in this form : (XXX.txt)\n");
                    scanf("%s", flname);
                    save(flname, root);
                    printf("Your file has been saved successfully,see you soon!\n");
                    freetree(root);
                    exit(0);
                } else if (strcmp(t, "n") == 0) {
                    printf("See you soon!\n");
                    exit(0);
                } else
                    printf("No such command, please insert again![y/n]\n");
            }
        }
        printf("Please select the operation from below:\n");
        menu();
    }
}