#include <bits/stdc++.h> 
#include <limits.h> 

using namespace std; 

#define vertices 6 
#define genesList PRANJL 
//#define starting 0 
#define initial_population 10 

#define cooldown(val) val*0.9

struct person
{ 
	string gnome; 
	int fitness; 
}; 

int random_in(int range_open, int range_close) 
{ 
	int rnum = range_close - range_open; 
	int return_value = range_open + rand() % rnum; 
	return return_value; 
} 

bool check_repeat(string str, char c) 
{ 
	for (int i = 0; i < str.size(); i++)
		if (str[i] == c) return true;
    
	return false; 
} 

string mutate(string gnome) 
{ 
	while(1)
    { 
		int point1 = random_in(1, vertices); 
		int point2 = random_in(1, vertices);

		if (point1 != point2)
        { 
			char temp = gnome[point1]; 
			gnome[point1] = gnome[point2]; 
			gnome[point2] = temp; 
			break; 
		} 
	} 
	return gnome; 
} 

string make_new_genome() 
{ 
	string gnome = "0"; 
	while(1)
    { 
		if(gnome.size() == vertices)
        { 
			gnome += gnome[0]; 
			break; 
		}

		int temp = random_in(1, vertices);

		if (!check_repeat(gnome, (char)(temp + 48))) 
			gnome += (char)(temp + 48); 
	} 
	return gnome; 
} 

int calculate_fitness(string gnome) 
{ 
	int map[vertices][vertices] = {
                                    { 0, 3, INT_MAX, 15, 4, 6 }, 
                                    { 3, 0, 2, 7, INT_MAX, 8 }, 
                                    { INT_MAX, 2, 0, 5, 5, 1 }, 
                                    { 15, 7, 5, 0, 9, 19 }, 
                                    { 4, INT_MAX, 5, 9, 0, 11 },
                                    { 6, 8, 1, 19, 11, 0}
                                };

	int fitness = 0; 
	for(int i=0; i<gnome.size()-1; i++)
    { 
		if(map[gnome[i]-48][gnome[i+1]-48] == INT_MAX) 
			return INT_MAX;

		fitness += map[gnome[i]-48][gnome[i+1]-48]; 
	} 
	return fitness; 
} 

bool lesser(struct person t1, struct person t2) 
{ 
	return t1.fitness < t2.fitness; 
} 

// Utility function for TSP problem. 
void TSP_genetic(int map[vertices][vertices]) 
{ 
	int generation = 1; 

	int threshold = 5; 

	vector<struct person> population; 
	struct person temp; 

	for(int i=0; i<initial_population; i++)
    { 
		temp.gnome = make_new_genome(); 
		temp.fitness = calculate_fitness(temp.gnome); 
		population.push_back(temp); 
	} 

	cout << "\nInitial population : " << endl << "GNOME\tFitness\n"; 
	for (int i=0; i<initial_population; i++)
		cout << population[i].gnome << "\t" << population[i].fitness << endl; 
	cout << "\n"; 

	//bool found = false; 
	int temperature = 10000; 

	while (temperature > 1000 && generation <= threshold)
    { 
		sort(population.begin(), population.end(), lesser); 

		cout << "\nCurrent Temperature : " << temperature << "\n"; 
		vector<struct person> new_population; 

		for (int i=0; i<initial_population; i++)
        { 
			struct person p1 = population[i]; 

			while(1)
            { 
				string new_g = mutate(p1.gnome); 
				struct person new_gnome;

				new_gnome.gnome = new_g; 
				new_gnome.fitness = calculate_fitness(new_gnome.gnome); 

				if (new_gnome.fitness <= population[i].fitness)
                { 
					new_population.push_back(new_gnome); 
					break; 
				} 
				else
                {
					float prob = pow(2.7, -1 * ((float)(new_gnome.fitness-population[i].fitness)/temperature)); 
					if (prob > 0.5)
                    { 
						new_population.push_back(new_gnome); 
						break; 
					} 
				} 
			} 
		} 

		temperature = cooldown(temperature);
		population = new_population; 
		cout << "Generation : " << generation << " \n"; 
		cout << "GNOME\tFitness\n\n"; 

		for (int i=0; i<initial_population; i++) 
			cout << population[i].gnome << "\t" << population[i].fitness << endl;

		generation++; 
	} 
} 

int main() 
{ 
	int map[vertices][vertices] = {
                                    { 0, 3, INT_MAX, 15, 4, 6 }, 
                                    { 3, 0, 2, 7, INT_MAX, 8 }, 
                                    { INT_MAX, 2, 0, 5, 5, 1 }, 
                                    { 15, 7, 5, 0, 9, 19 }, 
                                    { 4, INT_MAX, 5, 9, 0, 11 },
                                    { 6, 8, 1, 19, 11, 0}
                                };

	TSP_genetic(map); 
} 
