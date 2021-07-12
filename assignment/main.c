#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct student {
    char name[25];
    int id;
    int date_of_birth[3];
    int score_of_last_year;
    int key;
    };

struct student* hasharr[SIZE];
struct student* NULLItem;
struct student* item;

int keycalc(int day , int month, int year){
    int key;
    key = day + month + year;
    return key;
}

void createHashtable(){
    NULLItem = (struct student*) malloc(sizeof(struct student));
    NULLItem->id = -1;
    NULLItem->key = -1;
}

int hashfunc(int key) {
   return key % SIZE;
}

struct student *search(int key) {
   //get the hash
   int Index = hashfunc(key);

   //move in array until an empty
   while(hasharr[Index] != NULL) {

      if(hasharr[Index]->key == key)
         return hasharr[Index];

      //go to next cell
      ++Index;

      //wrap around the table
      Index %= SIZE;
   }

   return NULL;
}

void insert(int key, char name[25], int id, int day , int month, int year, int score_of_last_year, int a ) {

   struct student *item = (struct student*) malloc(sizeof(struct student));
   strcpy(item->name , name);
   item->id = id;
   item->date_of_birth[0] = day;
   item->date_of_birth[1] = month;
   item->date_of_birth[2] = year;
   item->score_of_last_year = score_of_last_year;
   item->key = key;

   //get the hash
   int Index = hashfunc(key);
    int i=0;
    int oldIndex=Index;
   //move in array until an empty or deleted cell
   while(hasharr[Index] != NULL && hasharr[Index]->key != -1) {
      if(a==1){
          //Linear probing
          ++Index;

      //wrap around the table
      Index %= SIZE;
      }
      else{
        //Quadratic probing
      Index=oldIndex;
      printf("lolol\n");
      //go to next cell
      Index=Index+(i*i);
      printf("Index is %d\n", Index);
      i++;
      printf("i is %d\n", i);
      //wrap around the table
      Index %= SIZE;
      }
   }

   hasharr[Index] = item;
}

struct student* delete(struct student* item) {
   int key = item->key;

   //get the hash
   int Index = hashfunc(key);

   //move in array until an empty
   while(hasharr[Index] != NULL) {

      if(hasharr[Index]->key == key) {
         struct student* temp = hasharr[Index];

         //assign a dummy item at deleted position
         hasharr[Index] = NULLItem;
         return temp;
      }

      //go to next cell
      ++Index;

      //wrap around the table
      Index %= SIZE;
   }

   return NULL;
}

void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hasharr[i] != NULL){
          if(hasharr[i]->id == -1){
        printf(" ~~ ");
      }
      else{
         printf(" (key: %d, Name: %s, ID: %d, Birthdate: %d,%d,%d, Score: %d)",hasharr[i]->key,hasharr[i]->name,hasharr[i]->id,hasharr[i]->date_of_birth[0],hasharr[i]->date_of_birth[1],hasharr[i]->date_of_birth[2],hasharr[i]->score_of_last_year);
      }

      }
      //else if(hasharr[i]->id == -1){
        //printf(" ~~ ");
      //}
      else
         printf(" ~~ ");
   }

   printf("\n");
}


int main()
{
    int a, keey, id, score_of_last_year, key, date_of_birth[3];
    char name[25];
    printf("Hello World\n");
    createHashtable();
    while(1){
        int c;
        printf(" 1. Insert\n 2. Search\n 3. Delete\n 4. Exit\n");
        scanf("%d", &c);
        if(c==1){
        printf("Choose a method: \n 1. Linear probing\n 2. Quadratic probing \n");
        scanf("%d", &a);
        printf("Enter name :\n");
        scanf("%s", name );
        printf("Enter id:\n");
        scanf("%d", &id );
        printf("Enter date of birth:\n");
        for ( int j = 0; j < 3; ++j)
            scanf("%d", &date_of_birth[j] );
        printf("Enter socre:\n");
        scanf("%d", &score_of_last_year );
        keey = keycalc( date_of_birth[0], date_of_birth[1], date_of_birth[2]);
        insert( keey, name, id, date_of_birth[0], date_of_birth[1], date_of_birth[2], score_of_last_year, a);
        display();
        }
        else if(c==2){
            printf("Enter a key:    (Note: you should enter the sum of day, month and year as a key.)\n");
            scanf("%d", &keey);
            item = search(keey);
            if(item != NULL) {
                printf("Element found: \n");
                printf(" (key: %d, Name: %s, ID: %d, Birthdate: %d/%d/%d, Score: %d\n)",item->key,item->name,item->id,item->date_of_birth[0],item->date_of_birth[1],item->date_of_birth[2],item->score_of_last_year);
            }
            else {
                printf("Element not found\n");
            }
        }
        else if(c==3){
            printf("Enter a key:    (Note: you should enter the sum of day, month and year as a key.)\n");
            scanf("%d", &keey);
            item = search(keey);
            if(item != NULL) {
                printf("Element found: \n");
                printf(" (key: %d, Name: %s, ID: %d, Birthdate: %d/%d/%d, Score: %d\n)",item->key,item->name,item->id,item->date_of_birth[0],item->date_of_birth[1],item->date_of_birth[2],item->score_of_last_year);
                printf("Item is deleted\n");
                delete(item);
            }
            else {
                printf("Element not found\n");
            }
        }
        else{
            display();
            exit(0);
        }

    }

    return 0;
}
