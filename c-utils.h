/* declarations for quicksort */
#define arraySize 10
extern int *a; // pointer for the array to be sorted
/* function declarations */
void swap(int *, int, int);
int partition(int *, int, int);
void sortArray(int *, int, int);
void printArray(int *, int);
int * randArray(int, int);

/* declarations for gcd */
#define MOD(x) ((x) < 0 ? -x : x)
int gcd(int, int); //function prototype
