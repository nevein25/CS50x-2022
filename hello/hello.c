#include <stdio.h>
#include <cs50.h>
int main(void)

{
    //taking user's name
    string name = get_string("Enter yout name: ");
    printf("Hello, %s\n", name);
}