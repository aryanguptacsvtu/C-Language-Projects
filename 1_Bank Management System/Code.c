#include <stdio.h>
#include <string.h>

const char *ACCOUNT_FILE = "account.dat";

typedef struct
{
    char name[50];
    int acc_no;
    float balance;
} Account;

void create_account()
{
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open file!\n");
        return;
    }

    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("\n------------------------------------------");
    printf("\n         CREATE NEW ACCOUNT");
    printf("\n------------------------------------------");

    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';

    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n[OK] Account created successfully for '%s' (A/C No: %d)\n", acc.name, acc.acc_no);
}

void deposit_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open account file!\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_r;

    printf("\n------------------------------------------");
    printf("\n             DEPOSIT MONEY");
    printf("\n------------------------------------------");

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            acc_r.balance += money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);

            printf("\n[OK] Deposited: Rs.%.2f", money);
            printf("\n[INFO] New Balance: Rs.%.2f\n", acc_r.balance);
            return;
        }
    }

    fclose(file);
    printf("\n[ERROR] Account No %d not found! Deposit failed.\n", acc_no);
}

void withdraw_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open the account file!\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_r;

    printf("\n------------------------------------------");
    printf("\n             WITHDRAW MONEY");
    printf("\n------------------------------------------");

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to withdraw: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file) == 1)
    {
        if (acc_r.acc_no == acc_no)
        {
            if (acc_r.balance >= money)
            {
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                printf("\n[OK] Withdrawn: Rs.%.2f", money);
                printf("\n[INFO] Remaining Balance: Rs.%.2f\n", acc_r.balance);
            }
            else
            {
                printf("\n[ERROR] Insufficient balance! Current balance: Rs.%.2f\n", acc_r.balance);
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n[ERROR] Account No %d not found! Withdrawal failed.\n", acc_no);
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open file!\n");
        return;
    }

    int acc_no;
    Account acc_read;

    printf("\n------------------------------------------");
    printf("\n              CHECK BALANCE");
    printf("\n------------------------------------------");

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("\n------------------------------------------");
            printf("\n Account Holder : %s", acc_read.name);
            printf("\n Account Number  : %d", acc_read.acc_no);
            printf("\n Current Balance : Rs.%.2f", acc_read.balance);
            printf("\n------------------------------------------\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n[ERROR] Account No %d not found!\n", acc_no);
}

void delete_account()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open file!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL)
    {
        printf("\n[ERROR] Unable to create temporary file!\n");
        fclose(file);
        return;
    }

    int acc_no;
    Account acc_r;
    int found = 0;

    printf("\n------------------------------------------");
    printf("\n              DELETE ACCOUNT");
    printf("\n------------------------------------------");

    printf("\nEnter account number to delete: ");
    scanf("%d", &acc_no);

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            found = 1;
            printf("\n[OK] Account '%s' (A/C No: %d) deleted successfully!\n", acc_r.name, acc_no);
            continue; // Skip writing this record
        }
        fwrite(&acc_r, sizeof(acc_r), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove(ACCOUNT_FILE);
    rename("temp.dat", ACCOUNT_FILE);

    if (!found)
    {
        printf("\n[ERROR] Account No %d not found in records.\n", acc_no);
    }
}

int main()
{
    printf("\n==================================================");
    printf("\n        WELCOME TO BANK MANAGEMENT SYSTEM");
    printf("\n==================================================");

    while (1)
    {
        int choice;
        printf("\n\n==================== MAIN MENU ====================");
        printf("\n 1. Create Account");
        printf("\n 2. Deposit Money");
        printf("\n 3. Withdraw Money");
        printf("\n 4. Check Balance");
        printf("\n 5. Delete Account");
        printf("\n 6. Exit");
        printf("\n===================================================");
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            delete_account();
            break;
        case 6:
            printf("\n===================================================");
            printf("\n Thank you for banking with us! Goodbye!");
            printf("\n===================================================\n");
            return 0;
        default:
            printf("\n[ERROR] Invalid choice! Please try again.\n");
            break;
        }
    }
}
