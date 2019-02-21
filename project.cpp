
#include<ctype.h>    //Header files.
#include<stdlib.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

void box()               //Function to display box.
{
 for(int i=1; i<79; i+=2)
	{
	 gotoxy(i, 0);
	 cout<<"O";
	}
 for(int j=0; j<25; j++)
	{
	 gotoxy(0, j);
	 cout<<"O";
	}
 for(int k=0; k<25; k++)
	{
	 gotoxy(79, k);
	 cout<<"O";
	}
 for(int l=1; l<79; l+=2)
	{
	 gotoxy(l, 24);
    cout<<"O";
	}
}

class hiscore        //High score structure.
{
 char name[20];
 int score;

 public:

 int highscore(char nm[], int scr)
 {
  fstream f("highscor.dat", ios::in|ios::binary);  //The High score database.
  int i=0;
  hiscore s[10];
  hiscore s1;
  strcpy(s1.name, nm);
  s1.score=scr;
  int chk=0;
  while(f.read((char*)&s[i], sizeof(s[i]))) i++;
  if(!i)
	{
	 s[i]=s1;
	 chk++;
	}
  else if(i)
	{
	 int pos=-1;
	 for(int j=0; j<i; j++)
		{
		 if(s[j].score<s1.score)  //Checking for whether the score is a high score or not.
			{
			 pos=j;
			 break;
			}
		}
	 if(i==10&&pos!=-1)
		{
       i--;
		}
	 if(i<10&&pos!=-1)           //To check for presence of 10 high scores, in which case the lowest is deleted,
		{                         //and the current is added in the right position.
		 for(j=i; j>pos; j--)
		  {
			s[j]=s[j-1];
		  }
		 s[pos]=s1;
		 chk++;
		}
	 if(i<10&&pos==-1)
		{
		 pos=i;
		 s[pos]=s1;
		 chk++;
		}
	}
  f.close();
  f.open("highscor.dat", ios::out|ios::binary);
  if (chk)
	{
	 for(int j=0; j<=i; j++)
		{
		 f.write((char*)&s[j], sizeof(s[j]));
		}
	 return (1);
	}
  else
	{
    for(int j=0; j<i; j++)
		{
		 f.write((char*)&s[j], sizeof(s[j]));
		}
	 return (0);
	}
 }

 void highscores()     //Displays high scores.
 {
  box();
  fstream f("highscor.dat", ios::in|ios::binary);
  int i=0;
  hiscore s[10];
  while(f.read((char*)&s[i], sizeof(s[i]))) i++;
  gotoxy(33, 4);
  cout<<"Name";
  gotoxy(40, 4);
  cout<<"Score";
  for(int j=0; j<i; j++)
	{
	 gotoxy(33, j+6);
	 puts(s[j].name);
	 gotoxy(40, j+6);
	 cout<<s[j].score;
	}
  gotoxy(78, 22);
  f.close();
 }

} s;

char str[5];
int maxi=10;

void difficulty()
{
 int choice;                    //Difficulty function.
 cout<<"Current difficulty: ";
 if((maxi/5)==1) cout<<"Hard."<<endl;
 else if ((maxi/5)==2) cout<<"Normal."<<endl;
 else if ((maxi/5)==3) cout<<"Easy."<<endl;
 cout<<"1. Hard.\n2. Normal.\n3. Easy.\n";
 cin>>choice;
 maxi=(choice*5);              //For calculation of number of chances. And score.
}

void getword()
{
 fstream f;
 f.open("words.txt", ios::in);   //Our word database. 5444 words.
 int i=0;
 int x;
 randomize();
 //x=0;
 x=random(5444);                 //Gets us a random word.
 while(i<=x)
	{
	 f.getline(str, 6, ' ');
	 i++;
	}
 f.close();
}

void play()
{
 char str1[1], str2[1];     //These are purely for comparison purpose.
 str1[1]='\0';
 str2[1]='\0';
 int j=2;
 char nam[20];              //Name. (Score records)
 int scor=0;                //Score. (Score records)
 int chk=0, chkr=0, chkrr=0;         //Number of bulls, number or repetitions respectively.
 int count=0;                    //Number of trials. Used for finding the score.
 char blist[5]="", rlist[5]="", rrlist[5]="";  //List of bulls and repetitions.
 float cows=0, bulls=0;
 char guess[5];
 gotoxy(8, 0);
 cout<<"Cows";
 gotoxy(14, 0);
 cout<<"Bulls"<<endl;
 getword();                           //This function here gets us the word.
 for(int i=0; i<(strlen(str)); i++)   //Here we initialize the repeat list.
	{
	 for(int k=0; k<(strlen(str)); k++)
		{
		 str1[0]=str[i];
		 str2[0]=str[k];
		 if((toupper(str[i])==toupper(str[k]))&&i!=k)
			{
			 int chk3=0;                  //If there's a repetition on the repeat list, this
			 for(int p=0; p<=chkr; p++)   //prevents that.
				{
				 if((toupper(str[i]))==(toupper(rlist[p]))) chk3++;
				}
			 if(!(chk3))
				{
				 rlist[chkr]=str[i];
				 chkr++;
				}
			}
		}
	}
 B:
 gotoxy(0, j);
 for(int o=0; o<10; o++)
	{
	 cout<<" ";
	}
 gotoxy(0, j);
 gets(guess);
 if(strlen(guess)!=4)   //If player enters something other than 4 letters long.
	{
	 goto B;
	}
 strcpy(blist, "");
 strcpy(rrlist, "");
 chk=0;
 for(i=0; i<(strlen(str)); i++)   //Here we're looking for bulls.
	{
	 str1[0]=str[i];
	 str2[0]=guess[i];
	 if(strcmpi(str1, str2)==0)
	  {
		int chk6=0;
		for(int q=0; q<=chk; q++)    //This is to check whether the bull already exists on the bull list.
			{
			 if(toupper(str[i])==toupper(blist[q])) chk6++;
			}
		if(!(chk6))
			{
			 blist[chk]=str[i];
			 chk++;
			}
		bulls++;
	  }
	}
 for(i=0; i<(strlen(guess)); i++)   //Here we initialize the repeat list for the guess.
	{
	 for(int k=0; k<(strlen(guess)); k++)
		{
		 str1[0]=guess[i];
		 str2[0]=guess[k];
		 if((toupper(guess[i])==toupper(guess[k]))&&i!=k)
			{
			 int chk3=0;                  //If there's a repetition on the repeat list, this
			 for(int p=0; p<=chkrr; p++)   //prevents that.
				{
				 if((toupper(guess[i]))==(toupper(rrlist[p]))) chk3++;
				}
			 if(!(chk3))
				{
				 rrlist[chkrr]=guess[i];
				 chkrr++;
				}
			}
		}
	}
 for(i=0; i<(strlen(str)); i++)
	{
	 for(int k=0; k<(strlen(str)); k++)  //Here we look for the various cow conditions.
		{
		 str1[0]=str[i];
		 str2[0]=guess[k];
		 if(strcmpi(str1, str2)==0&&i!=k)
			{
			 int chk1=0;
          int chk2=0;
			 int chk4=0;
			 for(int p=0; p<=chk; p++)  //Whether the cow is a bull already; if so, no cow.
				{
				 if(toupper(guess[k])==toupper(blist[p])) chk1++;
				}
			 for(int q=0; q<=chkrr; q++)  //To check for repetition in the guess.
				{
				 if(toupper(str[k])==toupper(rrlist[q])) chk2++;
				}
			 for(int r=0; r<=chkr; r++) //Whether the cow is repeated. If so, half a cow. (See further for why)
				{
				 if(toupper(guess[k])==toupper(rlist[r])) chk4++;
				}
			 if((!(chk1)&&!(chk4))||((chk1)&&(chk4))) //For when word is bull+repeated(=cow), or notbull+notrepeated(=cow).
				{
				 cows++;
				}
			 else if(!(chk1)&&(chk4))  //If repeated, two increments are done; hence, (0.5)*2=1, which is the value we need
				{                       //to be added.
				 cows+=0.5;
				}
			 if(chk2) cows-=0.5;
			}
		}
	}
 gotoxy(8, j);
 if(cows>4) cows=4;
 cout<<ceil(cows);
 gotoxy(14, j);
 cout<<bulls;
 puts(str);
 j++;
 count++;
 if(bulls==4)       //Right word guessed.
	{
    cout<<endl;
	 cout<<"Correct! Word: "; puts(str);
	 scor=0;
	 if((maxi/5)==1) scor=(((maxi-count))*10)+2;
	 else if((maxi/5)==2) scor=(((maxi-count)/2)*10)+1;
	 else if((maxi/5)==3) scor=((maxi-count)/3)*10;
	 cout<<"Enter name."<<endl;
	 gets(nam);
	 if(s.highscore(nam, scor)) cout<<"High score! "<<endl;
	 cout<<"Score: "<<scor;
	}
 else if(count<maxi&&bulls<4)   //Trials < Maximum, word guessed not correct.
	{
	 chk=0;
	 bulls=cows=0;
	 goto B;
	}
 else if(count>=maxi)  //No. of trials > Max. Number.
	{
    cout<<endl;
	 cout<<"Out of guesses! Correct Word: "; puts(str);
	 cout<<"Better luck next time!"<<endl;
	}
}

void instructions()
{
 cout<<"1. A four-letter word is required to be guessed by the player, by entering\n";
 cout<<"   the right four-letter words, judging by trial-and-error based on the number\n";
 cout<<"   of cows and bulls displayed.\n";
 cout<<"2. Each guess entered by the player is analysed and number of cows and number\n";
 cout<<"   of bulls are displayed.\n";
 cout<<"3. For every letter in the player's guess which is correct but in the wrong\n";
 cout<<"   position, a cow is added.\n";
 cout<<"   Example: If the word is MOON,\n";
 cout<<"        COWS\n";
 cout<<"   NEST   1     (N is correct, in the wrong place)\n";
 cout<<"   NORM   2     (N and M are correct in the wrong positions.)\n";
 cout<<"   MONO   2     (N and O are in the wrong positions.)\n";
 cout<<"4. For every letter in the player's guess which is correct and in the right\n";
 cout<<"   position, a bull is added.\n";
 cout<<"   Example: If the word is MOON,\n";
 cout<<"        BULLS\n";
 cout<<"   MORN   3		(M, O, N in the right place)\n";
 cout<<"   MEAN   2		(N and M are correct.)\n";
 cout<<"   MONO   2		(M and O are bulls, N and the second O are cows.)\n";
 cout<<"5. By making the right guesses, the player can guess the word, on an average,\n";
 cout<<"   within 10-15 trials.\n";
 cout<<"   The difficulty levels are\n";
 cout<<"   Hard- 5 trials.\n";
 cout<<"   Normal- 10 trials. (default)\n";
 cout<<"   Easy- 15 trials.\n";
 cout<<"6. High scores can be viewed from the main menu. To get a high score, a player\n";
 cout<<"   will have to guess the word as fast as possible, ie in minimum number of\n";
 cout<<"   trials. Players playing hard mode will score more with a correct guess, than\n";
 cout<<"   those playing in normal mode, who will score more with a correct guess than\n";
 cout<<"   those in easy mode.\n";
 cout<<"Press ENTER to return to main menu."<<endl;
}


void main()                //Main Menu.
{
 clrscr();
 gotoxy(0, 0);
 cout<<"CCCCCCCCCCCCCCCCCCCCOOOOOOOOOOOOOOOOOOWWWWWWWWWWWWWWWWSSSSSSSSSSSSSSSSSSS"<<endl;
 cout<<"CCCCC         CCCCCCOOO            OOOW  WWWWWWWWWW  WSSSSSSS      SSSSSS"<<endl;
 cout<<"CCCC   CCCCCC    CCCOO  OOOOOOOOOO  OOW  WWWWWWWWWW  WSSSSS   SSSSSSSSSSS"<<endl;
 cout<<"CCC   CCCCCCCCCCCCCCO  OOOOOOOOOOOO  OW  WWWWWWWWWW  WSSSS   SSSSSSSSSSSS"<<endl;
 cout<<"CC   CCCCCCCCCCCCCCCO  OOOOOOOOOOOO  OW  WWWWWWWWWW  WSSSSS   SSSSSSSSSSS"<<endl;
 cout<<"C   CCCCCCCCCCCCCCCCO  OOOOOOOOOOOO  OW  WWWWWWWWWW  WSSSSSSS   SSSSSSSSS"<<endl;
 cout<<"CC   CCCCCCCCCCCCCCCO  OOOOOOOOOOOO  OW  WWW    WWW  WSSSSSSSSS   SSSSSSS"<<endl;
 cout<<"CCC   CCCCCCCCCCCCCCO  OOOOOOOOOOOO  OW  WW  WW  WW  WSSSSSSSSSSS   SSSSS"<<endl;
 cout<<"CCCC   CCCCCC    CCCOO  OOOOOOOOOO  OOW  W  WWWW  W  WSSSSSSSSSS   SSSSSS"<<endl;
 cout<<"CCCCC         CCCCCCOOO            OOOW  WWWWWWWWWW  WSSSSSS      SSSSSSS"<<endl;
 cout<<"CCCCCCCCCCCCCCCCCCCCOOOOOOOOOOOOOOOOOOWWWWWWWWWWWWWWWWSSSSSSSSSSSSSSSSSSS"<<endl;
 cout<<"												 	 	A N D 											"<<endl;
 cout<<"BBBBBBBBBBBBBBUUUUUUUUUUUUUUUUULLLLLLLLLLLLLLLLLLLLLLLLLLLLLSSSSSSSSSSSSSSS"<<endl;
 cout<<"B          BBBUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSSS    SSSSS"<<endl;
 cout<<"B  BBBBBB   BBUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSS  SS  SSSS"<<endl;
 cout<<"B  BBBBBBB   BUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSS  SSSSSSSSS"<<endl;
 cout<<"B  BBBBBB   BBUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSS  SSSSSSSS"<<endl;
 cout<<"B  BBB    BBBBUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSSS   SSSSSS"<<endl;
 cout<<"B  BBBBBB   BBUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSSSSS  SSSSS"<<endl;
 cout<<"B  BBBBBBB   BUUU  UUUUUUU  UUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSSSSSSS  SSSS"<<endl;
 cout<<"B  BBBBBB   BBUUUU UUUUUUU UUUULLL  LLLLLLLLLL  LLLLLLLLLLLLSSSS  SS  SSSSS"<<endl;
 cout<<"B          BBBUUUU         UUUULLL          LL           LLLSSSSS    SSSSSS"<<endl;
 cout<<"BBBBBBBBBBBBBBUUUUUUUUUUUUUUUUULLLLLLLLLLLLLLLLLLLLLLLLLLLLLSSSSSSSSSSSSSSS"<<endl;
 getchar();
 int choice=0;
 A:
 clrscr();
 cout<<"Main Menu."<<endl;
 cout<<"1. Play."<<endl;
 cout<<"2. Change difficulty."<<endl;
 cout<<"3. High scores."<<endl;
 cout<<"4. Instructions."<<endl;
 cout<<"5. Exit."<<endl;
 cin>>choice;
 switch(choice)
 {
  case 1: clrscr(); play(); getchar(); goto A;
  case 2: clrscr(); difficulty(); getchar(); goto A;
  case 3: clrscr(); s.highscores(); getchar(); goto A;
  case 4: clrscr(); instructions(); getchar(); goto A;
  case 5: abort();
 }
}