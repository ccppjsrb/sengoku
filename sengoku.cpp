// 戦国無双
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

#define BIGBONUS 1/425.56
#define BG (1/728.18+BIGBONUS)
#define BELL (1/147.60+BG)
#define RED_10 (1/10.37+BELL)
#define BLACK_10 (1/10.37+RED_10)
#define CHERRY (1/128+BLACK_10)
#define RED_SIN (1/18.01+CHERRY)
#define BLACK_SIN (1/18.01+RED_SIN)

#define SPREPLAY (1/107.78+BLACK_SIN)
#define REPLAY (1/8+SPREPLAY)

#define RT_REPLAY (1/1.48+BLACK_SIN)


#define BIG_RED_10 1/24
#define BIG_BLACK_10 (1/24+BIG_RED_10)
#define BIG_BELL (1/12+BIG_BLACK_10)


#define LOW_0_0 0.021
#define LOW_0_1 (0.043+LOW_0_0)
#define LOW_0_2 (0.085+LOW_0_1)
#define LOW_0_3 (0.17+LOW_0_2)
#define LOW_0_4 (0.34+LOW_0_3)
#define LOW_0_5 (0.084+LOW_0_4)
#define LOW_0_6 (0.084+LOW_0_5)
#define LOW_0_7 (0.084+LOW_0_6)
#define LOW_0_8 (0.084+LOW_0_7)
#define LOW_0_10 (0.008+LOW_0_8)

#define LOW_1_0 0.021
#define LOW_1_1 (0.043+LOW_1_0)
#define LOW_1_2 (0.085+LOW_1_1)
#define LOW_1_3 (0.17+LOW_1_2)
#define LOW_1_4 (0.34+LOW_1_3)
#define LOW_1_5 (0.084+LOW_1_4)
#define LOW_1_6 (0.084+LOW_1_5)
#define LOW_1_7 (0.084+LOW_1_6)
#define LOW_1_8 (0.091+LOW_1_7)

#define LOW_2_0 0.021
#define LOW_2_1 (0.043+LOW_2_0)
#define LOW_2_2 (0.085+LOW_2_1)
#define LOW_2_3 (0.17+LOW_2_2)
#define LOW_2_4 (0.34+LOW_2_3)
#define LOW_2_5 (0.084+LOW_2_4)
#define LOW_2_6 (0.084+LOW_2_5)
#define LOW_2_7 (0.175+LOW_2_6)

#define LOW_3_0 0.021
#define LOW_3_1 (0.043+LOW_3_0)
#define LOW_3_2 (0.085+LOW_3_1)
#define LOW_3_3 (0.17+LOW_3_2)
#define LOW_3_4 (0.34+LOW_3_3)
#define LOW_3_5 (0.084+LOW_3_4)
#define LOW_3_6 (0.154+LOW_3_5)

#define LOW_4_0 0.156
#define LOW_4_1 (0.203+LOW_4_0)
#define LOW_4_2 (0.266+LOW_4_1)
#define LOW_4_3 (0.251+LOW_4_2)
#define LOW_4_4 (0.124+LOW_4_3)

#define LOW_5_0 0.308
#define LOW_5_1 (0.5+LOW_5_0)
#define LOW_5_2 (0.192+LOW_5_1)

#define HIGH_0_0 0.036
#define HIGH_0_1 (0.072+HIGH_0_0)
#define HIGH_0_2 (0.144+HIGH_0_1)
#define HIGH_0_3 (0.288+HIGH_0_2)
#define HIGH_0_4 (0.313+HIGH_0_3)
#define HIGH_0_5 (0.039+HIGH_0_4)
#define HIGH_0_6 (0.039+HIGH_0_5)
#define HIGH_0_7 (0.039+HIGH_0_6)
#define HIGH_0_8 (0.03+HIGH_0_7)

#define HIGH_1_0 0.036
#define HIGH_1_1 (0.072+HIGH_1_0)
#define HIGH_1_2 (0.144+HIGH_1_1)
#define HIGH_1_3 (0.288+HIGH_1_2)
#define HIGH_1_4 (0.313+HIGH_1_3)
#define HIGH_1_5 (0.039+HIGH_1_4)
#define HIGH_1_6 (0.039+HIGH_1_5)
#define HIGH_1_7 (0.069+HIGH_1_6)

#define HIGH_2_0 0.036
#define HIGH_2_1 (0.072+HIGH_2_0)
#define HIGH_2_2 (0.144+HIGH_2_1)
#define HIGH_2_3 (0.288+HIGH_2_2)
#define HIGH_2_4 (0.281+HIGH_2_3)
#define HIGH_2_5 (0.125+HIGH_2_4)
#define HIGH_2_6 (0.054+HIGH_2_5)

#define HIGH_3_0 0.25
#define HIGH_3_1 (0.25+HIGH_3_0)
#define HIGH_3_2 (0.339+HIGH_3_1)
#define HIGH_3_3 (0.162+HIGH_3_2)

#define HIGH_4_0 0.5
#define HIGH_4_1 (0.5+HIGH_4_0)

#define HIGH_5_0 1

#define HIGH_BELL 1/2.64
#define HIGH_CHERRY 1/2.64
#define HIGH_10 1/14.4

#define HIGH_AFTERBONUS_50 0.591
#define HIGH_AFTERBONUS_75 (0.309+HIGH_AFTERBONUS_50)
#define HIGH_AFTERBONUS_100 (0.093+HIGH_AFTERBONUS_75)
#define HIGH_FLG_25 0.665
#define HIGH_FLG_50 (0.243+HIGH_FLG_25)
#define HIGH_FLG_75 (0.046+HIGH_FLG_50)
#define HIGH_FLG_100 (0.046+HIGH_FLG_75)

#define LOW_BG 0.239
#define HIGH_BG 0.688

enum status{ low, high };
enum rtstatus{ normal, art, rt, petit_rt };
enum himode_game{ bonus, f };
class sengoku{
	int currentgame, totalgame, highgame, petitrtcount;
	status st;
	rtstatus rt;
	bool tenjou;
public:
	void init(){ currentgame = totalgame = 0;
		highgame = 0;
		st = low;
		rt = normal;
		petitrtcount = 0; 
		tenjou = false;
	}
	void play(){ ++currentgame; ++totalgame; if(st == high){ --highgame; if(!highgame) st = low; } if(petitrtcount) { --petitrtcount; if(!petitrtcount) rt = normal; }}
	void getbonus(){ currentgame = 0; petitrtcount = 0; tenjou = false; }
	int getcurrentgame(){ return currentgame; }
	int gettotalgame(){ return totalgame; }
	int gethighgame(){ return highgame; }
	int getpetitrtcount(){ return petitrtcount; }
	bool gettenjou(){ return tenjou;}
	status getst(){ return st; }
	rtstatus getrt(){ return rt; }
	void setst(status s){ st = s; }
	void setrt(rtstatus r){ rt = r; }
	void spreplay(){ petitrtcount = 3; rt = petit_rt; }
	void reachtenjou(){ tenjou = true; }
	void plus_highgame(int i){ highgame += i; }
};
class keiji{
	int get_medal;
	int norma;
	int musougage;
	int count2;
public:
	void init(){ get_medal = 0; musougage = 0; count2 = 0; }
	void bigbonus(status st);
	void setnorma(status st, int m);
	int medal(){ return get_medal; }
	int getnorma(){ return norma; }
	int getmusougage(){ return musougage;}
	void safe(){ --norma; }
	void mugen(){ norma = 0; }
};
void keiji::bigbonus(status st)
{
	double flg;
	int lost = 0;
	while(get_medal >= 400)
	{
		lost += 3;
		flg = (double)rand() / (RAND_MAX+1.0);
		if(flg < BIG_RED_10)
		{
			get_medal += 10;
			++musougage;
			++count2;
		}
		else if(BIG_RED_10 <= flg && flg < BIG_BLACK_10)
			++count2;
		else if(BIG_BLACK_10 <= flg && flg < BIG_BELL)
		{
			get_medal += 10;
			flg = (double)rand() / (RAND_MAX+1.0);
			if( flg < 0.2)
				++musougage;
		}
		else
			get_medal += 10;
	}
	get_medal -= lost;
	if(!count2 || musougage > 5)
		musougage = 5;
	setnorma(st, musougage);
}

void keiji::setnorma(status st, int m)
{
	double flg;
	flg = (double)rand() / (RAND_MAX+1.0);
	if(st == low)
	{
		switch(m)
		{
		case 0:
			if(flg < LOW_0_0)
				norma = 0;
			else if(LOW_0_0 <= flg && flg < LOW_0_1)
				norma = 1;
			else if(LOW_0_1 <= flg && flg < LOW_0_2)
				norma = 2;
			else if(LOW_0_2 <= flg && flg < LOW_0_3)
				norma = 3;
			else if(LOW_0_3 <= flg && flg < LOW_0_4)
				norma = 4;
			else if(LOW_0_4 <= flg && flg < LOW_0_5)
				norma = 5;
			else if(LOW_0_5 <= flg && flg < LOW_0_6)
				norma = 6;
			else if(LOW_0_6 <= flg && flg < LOW_0_7)
				norma = 7;
			else if(LOW_0_7 <= flg && flg < LOW_0_8)
				norma = 8;
			else
				norma = 10;		
			break;
		case 1:
			if(flg < LOW_1_0)
				norma = 0;
			else if(LOW_1_0 <= flg && flg < LOW_1_1)
				norma = 1;
			else if(LOW_1_1 <= flg && flg < LOW_1_2)
				norma = 2;
			else if(LOW_1_2 <= flg && flg < LOW_1_3)
				norma = 3;
			else if(LOW_1_3 <= flg && flg < LOW_1_4)
				norma = 4;
			else if(LOW_1_4 <= flg && flg < LOW_1_5)
				norma = 5;
			else if(LOW_1_5 <= flg && flg < LOW_1_6)
				norma = 6;
			else if(LOW_1_6 <= flg && flg < LOW_1_7)
				norma = 7;
			else
				norma = 8;
			break;
		case 2:
			if(flg < LOW_2_0)
				norma = 0;
			else if(LOW_2_0 <= flg && flg < LOW_2_1)
				norma = 1;
			else if(LOW_2_1 <= flg && flg < LOW_2_2)
				norma = 2;
			else if(LOW_2_2 <= flg && flg < LOW_2_3)
				norma = 3;
			else if(LOW_2_3 <= flg && flg < LOW_2_4)
				norma = 4;
			else if(LOW_2_4 <= flg && flg < LOW_2_5)
				norma = 5;
			else if(LOW_2_5 <= flg && flg < LOW_2_6)
				norma = 6;
			else
				norma = 7;
				break;
		case 3:
			if(flg < LOW_3_0)
				norma = 0;
			else if(LOW_3_0 <= flg && flg < LOW_3_1)
				norma = 1;
			else if(LOW_3_1 <= flg && flg < LOW_3_2)
				norma = 2;
			else if(LOW_3_2 <= flg && flg < LOW_3_3)
				norma = 3;
			else if(LOW_3_3 <= flg && flg < LOW_3_4)
				norma = 4;
			else if(LOW_3_4 <= flg && flg < LOW_3_5)
				norma = 5;
			else
				norma = 6;
			break;
		case 4:
			if(flg < LOW_4_0)
				norma = 0;
			else if(LOW_4_0 <= flg && flg < LOW_4_1)
				norma = 1;
			else if(LOW_4_1 <= flg && flg < LOW_4_2)
				norma = 2;
			else if(LOW_4_2 <= flg && flg < LOW_4_3)
				norma = 3;
			else
				norma = 4;
			break;
		case 5:
			if(flg < LOW_5_0)
				norma = 0;
			else if(LOW_5_0 <= flg && flg < LOW_5_1)
				norma = 1;
			else
				norma = 2;
			break;
		}
	}
	else	
	{
		switch(m)
		{
		case 0:
			if(flg < HIGH_0_0)
				norma = 0;
			else if(HIGH_0_0 <= flg && flg < HIGH_0_1)
				norma = 1;
			else if(HIGH_0_1 <= flg && flg < HIGH_0_2)
				norma = 2;
			else if(HIGH_0_2 <= flg && flg < HIGH_0_3)
				norma = 3;
			else if(HIGH_0_3 <= flg && flg < HIGH_0_4)
				norma = 4;
			else if(HIGH_0_4 <= flg && flg < HIGH_0_5)
				norma = 5;
			else if(HIGH_0_5 <= flg && flg < HIGH_0_6)
				norma = 6;
			else if(HIGH_0_6 <= flg && flg < HIGH_0_7)
				norma = 7;
			else
				norma = 8;		
			break;
		case 1:
			if(flg < HIGH_1_0)
				norma = 0;
			else if(HIGH_1_0 <= flg && flg < HIGH_1_1)
				norma = 1;
			else if(HIGH_1_1 <= flg && flg < HIGH_1_2)
				norma = 2;
			else if(HIGH_1_2 <= flg && flg < HIGH_1_3)
				norma = 3;
			else if(HIGH_1_3 <= flg && flg < HIGH_1_4)
				norma = 4;
			else if(HIGH_1_4 <= flg && flg < HIGH_1_5)
				norma = 5;
			else if(HIGH_1_5 <= flg && flg < HIGH_1_6)
				norma = 6;
			else
				norma = 7;
			break;
		case 2:
			if(flg < HIGH_2_0)
				norma = 0;
			else if(HIGH_2_0 <= flg && flg < HIGH_2_1)
				norma = 1;
			else if(HIGH_2_1 <= flg && flg < HIGH_2_2)
				norma = 2;
			else if(HIGH_2_2 <= flg && flg < HIGH_2_3)
				norma = 3;
			else if(HIGH_2_3 <= flg && flg < HIGH_2_4)
				norma = 4;
			else if(HIGH_2_4 <= flg && flg < HIGH_2_5)
				norma = 5;
			else
				norma = 6;
			break;
		case 3:
			if(flg < HIGH_3_0)
				norma = 0;
			else if(HIGH_3_0 <= flg && flg < HIGH_3_1)
				norma = 1;
			else if(HIGH_3_1 <= flg && flg < HIGH_3_2)
				norma = 2;
			else
				norma = 3;
			break;
		case 4:
			if(flg < HIGH_4_0)
				norma = 0;
			else
				norma = 1;
			break;
		case 5:
			norma = 0;
			break;
		}
	}

}

int highmode(himode_game h)
{
	double flg = (double)rand() / (RAND_MAX+1.0);
	if(h == bonus)
	{
		if(flg < HIGH_AFTERBONUS_50)
			return 50;
		else if(HIGH_AFTERBONUS_50 <= flg && flg < HIGH_AFTERBONUS_75)
			return 75;
		else
			return 100;
	}
	else
	{
		if(flg < HIGH_FLG_25)
			return 25;
		else if(HIGH_FLG_25 <= flg && flg < HIGH_FLG_50)
			return 50;
		else if(HIGH_FLG_50 <= flg && flg < HIGH_FLG_75)
			return 75;
		else
			return 100;
	}
}
int main()
{
	double getmedal=0.0, lostmedal=0.0;
	double flg;
	sengoku sim;
	keiji k;
	int count_10;
	int days, games;

	srand((unsigned)time(NULL));
	cout << "days?:";
	cin >> days;
	cout << "games?:";
	cin >> games;
	
	for(int j= 0; j<days; ++j)
	{
		count_10=0;
		sim.init();
		for(int i=0; i < games; ++i)
		{
			lostmedal += 3;
			flg = (double)rand() / (RAND_MAX+1.0);
			sim.play();
			if(sim.gethighgame() && sim.getst() == low)
				sim.setst(high);
		
			if(flg < BIGBONUS)
			{
				sim.getbonus();
				sim.plus_highgame(highmode(bonus));
				sim.setrt(art);
				count_10=0;
				k.init();				
				if(sim.gettenjou())
					k.bigbonus(high);
				else
					k.bigbonus(sim.getst());
				getmedal += k.medal();
			}
			else if(BIGBONUS <= flg && flg < BG)
			{
				getmedal += 60;
				sim.getbonus();
				sim.plus_highgame(highmode(bonus));
				count_10=0;
				flg = (double)rand() / (RAND_MAX+1.0);
				if(sim.getst() == low)
				{
					if(flg < LOW_BG)
					{
						k.mugen();
						sim.setrt(art);
					}
					else
						sim.setrt(rt);
				}
				else
				{
					if(flg < HIGH_BG)
					{
						k.mugen();
						sim.setrt(art);
					}
					else
						sim.setrt(rt);
				}
				
			}
			else if(BG <= flg && flg < BELL)
			{
				getmedal += 10;
				if(sim.getrt() == rt)
				{
					flg = (double)rand() / (RAND_MAX+1.0);
					if(flg < HIGH_BELL)
					{
						sim.setrt(art);
						k.mugen();
					}
				}
				else
				{
					flg = (double)rand() / (RAND_MAX+1.0);
					if(flg < HIGH_BELL)
					{
						sim.plus_highgame(highmode(f));
					}
				}

				count_10=0;
			}
			else if(BELL <= flg && flg < RED_10)
			{
				getmedal += 10;
				++count_10;
				if(count_10 >= 2)
				{
					if(sim.getrt() == rt)
					{
						flg = (double)rand() / (RAND_MAX+1.0);
						if(flg < HIGH_10)
						{
							sim.setrt(art);
							k.mugen();
						}
					}
					else
					{
						flg = (double)rand() / (RAND_MAX+1.0);
						if(flg < HIGH_10)
						{
							sim.plus_highgame(highmode(f));
						}
					}
				}
			}
			else if(RED_10 <= flg && flg < BLACK_10)
			{
				if(sim.getrt() == art)
					getmedal += 10;
				++count_10;
				if(count_10 >= 2)
				{
					if(sim.getrt() == rt)
					{
						flg = (double)rand() / (RAND_MAX+1.0);
						if(flg < HIGH_10)
						{
							sim.setrt(art);
							k.mugen();
						}
					}
					else
					{
						flg = (double)rand() / (RAND_MAX+1.0);
						if(flg < HIGH_10)
						{
							sim.plus_highgame(highmode(f));
						}
					}
				}			}
			else if(BLACK_10 <= flg && flg < CHERRY)
			{
				if(sim.getrt() == rt)
				{
					flg = (double)rand() / (RAND_MAX+1.0);
					if(flg < HIGH_CHERRY)
					{
						sim.setrt(art);
						k.mugen();
					}
				}
				else
				{
					flg = (double)rand() / (RAND_MAX+1.0);
					if(flg < HIGH_CHERRY)
					{
						sim.plus_highgame(highmode(f));
					}
				}			
				count_10=0;
			}
			else if(CHERRY <= flg && flg < RED_SIN)
			{
				if(sim.getrt() == art)
					if(k.getnorma())
						k.safe();
				count_10=0;
			}
			else if(RED_SIN <= flg && flg < BLACK_SIN)
			{
				if((sim.getrt() == art && k.getnorma()) || sim.getrt() == rt)
					sim.setrt(normal);
				count_10=0;
			}
			else if(sim.getrt() == normal)
			{
				if(BLACK_SIN <= flg && flg < SPREPLAY)
				{
					getmedal += 3;
					count_10=0;
					sim.spreplay();
				}
				else if(SPREPLAY <= flg && flg < REPLAY)
					getmedal += 3;
			}
			else if(BLACK_SIN <= flg && flg < RT_REPLAY)
				getmedal += 3;

			if(sim.getcurrentgame() >= 1059)
				sim.reachtenjou();
			if(sim.gettotalgame() >= 3000 && sim.getrt() == normal && sim.getst() == low)
				break;
		}
	}
	cout << "average:" << (getmedal - lostmedal)/days << " medals\n";
	cout << "return:" << getmedal / lostmedal * 100.0 << " %\n";
	
	return 0;
} 
