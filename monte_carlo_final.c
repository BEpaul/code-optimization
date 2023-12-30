#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define MAXVALUE 100000

int circle_count = 0;
int num_threads;
int num_per_thread;
pthread_mutex_t m;

void insert_sort(int *arr, int length)
{
	int i, j, temp;
	for (i = 1; i < length; i++)
	{
		temp = arr[i];
		for (j = i - 1; (j > 0) && (arr[j - 1] > temp); j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

void quick_sort(int arr[], int L, int R)
{
	int left = L;
	int right = R;
	int temp;
	int pivot = arr[(L + R) / 2];
	do
	{
		while (arr[left] < pivot)
		{
			left++;
		}
		while (arr[right] > pivot)
		{
			right--;
		}
		if (left <= right)
		{
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			left++;
			right--;
		}
	} while (left <= right);

	if (L < right)
	{
		quick_sort(arr, L, right);
	}

	if (left < R)
	{
		quick_sort(arr, left, R);
	}
}

void selection_sort(int *value, int n)
{
	int i, j;
	int min = 0;
	int temp = 0;
	int N = n;

	for (i = 0; i < N - 1; i++)
	{
		min = i;
		for (j = i + 1; j < N; j++)
		{
			if (value[min] > value[j])
			{
				min = j;
			}
		}

		temp = value[i];
		value[i] = value[min];
		value[min] = temp;
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, temp;
	int flag;

	for (i = n - 1; flag && (i > 0); i--)
	{
		for (j = 0; j < i; j++)
		{
			flag = 0;
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

long atoint(const char *S)
{
	long num = 0;
	int i = 0;

	while (S[i] && (S[i] >= '0' && S[i] <= '9'))
	{
		num = num * 10 + (S[i] - '0');
		i++;
	}

	return num;
}

double calc_square(double k)
{
	return k * k;
}

double rand_double()
{
	return random() / (double)RAND_MAX;
}

void *monte(void *arg)
{
	int point_in_circle = 0;
	int id = *((int *)arg);
	double x, y;

	for (int i = 0; i < id; i++)
	{
		x = rand_double();
		y = rand_double();
		if (calc_square(x) + calc_square(y) < 1.0)
			point_in_circle += 1;
	}

	pthread_mutex_lock(&m);
	circle_count += point_in_circle;
	pthread_mutex_unlock(&m);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int numbers_bubble[MAXVALUE];
	int numbers_select[MAXVALUE];
	int numbers_quick[MAXVALUE];
	int numbers_insert[MAXVALUE];

	// 버블정렬
	for (int j = 0; j < MAXVALUE; j++)
	{ 
		numbers_bubble[j] = rand() % MAXVALUE;
	}

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("bubble number: %d\n", numbers_bubble[k]);
	}

	bubble_sort(numbers_bubble, MAXVALUE);

	printf("======== bubble sorting ========\n");

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("after bubble number: %d\n", numbers_bubble[k]);
	}

	// 선택정렬
	for (int j = 0; j < MAXVALUE; j++)
	{
		numbers_select[j] = rand() % MAXVALUE;
	}

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("select number: %d\n", numbers_select[k]);
	}


	selection_sort(numbers_select, MAXVALUE);

	printf("======== selection sorting ========\n");

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("after select number: %d\n", numbers_select[k]);
	}

	// 퀵 정렬
	for (int j = 0; j < MAXVALUE; j++)
	{
		numbers_quick[j] = rand() % MAXVALUE;
	}

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("quick number: %d\n", numbers_quick[k]);
	}

	printf("======== quick sorting ========\n");

	quick_sort(numbers_quick, 0, MAXVALUE);

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("after quick number: %d\n", numbers_quick[k]);
	}

	// 삽입 정렬
	for (int j = 0; j < MAXVALUE; j++)
	{
		numbers_insert[j] = rand() % MAXVALUE;
	}

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("insert number: %d\n", numbers_insert[k]);
	}

	printf("======== insert sorting ========\n");

	insert_sort(numbers_insert, MAXVALUE);

	for (int k = 0; k < MAXVALUE; k++)
	{
		printf("after insert number: %d\n", numbers_insert[k]);
	}

	num_threads = atoint(argv[1]);
	num_per_thread = atoint(argv[2]);
	double pi;

	pthread_t tid[num_threads];
	pthread_mutex_init(&m, NULL);
	srandom((unsigned)time(NULL));

	for (int i = 0; i < num_threads; i++)
		pthread_create(&tid[i], 0, monte, &num_per_thread);
	for (int i = 0; i < num_threads; i++)
		pthread_join(tid[i], NULL);

	pi = 4.0 * circle_count / (num_per_thread * num_threads);
	printf("%lf\n", pi);

	return 0;
}