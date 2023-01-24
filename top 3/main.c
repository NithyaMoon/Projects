/* This program is modeled on the cartesian plane to find coordinates of all monsters around you in a city, in the program it sorts the location 
based on their distance. It idenitifies if their is a monster at a location and if so there is a rank on a sorted list of monsters. 
This program is written by: Nithya Munagala*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "leak_detector_c.h"

// global variables
typedef struct coordinate
{
int x;
int y;
}coordinate;

coordinate X;
coordinate Y;

FILE *filePtr;

// function prototypes
void merge(coordinate coords[], int l, int m, int h);//
void mergeSort(coordinate coords[], int l, int h, int t);  //
void insertionSort(coordinate coords[],int l, int h); // 
void sort(coordinate coords[], int len, int t ); // 

int compareTo(coordinate *firstPtr, coordinate *SecPtr); //
coordinate *readData(coordinate array[], int len); //
int binarySearch(coordinate array[], int len, coordinate hand);

//main function
int main()
{
    //variable declaration 
  //atexit (report_mem_leak);
  int len;
  int s;
  int threshold;
  int i;

  filePtr = fopen("out.txt", "w");

//creating hand and array for coords
  coordinate hand;

//scans coords, reads the number of cords, and sorts them in ascending order
  scanf("\n%d %d %d %d %d", &X.x, &Y.y, &len, &s, &threshold);

  coordinate *tempArray;

  tempArray = readData(tempArray, len);
  sort(tempArray, len, threshold);
  
//prints cords using compareto
  for(i = 0; i<len; i++)
    {
      printf("%d %d\n", tempArray[i].x, tempArray[i].y);
      fprintf(filePtr, "%d %d\n", tempArray[i].x, tempArray[i].y);
    }
  
   //loop to find s cords and print output to file
  for(i = 0; i <s; i++)
    {
      scanf("%d %d", &hand.x, &hand.y);
      
      int counter = binarySearch(tempArray, len, hand);
      //loop for if key is not found
      if (counter == -1)
      {
        printf("%d %d not found\n",hand.x,hand.y);
        fprintf(filePtr, "%d %d not found\n",hand.x,hand.y);
      }
        //loop for if key is found
      else
      {
        printf("%d %d found at rank %d\n", hand.x, hand.y, counter+1);
        fprintf(filePtr, "%d %d found at rank %d\n", hand.x, hand.y, counter+1);
      }
    }
  free(tempArray);   
  return 0;
}

//compares both pointers and returns distance
int compareTo(coordinate *firstPtr, coordinate *SecPtr)
{
    //calculation for distance between pointers
  int distance1 = ((int) pow(X.x - firstPtr->x, 2) +(int) pow(Y.y - firstPtr->y,2));
  int distance2 = ((int) pow(X.x - SecPtr ->x, 2) + (int) pow(Y.y - SecPtr->y,2));

    //loops to return value to whether distances are bigger than, less than, or equal to
  if(distance1 < distance2)
  {
    return -1;
  }
  
  else if(distance1 > distance2)
  {
    return 1;
  }
  
  else
  {
        //loops for if pointers for x are larger than, similar to above loops
    if (firstPtr->x < SecPtr->x)
    {
      return -1;
    }
    
    else if(firstPtr->x > SecPtr ->x)
    {
      return 1;
    }
    
    else
    {
      if(firstPtr->y < SecPtr->y)
      {
        return -1;
      }
      
      else if(firstPtr->y > SecPtr->y)
      {
        return 1;
      }
        
      else
      {
        return 0;
      }
    }
  }
}

int binarySearch(coordinate array[], int len, coordinate hand)
{
  //variable declaration
  int l = 0;
  int h = len-1;

  //loops and searches for mid
  while(l <= h)
  {
  //mid formula
    int m = (l+h)/2;
    
    float distance = compareTo(&hand, &array[m]);
    
    if(distance == 0)
    {
      return m;
    }
    
    else if (distance < 0)
    {
      h = m-1;
    }
    
    else
    {
      l = m + 1;
    }
  }
return -1;
  }

void merge(coordinate array[], int l, int m, int r)
{
  //variable declaration
  int i;
  int j;
  int k;
  int p1 = m - l + 1;
  int p2 = r - m;   

//mallocs subarrays 
  coordinate *L = malloc(p1*sizeof(coordinate));
  coordinate *R = malloc(p2*sizeof(coordinate));

  //copies subarray data
  for(i=0; i<p1; i++)
    L[i] = array[l + i];
  for(j=0; j<p2;j++)
    R[j] = array[m + 1 + j];

     i = 0;
     j = 0;
     k = l;

  //merges subarray and the sort with compareto function 
  while (i < p1 && j < p2)
  {
    if (compareTo(&L[i], &R[j]) <=0)
    {
      array[k] = L[i];
      i++;
    }
    else
    {
      array[k] = R[j];
      j++;
      }
    k++;
    }
  
  while ( i < p1)
  {
    array[k] = L[i];
    i++;
    k++;
  }

  
  while(j < p2)
  {
    array[k] = R[j];
    j++;
    k++;
  }
  //frees left and right
  free(L);
  free(R);
}

void mergeSort(coordinate array[], int l, int r, int threshold)
{
  //variable declaration
  int len = (l - r) + 1;
  
  //loop to check if subarray is less than threshold 
  if (len <= threshold)
  {
    insertionSort(array, l, r);
  }
    
  else
  {
    //formula for mid along with mergesorts for left, right, and merged subarrays
    int m = (l+r)/2;
    
    mergeSort(array, l, r, threshold);
    mergeSort(array, m+1,r, threshold);
    merge(array, l, m,r);
  }
}

//creates a sort function to input array from low to high
void insertionSort(coordinate array[], int l, int h)
{
  //variable declaration 
  int i;
  int j;
  
  //temporarily holds data
  coordinate hand;

  //loop in order to check second value and compare values
  for(i = l+1; i<= h; i++)
{
  j = i - 1;
  hand = array[i];
  
  while(j>=l && compareTo(&hand, &array[j]) < 0)
  {
    array[j + 1] = array[j];
    j--;
        }
        array[j + 1] = hand;
    }
}
//sorts the array based off threshold
void sort (coordinate coords[], int len, int threshold)
{
  if (len<= threshold)
  {
//creates loop to check whether n is less than or above t (aka. length larger than threshold)
    insertionSort(coords, 0, len-1);
  }
  
  else
  {
    mergeSort(coords, 0, len-1, threshold);
  }
}
  
//reads for number of coordinates
coordinate *readData(coordinate array[], int len)
{
  //mallocs coordinate
  coordinate *tempArray = malloc(len *sizeof(coordinate));
  //variable declaration
  int i = 0;
  //loop to find number of coords
  while (i<len)
  {
    scanf("%d %d", &tempArray[i].x, &tempArray[i].y);
    i++;
  }
  return tempArray;
}

