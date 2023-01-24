// COP 3502C Programming Assignment 5
/*  This program takes an unordered stream of distinct strings containing only one word and lowercase letters with a maximum of 50. As soon as the string is received, it will print the median of the strings. If it has an even number of items we have two numbers in the middle and that median will be the average of those two numbers.      */
//This program is written by: Nithya Munagala 

//libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"
#define maxCHAR 51
//file output function
FILE  *out;

// struct for the heap structure
typedef struct heapStruct {
// double pointer for the heap arrays
    char** heap_arr;
    int capacity;
    int size;
}heapStruct;

// variable declarations
heapStruct *initHeap(int n);
void insert(heapStruct *h, char input[], char p);
void percUP(heapStruct *h, int index, char p);
void percDOWN(struct heapStruct *h, int index, char p);
char* removeMin(struct heapStruct *h);
char* removeMax(struct heapStruct *h);
void swap(heapStruct *h, int index1, int index2);
int min(char a[], int indexOfA, char b[], int indexOfB);
int max(char a[], int indexOfA, char b[], int indexOfB);
int compTo(char str1[], char str2[]);
void freeHeap(heapStruct *h,int n);
void printMedian(int n);

//main function
int main(){
  // variable declaration
  int n;
  atexit(report_mem_leak);
  // opens up file
  out = fopen("out.txt", "w");
  // scans in median and prints out then returns function
  scanf("%d", &n);
  printMedian(n);
  return 0;
}

//prints median 
void printMedian(int n){
  
  // struct declaration and strlen
    char input[maxCHAR];
    heapStruct *left;
    heapStruct *right;
    char median[maxCHAR];
    int comp;
    char* buffer;
  
// variable declaration to find median
    left = initHeap(n);
    right = initHeap(n);
    char maximum = 'm';
    char min = 'n';
  
// scans for string and inserts
      scanf("%s", input);
      strcpy(median, input);

      insert(left, input, maximum);

      printf("%s\n", median);
      fprintf(out, "%s\n", median);
  
// for loop for values
      for(int i=0; i<n-1; i++)
      {
        // scan val
          scanf("%s", input);
          comp = compTo(input, median);
        
        // if the left side is equal to right then
          if(left->size==right->size)
          {
            //and if it is less than 0
              if(compTo(input,left->heap_arr[1])<0){
                //inserts maximum value of left
                  insert(left,input, maximum);
                  strcpy(median,left->heap_arr[1]);
              }
                //otherwise
              else if(compTo(input, right->heap_arr[1])>0)
              {
                //inserts minimum to the right
                  insert(right,input, min);
                  strcpy(median,right->heap_arr[1]);
              }
              else
              {
                //otherwise inserts maximum found in left
                  insert(left,input, maximum);
                  strcpy(median,left->heap_arr[1]);
              }
            
            //prints out median 
              printf("%s\n", median);
              fprintf(out, "%s\n", median);
          }
            //if left is greater the right
          else if(left->size>right->size)
          {
              if(comp<0)
              {
                //then removes the max
                  buffer = removeMax(left);
                //and inserts min in right
                  insert(right, buffer, min);                    
                //and max in left
                  insert(left, input, maximum);
              }
            //if comparision is greater than 0
              if(comp>0)
              {
                //inserts right input
                  insert(right, input, min);
              }
            //prints out right array
              printf("%s %s\n", left->heap_arr[1], right->heap_arr[1]);
              fprintf(out, "%s %s\n", left->heap_arr[1], right->heap_arr[1]);
          }
            //if left side is less than right side
          else if(left->size<right->size)
          {
            //if comparision is more than 0
              if(comp>0)
              {
                //buffer removes the minimum of right
                  buffer = removeMin(right);
                //then inserts the max of left
                  insert(left, buffer, maximum);
                  insert(right, input, min);
              }
            //if comparision is less than 0
              if(comp<0)
              {
                // insert left 
                  insert(left, input, maximum);
              }
            // prints out the vals of the list along with file output
              printf("%s %s\n", left->heap_arr[1], right->heap_arr[1]);
              fprintf(out, "%s %s\n", left->heap_arr[1], right->heap_arr[1]);
          }
      }
  //closes file along with frees left and right heap
    free(buffer);
    freeHeap(left,n);
    freeHeap(right,n);
    fclose(out);
}

//init heap function
heapStruct* initHeap(int n) 
{
  // variable declaration
    struct heapStruct* h;

  // creates space for structure
    h = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
    h->capacity = n;
    h->heap_arr = malloc(sizeof(char *)*(n+1));
    for(int i =0; i<(n+1); i++)
    {
      // creates size for heap
        h->heap_arr[i] = malloc(sizeof(char)*maxCHAR);
    }
    h->size = 0;
    return h;
}

//insert function
void insert(struct heapStruct *h, char input[], char p) 
{
  // if size is of capactiy then
    if (h->size == h->capacity) 
    {
      // reallocate space
        h->heap_arr = realloc(h->heap_arr, sizeof(char)*(2*h->capacity+1));
        h->capacity *= 2;
    }
    h->size++;
    strcpy(h->heap_arr[h->size],input);
    percUP(h, h->size, p);
}

// percolate up function
void percUP(struct heapStruct *h, int index, char p) 
{
    if (index > 1) 
    {
        if(p == 'm')
        {
          // if comparision of indexes is less than 0
            if (compTo(h->heap_arr[index/2],h->heap_arr[index])<0) 
            {
              // then move the node up one level
                swap(h, index, index/2);
              // and repeat if needed
                percUP(h, index/2, p);
            }
        }
        else if(p == 'n')
        {
           // if comparision of indexes is more than 0
            if (compTo(h->heap_arr[index/2],h->heap_arr[index])>0)
            {
              // and move node up a level
                swap(h, index, index/2);
              // then repeat if needed
                percUP(h, index/2, p);
            }
        }
    }
}
// percolate down function
void percDOWN(struct heapStruct *h, int index, char p) 
{
    if(p == 'n')
    {
        int minimum;
        if ((2*index+1) <= h->size) 
        {
            minimum = min(h->heap_arr[2*index], 2*index, h->heap_arr[2*index+1], 2*index+1);
          // if indexes are less than 0
            if (compTo(h->heap_arr[index],h->heap_arr[minimum])>0) 
            {
              // then move down one level
                swap(h, index, minimum);
              // and repeat if needed
                percDOWN(h, minimum, p);
            }
        }
        // otherwise compares and swaps val
        else if (h->size == 2*index) 
        {
          // if it is more then 0
            if ((h->heap_arr[index],h->heap_arr[2*index])>0)
              // then swap indexes
                swap(h, index, 2*index);
        }
    }
    if(p=='m')
    {
      // otherwise if more than 2
        int maximum;
        if ((2*index+1) <= h->size) 
        {
            maximum = max(h->heap_arr[2*index], 2*index, h->heap_arr[2*index+1], 2*index+1);
          // if vals are less than 0
            if (compTo(h->heap_arr[index],h->heap_arr[maximum])<0)
            {
              // swap the vals and moves downwards until needed
                swap(h, index, maximum);
                percDOWN(h, maximum, p);
            }
        }
        // otherwise if more than 2
        else if (h->size == 2*index) 
        {
          //then swap
            if (compTo(h->heap_arr[index],h->heap_arr[2*index])<0)
                swap(h, index, 2*index);
        }
    }
    
}
// swaps the indexes if needed
void swap(struct heapStruct *h, int index1, int index2) 
{
    char temp[maxCHAR];
  //string copies indexes
    strcpy(temp,h->heap_arr[index1]);
    strcpy(h->heap_arr[index1],h->heap_arr[index2]);
    strcpy(h->heap_arr[index2],temp);
}
//compares the first string to the second strings length 
int compTo(char str1[], char str2[])
{
  //if strlen are equal
    if(strlen(str1)==strlen(str2))
    {
      // and greater than 0 return 1 
        if(strcmp(str1,str2)>0)
            return 1;
        else
            return -1;
    }
  //if not equal return one 
    if(strlen(str1)>strlen(str2))
    {
        return 1;
    }
      //otherwise return -1 
    else{
        return -1;
    }
}

// finds the minimum val
int min(char a[], int indexOfA, char b[], int indexOfB) 
{
    //if comparision of a and b is less than 0 than a returns index 
    if (compTo(a,b)<0)
        return indexOfA;
    else
        return indexOfB;
}
// finds the maximum val
int max(char a[], int indexOfA, char b[], int indexOfB)
{
  //if comparision of a and b is greater than 0 returns index a 
    if (compTo(a,b)>0)
        return indexOfA;
    else
        return indexOfB;
}

//removes the minimum of heap
char* removeMin(struct heapStruct *h) 
{
//creates space for char
    char* retval = malloc(sizeof(char)*maxCHAR);
  //if height is bigger than 0
    if (h->size > 0) {
        strcpy(retval,h->heap_arr[1]);
        strcpy(h->heap_arr[1],h->heap_arr[h->size]);
        h->size--;
      //perculate down
        percDOWN(h, 1, 'n');
        return retval;
    }

    else
        return NULL;
}

//removes maximum
char* removeMax(struct heapStruct *h) 
{
  //creates space for maximum
    char* retval = malloc(sizeof(char)*maxCHAR);
  //if the height is greater than 0
    if (h->size > 0) {
        strcpy(retval,h->heap_arr[1]);
        strcpy(h->heap_arr[1],h->heap_arr[h->size]);
        h->size--;
      //perculate down
        percDOWN(h, 1, 'm');
        return retval;
    }
    else
        return NULL;
}

// frees the heap in function
void freeHeap(heapStruct *h,int n)
{
  // for loop for heap size to continue through array
    for(int i=0; i<(n+1); i++)
    {
      // frees heap array
        free(h->heap_arr[i]);
    }
    free(h->heap_arr);
    free(h);
}
