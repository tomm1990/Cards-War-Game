#define _CRT_SECURE_NO_WARNINGS
// -------------- Homework no.3 for Matam - Tom Goldberg ( ID : 302815279 ), Yonatan Rab ( ID : 300979747 ) ---------------------- //

#include "Header.h"

#define CREATITEM (snode*)malloc(sizeof(snode));		// typedef for malloc
#define ISEMPTY printf("\nEMPTY LIST:");				// expresion for empty list


typedef struct Card										// struct of item with typedef
{
	sign sign;						
	color color;
	char* name;
	int value;
	struct Card *next;
} snode;


snode* create_node(snode *arr);

void FreeList();										// free malloc expresions of lists
char* normalize(int val);								// function for the name of the value
void display1(snode *head);								// display linked list from the start
void InitializePack(snode val[]);						// initializing pack of cards ( items )
void swap(snode *a, snode *b);							// custom made swap function
void randomize(snode *arr, int n);						// custom made random function
void simulation(snode *first1, snode *first2, FILE* MyFile);	// main simulation function which retreive two linked lists and ptr to file
int remove_f_front(snode** head);						// function that removes front item from linked list
void add_to_end(snode* head, snode *val);				// function that adds item to end of likned list
int count_items(snode *head);							// function that counts the number of items
void left(snode* first1, snode* first2, FILE* MyFile);	// function that tells how item left in linked list
void war(snode* first1, snode* first2, FILE* MyFile);	// function that operate round of war


snode *newnode, *temp, *current, *temp1, *temp2, *first1 = NULL, *last1 = NULL, *first2 = NULL, *last2 = NULL;
static int turn;

int main()
{
	bool repeat;
	do {
		first1 = NULL, last1 = NULL, first2 = NULL, last2 = NULL;
		turn = 0;
		FILE* MyFile;
		MyFile = fopen("GameResult.txt", "r");
		if (MyFile == NULL)									// if file was not open
		{
			MyFile = fopen("GameResult.txt", "w");
			printf("\n-------------  Creating new file  -------------\n");
			fprintf(MyFile, "\n------------- New File  -------------\n");
			if (MyFile == NULL)
			{
				printf("The GameResult.txt could not be opened\n");
			}
		}
		else
		{
			MyFile = fopen("GameResult.txt", "a");
			printf("\n-------------  Appen to exist file  -------------\n");
			fprintf(MyFile, "\n------------- Appen to file  -------------\n");
		}

		struct Card FullPack[52];							// declaring array of 52 cards
		InitializePack(FullPack);							// initializing the array
		randomize(FullPack, 52);							// random the cards in the array

		first1 = CREATITEM;									// initizaling player 1 linked list
		if (first1 == NULL) {
			exit(1);
		}
		first1->value = 1;									// declaring default values (must)
		first1->next = NULL;
		first1->sign = Clubs;
		first1->color = Black;
		first1->name = "";

		first2 = CREATITEM;									// initizaling player 2 linked list
		if (first2 == NULL) {
			exit(1);
		}
		first2->value = 1;									// declaring default values (must)
		first2->next = NULL;
		first2->sign = Clubs;
		first2->color = Black;
		first2->name = "";

		printf("\n ------ Deviding the full pack to 2 players  ------ \n");
		add_to_end(first1, (FullPack));						// Deviding the full pack to 2 players
		remove_f_front(&first1);
		add_to_end(first2, (FullPack + 1));
		remove_f_front(&first2);
		for (int i = 2; i < 52; i++)
		{
			add_to_end(first1, (FullPack + i));
			add_to_end(first2, (FullPack + i + 1));
			i++;
		}

		printf("\nPlayer 1 List:\n");
		display1(first1);									// prints player 1 linked list
		printf("Player 1 has %d Cards\n", count_items(first1));	// prints number of items

		printf("\nPlayer 2 List:\n");
		display1(first2);									// prints player 2 linked list
		printf("Player 2 has %d Cards\n\n\n", count_items(first2)); // prints number of items

		int choice;											// declaring (int)choice for user input
		printf("\n\n\n ------ Welcome to War of Cards  ------ \n # Main Menu : ( Please choose )\n");
		printf("\n1. Enter (1) to start the simulation\n2. Enter (2) to exit\nChoice: ");
		scanf("%d", &choice);								// getting the user choice
		while ((choice != 1) && (choice != 2))				// if user input is out of range than keep asking for valid value
		{
			printf("\nPlease enter a valid number!\n1. Enter (1) to start the simulation\n2. Enter (2) to exit\nChoice: ");
			scanf("%d", &choice);
		}
		switch (choice)										// switch on the choice of user
		{
			case 1:
			{
				simulation(first1, first2, MyFile);			// case 1 : start simulation()
				printf("\n-------- End of Simulation--------\n");
			}
			case 2:
			{
				//FreeList();
				printf("\nPlayer 1 Linked List has been deleted\n");
				printf("Player 2 Linked List has been deleted\n");
				printf("\nGood bye\n");
				system("pause");
				return 0;									// case 2 : exit program
			}
		}
		
		printf("\nOnce again? : ( Please enter 1 for YES, 0 for NO )");
		scanf("%d", &repeat);
		while ((repeat != 1) && (repeat != 0))				// if user input is out of range than keep asking for valid value for repeat the simulation
		{
			printf("\nPlease enter a valid number!\nOnce again? : ( Please enter 1 for YES, 0 for NO )\nChoice: ");
			scanf("%d", &repeat);
		}
	} while (repeat);
	printf("Good Bye\n");
	system("pause");
	return 0;
}

void war(snode* first1, snode* first2, FILE* MyFile)
{
	temp1 = first1;
	temp2 = first2;
	if ((count_items(temp1) > 3) && (count_items(temp1) > 3))
	{
		for (int i = 0; i < 3; i++)
		{
			temp1 = temp1->next;
			temp2 = temp2->next;
			printf("\n\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s\n", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
		printf("\n->\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s  |", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));	
		if ((temp1->value)>(temp2->value))
		{
			//printf("Turn <%d> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!\n");
			printf("Player 1 wins!\n");
			fprintf(MyFile, " Player 1 wins!\n");


			for (int i = 0; i < 5; i++)
			{
				add_to_end(first1, first2);
				add_to_end(first1, first1);
				remove_f_front(&first2);
				remove_f_front(&first1);
			}
			
			printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));
			// Turn <x> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!
		}
		else if ((temp1->value)<(temp2->value))
		{
			printf("Player 2 wins! \n");
			fprintf(MyFile, " Player 2 wins!\n");
			for (int i = 0; i < 5; i++)
			{
				add_to_end(first2, first1);
				add_to_end(first2, first2);
				remove_f_front(&first2);
				remove_f_front(&first1);
			}
			
			printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));
			// Turn <x> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!
		}
		else
		{
			printf("War!\n");
			war(first1, first2, MyFile);
		}
		left(first1, first2, MyFile);
	}
}

void left(snode* first1, snode* first2, FILE* MyFile)
{ 
	if ((first1 == NULL) || (first2 == NULL))
	{

		if (first1 == NULL){
			printf("\nPlayer 2 is the winner!\n");
			fprintf(MyFile, "\nPlayer 2 is the winner!\n");
		}
		else if (first2 == NULL){
			printf("\nPlayer 1 is the winner!\n");
			fprintf(MyFile, "\nPlayer 1 is the winner!\n");
		}
	}
}

int count_items(snode *head)
{
	int counter = 1;
	if (head == NULL) {
		return 0;
	}
	while (head->next != NULL) {
		head = head->next;
		counter++;
	}
	return counter;
}

void add_to_end(snode *head, snode *val) 
{	
	snode* current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	/* now we can add a new variable */
	current->next = CREATITEM;
	current->next->value = val->value;
	current->next->sign = val->sign;
	current->next->color = val->color;
	current->next->name = val->name;
	current->next->next = NULL;
	printf("(%d)%s of %s %s was added\n", current->next->value, current->next->name, getCardColor(current->next->color), getCardSign(current->next->sign));
}

int remove_f_front(snode** head) {
	int retval = -1;
	snode * next_node = NULL;

	if (*head == NULL) {
		return -1;
	}

	next_node = (*head)->next;
	retval = (*head)->value;
	free(*head);
	*head = next_node;

	return retval;
}

void simulation(snode *first1, snode *first2, FILE* MyFile)
{
	temp1 = NULL;
	temp2 = NULL;
	printf("------ Starting simulation ------ \n");
	fprintf(MyFile, "\n\n------ Starting simulation ------ \n");
	while ((first1!=NULL) && (first2!=NULL))
	{
		//Turn <%d> : Player 1 draws : ________ - Player 2 draws : _______ 
		printf("\nTurn <%d>:Player 1 draws: %s of %s <-> Player 2 draws: %s of %s\n", ++turn, first1->name, getCardSign(first1->sign), first2->name, getCardSign(first2->sign));
		fprintf(MyFile, "Turn <%d>:\tPlayer 1 draws : %s of %s <---> Player 2 draws : %s of %s | ", turn, first1->name, getCardSign(first1->sign), first2->name, getCardSign(first2->sign));
		if ((first1->value)>(first2->value))
		{
			//printf("Turn <%d> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!\n");
			printf("Player 1 wins! \n");
			fprintf(MyFile,"Player 1 wins!\n");
			add_to_end(first1, first2);
			add_to_end(first1, first1);
			remove_f_front(&first2);
			remove_f_front(&first1);
			printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));
			// Turn <x> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!
			//fprintf(ofp, "%d %c", num, tav);
			

		}
		else if ((first1->value)<(first2->value))
		{
			printf("Player 2 wins! \n");
			fprintf(MyFile, "Player 2 wins!\n");
			add_to_end(first2, first1);
			add_to_end(first2, first2);
			remove_f_front(&first2);
			remove_f_front(&first1);
			printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));

		}
		else
		{
			printf("War!\n");
			fprintf(MyFile, "War !\n");
			//war(first1, first2, MyFile);
			temp1 = first1;
			temp2 = first2;
			if ((count_items(temp1) > 3) && (count_items(temp1) > 3))
			{
				for (int i = 0; i < 3; i++)
				{
					temp1 = temp1->next;
					temp2 = temp2->next;
					printf("\n\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s\n", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));
					fprintf(MyFile, "\t\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s\n", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));

				}

				//Turn <%d> : Player 1 draws : ________ - Player 2 draws : _______ 
				temp1 = temp1->next;
				temp2 = temp2->next;
				printf("\n--->\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s\n", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));
				fprintf(MyFile, "-->\t\tPlayer 1 draws: %s of %s <-> Player 2 draws: %s of %s  |", temp1->name, getCardSign(temp1->sign), temp2->name, getCardSign(temp2->sign));

				if ((temp1->value)>(temp2->value))
				{
					printf("Player 1 wins!\n");
					fprintf(MyFile, " Player 1 wins!\n");


					for (int i = 0; i < 5; i++)
					{
						add_to_end(first1, first2);
						add_to_end(first1, first1);
						remove_f_front(&first2);
						remove_f_front(&first1);
					}

					printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));
					// Turn <x> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!
					//fprintf(ofp, "%d %c", num, tav);
				}
				else if ((temp1->value)<(temp2->value))
				{
					//printf("Turn <%d> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!\n");
					printf("Player 2 wins! \n");
					fprintf(MyFile, " Player 2 wins!\n");


					for (int i = 0; i < 5; i++)
					{
						add_to_end(first2, first1);
						add_to_end(first2, first2);
						remove_f_front(&first2);
						remove_f_front(&first1);
					}

					printf("Player 1 has %d Cards ----- Player 2 has %d Cards\n", count_items(first1), count_items(first2));
					// Turn <x> : Player 1 draws : ________ - Player 2 draws : _______ | player <y> wins!
					//fprintf(ofp, "%d %c", num, tav);
				}
				else
				{
					//printf("War!\n");
					//war(first1, first2, MyFile);
					add_to_end(first1, first1);
					add_to_end(first2, first2);
					remove_f_front(&first2);
					remove_f_front(&first1);
				}
				left(first1, first2, MyFile); // warninggggggggggggg
			}
			//-------
			/*printf("\nPlayer 1 List:\n");
			display1(first1);
			printf("Player 1 has %d Cards\n", count_items(first1));

			printf("\nPlayer 2 List:\n");
			display1(first2);
			printf("Player 2 has %d Cards\n\n\n", count_items(first2));*/
			//-----
			
		}
		left(first1, first2, MyFile); // warninggggggggggggg
		

	}

}

void randomize(snode *arr, int n)
{
	printf("--------Shuffling Pack--------\n");
	for ( int i = n - 1 ; i > 0 ; i-- )
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
		printf("(%d)%s of %s %s\n", (arr + i)->value, (arr + i)->name, getCardColor((arr + i)->color), getCardSign((arr + i)->sign));
	}
	printf("--------Pack was shuffled--------\n\n\n");
}

void swap(snode *a, snode *b)
{
	snode temp = *a;
	*a = *b;
	*b = temp;
}

void InitializePack(snode *pack)
{
	struct Card *temp;
	temp = pack;
	char *array[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	printf("--------Initializing Pack of 52 Cards--------\n");
	for (int i = 1; i <= 4; i++)
	{
		int val;
		for (val = 2; val <= 14; val++)
		{
			temp->value = val;						// initializing value
			temp->name = normalize(temp->value);			// initializing name
			char* sign = array[i-1];				// rand() % 4
			if ((strstr("Hearts", sign)) || (strstr("Diamonds", sign))) {
				temp->color = Red;					// initializing color
				if (strstr("Hearts", sign)) temp->sign = Hearts;
				else temp->sign = Diamonds;			// initializing sign
			}
			else if ((strstr("Clubs", sign)) || (strstr("Spades", sign))){
				temp->color = Black;
				if (strstr("Clubs", sign)) temp->sign = Clubs;
				else temp->sign = Spades;

			}
			printf("(%d)%s of %s %s\n", temp->value, temp->name, getCardColor(temp->color), getCardSign(temp->sign));
			temp++;
		}
	}
	printf("--------Pack was successfully initialized--------\n\n\n");
}

snode* create_node(snode *arr)
{
	newnode = CREATITEM;
	if (newnode == NULL)
	{
		printf("\nMemory was not allocated!\nPlease try again later\n");
		system("pause");
		return 0;
	}
	else
	{
		newnode->value = arr->value;						// initializing value
		newnode->name = arr->name;							// initializing name
		newnode->sign = arr->sign;							// initializing sign
		newnode->color = arr->color;						// initializing color
		//if ((strstr("Hearts", sign)) || (strstr("Diamonds", sign))) {
		//	newnode->color = Red;					// initializing color
		//	if (strstr("Hearts", sign)) newnode->sign = Hearts;
		//	else newnode->sign = Diamonds;			// initializing sign
		//}
		//else if ((strstr("Clubs", sign)) || (strstr("Spades", sign))){
		//	newnode->color = Black;
		//	if (strstr("Clubs", sign)) newnode->sign = Clubs;
		//	else newnode->sign = Spades;
		//}
		//else
		//{
		//	printf("Error\n");
		//	exit(1);
		//}
		newnode->next = NULL;
		return newnode;
	}
}

void FreeList()
{
	snode* to_free1=NULL;
	if (first1)
	{
		to_free1 = first1;
		while (to_free1 != NULL)
		{
			first1 = first1->next;
			free(to_free1);
			to_free1 = first1;
		}
		printf("\n\nPlayer 1 Linked List has been deleted\n");
	}
	snode* to_free2 = NULL;
	if (first2)
	{
		to_free2 = first2;
		while (to_free2 != NULL)
		{
			first2 = first2->next;
			free(to_free2);
			to_free2 = first2;
		}
		printf("\nPlayer 2 Linked List has been deleted\n");
	}
	snode* to_free_temp1 = NULL;
	if (temp1)
	{
		to_free_temp1 = temp1;
		while (to_free_temp1 != NULL)
		{
			temp1 = temp1->next;
			free(to_free_temp1);
			to_free_temp1 = temp1;
		}
		printf("\ntemp1 Linked List has been deleted\n");
	}
	snode* to_free_temp2 = NULL;

	if (temp2)
	{
		to_free_temp2 = temp2;
		while (to_free_temp2 != NULL)
		{
			temp2 = temp2->next;
			free(to_free_temp2);
			to_free_temp2 = temp2;
		}
		printf("\ntemp2 Linked List has been deleted\n");
	}
}

char* normalize(int val)								// function for the name of the value
{
	switch (val){										// switch case of the number value
	case 2: return "Two";
	case 3: return "Three";
	case 4: return "Four";
	case 5: return "Five";
	case 6: return "Six";
	case 7: return "Seven";
	case 8: return "Eight";
	case 9: return "Nine";
	case 10: return "Ten";
	case 11: return "Jack";
	case 12: return "Qeeun";
	case 13: return "King";
	case 14: return "Ace";
	}
}

void display1(snode *head)								// display list function
{
		snode * current = head;							// decleration
		while (current != NULL) {
			printf("(%d)%s of %s %s\n", current->value, current->name, getCardColor(current->color), getCardSign(current->sign));
			current = current->next;
		}
}

 

