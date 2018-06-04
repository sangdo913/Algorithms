#include<iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>

using namespace std;
typedef int BLOCK[4];

void cpy(BLOCK a, BLOCK b)
{
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
}
void print(BLOCK a)
{
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
}

void swap(int& i1, int& i2)
{
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

bool func(int i1, int i2)
{
    return i1 < i2;
}

void QuickSort(int arr[], int left, int right)
{
    int l = left + 1, r = right;

    while(true)
    {
        while(l < right && !func(arr[left], arr[l])) l++;
        while(r > left && !func(arr[r], arr[left])) r--;

        if(l < r) 
        {
            swap(arr[l], arr[r]);
        }
        else break;
    }

    swap(arr[left], arr[r]);

    if(left < r - 1) QuickSort(arr, left, r - 1);
    if(right > r + 1) QuickSort(arr, r + 1, right);

}

int main()
{
    int arr[100];
    srand(time(NULL));
    int tc = 100;

    while(tc--)
    {
        for (int i = 0; i < 10; i++)
        {
            arr[i] = rand()% 100;
        }

        QuickSort(arr, 0, 9);

        printf("After : ");
        for (int i = 0; i < 10; i++)
        {
            printf("%2d ", arr[i]);
        }
        
        bool res = true;
        for(int i = 0; i < 9; i++)
        {
            if(arr[i] > arr[i+1]) 
            {
                res = false;
                printf("FALSE\n");
                break;
            }
        }

        if(res) printf("TRUE\n");
        printf("\n");
    }
        return 0;
}