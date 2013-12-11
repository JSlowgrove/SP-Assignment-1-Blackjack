#include <iostream>
#include <Windows.h>
#include <cctype>
#include <ctime>
#include <string>

using namespace std;

void splash(), title(), gameSetup(), play(int*), flip(int, char), win(), lose(), again();

struct cardStruct
{
	int num;
	char set;
};

cardStruct card[52];
void hand(int,cardStruct[]), dealerTurn(int**,int,cardStruct[]);

int main(){
	splash();
	title();
	int current;
	bool on = true, first = true;
	system("CLS");
	char choice[1];
	while(on)
	{
		system("CLS");
		cout<<"\n";
		cout<<"		 ----- \n";
		cout<<"		|Alpha|\n";
		cout<<"		|  -  |\n";
		cout<<"		| |A| | - BLACKJACK\n";
		cout<<"		|  -  |\n";
		cout<<"		|Cards|\n";
		cout<<"		 ----- \n\n";
		cout<<"Welcome to Alpha Cards - Blackjack, please choose your task:\n(Play = P, Rules = R, Credits = C, End = E)\n";
		cin>>choice[0];
		switch(choice[0])
		{
		case 'P':
		case 'p':
			system("CLS");
			if (first == true || 52 - current < 22) //checks if need to shuffle
			{
				current = 0;
				first = false;
				gameSetup();
			}
			else
			{
			}
			play(&current);
			break;

		case 'R':
		case 'r':
			system("CLS");
			cout<<"RULES OF BLACKJACK:\n";
			cout<<"The aim is to get a score as close to 21 as possible, the closest player wins.\n";
			cout<<"Cards 2 to 10 are equal to there value.\n";
			cout<<"King,Queen and Jack are equal to 10 and Ace is equal to 1 or 11 depending on the players choice.\n";
			cout<<"Each player starts with 2 cards and each turn the player gets the choice to stand(keep the hand) or hit(take a card from the deck).\n";
			cout<<"This goes on until the player either stands or goes bust(has a hand with a higher value than 21), if the player goes bust they lose.\n";
			cout<<"When all players are done, the dealer shows his hand, if he has a blackjack (21) all players loose unless they also have blackjack in which case they have there bet returned.\n";
			cout<<"If the Dealers hand is lower than 17 then they hit, else they stand.\n";
			cout<<"If they Dealer goes bust all they player wins, else any player with more points than the dealer wins, and get a bouns equal to half there original wager.\n\n";
			system("pause");
			break;

		case 'C':
		case 'c':
			system("CLS");
			cout<<"CREDITS:\nMade by Jamie Slowgrove\n\n";
			system("pause");
			break;

		case 'E':
		case 'e':
			on = false;
			break;

		default:

			break;
		}
	}
	return 0;
}
//splash screen for begining
void splash()
{
	cout<<"\n\n\n        Blackjack Assignment - James Ronald John Slowgrove";
	Sleep(2000);
} //splash screen

//title animation
void title()
{
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|A    |\n";
	cout<<"		|     |\n";
	cout<<"		|  "<<'\x06'<<"  |\n";
	cout<<"		|     |\n";
	cout<<"		|    A|\n";
	cout<<"		 ----- ";
	Sleep(200);
	system("CLS");
	cout<<"\n\n\n";
	cout<<"		  --- \n";
	cout<<"		 ||  |\n";
	cout<<"		 |   |\n";
	cout<<"		 |   |\n";
	cout<<"		 |   |\n";
	cout<<"		 |  ||\n";
	cout<<"		  --- ";
	Sleep(200);
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		   - \n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		   - ";
	Sleep(200);
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		  --- \n";
	cout<<"		 |Apa|\n";
	cout<<"		 |   |\n";
	cout<<"		 | | |\n";
	cout<<"		 |   |\n";
	cout<<"		 |Crs|\n";
	cout<<"		  --- ";
	Sleep(200);
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|Alpha|\n";
	cout<<"		|  -  |\n";
	cout<<"		| |A| |\n";
	cout<<"		|  -  |\n";
	cout<<"		|Cards|\n";
	cout<<"		 ----- \n\n";
	cout<<"	       BLACKJACK ";
	Sleep(1000);
}

void gameSetup()
{	
	char set;
	int x=0;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			set = '\x03';
			break;
		case 1:
			set = '\x04';
			break;
		case 2:
			set = '\x05';
			break;
		case 3:
			set = '\x06';
			break;
		}

		for (int a = 1; a < 14; a++)
		{
			card[x].set = set;
			card[x].num = a;
			x++;
		}
	}
	cardStruct temp[52]; //tempory deck
	for (int i = 0; i < 52; i++)
	{
		temp[i].num = -1;	//sets the deck nums to -1 
	}
	bool test;
	int rnd;
	srand(time(NULL)); //uses the time to make a seed
	for (int i = 0; i < 52; i++)
	{
		test = true;
		while (test)
		{

			rnd = rand() % 52; //random number between 0 and 52
			if (temp[rnd].num != -1) // if the card is already filled
			{
				//do nothing
			}
			else
			{
				test = false;
				temp[rnd].num = card[i].num;
				temp[rnd].set = card[i].set;
			}
		}
	}
	for (int i = 0; i < 52; i++) //fill the origional deck with the shuffled deck
	{
		card[i].num = temp[i].num;
		card[i].set = temp[i].set;
	}
}

void play(int* current)
{
	bool cont = true, playerBlackjack = false, dealerBlackjack = false, a = false;
	cardStruct dealerHand[11];
	cardStruct playerHand[11];

	char* choice;
	choice = new char[100];

	int cardsInHand = 2, playerScore = 0, ace = 0;

	//drawing first 2 cards for dealer and player#########################################################################
	playerHand[0] = card[*current];
	if (playerHand[0].num == 1)
	{
		ace++;
		a=true;
	}
	else
	{
		if (playerHand[0].num > 9)
		{
			playerScore = playerScore + 10;
		}
		else
		{
			playerScore = playerScore + playerHand[0].num;
		}
	}
	flip(playerHand[0].num, playerHand[0].set);
	(*current)++;
	dealerHand[0] = card[*current];
	(*current)++;
	playerHand[1] = card[*current];
	if (playerHand[1].num == 1)
	{
		ace++;
		a=true;
	}
	else
	{
		if (playerHand[1].num > 9)
		{
			playerScore = playerScore + 10;
		}
		else
		{
			playerScore = playerScore + playerHand[1].num;
		}
	}
	flip(playerHand[1].num, playerHand[1].set);
	(*current)++;
	dealerHand[1] = card[*current];
	(*current)++;
	system("CLS");
	cout<<"\n\n\n\t\tDEALER'S CARD:";
	Sleep(1000);
	flip(dealerHand[0].num, dealerHand[0].set);

	//####################################################################################################################

	//checks for blackjack################################################################################################
	if (playerHand[0].num == 1)
	{
		if (playerHand[1].num == 10 || playerHand[1].num == 11 || playerHand[1].num == 12 || playerHand[1].num == 13)
		{
			playerBlackjack = true;
		}
	}
	else 
	{
		if (playerHand[0].num == 10 || playerHand[0].num == 11 || playerHand[0].num == 12 || playerHand[0].num == 13)
		{
			if (playerHand[1].num == 1)
			{
				playerBlackjack = true;
			}
		}
	}
	if (dealerHand[0].num == 1)
	{
		if (dealerHand[1].num == 10 || dealerHand[1].num == 11 || dealerHand[1].num == 12 || dealerHand[1].num == 13)
		{
			dealerBlackjack = true;
		}
	}
	else 
	{
		if (dealerHand[0].num == 10 || dealerHand[0].num == 11 || dealerHand[0].num == 12 || dealerHand[0].num == 13)
		{
			if (dealerHand[1].num == 1)
			{
				dealerBlackjack = true;
			}
		}
	}
	if (playerBlackjack && dealerBlackjack == false)
	{
		cout<< "\n\nPlayer has Blackjack, Player Wins";
		cin.ignore();
		cin.get();
		//win
		cont = false;
	}
	if (playerBlackjack && dealerBlackjack)
	{
		cout<< "\n\nBoth Dealer and Player has Blackjack, No one wins";
		cin.ignore();
		cin.get();
		//draw
		cont = false;
	}
	if (playerBlackjack == false && dealerBlackjack)
	{
		cout<< "\n\nDealer has Blackjack, Dealer Wins";
		cin.ignore();
		cin.get();
		//lose
		cont = false;
	}
	//####################################################################################################################

	//Player Turn#########################################################################################################
	bool stand = false;
	while (cont)
	{
		system("CLS");
		cout<<"Your Hand: ";
		hand(cardsInHand, playerHand);//displaying hand

		cout<<"\n\nDealer's shown card: ";
		hand(1, dealerHand);// dealers first card
		cout<<endl;

		for (int i = 0; i < ace; i++)
		{
			while(a)
			{
				int temp;
				cout<<"\n\nWhat value for the Ace? (1/11)\n";
				cin>>temp;
				if (temp==1)
				{
					playerScore++;
					a=false;
				}
				else
				{
					if (temp==11)
					{
						playerScore = playerScore + 11;
						a=false;
					}
				}
			}
			ace=0;
		}
		if (playerScore <= 21){
			cout<<"\nCard Score: "<<playerScore<<endl;
			cout<<"\nHit or Stand? (H/S)\n";
			cin>>choice;
			if(choice[0] == 'H' || choice[0] == 'h')
			{
				playerHand[cardsInHand] = card[*current];
				if (playerHand[cardsInHand].num == 1)
				{
					ace++;
					a=true;
				}
				else
				{
					if (playerHand[cardsInHand].num > 9)
					{
						playerScore = playerScore + 10;
					}
					else
					{
						playerScore = playerScore + playerHand[cardsInHand].num;
					}
				}
				flip(playerHand[cardsInHand].num, playerHand[cardsInHand].set);
				(*current)++;
				cardsInHand++;
			}
			else
			{
				if (choice[0] == 'S' || choice[0] == 's')
				{
					stand = true;
					cont = false;
				}
			}
		}
		else
		{
			cout << "\n\nYOU ARE BUST!";
			cont = false;
			cin.ignore();
			cin.get();
			//lose
		}
	}

	// if dealer gets a go
	if (stand == true)
	{
		dealerTurn(&current, playerScore, dealerHand);
	}

	delete [] choice;
	choice = 0;
}

void dealerTurn(int** current, int playerScore, cardStruct dealerHand[])
{	
	int cardsInHand = 2;
	bool cont = true;
	bool a = false;
	int dealerScore = 0;
	int ace = 0;
	if (dealerHand[0].num == 1)
	{
		ace++;
		a=true;
	}
	else
	{
		if (dealerHand[0].num > 9)
		{
			dealerScore = dealerScore + 10;
		}
		else
		{
			dealerScore = dealerScore + dealerHand[0].num;
		}
	}
	if (dealerHand[1].num == 1)
	{
		ace++;
		a=true;
	}
	else
	{
		if (dealerHand[1].num > 9)
		{
			dealerScore = dealerScore + 10;
		}
		else
		{
			dealerScore = dealerScore + dealerHand[1].num;
		}
	}
	flip(dealerHand[1].num, dealerHand[1].set);
	while (cont)
	{
		system("CLS");
		cout<<"Dealers hand: ";
		hand(cardsInHand, dealerHand);//displaying hand

		for (int i = 0; i < ace; i++)
		{
			while(a)
			{
				if (dealerScore + 11 > 21)
				{
					dealerScore++;
					a=false;
					cout<<"Dealer chooses 1 for the value of the Ace\n";
				}
				else
				{
					dealerScore = dealerScore + 11;
					a=false;
					cout<<"Dealer chooses 11 for the value of the Ace\n";
				}
			}
			ace=0;
		}
		cout<<"\nThe Dealer's Score: "<<dealerScore<<endl;
		cin.ignore();
		cin.get();
		if (dealerScore < 21){
			if(dealerScore + 10 <= 21 || dealerScore <= 14)
			{
				dealerHand[cardsInHand] = card[**current];
				if (dealerHand[cardsInHand].num == 1)
				{
					ace++;
					a=true;
				}
				else
				{
					if (dealerHand[cardsInHand].num > 9)
					{
						dealerScore = dealerScore + 10;
					}
					else
					{
						dealerScore = dealerScore + dealerHand[cardsInHand].num;
					}
				}
				flip(dealerHand[cardsInHand].num, dealerHand[cardsInHand].set);
				(**current)++;
				cardsInHand++;
			}
			else
			{
				if(dealerScore < playerScore){
					dealerHand[cardsInHand] = card[**current];
					if (dealerHand[cardsInHand].num == 1)
					{
						ace++;
						a=true;
					}
					else
					{
						if (dealerHand[cardsInHand].num > 9)
						{
							dealerScore = dealerScore + 10;
						}
						else
						{
							dealerScore = dealerScore + dealerHand[cardsInHand].num;
						}
					}
					flip(dealerHand[cardsInHand].num, dealerHand[cardsInHand].set);
					(**current)++;
					cardsInHand++;
				}
				else
				{
					cout << "Dealer wins";
					cont = false;
					cin.ignore();
					cin.get();
					//lose
				}
			}
		}
		else
		{
			if (dealerScore == 21)
			{
				cout << "\n\nDRAW!";
				cont = false;
				cin.ignore();
				cin.get();
				//draw
			}
			else
			{
				cout << "\n\nDEALER IS BUST!";
				cont = false;
				cin.ignore();
				cin.get();
				//win
			}
		}
	}
}

void hand(int cardsInHand,cardStruct Hand[])
{
	for (int i = 0; i <cardsInHand; i++)
	{
		if (i==0)
		{
		}
		else
		{
			cout<< ", "; 
		}
		switch (Hand[i].num)
		{
		case 1:
			cout<<"Ace";
			break;
		case 11:
			cout<<"Jack";
			break;
		case 12:
			cout<<"Queen";
			break;
		case 13:
			cout<<"King";
			break;
		default:
			cout << Hand[i].num;
			break;
		}
		cout <<" of ";
		switch (Hand[i].set)
		{
		case '\x05':
			cout<<"Clubs";
			break;
		case '\x03':
			cout<<"Hearts";
			break;
		case '\x04':
			cout<<"Diamonds";
			break;
		case '\x06':
			cout<<"Spades";
			break;
		}
	}
}

//flip animation
void flip(int num, char set)
{ 
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|Alpha|\n";
	cout<<"		|  -  |\n";
	cout<<"		| |A| |\n";
	cout<<"		|  -  |\n";
	cout<<"		|Cards|\n";
	cout<<"		 ----- \n\n";
	Sleep(200);
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		  --- \n";
	cout<<"		 |Apa|\n";
	cout<<"		 |   |\n";
	cout<<"		 | | |\n";
	cout<<"		 |   |\n";
	cout<<"		 |Crs|\n";
	cout<<"		  --- ";
	Sleep(200);
	system("CLS"); 
	cout<<"\n\n\n";
	cout<<"		   - \n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		  | |\n";
	cout<<"		   - ";
	Sleep(200);
	system("CLS");
	cout<<"\n\n\n";
	cout<<"		  --- \n";
	cout<<"		 ||  |\n";
	cout<<"		 |   |\n";
	cout<<"		 |   |\n";
	cout<<"		 |   |\n";
	cout<<"		 |  ||\n";
	cout<<"		  --- ";
	Sleep(200);
	system("CLS");
	switch (num)
	{
	case 1:
		void ace(char);
		ace(set);
		break;
	case 2:
		void two(char);
		two(set);
		break;
	case 3:
		void three(char);
		three(set);
		break;
	case 4:
		void four(char);
		four(set);
		break;
	case 5:
		void five(char);
		five(set);
		break;
	case 6:
		void six(char);
		six(set);
		break;
	case 7:
		void seven(char);
		seven(set);
		break;
	case 8:
		void eight(char);
		eight(set);
		break;
	case 9:
		void nine(char);
		nine(set);
		break;
	case 10:
		void ten(char);
		ten(set);
		break;
	case 11:
		void jack(char);
		jack(set);
		break;
	case 12:
		void queen(char);
		queen(set);
		break;
	case 13:
		void king(char);
		king(set);
		break;
	default:
		break;
	}
	Sleep(2000);
}

//card displays
void ace(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|A    |\n";
	cout<<"		|     |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|     |\n";
	cout<<"		|    A|\n";
	cout<<"		 ----- ";
}

void two(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|2    |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|     |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|    2|\n";
	cout<<"		 ----- ";
}

void three(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|3    |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		|    3|\n";
	cout<<"		 ----- ";
}

void four(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|4    |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|     |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|    4|\n";
	cout<<"		 ----- ";
}

void five(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|5    |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|  "<<set<<"  |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|    5|\n";
	cout<<"		 ----- ";
}

void six(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|6    |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|    6|\n";
	cout<<"		 ----- ";
}

void seven(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|7    |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		|    7|\n";
	cout<<"		 ----- ";
}

void eight(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|8    |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		| "<<set<<" "<<set<<" |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		|    8|\n";
	cout<<"		 ----- ";
}

void nine(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|9    |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		|    9|\n";
	cout<<"		 ----- ";
}

void ten(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|10   |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		|"<<set<<set<<set<<set<<" |\n";
	cout<<"		| "<<set<<set<<set<<" |\n";
	cout<<"		|   10|\n";
	cout<<"		 ----- ";
}

void jack(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|J _ "<<set<<"|\n";
	cout<<"		|  0  |\n";
	cout<<"		|  +  |\n";
	cout<<"		|  ^  |\n";
	cout<<"		|"<<set<<"   J|\n";
	cout<<"		 ----- ";
}

void queen(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|Q m "<<set<<"|\n";
	cout<<"		|  0  |\n";
	cout<<"		|  +  |\n";
	cout<<"		|  ^  |\n";
	cout<<"		|"<<set<<"   Q|\n";
	cout<<"		 ----- ";
}

void king(char set)
{
	cout<<"\n\n\n";
	cout<<"		 ----- \n";
	cout<<"		|K M "<<set<<"|\n";
	cout<<"		|  0  |\n";
	cout<<"		|  +  |\n";
	cout<<"		|  ^  |\n";
	cout<<"		|"<<set<<"   K|\n";
	cout<<"		 ----- ";
}