
#define SDL_MAIN_HANDLED
#define POINTS_COUNT 750

#include<SDL2/SDL.h>
#include<iostream>
#include<ctime>
using namespace std;

//Global Constants
const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 750;
int points[POINTS_COUNT];
int padding;

void BubbleSort(int arr[], int &j, int& k);
void draw( SDL_Renderer* renderer);
void merge(SDL_Renderer* renderer,int arr[], int l, int m, int r);
void mergeSort(SDL_Renderer* renderer,int arr[], int l, int r);
int partition(SDL_Renderer* renderer,int arr[], int low, int high);
void quickSort(SDL_Renderer* renderer,int arr[], int low, int high);
void InsertionSort(int arr[], int& j, int& k);
void CocktailSort(SDL_Renderer* renderer,int a[], int n);
void slowCocktailSort(SDL_Renderer* renderer, int a[], int n);
void swap(int* a, int* b);
void selectionSortT(SDL_Renderer* renderer, int arr[], int n);
void heapify(int arr[], int n, int i);
void heapSort(SDL_Renderer* renderer,int arr[], int n);

int main(int argc, char** argv) {
	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(static_cast<unsigned int>(time(0)));
	//Initializing Variables
	SDL_Window* win;
	SDL_Event event;
	SDL_Renderer* renderer;
	int i,j,k=0;
	bool gameLoop = true;
	bool startSort = false;
	bool startMergeSort = false;
	bool quick = false;
	bool startInsertionSort = false;
	bool textRendered = false;
	bool startCocktailsort = false;
	bool slowCocktailsort = false;
	bool selectionSort = false;
	bool startHeapSort = false;
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0,0,0 };
	
	//making random array;
	for ( i = 0; i < POINTS_COUNT; ++i) {
		points[i] = rand() % 550;

	}


	//Creating Window and renderer
	win = SDL_CreateWindow("Sort", 50, 50, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	//Main Game Loop
	while (gameLoop) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT ) {
			gameLoop = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_b) {
				startSort = true;
			}
			if (event.key.keysym.sym == SDLK_s) {
				startSort = false;
				startMergeSort = false;
			}
			if (event.key.keysym.sym == SDLK_n) {
				for (i = 0; i < POINTS_COUNT; ++i) {
					points[i] = rand() % 550;
					j = 0;
					k = 0;
					startSort = false;
					startMergeSort = false;
					startInsertionSort = false;
				}
			}
			if (event.key.keysym.sym == SDLK_m) {
				startMergeSort = true;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				exit(0);
			}
			if (event.key.keysym.sym == SDLK_q) {
				quick = true;
			}
			if (event.key.keysym.sym == SDLK_i) {
				startInsertionSort = true;
			}
			if (event.key.keysym.sym == SDLK_c) {
				startCocktailsort = true;
			}
			if (event.key.keysym.sym == SDLK_v) {
				slowCocktailsort = true;
			}
			if (event.key.keysym.sym == SDLK_t) {
				selectionSort = true;
			
			}
			if (event.key.keysym.sym == SDLK_h) {
				startHeapSort = true;
				
			}
		}

		//Drawing Part
		SDL_RenderPresent(renderer);
		draw(renderer);
		//sorting stuff
		if (startSort) {
			BubbleSort(points, j, k);
		}
		else if (startMergeSort) {
			mergeSort(renderer, points, 0, 749);
			startMergeSort = false;
		}
		else if (quick) {
			quickSort(renderer,points, 0, 749);
			quick = false;
		}
		else if (startInsertionSort) {
			InsertionSort(points, j, k);
		}
		else if (startCocktailsort) {
			CocktailSort(renderer,points, POINTS_COUNT);
			startCocktailsort = false;
		}
		else if (slowCocktailsort) {
			slowCocktailSort(renderer, points, POINTS_COUNT);
			slowCocktailsort = false;
		}
		else if (selectionSort) {
			selectionSortT(renderer,points, POINTS_COUNT);
			selectionSort = false;
		}
		else if (startHeapSort) {
			heapSort(renderer,points, POINTS_COUNT);
			startHeapSort = false;
		}

	}
	
	

	//Destroying Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	return 0;
}
void draw( SDL_Renderer* renderer) {
	int padding = 25;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < POINTS_COUNT; i++)
	{
		SDL_RenderDrawLine(renderer, padding + i, 0, padding + i, points[i]);
	}
	SDL_RenderPresent(renderer);

}
void BubbleSort(int arr[], int& j, int& k) {
	int temp;
	if (k < POINTS_COUNT) {
		for (j = 0; j < POINTS_COUNT; ++j) {
			if (points[j] > points[j + 1]) {
				temp = points[j];
				points[j] = points[j + 1];
				points[j + 1] = temp;
			}
		}
	}

	if (j < POINTS_COUNT - k - 1) {
		k++;
	}

}
void selectionSortT(SDL_Renderer* renderer, int arr[], int n)
{
	int i, j, min_idx;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		swap(&arr[min_idx], &arr[i]);
		draw(renderer);
	}
}
void merge(SDL_Renderer* renderer,int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int* L = new int[n1];
	int* R= new int[n2];

  
	for (int i = 0; i < n1; i++) {
		draw(renderer);
		L[i] = arr[l + i];
	}
	for (int j = 0; j < n2; j++) {
		draw(renderer);
		R[j] = arr[m + 1 + j];
	}

	int i = 0;

 
	int j = 0;

	int k = l;

	while (i < n1 && j < n2)
	{
		draw(renderer);
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		draw(renderer);
		arr[k] = L[i];
		i++;
		k++;
	}


	while (j < n2)
	{
		draw(renderer);
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}
void mergeSort(SDL_Renderer* renderer,int arr[], int l, int r)
{
	if (l < r)
	{


		int m = l + (r - l) / 2;
		mergeSort( renderer,arr, l, m);
		mergeSort(renderer,arr, m + 1, r);

		merge( renderer,arr, l, m, r);
	}
}
int partition(SDL_Renderer* renderer,int arr[], int low, int high)
{
	int pivot = arr[high];    
	int i = (low - 1);  
	for (int j = low; j <= high - 1; j++)
	{

		if (arr[j] <= pivot)
		{
			i++;    
			swap(&arr[i], &arr[j]);
		}
		draw(renderer);
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void quickSort(SDL_Renderer* renderer,int arr[], int low, int high)
{
	if (low < high)
	{

		int pi = partition(renderer,arr, low, high);


		quickSort(renderer,arr, low, pi - 1);
		quickSort(renderer,arr, pi + 1, high);
	}
}
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void InsertionSort(int arr[], int& j, int& k) {
	int key;
	if (k < POINTS_COUNT) {
		key = arr[k];
		j = k - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}

	if (j < POINTS_COUNT) {
		k++;
	}

}
void CocktailSort(SDL_Renderer* renderer,int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) {

		swapped = false;

			for (int i = start; i < end; ++i) {
				if (a[i] > a[i + 1]) {
					swap(a[i], a[i + 1]);
					swapped = true;
				}
			}
				draw(renderer);

		if (!swapped)
			break;

		swapped = false;

		--end;

			for (int i = end - 1; i >= start; --i) {
				if (a[i] > a[i + 1]) {
					swap(a[i], a[i + 1]);
					swapped = true;
				}
			}
				draw(renderer);
 
		++start;
	}
}
void slowCocktailSort(SDL_Renderer* renderer, int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) {

		swapped = false;


		for (int i = start; i < end; ++i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
				draw(renderer);
			}
		}

		if (!swapped)
			break;

		swapped = false;

		--end;

		for (int i = end - 1; i >= start; --i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
				draw(renderer);
			}
		}

 
		++start;
	}
}
void heapify(int arr[], int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}
void heapSort(SDL_Renderer* renderer,int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		draw(renderer);
		heapify(arr, i, 0);
	}
}
