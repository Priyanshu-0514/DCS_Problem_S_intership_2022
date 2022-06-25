#include<bits/stdc++.h>
using namespace std;

void printGraph(vector<vector<int>>& graph){
    cout<<"\nPrint Graph\n";
    int ptr = 0;
    for(auto x : graph){
        cout<<ptr<<" :: ";
        for(auto y : x){
            cout<<y<<" ";
        }
        cout<<"\n";
        ptr++;
    }
}

void function_one(vector<vector<int>>& graph,vector<int>& degree,int n,int m,float a,float b){
    vector<int> newdeg = degree;

    // unordered_map<int,int>m;
    for (int i = 0; i < n; i++)
    {
        // sort(graph[i].begin(),graph[i].end());
        float ratio = (newdeg[i] * 1.0) / degree[i];
            unordered_map<int,int>m;
        while (ratio > 0 && (ratio < a or ratio > b))
        {
            int maxxi = INT_MIN, val = -1;
            for (auto &v:graph[i])
            {
                float deg = (1.0*newdeg[v])/degree[v];
                if ((deg < a || deg > b) && maxxi > newdeg[v] )
                {
                    maxxi = newdeg[v];
                    val = v;
                    if(m[val]!=0) continue;
                }
            }
            
                m[val]++;

                newdeg[i]--;
                newdeg[val]--;
        
            ratio = (newdeg[i] * 1.0) / degree[i];
        }
    }

    // Analysing New Graph and Old Graph.

    for(int i = 0; i<n ; i++){
        cout<<"\nFor Vertex "<<i<<" Old Degree : "<<degree[i]<<" New Degree : "<<newdeg[i]<<"\n";
        cout<<"Fraction of vertex retained : "<<(float)newdeg[i]/degree[i]<<"\n";
    }
}

void function_two(vector<vector<int>>& edges,vector<int>& degree,int n,int m,float a,float b){
    vector<int> newdeg = degree;
    int u,v;
    float ratio1,ratio2;
    
    for(int i = 0; i< m ; i++){
        // Particular Order 
        // we have to send edges randomly.
        u = edges[i][0];
        v = edges[i][1];
        
        ratio1 = (float)newdeg[u]/degree[u];
        ratio2 = (float)newdeg[v]/degree[v];
        bool flag = true;

        cout<<"#"<<i<<" :: "<<u<<"-"<<v<<" "<<ratio1<<" , "<<ratio2<<"\n";

        if((ratio1 >= a && ratio1 <= b) && (ratio2 >= a && ratio2 <= b)){
            cout<<"DEBUG 101";
            continue;
        }

        if(ratio1 > a){
                if(ratio2 > a){
                    newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and 
                    newdeg[v]--; // ratio2 > Beta.
                }else{
                    continue;
                }
        }else if(ratio1 > a){              // Ratio1 < Betta and maybe > alpha
                if(ratio2 > a){
                    newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and 
                    newdeg[v]--; // ratio2 > Beta.
                }else{
                    continue;
                }
        }else{
            continue;
        }

        ratio1 = (float)newdeg[u]/degree[u];
        ratio2 = (float)newdeg[v]/degree[v];
        cout<<ratio1<<" , "<<ratio2<<"\n\n";
        
    }

    // Print the Result
    for(int i = 0; i<n ; i++){
        cout<<"\nFor Vertex "<<i<<" Old Degree : "<<degree[i]<<" New Degree : "<<newdeg[i]<<"\n";
        cout<<"Fraction of vertex retained : "<<(float)newdeg[i]/degree[i]<<"\n";
    }
}

void function_three(vector<vector<int>>& edges,vector<int>& degree,int n,int m,float a,float b){
    vector<int> newdeg = degree;
    int u,v;
    float ratio1,ratio2;
    
    for(int i = 0; i< m ; i++){
        // Particular Order 
        // we have to send edges randomly.
        u = edges[i][0];
        v = edges[i][1];
        
        ratio1 = (float)newdeg[u]/degree[u];
        ratio2 = (float)newdeg[v]/degree[v];
        bool flag = true;

        cout<<"#"<<i<<" :: "<<u<<"-"<<v<<" "<<ratio1<<" , "<<ratio2<<"\n";

        if((ratio1 >= a && ratio1 <= b) && (ratio2 >= a && ratio2 <= b)){
            // cout<<"DEBUG 101";
            continue;
        }

        if(ratio1 > a){
                if(ratio2 > a){
                    // To Strictly Follow the Lower Bound.
                    float r1 = ((float)newdeg[u] - 1)/degree[u];
                    float r2 = ((float)newdeg[v] - 1)/degree[v];
                    if(r1 >= a && r2 >= a){
                        newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and 
                        newdeg[v]--; // ratio2 > Beta.
                    }
                    
                }else{
                    continue;
                }
        }else if(ratio1 > a){              // Ratio1 < Betta and maybe > alpha
                if(ratio2 > a){
                    
                     float r1 = ((float)newdeg[u] - 1)/degree[u];
                    float r2 = ((float)newdeg[v] - 1)/degree[v];
                    if(r1 >= a && r2 >= a){
                        newdeg[u]--; // Edges U-V is removed when ratio1 > aplha and 
                        newdeg[v]--; // ratio2 > Beta.
                    }
                }else{
                    continue;
                }
        }else{
            continue;
        }

        // ratio1 = (float)newdeg[u]/degree[u];
        // ratio2 = (float)newdeg[v]/degree[v];
        // cout<<ratio1<<" , "<<ratio2<<"\n\n";
        
    }

    // Print the Result
    for(int i = 0; i<n ; i++){
        cout<<"\nFor Vertex "<<i<<" Old Degree : "<<degree[i]<<" New Degree : "<<newdeg[i]<<"\n";
        cout<<"Fraction of vertex retained : "<<(float)newdeg[i]/degree[i]<<"\n";
    }
}

int main(){
    int n,m;
    cin>>n>>m;

    // Undirected Unweighted Graph
    // DCS :: Degree Constrained Subgraph Problem...
    
    vector<vector<int>>    graph(n);
    vector<int> degree(n,0);

    vector<vector<int>> edges;
    
    for(int i = 0; i<m ; i++ ){
        int u,v;
        cin>>u>>v;
        edges.push_back({u,v});
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    cout<<"\n"<<n<<" vertex && "<<m<<" edges are there\n";
    printGraph(graph);

    // Now DCS Problem let a = 50% bad b = 70% so we have to reduce the degree of each verted
    // between 50% to 70%.

    float a = 0.5,b = 0.7; // a = alpha , b = beeta
    
    // function_one(graph,degree,n,m,a,b);

    // ********* IMPLEMENTING THE SECOND FUNCTION ********** Following the UPPER BOUND STRICTLY

    // function_two(edges,degree,n,m,a,b);

    // ********* IMPLEMENTING THE THIRD FUNCTION ********** Following the LOWER BOUND STRICTLY

    function_three(edges,degree,n,m,a,b);


   return 0;
}