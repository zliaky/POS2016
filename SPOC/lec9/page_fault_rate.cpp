#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_PAGE 100
#define MAX_TIME 1000

int working_set[MAX_PAGE];
int max_page;
int window_size;
int history[MAX_TIME];
int t_current;
int t_last;
int t;
int error_t;

void out()
{
	cout << "working set: ";
	for (int i = 0; i <= max_page; i++)
	{
		if (working_set[i] == true) cout << i << " ";
	}
	cout << endl;
}

void add(int page)
{
	working_set[page] = true;
}

void replace(int page)
{
	cout << "now replace" << endl;
	for (int i = 0; i <= max_page; i++)
	{
		working_set[i] = false;
	}
	for (int i = t_current-1; i > t_last; i--)
	{
		working_set[history[i]] = true;
	}
	add(page);
}

void init()
{
	for (int i = 0; i < MAX_PAGE; i++)
	{
		working_set[i] = false;
	}
	t_current = -1;
	t_last = -1;
	max_page = 0;
	t = 0;
	error_t = 0;
}

void output_result()
{
	cout << "===============" << endl;
	cout << "result:" << endl;
	cout << "Hits = " << t - error_t << endl;
	cout << "Misses = " << error_t << endl;
	cout << "Hit rate = " << (double)(t-error_t)/t << endl;
}

int main()
{
	cout << "Window size:";
	cin >> window_size;
	init();
	while (1)
	{
		cout << "===============" << endl;
		int page;
		cout << "step " << t << "         ";
		cout << "Page no:";
		cin >> page;
		if (page > max_page) max_page = page;
		history[t] = page;
		if (page < 0)
		{
			output_result();
			break;
		}
		if (working_set[page] == false)
		{
			error_t++;
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
		t++;
	}
	
	return 0;
}
