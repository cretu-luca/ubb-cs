#include <fstream>
using namespace std;
ifstream fin("input3.in");
ofstream fout("input3.out");

int n, x[20], number_of_associative_tables;

bool is_associative(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
            /// this simulates the iteration of a matrix, by calculating the position in a one row array
            /// checks if i * (j * k) = (i * j) * k
            if(x[n * x[n * i + j] + k] != x[n * i + x[n * j + k]])
                return false;
    return true;
}

void generate_table(int k){
    if(k == n * n){ /// the table is complete
        if(is_associative()){
            for(int i = 0; i < k; i++){
                if(i % n == 0)
                    fout << '\n';
                string element = "a" + to_string(x[i] + 1);
                fout << element << " ";
            }
            fout << '\n';

            number_of_associative_tables++;
        }
    }
    else { /// more elements to add
        /// generate the table (n * n cartesian product) using backtracking - the algorithm for permutations with repetitions
        for(int i = 0; i < n; i++){
            x[k] = i;
            generate_table(k + 1);
        }
    }
}

int main(){
    fin >> n;
    fout << "n is " << n << '\n';
    fout << "The operation tables of the associative operations on the given set are given by the matrices: \n";
    generate_table(0);
    fout << "\nThe number of associative operations on the given set is " << number_of_associative_tables;
}


