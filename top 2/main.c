//  main.c
// This program is written by: Nithya Munagala

/*This progam allows customers queue in several lines, upon arrival the cutsomer's time of arrival, 
last name, and line number where they are standing is printed.  
The number of tickets to be purchased by the customers are recorded for one cashier

The cashier determines status of all lines by checking who has the fewest tickets out of those front of each line,
if two customers have the same ticket size they will choose who comes from a smaller line number
*/

//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "leak_detector_c.h"

//constants
const int NumLines = 12;
const int MaxNameSize = 16;
const int MaxItems =100;
const int Maxtime = 100000000;

// 3 struncts customers, node, queue
typedef struct customer{
    int time;
    char name[16];
    int line_num;
    int ticketNum;
}customer;

// linked list for nodes
typedef struct node{
    customer* data;
    //node* customer
    //make queue using linked list
    struct node * next;
}node;

//Queues for linked list
typedef struct queue{
    node* front;
    node* back;
}queue;


customer* makeCustomer(char *name, int ticket, int line, int time)
{
  //creates customer based on struct
  customer* createCustomer = malloc(sizeof(customer));
    strcpy(createCustomer ->name, name);

  //checks inputs for restrictions
    createCustomer->line_num = line;
    createCustomer->ticketNum = ticket;
    createCustomer->time = time;

  //returns allocation for create customer
    return createCustomer;
}
    
//initalises queues and sets to NULL
   void init(struct queue *Q){
    Q -> front = Q -> back = NULL;
     }

// variable declaration
int isEmpty(queue *Q){

  // if front and back are NULL, return 1, else return 0.
  if(Q->front == NULL && Q->back == NULL)
    return 1;
  return 0;
}
//check enqueue further
//function determines who goes next in line
void enqueue(queue* Q, node*data){
  //checks for back person of line to add to placement
    if (isEmpty(Q)){
        Q -> front = Q -> back = data;
    }
  else
    {
      Q -> back -> next = data;
      Q -> back = data ;
      }
}

//function to remove or release customer from queue
node* dequeue(queue* Q)
{
  //variable declaration
  node *tmp;
  //checks if front of line is empty, if so returns NULL
  if (isEmpty(Q))
  {
    return NULL;
    }
  tmp = Q->front;
  //front of queue points to next person
  Q -> front = Q -> front-> next;
  
  if (Q->front == NULL)
  {
    Q->back = NULL;
    }
  //frees customer
  return (tmp);
  }
  //creates peek function
customer *peek(queue* Q)
{
  if(isEmpty(Q))
  {
    return NULL;
  }
  return Q->front->data;
}
//frees queue function and dequeue or Q
void freeing(queue *Q)
{
  if(isEmpty(Q))
  {
    free(Q);
    }
  dequeue(Q);
  }


    int getNextCustomerToBeProcessed(queue* line, int time){
      //variable declaration
        int res = -1, mintickets = MaxItems + 1;
      //for loop for numlines
        for (int i=0; i< NumLines; i++)
        {
          //checks if queues are empty
            if (isEmpty(&line[i]))
            {
              //if not continue
              continue;
              }
          //sets variable to front of queue and checks if customers time is larger then current time
          customer* tmp = peek(&line[i]);
          
          if (tmp->time > time){
            continue;
            }
            
            //updates the minimum tickets and checks who has lowest
            if (tmp-> ticketNum < mintickets)
            {
            //update the result
                res = i;
                mintickets = tmp->ticketNum;
                }
    }
      //checks for changed result, if so then it is returned
    if (res != -1){
      return res;
      }
      //variable declaration
      int best_time;
      best_time = Maxtime + 1;

      //checks if queue is empty and if so sets variable to front of line
      for (int j=0; j< NumLines; j++)
      {
        if (isEmpty(&line[j]))
        {
          continue;
        }
        else
        {
          customer*timetmp = peek(&line[j]);
          //checks if time is less than bestime and index is stored along with time
          if (timetmp ->time < best_time)
        {
          res = j;
          best_time = timetmp -> time;
          }
        }
        }
      //returns result
return res;
      }



int main(){
//memory leak detector
 atexit (report_mem_leak);

  //variable declarations
  int numCustomers;
  int testCases;
  int line_num;
  int TicketNum;
  int Time;
  char Cust_name[16];

//scan test cases
scanf("%d", &testCases);
  for (int i=0; i<testCases; i++)
  {
    //scans in number of customers 
    int timeTotal = 0;
    scanf("%d", &numCustomers);
    queue Q[12];

    for (int i=0; i<12; i++)
      {
        //initialises queues
        init (&Q[i]);
      }
    for (int i=0; i< numCustomers; i++)
      {
        // scans all of customer info and passed it to new function
        scanf("%d %d %s %d", &Time, &line_num, Cust_name, &TicketNum);
        node* CustomerInfo = malloc(sizeof(node));
        customer* customers = makeCustomer(Cust_name, TicketNum, line_num, Time);
        CustomerInfo -> data = customers;
        CustomerInfo -> next = NULL;
        //finds a match between line number and the variable 
        enqueue(&Q[line_num - 1], CustomerInfo); 
      }
    //malloc node to be size of node inside for loop above
    int lineholder = 0;
  for (int j=0; j < numCustomers; j++)
    {
    int minItems = MaxItems;
      // where the next customer will be found aka lineholder
     lineholder = getNextCustomerToBeProcessed(Q, timeTotal);

      node* nodeCustomer = dequeue(&Q[lineholder]);
      
      customer* customerPtr = nodeCustomer -> data;

      //update the time 
      if (timeTotal < customerPtr -> time)
     {
      timeTotal = customerPtr -> time;
      }     
      //formula for how long it takes to process the data while time is incremented 
     timeTotal += 30 + (5 * customerPtr -> ticketNum);
     //print statement output
     printf("%s from line %d checks out at time %d.\n", customerPtr -> name, customerPtr -> line_num, timeTotal);
     //frees customepte and nodecustomer
      free(customerPtr);
      free(nodeCustomer);
      
      
  
      
    }
  }
  return 0;
  }

  
