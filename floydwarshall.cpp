#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#define INF 9999999


void printSolution (int V, int **D){

        for (int i = 0; i < V; i++){
                for (int j = 0; j < V; j++){
                        if (D[i][j] == INF){
                                cout << "INF ";
                        } else {
                                cout<<D[i][j]<< " ";
                        }
                }
                cout<<endl;
        }
}

void FloydWarshall( int V, int **G) {

        //create distances matrix
        int **D;
        D = new int*[V];
        for(int i=0;i<V;i++){
                D[i]=new int[V];
        }

        //initialize distances' matrix
        for (int i = 0; i < V; i++){
                for(int j = 0; j < V; j++){
                        D[i][j] = G[i][j];
                }
        }

        for (int k = 0; k < V ; k++){
                for (int i = 0; i < V; i++){
                        for(int j = 0; j < V; j++){
                                if (D[i][k] + D[k][j] < D[i][j]) {
                                        D[i][j] = D[i][k] + D[k][j];
                                }
                        }
                }
        }

        printSolution(V, D);

}


int main(int argc, char *argv[]){

        //read the file with the graph dimensions and the arguments for the adjacency matrix
        char *s = argv[1];
        std::ifstream file(s);

        //variables to read each variable
        int V;
        string n;               //get the number of vertices
        string word;        //get the values of the adjacency matrix
        getline(file, n);
        V = std::stoi(n);         //convert string to int

        cout << V << " vértices"<<endl;

        int **G;
        G = new int*[V];
        for(int i=0;i<V;i++){
                G[i]=new int[V];
        }


        int i = 0, j = 0;

        while( file >> word){
                if (word == "INF"){
                        G[i][j] = INF;
                } else {
                        G[i][j] = std::stoi(word);
                }

                //cout<<i<< ","<< j <<endl;

                if (j < V-1){
                        j++;
                } else {
                        j = 0;
                        i++;
                }
        }

        cout<< "--------------------------GRAFO--------------------"<<endl;

        for (i = 0; i < V; i++){
                for (j = 0; j < V; j++){
                        if (G[i][j] == INF){
                                cout<<"INF ";
                        } else {
                                cout<<G[i][j]<< " ";
                        }
                }
                cout<<endl;
        }


        cout<< "--------------------------SOLUCAO-----------------"<<endl;
        FloydWarshall(V,G);

        return 0;

}