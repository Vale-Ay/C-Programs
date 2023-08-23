#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int faults; 
int hits;
int pointer;


//Strategy for FIFO
void fifo(int frame_size,int frame[], int reference)
{
	int i;
	bool alloted = false; // check if the page hit or faulted
	for(i = 0;i < frame_size; i++)
	{
		if(frame[i] == reference)// ensure if the page hit
		{
			alloted = true;
			printf("\nHit for %d ", reference);
			hits++;
			break;
		}
		else if(frame[i]==-1)// if it returns -1 then it faulted
		{
			alloted = true;
			frame[i] = reference;
			printf("\nFault for %d ", reference);
			faults++;
			break;
		}
	}
	if(alloted == false)//automatically faults
	{
		faults++;
		printf("\nFault for %d ", reference);
		frame[pointer] = reference;
		pointer = (pointer+1)%frame_size;
	}
	
}

//Strategy for LRU
void lru(int frame_size,int frame[], int reference, int current_position,int reference_length, int references[])
{
	int i;
	bool allocated=false;// check if the page hit or faulted
	for(i=0;i<frame_size;i++)
	{
		if(frame[i]==reference)// ensure if the page hit
		{
			printf("\nHit for %d ", reference);
			hits++;
			allocated = true;
			break;
		}
		else if(frame[i]==-1)// if it returns -1 then it faulted
		{
			frame[i] = reference;
			printf("\nFault for %d ", reference);
			faults++;
			allocated = true;
			break;
		}
	}
	if(allocated==false)//automatically faults
	{
		frame[i] = reference;
		printf("\nFault for %d ", reference);
		faults++;	
	}
	
}

int main()
{
	int frame_size,i,number_of_references;
	printf("Enter frame size: ");
	scanf("%d",&frame_size);// takes in the frames
	int frame[frame_size];
	
	for(i = 0;i < frame_size; i++)
	{
		frame[i] = -1;
	}
	
	
	printf("Enter no. references: ");
	scanf("%d",&number_of_references);//takes in the refrences
	int reference[number_of_references];

	int ch;
	int rand(void);// initiates the rand()
    int choice = (rand() % 3);//randomly pick between 0-3
	if(choice == 1)//if it choose 1 then it will run FIFO
	{
		printf("\nUsing FIFO; input 'e' to display result:");
		
		for(i=0;i<number_of_references;i++)
		{
			scanf("%d",&reference[i]);
			fifo(frame_size,frame,reference[i]);//calls FIFO function
		}
		
	}
	else//if it choose 2 then it will run LRU
	{
		printf("\nUsing LRU; input 'e' to display result:");
		
		for(i=0;i<number_of_references;i++)
		{
			scanf("%d",&reference[i]);
			lru(frame_size,frame,reference[i],i, number_of_references,reference);//calls LRU function
		}
				
	}
   	//Lastly display the noumber of faults and hits
	printf("\n\nNo. of faults: %d \nNo. of hits: %d\n",faults,hits);
	
}