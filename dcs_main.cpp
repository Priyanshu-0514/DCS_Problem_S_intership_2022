#include <bits/stdc++.h>
using namespace std;
#define map unordered_map<int,int>

void printGraph(vector<vector<int>>& graph,map&revmp){
    cout<<"\nPrint Graph\n";
    int ptr = 0;
    for(auto x : graph){
        cout<<revmp[ptr]<<" :: ";
        for(auto y : x){
            cout<<revmp[y]<<" ";
        }
        cout<<"\n";
        ptr++;
    }
}

void function_one(vector<vector<int>> &graph, vector<int> &degree, int n, int m, float a, float b,map&revmp)
{
    vector<int> newdeg = degree;

    // unordered_map<int,int>m;
    for (int i = 0; i < n; i++)
    {
        // sort(graph[i].begin(),graph[i].end());
        float ratio = (newdeg[i] * 1.0) / degree[i];
        unordered_map<int, int> m;
        while (ratio > 0 && (ratio < a or ratio > b))
        {
            int maxxi = INT_MIN, val = -1;
            for (auto &v : graph[i])
            {
                float deg = (1.0 * newdeg[v]) / degree[v];
                if ((deg < a || deg > b) && maxxi > newdeg[v])
                {
                    maxxi = newdeg[v];
                    val = v;
                    if (m[val] != 0)
                        continue;
                }
            }

            m[val]++;

            newdeg[i]--;
            newdeg[val]--;

            ratio = (newdeg[i] * 1.0) / degree[i];
        }
    }

    // Analysing New Graph and Old Graph.

    for (int i = 0; i < n; i++)
    {
        cout << "\nFor Vertex " << revmp[i] << " Old Degree : " << degree[i] << " New Degree : " << newdeg[i] << "\n";
        cout << "Fraction of vertex retained : " << (float)newdeg[i] / degree[i] << "\n";
    }
}

void function_two(vector<vector<int>> &edges, vector<int> &degree, int n, int m, float a, float b,map&revmp)
{
    vector<int> newdeg = degree;
    int u, v;
    int numOfNodes = revmp.size();
    int numOfEdgesRemoved = 0;
    float ratio1, ratio2;

    for (int i = 0; i < m-1; i++)
    {
        // Particular Order
        // we have to send edges randomly.
        u = edges[i][0];
        v = edges[i][1];

        ratio1 = (float)newdeg[u] / degree[u];
        ratio2 = (float)newdeg[v] / degree[v];
        bool flag = true;

        if ((ratio1 >= a && ratio1 <= b) && (ratio2 >= a && ratio2 <= b))
        {
            continue;
        }

        if (ratio1 > a)
        {
            if (ratio2 > a)
            {
                newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and
                newdeg[v]--; // ratio2 > Beta.
                numOfEdgesRemoved++;
            }
            else
            {
                continue;
            }
        }
        else if (ratio1 > a)
        { // Ratio1 < Betta and maybe > alpha
            if (ratio2 > a)
            {
                newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and
                newdeg[v]--; // ratio2 > Beta.
                numOfEdgesRemoved++;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        ratio1 = (float)newdeg[u] / degree[u];
        ratio2 = (float)newdeg[v] / degree[v];
    }

    // Print the Result
    cout<<"\nDebug6.(b).."<<" $ ";
    // Create and open a text file
    ofstream MyFile("oregon1_010526(output_f2).txt");

    // Print the Result
    int fault_node_at_maxi = 0;
    int fault_node_at_mini = 0;
    float maxi_violation = b;
    float mini_violation = a;
    float total_violation_upper = 0.0;
    float total_violation_lower = 0.0;

    for (int i = 0; i < n; i++)
    {
        if(degree[i] != 0){
            // cout<<"Debug 8$ ";
            float ratio = (float)newdeg[i] / degree[i];
            MyFile << "\nFor Vertex " << revmp[i] << " Old Degree : " << degree[i] << " New Degree : " << newdeg[i] << "\n";
            MyFile << "Fraction of vertex retained : " << ratio << "\n";

            if(ratio > 0.7){
                fault_node_at_maxi++;
                if(ratio > maxi_violation)  maxi_violation = ratio;
                total_violation_upper += (ratio - 0.7);
            }

            if(ratio < 0.5){
                fault_node_at_mini++;
                if(ratio < mini_violation)  mini_violation = ratio;
                total_violation_lower += (0.5 - ratio);
            }
        
        }
        // cout<<"Here 8$ ";
    }

    float compression = (float)(m-numOfEdgesRemoved)/m;
    float density = (float)(m-numOfEdgesRemoved)/numOfNodes;
    float avg_violation_upper = total_violation_upper/m;
    float avg_violation_lower = total_violation_lower/m;
    int fault_node = fault_node_at_mini + fault_node_at_maxi;

    MyFile<<"\n\nOBSERVATIONS :::: ";

    MyFile<<"\n\nCompression in Graph : "<<compression;
    MyFile<<"\nDensity of Graph : "<<density;

    MyFile<<"\n\nNumber of Vertex violating on Upper Limit : "<<fault_node_at_maxi;
    MyFile<<"\nMaximum Violation on Upper Limit : "<<maxi_violation;
    MyFile<<"\nAverage Violation on Upper Limit : "<<avg_violation_upper;

    MyFile<<"\n\n Numberof Vertex violating on Lower Limit : "<<fault_node_at_mini;
    MyFile<<"\nMinimum Violation of Lower Limit : "<<mini_violation;
    MyFile<<"\nAverage Violation Lower Limit : "<<avg_violation_lower;

    MyFile.close();
    
}

void function_three(vector<vector<int>> &edges, vector<int> &degree, int n, int m, float a, float b,map&revmp)
{
    vector<int> newdeg = degree;
    int u, v;
    float ratio1, ratio2;
    int numOfNodes = revmp.size();
    cout<<"Number of Nodes in Graph: "<<numOfNodes<<"\n";
    int numOfEdgesRemoved = 0;
    cout<<"Debug7(a).";

    // Randomised the edges using Randomised sort function
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(edges.begin(), edges.end(), std::default_random_engine(seed));

    for (int i = 0; i < m-1; i++)
    {
        // Particular Order
        // we have to send edges randomly.
        u = edges[i][0];
        v = edges[i][1];
        // cout<<"\n"<<revmp[u]<<" - "<<revmp[v]<<"# ";1

        ratio1 = (float)newdeg[u] / degree[u];
        ratio2 = (float)newdeg[v] / degree[v];
        bool flag = true;

        // cout<<"#"<<i<<" :: "<<u<<"-"<<v<<" "<<ratio1<<" , "<<ratio2<<"\n";

        if ((ratio1 >= a && ratio1 <= b) && (ratio2 >= a && ratio2 <= b))
        {
            // cout<<"DEBUG 101";
            continue;
        }

        if (ratio1 > a)
        {
            if (ratio2 > a)
            {
                // To Strictly Follow the Lower Bound.
                float r1 = ((float)newdeg[u] - 1) / degree[u];
                float r2 = ((float)newdeg[v] - 1) / degree[v];
                if (r1 >= a && r2 >= a)
                {
                    newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and
                    newdeg[v]--; // ratio2 > Beta.
                    numOfEdgesRemoved++;
                }
            }
            else
            {
                continue;
            }
        }
        else if (ratio1 > a)
        { // Ratio1 < Betta and maybe > alpha
            if (ratio2 > a)
            {

                float r1 = ((float)newdeg[u] - 1) / degree[u];
                float r2 = ((float)newdeg[v] - 1) / degree[v];
                if (r1 >= a && r2 >= a)
                {
                    newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and
                    newdeg[v]--; // ratio2 > Beta.
                    numOfEdgesRemoved++;
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        // ratio1 = (float)newdeg[u]/degree[u];
        // ratio2 = (float)newdeg[v]/degree[v];
        // cout<<ratio1<<" , "<<ratio2<<"\n\n";
    }

    cout<<"\nDebug7.(b).."<<" $ ";
    // Create and open a text file
    ofstream MyFile("oregon1_010526(output_f3).txt");

    // Print the Result
    int fault_node_at_maxi = 0;
    int fault_node_at_mini = 0;
    float maxi_violation = b;
    float mini_violation = a;
    float total_violation_upper = 0.0;
    float total_violation_lower = 0.0;

    for (int i = 0; i < n; i++)
    {
        if(degree[i]!= 0){
            // cout<<"Debug 8$ ";
            float ratio = (float)newdeg[i] / degree[i];
            MyFile << "\nFor Vertex " << revmp[i] << " Old Degree : " << degree[i] << " New Degree : " << newdeg[i] << "\n";
            MyFile << "Fraction of vertex retained : " << ratio << "\n";

            if(ratio > 0.7){
                fault_node_at_maxi++;
                if(ratio > maxi_violation)  maxi_violation = ratio;
                total_violation_upper += (ratio - 0.7);
            }

            if(ratio < 0.5){
                fault_node_at_mini++;
                if(ratio < mini_violation)  mini_violation = ratio;
                total_violation_lower += (0.5 - ratio);
            }
        
        }
        // cout<<"Here 8$ ";
    }

    float compression = (float)(m-numOfEdgesRemoved)/m;
    float density = (float)(m-numOfEdgesRemoved)/numOfNodes;
    float avg_violation_upper = total_violation_upper/m;
    float avg_violation_lower = total_violation_lower/m;
    int fault_node = fault_node_at_mini + fault_node_at_maxi;

    MyFile<<"\n\nOBSERVATIONS :::: ";

    MyFile<<"\n\nCompression in Graph : "<<compression;
    MyFile<<"\nDensity of Graph : "<<density;

    MyFile<<"\n\nNumber of Vertex violating on Upper Limit : "<<fault_node_at_maxi;
    MyFile<<"\nMaximum Violation on Upper Limit : "<<maxi_violation;
    MyFile<<"\nAverage Violation on Upper Limit : "<<avg_violation_upper;

    MyFile<<"\n\n Numberof Vertex violating on Lower Limit : "<<fault_node_at_mini;
    MyFile<<"\nMinimum Violation of Lower Limit : "<<mini_violation;
    MyFile<<"\nAverage Violation Lower Limit : "<<avg_violation_lower;

    MyFile.close();
}

int main()
{
    int n, m;
    vector<vector<int>> graph;
    vector<int> degree;

    vector<vector<int>> edges;
    // cin >> n >> m;

    // Undirected Unweighted Graph
    // DCS :: Degree Constrained Subgraph Problem...

    string myText;
    ifstream MyReadFile("oregon1_010526(pure).txt");

    // Use a while loop together with the getline() function to read the file line by line
    int cnt = 0;
    int maxi = INT_MIN;
    cout<<"Debug1 "<<"$\n";
//for mapping orginal vertex -> new compressed vertex according to array indexing (from 0 )
    unordered_map<int,int>map1;
    int cntt=0;
    while (getline(MyReadFile, myText))
    {
        // Output the text from the file
        // cout<<"\n"<<cnt<<" : "<<myText;2

        int size = myText.size();
        string num = "";
        int temp = 0;
        while (temp < size)
        {
            if (myText[temp] != '\t')
            {
                num += myText[temp];
                temp++;
            }
            else
            {
                temp++;
                break;
            }
        }
        
        int num1 = stoi(num);
        num = "";
        while(temp < size){
            num += myText[temp];
            temp++;
        }
        int num2 = stoi(num);
        // cout<<" debug3 ";

        if(cnt == 0){
            n = num1;
            m = num2;
            graph.resize(n);
            degree.resize(n,0);
            cout<<"Code is Running  ";
            
        }else{

         int u, v;
         u = num1;
         v = num2;
         if(map1.find(u)==map1.end()){
            map1[u]=cntt++;
           
        }
        if(map1.find(v)==map1.end()){
            map1[v]=cntt++;
           
        }
        maxi = max({u,v,maxi});
        u=map1[u];
        v=map1[v];
        edges.push_back({u, v});
        // graph[u].push_back(v);
        // graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
        }

        cnt++;
        // cout<<" $ ";3
    }
     //for reverse mapping  compressed vertex -> orginal vertex 
     unordered_map<int,int>revmp;
     for(auto &p:map1){
        revmp[p.second]=p.first;
    }

    MyReadFile.close();
    cout<<"\nMAXI : "<<maxi<<"#\n";

    
    cout<<" map size "<<map1.size()<<" revmap size "<<revmp.size()<<endl;
    cout<<" graph size "<<map1.size()<<" edge size "<<revmp.size()<<endl;
    cout << "\n"
         << n << " vertex && " << m << " edges are there\n";
    // printGraph(graph);

    // Now DCS Problem let a = 50% bad b = 70% so we have to reduce the degree of each verted
    // between 50% to 70%.

    float a = 0.5, b = 0.7; // a = alpha , b = beeta

    // function_one(graph,degree,n,m,a,b);

    // ********* IMPLEMENTING THE SECOND FUNCTION ********** Following the UPPER BOUND STRICTLY

    function_two(edges,degree,n,m,a,b,revmp);

    // ********* IMPLEMENTING THE THIRD FUNCTION ********** Following the LOWER BOUND STRICTLY

    cout<<"Debug7 $\n";
    function_three(edges,degree,n,m,a,b,revmp);

    return 0;
}