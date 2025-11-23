#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void addition()
{
    float a, b;
    printf("\n➕ Enter first number: ");
    scanf("%f", &a);
    printf("➕ Enter second number: ");
    scanf("%f", &b);
    printf("✅ Sum of %.2f and %.2f is: %.2f\n", a, b, a + b);
}

void subtraction()
{
    float a, b;
    printf("\n➖ Enter first number: ");
    scanf("%f", &a);
    printf("➖ Enter second number: ");
    scanf("%f", &b);
    printf("✅ Subtraction of %.2f from %.2f is: %.2f\n", b, a, a - b);
}

void multiplication()
{
    float a, b;
    printf("\n✖️  Enter first number: ");
    scanf("%f", &a);
    printf("✖️  Enter second number: ");
    scanf("%f", &b);
    printf("✅ Multiplication of %.2f and %.2f is: %.2f\n", a, b, a * b);
}

void division()
{
    float a, b;
    printf("\n➗ Enter first number: ");
    scanf("%f", &a);
    printf("➗ Enter second number: ");
    scanf("%f", &b);
    if (b == 0)
    {
        printf("⚠️  Division by zero is not possible.\n");
        return;
    }
    printf("✅ Division of %.2f by %.2f is: %.2f\n", a, b, a / b);
}

void modulus()
{
    int a, b;
    printf("\n🧮 Enter first number: ");
    scanf("%d", &a);
    printf("🧮 Enter second number: ");
    scanf("%d", &b);
    if (b == 0)
    {
        printf("⚠️  Division by zero is not possible.\n");
        return;
    }
    printf("✅ Modulus of %d by %d is: %d\n", a, b, a % b);
}

void power()
{
    float a, b;
    printf("\n🔋 Enter base number: ");
    scanf("%f", &a);
    printf("🔋 Enter exponent number: ");
    scanf("%f", &b);
    if (b == 0)
    {
        printf("✅ %.2f raised to the power of %.2f is: 1\n", a, b);
        return;
    }
    printf("✅ %.2f raised to the power of %.2f is: %.5f\n", a, b, pow(a, b));
}

void square_root()
{
    float num;
    printf("\n🔢 Enter a number: ");
    scanf("%f", &num);
    if (num < 0)
    {
        printf("⚠️ Square root of a negative number is not a real number.\n");
        return;
    }
    printf("✅ Square root of %.2f is: %.5f\n", num, sqrt(num));
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul"); // Enable UTF-8 mode in Windows cmd

#endif

    int choice;
    printf("\n🎉 ---- Welcome to Simple Calculator ---- 🎉");

    do
    {
        printf("\n\n🔢 Please select an option from the menu below:");
        printf("\n1️⃣  Press 1 for Addition");
        printf("\n2️⃣  Press 2 for Subtraction");
        printf("\n3️⃣  Press 3 for Multiplication");
        printf("\n4️⃣  Press 4 for Division");
        printf("\n5️⃣  Press 5 for Modulus");
        printf("\n6️⃣  Press 6 for Power");
        printf("\n7️⃣  Press 7 for Square Root");
        printf("\n0️⃣  Press 0 for Exit");

        printf("\n\n👉 Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addition();
            break;

        case 2:
            subtraction();
            break;

        case 3:
            multiplication();
            break;

        case 4:
            division();
            break;

        case 5:
            modulus();
            break;

        case 6:
            power();
            break;

        case 7:
            square_root();
            break;

        case 0:
            printf("\n🙏 Thank you for using Simple Calculator. Goodbye! 👋\n");
            exit(0);

        default:
            printf("❌ Invalid choice. Please try again.\n");
            break;
        }
    } while (1);

    return 0;
}
