#include<bits/stdc++.h>

using namespace std;

struct Node {
    string question;
    map<string, Node*>children;
};

bool allPositive(vector<vector<string>> examples){
    for(int i = 0; i < examples.size(); i++){
        if(examples[i][examples[i].size()-1] == "no"){
            return false;
        }
    }
    return true;
}

bool allNegative(vector<vector<string>> examples){
    for(int i = 0; i < examples.size(); i++){
        if(examples[i][examples[i].size()-1] == "yes"){
            return false;
        }
    }
    return true;
}

string mostCommonOutput(vector<vector<string>> examples){
    map<string, int> count;
    for(auto example: examples){
        count[example[example.size()-1]]++;
    }
    string mostCommon = examples[0][examples[0].size()-1];
    for(auto c: count){
        if(c.second > count[mostCommon]){
            mostCommon = c.first;
        }
    }
    return mostCommon;
}

string selectBestAttribute(vector<vector<string>> examples, vector<string> attributes){
    map<string, double> infoGain;
    for(auto attribute: attributes){
        infoGain[attribute] = 0;
    }
    // Calculate the entropy of the target attribute
    map<string, int> count;
    for(auto example: examples){
        count[example[example.size()-1]]++;
    }
    double entropy = 0;
    for(auto c: count){
        double p = (double)c.second/examples.size();
        entropy += -p*log2(p);
    }
    // Calculate the information gain of each attribute
    for(auto attribute: attributes){
        map<string, int> count;
        map<string, map<string, int>> count2;
        for(auto example: examples){
            count[example[example.size()-1]]++;
            count2[example[example.size()-1]][example[find(attributes.begin(), attributes.end(), attribute)-attributes.begin()]]++;
        }
        double remainder = 0;
        for(auto c: count){
            double p = (double)c.second/examples.size();
            double entropy2 = 0;
            for(auto c2: count2[c.first]){
                double p2 = (double)c2.second/c.second;
                if(p2 != 0){
                    entropy2 += -p2*log2(p2);
                }
            }
            remainder += p*entropy2;
        }
        infoGain[attribute] = entropy - remainder;
    }
    // Return the attribute with the highest information gain
    string bestAttribute = attributes[0];
    for(auto attribute: attributes){
        if(infoGain[attribute] > infoGain[bestAttribute]){
            bestAttribute = attribute;
        }
    }
    return bestAttribute;
}


vector<string> possibleValues(string attribute, vector<vector<string>> examples, vector<string> attributes) {
    set<string> values;
    int attributeIndex = find(attributes.begin(), attributes.end(), attribute)-attributes.begin(); // You need to implement this function

    for (auto example : examples)
        values.insert(example[attributeIndex]);

    return vector<string>(values.begin(), values.end());
}

vector<vector<string>> selectExamplesWithValue(vector<vector<string>> examples, string attribute, string value, vector<string> attributes){
    vector<vector<string>> examplesWithValue;
    int attributeIndex = find(attributes.begin(), attributes.end(), attribute)-attributes.begin();
    for(int i = 0; i < examples.size(); i++){
        if(examples[i][attributeIndex] == value){
            examplesWithValue.push_back(examples[i]);
        }
    }
    return examplesWithValue;
}


Node* ID3(vector<vector<string>> examples, vector<string> attributes){
    Node* node = new Node();

    // If all examples are positive or are negative, return a leaf node 
    // 所有样本属性相同
    if(allPositive(examples)||allNegative(examples)){
        node->question = examples[0][examples[0].size()-1];
        return node;
    }

    // If attributes is empty, return a leaf node with the most common value of the target attribute in examples
    // 属性为空
    if(attributes.empty()){
        node->question=mostCommonOutput(examples);
        return node;
    }

    // Otherwise, A <- the attribute in attributes that best classifies examples
    // A <- 信息增益最大的属性
    string bestAttribute = selectBestAttribute(examples, attributes);
    node->question = bestAttribute;

    // For each possible value of the best attribute, add a new branch below node
    // 对于最佳属性的每个可能值，在节点下添加一个新分支
    for(string value:possibleValues(bestAttribute,examples,attributes)){
        vector<vector<string>> examplesWithValue = selectExamplesWithValue(examples, bestAttribute, value, attributes);
        if(examplesWithValue.empty()){
            Node* leaf = new Node();
            leaf->question = mostCommonOutput(examples);
            node->children[value] = leaf;
        }else{
            vector<string> newAttributes = attributes;
            newAttributes.erase(find(newAttributes.begin(), newAttributes.end(), bestAttribute));
            node->children[value] = ID3(examplesWithValue, newAttributes);
        }
    }
    return node;
    }

void printTree(Node* node, string indent = "") {
    if (node->children.empty()) {
        cout << indent << node->question << endl;
    } else {
        cout << indent << node->question << "?" << endl;
        for (auto pair : node->children) {
            cout << indent << "- " << pair.first << ": ";
            printTree(pair.second, indent + "  ");
        }
    }
}

int main() {
    vector<vector<string>> examples = {
        {"sunny", "hot", "high", "weak", "no"},
        {"sunny", "hot", "high", "strong", "no"},
        {"overcast", "hot", "high", "weak", "yes"},
        {"rain", "mild", "high", "weak", "yes"},
        {"rain", "cool", "normal", "weak", "yes"},
        {"rain", "cool", "normal", "strong", "no"},
        {"overcast", "cool", "normal", "strong", "yes"},
        {"sunny", "mild", "high", "weak", "no"},
        {"sunny", "cool", "normal", "weak", "yes"},
        {"rain", "mild", "normal", "weak", "yes"},
        {"sunny", "mild", "normal", "strong", "yes"},
        {"overcast", "mild", "high", "strong", "yes"},
        {"overcast", "hot", "normal", "weak", "yes"},
        {"rain", "mild", "high", "strong", "no"}
    };
    vector<string> attributes = {"outlook", "temperature", "humidity", "wind"};
    Node* root = ID3(examples, attributes);
    printTree(root);
}