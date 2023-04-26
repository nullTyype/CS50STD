#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Gets name
    string name = get_string("Name: ");
    // Prints name
    printf("Hello, %s\n", name);
}