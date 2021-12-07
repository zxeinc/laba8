#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <queue>
using namespace std;

void matrix(int** g , int size)
{
	int n = 1;

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		g[i] = (int*)malloc(size * sizeof(int));
		g[i][i] = 0;

		for (int j = n; j < size; j++)
		{
			if (rand() % 100 > 72) 
			{
				g[i][j] = 0;
			}
			else
			{
				g[i][j] = rand() % size;
			}
		}
		n++;
	}
	n = 1;
	for (int i = 0; i < size; i++)
	{
		for (int j = n; j < size; j++)
			g[j][i] = g[i][j];
		n++;
	}

	for (int i = 0; i < size; i++)
		{
		printf("%2d ", i + 1);
		}

	printf("\n");

	for (int i = 0; i < size; i++) 
		{
			printf("___");
		}
	for (int i = 0; i < size; i++)
	{
		printf("\n");
		for (int j = 0; j < size; j++)
		{
			printf("%2d ", g[i][j]);
		}
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("___");
	}
}


void BFSD(int v, int* dist, int** g, int size)
{
	queue <int> q;
	q.push(v);
	dist[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();


		for (int i = 0; i < size; i++)
		{

			if ((g[v][i] > 0) && (dist[i]) > dist[v] + g[v][i])
			{
				q.push(i);
				dist[i] = dist[v] + g[v][i];
			}

		}

	}
	//printf("\n\n");
	//for (int i = 0; i < size; i++)
	//{
	//	printf("%d ", dist[i]);
	//}
}



void F(int** g, int size)
{
	int d = -1, r = 10000, n = 0;
	int* dist = (int*)malloc(size * sizeof(int));
	int* k = (int*)malloc(size * sizeof(int)), * is = (int*)malloc(size * sizeof(int)), * kon = (int*)malloc(size * sizeof(int)), * dom = (int*)malloc(size * sizeof(int)), * extra = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++) 
		{
			dist[k] = 9999;
		}
		BFSD(i, dist, g, size);
		for (int j = 0; j < size; j++)
		{
			if (extra[i] < dist[j] && dist[j] != 9999) 
			{
				extra[i] = dist[j];
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (d < extra[i])
		{
			d = extra[i];
		}
		if (r > extra[i] && extra[i] != 0)
		{
			r = extra[i];
		}
	}
	for (int i = 0; i < size; i++) 
	{
		k[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (g[i][j] > 0)
			{
				k[i]++;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		is[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		if (k[i] == 0) 
		{
			is[i] = 1;
		}
	}
	for (int i = 0; i < size; i++) 
	{
		kon[i] = 0;
	}
	for (int i = 0; i < size; i++) 
	{
		if (k[i] == 1) 
		{
			kon[i] = 1;
		}
	}
	for (int i = 0; i < size; i++)
	{
		dom[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		if (k[i] == size - 1) 
		{
			dom[i] = 1;
		}
	}
	printf("\nR: %d\n", r);
	printf("D: %d\n", d);
	printf("Эксцентриситет:");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", extra[i]);
	}
	printf("\nПереферийные вершины:");
	for (int i = 0; i < size; i++)
	{
		if (extra[i] == d) printf("%d ", i + 1);
	}
	printf("\nЦентральные вершины:");
	for (int i = 0; i < size; i++) 
	{
		if (extra[i] == r) 
		{ 
			printf("%d ", i + 1);
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (is[i] == 1)
		{
			printf("\nИзолированная: %d", i + 1);
		}
		//else
		//{
		//	printf("\nНе изолированная: %d", i + 1);
		//}
	}
	for (int i = 0; i < size; i++)
	{
		if (kon[i] == 1) {
			printf("\nКонцевая: %d", i + 1);
		}
		//else
		//{
		//	printf("\nНе концевая: %d", i + 1);
		//}
	}
	for (int i = 0; i < size; i++) 
	{
		if (dom[i] == 1) {
			printf("\nДоминантная: %d", i + 1);
		}
		//else
		//{
		//	printf("\nНе доминантная: %d", i + 1);
		//}
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");

	int i = 0;
	int j = 0;
	int size = 0;
	int** g = 0;
	int v = 0;

	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	printf("Размер матрицы: ");
	scanf("%d", &size);

	g = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
	{
		g[i] = (int*)malloc(size * sizeof(int));
	}

	matrix(g,size);

	int* dist = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		dist[i] = INT16_MAX;
	}


	F(g, size);

	printf("\n");

	system("pause");
}
