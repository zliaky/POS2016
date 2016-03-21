#include <iostream>
#include <stdio.h>
using namespace std;

#define T_MAX 10

int working_set[100];
bool refer[100];
int size = 0;
int window_size;
int history[1010];
int t_current = -1;
int t_last = -1;
int max_page = 0;

int find(int n)
{
	for (int i = 0; i < size; i++)
	{
		if (working_set[i] == n) return i;
	}
	return -1;
}

void out()
{
	for (int i = 0; i < size; i++)
	{
		cout << working_set[i] << " ";
	}
	cout << endl;
}

void add(int page)
{
	working_set[size] = page;
	size++;
}

void replace(int page)
{
	cout << "now replace" << endl;
	for (int i = 0; i <= max_page; i++)
	{
		refer[i] =  false;
	}
	for (int i = t_current-1; i > t_last; i--)
	{
		refer[history[i]] = true;
	}
	for (int i = 0; i < size; i++)
	{
		if (refer[working_set[i]] == false)
		{
			for (int j = i; j < size-1; j++)
			{
				working_set[j] = working_set[j+1];
			}
			size--;
		}
	}
	add(page);
}

int main()
{
//	freopen("input.txt", "r", stdin);
	int t = 0;
	int history_size = 0;
	cout << "Window size:";
	cin >> window_size;
	while (1)
	{
		int page;
		cout << "step " << t << "         ";
		cout << "Page no:";
		cin >> page;
		if (page > max_page) max_page = page;
		history[history_size] = page;
		history_size++;
		if (page < 0)
		{
			cout << "error page no\n";
			break;
		}
		int it = find(page);
		if (it == -1)
		{
			t_current = t;
			cout << "page fault!   current time:" << t_current << "     last time:" << t_last << "\n";
			if (t_current-t_last<=window_size)
			{
				add(page);
			}
			else
			{
				replace(page);
			}
			t_last = t;
		}
		out();
		cout << "===============" << endl;
		t++;	
	}
	
	return 0;
}
