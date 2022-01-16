#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

const int SIZE = 100000;
int SortedArray[SIZE];                //3 arrays of size 100,000 are declared outside to evade stack overflow error.
int RandomArray[SIZE];
int DescendingArray[SIZE];


int partition(int T[], int FirstIndex, int LastIndex)
{
    int pivot, temp, loop, cutPoint;

    pivot = T[FirstIndex];              //Pivot was chosen arbitrarily as the first data (index 0).
    
    loop = 1;              //This loop acts as a condition, when its value is 1, it will continue to partition        
                           //and sort the array. Once it becomes 0, as you'll see in the upcoming lines, it
                           // will exit the partition function.
    while (loop)
    {
        while (T[LastIndex] > pivot)
        {
            LastIndex--;                        //These 2 while loops attempt to correctly place the pivot
        }                                       //value according to which of the array data is greater than 
                                                //it, and which is less than it. These 2 loops only do one
        while (T[FirstIndex] < pivot)           //round though, and not multiple at once.
        {
            FirstIndex++;
        }

        if (FirstIndex < LastIndex)             //Once the while loops locate the correct position, the pivot
        {                                       //is then swapped with the data value of the position located
            temp = T[FirstIndex];               //from the 2 while loops above. This swap depends on if the 
            T[FirstIndex] = T[LastIndex];       //'FirstIndex' value is less than 'LastIndex' value.
            T[LastIndex] = temp;
        }

        else                            //If 'FirstIndex' is not less than 'LastIndex', this means that the 
        {                               //partition function has made multiple rounds sorting the pivot into 
            loop = 0;                   //its correct position, and its good to go. Loop will be 0, stopping
            cutPoint = LastIndex;       //the function, and most importantly returning the index value of 
        }                               //the pivot as cutPoint back to the quicksort function.

    }

    return cutPoint;
}

void QuickSort(int arrayT[], int FirstIndex, int LastIndex)         //Recursive sorting algorithm
{
    int cutPoint;               //The index value of where the array is to be split.

    if (FirstIndex < LastIndex)         //Checks whether array contains more than one data value.
    {
        cutPoint = partition(arrayT, FirstIndex, LastIndex);    //Pivot index will be returned as the cutpoint once array is passed into the partition function.
        
        QuickSort(arrayT, FirstIndex, cutPoint);        //2 recursive calls will be made, one for the array 
                                                        //with data values less than cutpoint, and the other
        QuickSort(arrayT, cutPoint + 1, LastIndex);     //with data values less than cutpoint. The left side
    }                                                   //of the pivot array will be done first, then right
}                                                       //side will be done after. 

void bubbleSort(int array[], int size)
{
    int i, j;

    cout << "BubbleSortV1 is being used." << endl << endl;

    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
}

void bubbleSortV2(int array[], int size) {
    cout << " BubbleSortV2 is being used." <<endl<<endl;
    
    for (int i = 0; i < size; i++) 
    {
        int flag = false;                           //Optimized bubble sort function which has flag
                                                    //introduced into it for increased efficiency
        for (int j = 0; j < (size - i - 1); j++)
            if (array[j] > array[j + 1])
            {
                flag = true;
                int temp = array[j];                //Where the swapping occurs
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        if (flag == false)
        {
            cout << "Array is already sorted " << endl;
            break;
        }
    }
}

void SelectionSortV1(int array[], int n)
{
    cout << "Selection Sort V1 is being used." << endl << endl;

    int i, j, loc, temp, min;

    for (i = 0; i < n - 1; i++)
    {
        min = array[i];
        loc = i;
        for (j = i + 1; j < n; j++)
        {
            if (min > array[j])
            {
                min = array[j];
                loc = j;
            }
        }

        temp = array[i];
        array[i] = array[loc];
        array[loc] = temp;
    }

}

void SelectionSortV2(int* arr, int n)           //Function of the 2nd version of the selection sort
{
    cout << "Selection Sort V2 is being used." << endl << endl;
    
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int min = arr[i], max = arr[i];
        int min_i = i, max_i = i;
        for (int k = i; k <= j; k++) {
            if (arr[k] > max) {
                max = arr[k];
                max_i = k;
            }
            else if (arr[k] < min) {
                min = arr[k];
                min_i = k;
            }
        }

        swap(arr[i], arr[min_i]);       //swap function

        if (arr[min_i] == max)
            swap(arr[j], arr[min_i]);
        else
            swap(arr[j], arr[max_i]);
    }
}



void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++)              //Basic array print function.
    {
        cout << "[" << array[i] << "]";
    }

    cout << endl << endl;
}

bool isSorted(const int* ar, int size) {        //Function that checks whether array is sorted.
                                                //It will be useful in improving the QuickSort algorithm
    if (size == 0)                              //as it will help avoid its major downfall, sorting on already
        return true;                            //sorted arrays.

    int previous_value = *ar;

    while (size)
    {
        if (*ar < previous_value)
            return false;
        previous_value = *ar;

        ++ar;
        --size;
    }
    return true;
}

void QuickSortV2(int array[], int size)         //Improved version of the default QuickSort algorithm.
{                                               //It first checks whether the array is sorted or not using 
                                                // the isSorted function. If it is, it will exit the program
                                                //without calling the quicksort function. However, if its not,
                                                //it will call the quicksort function.
    
    if (isSorted(array, size))
    {
        cout << "Sorting is unnecessary. Array is already sorted." << endl << endl;
    }
    else
    {
        cout << "Quicksort will be used." << endl << endl;
        QuickSort(array, 0, size - 1);
    }
}

void FillArray(int* ArrayX, string FileName, int size)
{
    ifstream file;                                  //Function used to fill an array with input from an
                                                    //external file. I placed this outside the main to 
                                                    //avoid the stack overflow error.
    file.open(FileName);

    if (file.fail())
    {
        cout << "File of array not found." << endl << endl;
        exit(1);
    }

    int count = 0;
    while (!file.eof())
    {
        file >> ArrayX[count];
        count++;
    }

    file.close();
}

int main()
{
    FillArray(SortedArray, "sorted100kARRAY.txt", SIZE);     //Fill the 3 arrays be calling a function that
    FillArray(RandomArray, "random100kARRAY.txt", SIZE);     //will fill the arrays according to file names.
    FillArray(DescendingArray, "descending100kArray.txt", SIZE);

    cout << "Array used is:   ";
    print_array(DescendingArray, 10);             //Just to make sure of the array youre using.

    time_t time1, time2;
    clock_t start, end;
    double dif_sec;

    time(&time1);               //Time starts
    start = clock();

    SelectionSortV2(DescendingArray, SIZE);         

    time(&time2);               //Time stops
    end = clock();

    dif_sec = difftime(time2, time1);           //Total time is calculated and stored in 'dif_sec'.

    cout << "time_t: Algorithm started at " << time1 << " and ended at " << time2 << ", taking an approximate time of " << time2 - time1 <<" seconds to sort."<< endl;
    cout << "clock_t: Algorithm started at " << start << " and ended at " << end << ", taking a time of " << double(end-(double)start) / CLOCKS_PER_SEC <<" seconds to sort."<< endl << endl;

    print_array(DescendingArray, 10);         
}
