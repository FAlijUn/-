#include<bits/stdc++.h>

using namespace std;

double start(){
    // 创建一个随机解
    return (double)rand() / RAND_MAX;
}

double cost(double x){
    // 计算解的成本
    return pow(x, 2);
}

double neighbour(double x){
    // 生成一个新解
    return x + ((double)rand() / RAND_MAX-0.5)/10;
}

double acceptance_probability(double cost, double new_cost, double temperature){
    // 计算接受概率
    if(new_cost < cost){
        return 1;
    }
    return exp((cost - new_cost) / temperature);
}

double temperature(double fraction){
    // 计算温度
    return max(0.01, min(1.0, 1 - fraction));
}


// 模拟退火：以一定概率接受更差的解，随着时间的推移，概率逐渐减小
double simulated_annealing(double (*cost)(double), double (*neighbour)(double), double (*acceptance_probability)(double, double, double), double (*temperature)(double), int maxsteps=1000){
    // 模拟退火算法
    srand(time(NULL));
    double x = start();
    double current_cost = cost(x);
    for(int step=0; step<maxsteps; step++){
        double T = temperature((double)step/maxsteps);
        double new_x = neighbour(x);
        double new_cost = cost(new_x);
        if(acceptance_probability(current_cost, new_cost, T) > (double)rand() / RAND_MAX){
            x = new_x;
            current_cost = new_cost;
        }
    }
    return x;
}

int main(){
    cout << simulated_annealing(cost, neighbour, acceptance_probability, temperature) << endl;
    return 0;
}