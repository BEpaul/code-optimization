#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


int circle_count = 0;
int num_threads;
int num_per_thread;
pthread_mutex_t m;

void insert_sort(int *arr, int length) 
{
	int i, j, temp;
	for (i = 1; i < length; i++) {
		temp = arr[i];
		for (j = i-1; (j > 0) && (arr[j-1] > temp); j--) {
			arr[j+1] = arr[j];
		}
		arr[j+1] = temp;
	}
}

void quick_sort(int arr[], int L, int R)
{
	int left = L;
	int right = R;
	int temp;

	do
	{
		while (arr[left] < arr[(L + R) / 2])
		{
			left++;
		}
		while (arr[right] > arr[(L + R) / 2])
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

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
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

	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

long atoint(const char *S)
{
	long num = 0;
	int i = 0;

	while (S[i])
	{
		if (S[i] >= '0' && S[i] <= '9') {
			num = num * 10 + (S[i] - '0');
			i++;
		}
		else {
			break;
		}
	}

	return num;
}

double calc_square(double k)
{
	double s;
	s = k * k;

	return s;
}

double rand_double()
{
	double result;
	result = random() / (double)RAND_MAX;

	return result;
}

void *monte(void *arg)
{
	int point_in_circle = 0;
	double x, y;

	for (int i = 0; i < *((int *)arg); i++)
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
	int numbers_bubble[100000];
	int numbers_select[100000];
	int numbers_quick[100000];
	int numbers_insert[100000];

	// 버블정렬
	for (int j = 0; j < sizeof(numbers_bubble) / sizeof(int); j++)
	{ 
		numbers_bubble[j] = rand() % (sizeof(numbers_bubble) / sizeof(int));
	}

	for (int k = 0; k < sizeof(numbers_bubble) / sizeof(int); k++)
	{
		printf("bubble number: %d\n", numbers_bubble[k]);
	}

	bubble_sort(numbers_bubble, sizeof(numbers_bubble) / sizeof(int));

	printf("======== bubble sorting ========\n");

	for (int k = 0; k < sizeof(numbers_bubble) / sizeof(int); k++)
	{
		printf("after bubble number: %d\n", numbers_bubble[k]);
	}

	// 선택정렬
	for (int j = 0; j < sizeof(numbers_select) / sizeof(int); j++)
	{
		numbers_select[j] = rand() % (sizeof(numbers_bubble) / sizeof(int));
	}

	for (int k = 0; k < sizeof(numbers_select) / sizeof(int); k++)
	{
		printf("select number: %d\n", numbers_select[k]);
	}


	selection_sort(numbers_select, sizeof(numbers_select) / sizeof(int));

	printf("======== selection sorting ========\n");

	for (int k = 0; k < sizeof(numbers_select) / sizeof(int); k++)
	{
		printf("after select number: %d\n", numbers_select[k]);
	}

	// 퀵 정렬
	for (int j = 0; j < sizeof(numbers_quick) / sizeof(int); j++)
	{
		numbers_quick[j] = rand() % (sizeof(numbers_quick) / sizeof(int));
	}

	for (int k = 0; k < sizeof(numbers_quick) / sizeof(int); k++)
	{
		printf("quick number: %d\n", numbers_quick[k]);
	}

	printf("======== quick sorting ========\n");

	quick_sort(numbers_quick, 0, sizeof(numbers_quick) / sizeof(int));

	for (int k = 0; k < sizeof(numbers_quick) / sizeof(int); k++)
	{
		printf("after quick number: %d\n", numbers_quick[k]);
	}

	// 삽입 정렬
	for (int j = 0; j < sizeof(numbers_insert) / sizeof(int); j++)
	{
		numbers_insert[j] = rand() % (sizeof(numbers_insert) / sizeof(int));
	}

	for (int k = 0; k < sizeof(numbers_insert) / sizeof(int); k++)
	{
		printf("insert number: %d\n", numbers_insert[k]);
	}

	printf("======== insert sorting ========\n");

	insert_sort(numbers_insert, sizeof(numbers_insert) / sizeof(int));

	for (int k = 0; k < sizeof(numbers_insert) / sizeof(int); k++)
	{
		printf("after insert number: %d\n", numbers_insert[k]);
	}

	num_per_thread = atoint(argv[2]);
	double pi;

	pthread_t tid[atoint(argv[1])];
	pthread_mutex_init(&m, NULL);
	srandom((unsigned)time(NULL));

	for (int i = 0; i < atoint(argv[1]); i++)
		pthread_create(&tid[i], 0, monte, &num_per_thread);
	for (int i = 0; i < atoint(argv[1]); i++)
		pthread_join(tid[i], NULL);

	pi = 4.0 * circle_count / (atoint(argv[2]) * atoint(argv[1]));
	printf("%lf\n", pi);

	return 0;
}