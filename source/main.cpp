#include <iostream>
#include <random>
#include <ctime>


#define DEBUG 1

#if DEBUG
	#define LOG(x) cout << endl << x << endl;
#else
	#define LOG (x)
#endif // Debug


using namespace std;


struct Damage
{
	float low;
	float high;
};


int main()
{
	default_random_engine randomize;
	uniform_real_distribution<float> attack(0.0f, 1.0f);
	uniform_real_distribution<float> Inititive(0.0f, 1.0f);

	// Humans vs Orcs


	// humans stats
	float humanHealth = 100.0f;
	float currentHumanHealth = humanHealth;
	Damage humanDamage;
	humanDamage.low = 30.0f;
	humanDamage.high = 60.0f;
	float humanAtkpercent = 0.5f;
	int numHumans;
	float humanAttack = 0.0f; // chance to damage enemy


	// Orcs stats
	float orcHealth = 230.0f;
	float currentOrcHealth = orcHealth;
	Damage orcDamage;
	orcDamage.low = 60.0f;
	orcDamage.high = 120.0f;
	float orcAtkPercent = 0.7f;
	int numOrcs;
	float orcAttack = 0.0f; // chance to damage enemy


	uniform_real_distribution<float> h_Damage(humanDamage.low, humanDamage.high);
	uniform_real_distribution<float> o_Damage(orcDamage.low, orcDamage.high); 


	cout << "Humans vs Orcs\n";


	// how many of each army?
	cout << "\nEnter the number of Humans in this army: ";
	cin >> numHumans;

	int HumansStarting = numHumans;

	// Orcs
	cout << "\nEnter the number of Orcs: ";
	cin >> numOrcs;

	int OrcsStarting = numOrcs;



	// randomize inititive
	char turn = ' ';
	float inititiveHuman = 0.0f; 
	float inititiveOrc = 0.0f; 


	cout << endl << "combat begins" << endl;


	while ((numHumans > 0) && (numOrcs > 0))
	{
		// inititive rolls
		// Humans
		inititiveHuman = Inititive(randomize);
		inititiveOrc = Inititive(randomize);

		//LOG("Human: " << inititiveHuman);
		//LOG("Orc: " << inititiveOrc);
		
		if (inititiveHuman > inititiveOrc)
		{
			turn = 'H';
		}
		else
		{
			turn = 'O';
		}


		// combat
		if (turn == 'H') // (Humans turn)
		{
			//LOG("Humans turn");

			humanAttack = attack(randomize);
			if (humanAttack >= humanAtkpercent)
			{
				float testnum = h_Damage(randomize);
				//LOG("Damage: " << testnum);
				currentOrcHealth -= testnum;

				if (currentOrcHealth <= 0)
				{
					//LOG("Orc Dies");
					numOrcs--;
					currentOrcHealth = orcHealth;
				}
			}

			turn = 'O';
		}

		else // turn == 'O' (Orcs turn)
		{
			//LOG("Orcs turn");
			orcAttack = attack(randomize);
			if (orcAttack >= orcAtkPercent)
			{
				float testnum = o_Damage(randomize);
				//LOG("Damage: " << testnum);
				currentHumanHealth -= testnum;


				if (currentHumanHealth <= 0)
				{
					//LOG("Human Dies");
					numHumans--;
					currentHumanHealth = humanHealth;
				}
			}



			turn = 'H';
		}

	}

	cout << endl << "combat has ended" << endl;


	// end results

	if (numHumans > 0)
		cout << endl << "Humans Won the WAR!" << endl;
	else
		cout << endl << "Orcs Won!" << endl;


	cout << HumansStarting - numHumans << " Humans Died in Combat" << endl;
	cout << OrcsStarting - numOrcs << " Orcs Died in Combat" << endl;


	getchar();
	getchar();

	return 0;
}