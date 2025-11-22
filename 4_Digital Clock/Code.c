#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void fill_time(char *buffer, int format)
{
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);
    if (format == 1)
    {
        strftime(buffer, 50, "%H:%M:%S", current_time);
    }
    else
    {
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
}

void fill_date(char *buffer)
{
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);

    strftime(buffer, 100, "%A, %B %d, %Y", current_time);
}

int input_format()
{
    int format;
    printf("\n🕒 Choose the time format: ");
    printf("\n1. 24 Hour format");
    printf("\n2. 12 Hour format (default)");
    printf("\n👉 Make a choice(1/2): ");
    scanf("%d", &format);

    if (format != 1 && format != 2)
    {
        printf("Invalid input. Defaulting to 12-hour format.\n");
        format = 2;
        while (getchar() != '\n')
            ; // Clear input buffer
    }
    return format;
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{

#ifdef _WIN32
    system("chcp 65001 > nul"); // Enable UTF-8 mode in Windows cmd

#endif

    char time[50], date[100];
    int format = input_format();

    printf("\n🚀 Clock starting! Press Ctrl+C to stop.\n");
    sleep(3);

    while (1)
    {
        fill_time(time, format);
        fill_date(date);
        clear_screen();
        printf("⏰ Current Time: %s\n", time);
        printf("📅 Date: %s\n", date);
        sleep(1);
    }
    return 0;
}
