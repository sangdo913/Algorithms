#include<iostream>

using namespace std;

int ShareAndReminder()
{
   const char arr[5][6] =
   {
        "#++++",
        "+#+++",
        "++#++",
        "+++#+",
        "++++#"
   };

    for(int i = 0; i < 5; i++)
    {
        cout << arr[i] << '\n';
    }
    return 0;
}