#include<bits/stdc++.h>

using namespace std;    

// Simoid function
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Derivative of sigmoid function
double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Training function
void train(vector<vector<double>>& weights, vector<double>& biases, vector<vector<double>>& inputs, vector<double>& outputs, int epochs, double learning_rate) {
    for(int epoch = 0; epoch < epochs; epoch++) {
        for(int i = 0; i < inputs.size(); i++) {
            vector<double> input = inputs[i];
            vector<double> weight_input_sum;
            for(int j = 0; j < weights.size(); j++) {
                double sum = 0;
                for(int k = 0; k < weights[j].size(); k++) {
                    for(int l=0; l<input.size(); l++){
                        sum += input[l] * weights[j][k];
                    }
                }
                sum += biases[j];
                weight_input_sum.push_back(sum);
            }
            vector<double> layer_output;
            for(int j = 0; j < weight_input_sum.size(); j++) {
                layer_output.push_back(sigmoid(weight_input_sum[j]));
            }
            vector<double> errors;
            for(int j = 0; j < layer_output.size(); j++) {
                errors.push_back(outputs[i] - layer_output[j]);
            }
            vector<double> adjustments;
            for(int j = 0; j < errors.size(); j++) {
                adjustments.push_back(errors[j] * sigmoid_derivative(layer_output[j]));
            }
            for(int j = 0; j < weights.size(); j++) {
                for(int k = 0; k < weights[j].size(); k++) {
                    weights[j][k] += input[k] * adjustments[j] * learning_rate;
                }
                biases[j] += adjustments[j] * learning_rate;
            }
        }
    }
}

int main(){
    vector<vector<double>> weights = {{0.1, 0.2, 0.3}, {0.2, 0.3, 0.4}, {0.3, 0.4, 0.5}};
    vector<double> biases = {0.1, 0.2, 0.3};
    vector<vector<double>> inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<double> outputs = {0, 1, 1, 0};
    train(weights, biases, inputs, outputs, 10000, 0.1);
    cout << "Weights: " << endl;
    for (int i = 0; i < weights.size(); i++) {
        for (int j = 0; j < weights[i].size(); j++) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}