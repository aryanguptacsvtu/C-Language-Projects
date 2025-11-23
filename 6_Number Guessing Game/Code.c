#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul"); // Enable UTF-8 mode in Windows cmd
#endif

    int random, guess, count;
    char choice;

    printf("--- Welcome to Number Guessing Game ---\n");

    do
    {
        srand(time(0));
        random = rand() % 100 + 1;
        count = 0;

        printf("\n🎮 New Game Started! Guess a number between 1 to 100.\n");

        do
        {
            printf("\n👉 Enter your guess: ");
            scanf("%d", &guess);
            count++;

            if (guess > random)
            {
                printf("🔻 Lower number please!\n");
            }
            else if (guess < random)
            {
                printf("🔺 Higher number please!\n");
            }
            else
            {
                printf("\n🎉 Congratulations!! You guessed it in %d attempts 🎉\n", count);
            }

        } while (guess != random);

        printf("✅ The random number was: %d\n", random);
        printf("👋 Thanks for playing!!\n");

        printf("\n🔁 Do you want to play again? (Y/N): ");
        scanf(" %c", &choice);
        choice = tolower(choice);

    } while (choice == 'y');

    printf("\n👋 Game exited. Goodbye!\n");
    return 0;
}
