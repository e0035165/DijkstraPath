//
//  main.cpp
//  DijkstraPath
//
//  Created by Sart Way on 3/8/23.
//

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <list>
#include<queue>
#include<set>
using namespace std;


string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
vector<int> shortestReach(int n, vector<vector<int>> edges, int s);


vector<int> shortestReach(int n, vector<vector<int>> edges, int s)
{
    vector<int> result;
    vector<vector<pair<int,int>>> sorted_edges(n);
    for(auto x=edges.begin();x!=edges.end();++x)
    {
        pair<int,int>temp((*x)[1]-1,(*x)[2]);
        pair<int,int>tempt((*x)[0]-1,(*x)[2]);
        cout << (*x)[0] - 1 << " val: " << (*x)[1] - 1 << endl;
        sorted_edges[(*x)[0]-1].push_back(temp);
        sorted_edges[(*x)[1]-1].push_back(tempt);
    }
    int* distances = new int[n];
    bool *visited = new bool[n];
    //bool *inQueue = new bool[n];
    for(int i=0;i<n;++i)
        distances[i] = INT_MAX,visited[i]=false;
    
    queue<int>nodes;
    set<int>nodal;
    nodes.push(s-1);
    nodal.insert(s-1);
    distances[s-1] = 0;
    
    do{
        int index = nodes.front();
        auto it = nodal.begin();
        index = *it;
        for(auto x=sorted_edges[index].begin();x!=sorted_edges[index].end();++x)
        {
            if((distances[index] + (*x).second) < distances[(*x).first])
            {
                distances[(*x).first] = distances[index] + (*x).second;
                nodes.push((*x).first);
                if(nodal.find((*x).first)!=nodal.end())
                {
                    nodal.erase((*x).first);
                }
                nodal.insert((*x).first);
            }
        }
        visited[index] = true;
        nodal.erase(it);
        nodes.pop();
    }while(!nodes.empty());
    
    delete [] visited;
    
    for(int i=0;i<n;++i)
    {
        if(distances[i]==INT_MAX)
        {
            result.push_back(-1);
        } else if(distances[i] != 0)
        {
            result.push_back(distances[i]);
        }
    }
    //cout << endl;
    return result;
}


int main(int argc, const char * argv[]) {
    fstream input("input.txt", ios::in | ios::out);
    fstream output("output.txt", ios::in);
    string q_temp;
    if(input.is_open())
    {
        cout << "File 1 is open" << endl;
    }
    
    if(output.is_open())
    {
        cout << "File 2 is open" << endl;
    }
    getline(input, q_temp);
    
    int q = stoi(ltrim(rtrim(q_temp)));
    
    for(int t_itr=0;t_itr<q;++t_itr)
    {
        string first_multiple_input_temp;
        string second_multiple_input_temp;
        getline(input, first_multiple_input_temp);
        getline(output, second_multiple_input_temp);
        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));
        vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));
        
        vector<int>correct_answer;
        for(int i=0;i<(int) second_multiple_input.size();++i)
        {
            correct_answer.push_back(stoi(second_multiple_input[i]));
        }
        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            string edges_row_temp_temp;
            getline(input, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 3; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(input, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));
        
        //vector<int> result = shortestReach(n, edges, s);
//        cout << "Starting node: " << s << endl;
//        for(auto x=edges.begin();x!=edges.end();++x)
//        {
//            cout << " Node: " << (*x)[0] << " Secondary node: " << (*x)[1]
//            << " undirected weight: " << (*x)[3] << endl;
//        }
//        cout << "Total number of nodes: " << n << endl;
//        cout << "Total number of connections: " << m << endl;
        vector<int>result = shortestReach(n,edges,s);
        for (size_t i = 0; i < result.size(); i++) {
//            if(result[i]!=correct_answer[i])
//            {
//                cout << "Failed" << endl;
//                break;
//            }
            cout << result[i] << " ";
        }

        cout << "\n";
    }
    
    
    input.close();
    return 0;
}


string ltrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
