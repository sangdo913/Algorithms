#pragma once
#include<iostream>

using namespace std;
void Quick_Swap(int *arr, int x, int y)
{
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}
int Quick_COunt = 0;
void setPivot(int *arr, int left, int right)
{
	int values[3],mid = (left+right)/2;
	values[0] = arr[left];
	values[1] = arr[mid];
	values[2] = arr[right];
	int temp;
	if (values[0] > values[1])
	{
		Quick_Swap(values, 0, 1);
	}
	if (values[1] > values[2])
	{
		Quick_Swap(values, 1, 2);
	}

	if (values[0] < values[1])
	{
		Quick_Swap(values, 0, 1);
	}

	arr[left] = values[0]; arr[mid] = values[1]; arr[right] = values[2];
}

void Quicksort(int *arr, int left, int right)
{
	if (left >= right) return;
	setPivot(arr, left, right);
	int pivot = left, mid = (left+right)/2,low = left, high = right;

	while (low <= high)
	{
		while (low <= right && arr[low] <= arr[pivot])low++;
		while (high > pivot  && arr[high] >= arr[pivot]) high--;

		if (low < high) Quick_Swap(arr, low, high);
	}
	Quick_COunt++;
	Quick_Swap(arr, pivot, high);
	Quicksort(arr, left, high-1);
	Quicksort(arr, high+ 1, right);
	cout << Quick_COunt << endl;
}