/* Exercise 4.13 Write a recursive version of the function reverse(s) , 
 * which reverses the string s in place. */
#include <stdio.h>
#include <string.h>

void reverse_recursive(char str[], int start, int end);

int main () 
{
    char s[] = "Zedro 42!";

    printf("The string before reverse is : '%s'\n", s);
    reverse_recursive(s, 0, strlen(s)-1);
    printf("The string after reverse is : '%s'\n", s);
    return (0);
}

/* reverse_recursive :Recursively reverse the string s */
void reverse_recursive(char str[], int start, int end)
{
    char temp;

    if (start < end)
    {
        reverse_recursive(str, start+1, end-1);
        // Do the swap
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }
}
