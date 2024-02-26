// 遗传算法生成一个目标字符串
#include<bits/stdc++.h>
using namespace std;

//定义种群的大小
const int POPULATION_SIZE = 100;

struct Individual {
    string chromosome;
    int fitness;
    Individual(string chromosome, int fitness) : chromosome(chromosome), fitness(fitness) {};
};

int random_num(int start, int end) {
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

int mutated_genes(){
    int len = 10;//可能的基因型
    int r = random_num(0, len - 1);
    return (char)(r+'0');
}

string create_gnome() {
    int len = 10;
    string gnome = "";
    for(int i = 0; i < len; i++)
        gnome += mutated_genes();
    return gnome;
}

//计算适应度
int calculate_fitness(string chromosome) {
    string target = "1010101010"; //目标字符串
    int fitness = 0;
    for(int i =0; i < chromosome.size(); i++) {
        if(chromosome[i] != target[i])
            fitness++;
    }
    return fitness;
}

//交叉产生新的后代
Individual mate(Individual par1, Individual par2){
    string child_chromosome = "";
    int len = par1.chromosome.size();
    for(int i = 0; i < len; i++) {
        float p = random_num(0, 100)/100;
        if(p < 0.45)
            child_chromosome += par1.chromosome[i];
        else if(p < 0.90)
            child_chromosome += par2.chromosome[i];
        else
            child_chromosome += mutated_genes();
    }
    return Individual(child_chromosome, calculate_fitness(child_chromosome));
}

int main(){
    srand((unsigned)(time(0)));
    
    int generation = 0;
    vector<Individual> population;
    bool found = false;

    //初始化种群
    for(int i = 0; i < POPULATION_SIZE; i++) {
        string gnome = create_gnome();
        population.push_back(Individual(gnome, calculate_fitness(gnome)));
    }

    while(! found){
        //按照适应度排序
        sort(population.begin(), population.end(), [](const Individual &x, const Individual &y) { return x.fitness < y.fitness; });

        //如果找到目标,适应度为0
        if(population[0].fitness <= 0) {
            found = true;
            break;
        }

        vector<Individual> new_generation;

        //选择适应度高的个体
        int s = (10*POPULATION_SIZE)/100;
        for(int i = 0; i < s; i++)
            new_generation.push_back(population[i]);
        
        //50%的个体进行交叉
        s = (90*POPULATION_SIZE)/100;
        for(int i = 0; i < s; i++) {
            int r = random_num(0, 50);
            Individual parent1 = population[r];
            r = random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = mate(parent1, parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;
        cout << "Generation: " << generation << "\t";
        cout << "String: " << population[0].chromosome << "\t";
        cout << "Fitness: " << population[0].fitness << "\n";
        generation++;
    }
    cout << "Generation: " << generation << "\t";
    cout << "String: " << population[0].chromosome << "\t";
    cout << "Fitness: " << population[0].fitness << "\n";
}