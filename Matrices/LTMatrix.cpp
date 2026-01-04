#include <iostream>
using namespace std;
 
class LTMatrix{

private:
    int n;
    int* A;

public:
    LTMatrix(int n){ // constructor
        A = nullptr;
        this->n = n;
        A = new int [n * (n + 1)/2];
    }

    ~LTMatrix(){ // destructor
         delete[] A;
    }
    
    // ============================================================================
    // CORE OPERATIONS row major ->  ((i * (i - 1))/2) + j - 1
    // ============================================================================    
    void setRowMajor(int i, int j, int x);
    int getRowMajor(int i, int j);

    // ============================================================================
    // CORE OPERATIONS column major -> (n * (j-1) - (((j-2) * (j-1))/2)) + (i-j)
    // ============================================================================
    void setColMajor(int i, int j, int x);
    int getColMajor(int i, int j);

    int getN(){ 
        return n; 
    }

    void setN(int n){
        this->n = n;
    }

    void Display(bool row=true);
};
 
void LTMatrix::setRowMajor(int i, int j, int x) {
    if (i >= j){
        int index = ((i * (i - 1))/2) + j - 1; // row major formula
        A[index] = x;
    }
}
 
void LTMatrix::setColMajor(int i, int j, int x) {
    if (i >= j){
        int index = (n * (j-1) - (((j-2) * (j-1))/2)) + (i-j); // column major formula
        A[index] = x;
    }
}
 
int LTMatrix::getRowMajor(int i, int j) {
    if (i >= j){
        int index = ((i * (i - 1))/2) + j - 1; // row major formula
        return A[index];
    } else {
        return 0;
    }
}
 
int LTMatrix::getColMajor(int i, int j) {
    if (i >= j){
        int index = (n * (j-1) - (((j-2) * (j-1))/2)) + (i-j); // column major formula
        return A[index];
    } else {
        return 0;
    }
}
 
void LTMatrix::Display(bool row) {
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if (i >= j){
                if (row){
                    cout << getRowMajor(i, j) << " ";
                } else {
                    cout << getColMajor(i, j) << " ";
                }
            } else {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }
}

void LTMatrix::setN(int n){
        this->n = n;
    }
 
int main() {
 
    LTMatrix rm(4);
    rm.setRowMajor(1, 1, 1);
    rm.setRowMajor(2, 1, 2);
    rm.setRowMajor(2, 2, 3);
    rm.setRowMajor(3, 1, 4);
    rm.setRowMajor(3, 2, 5);
    rm.setRowMajor(3, 3, 6);
    rm.setRowMajor(4, 1, 7);
    rm.setRowMajor(4, 2, 8);
    rm.setRowMajor(4, 3, 9);
    rm.setRowMajor(4, 4, 10);
 
    rm.Display();
    cout << endl;
 
    LTMatrix cm(4);
    cm.setColMajor(1, 1, 1);
    cm.setColMajor(2, 1, 2);
    cm.setColMajor(2, 2, 3);
    cm.setColMajor(3, 1, 4);
    cm.setColMajor(3, 2, 5);
    cm.setColMajor(3, 3, 6);
    cm.setColMajor(4, 1, 7);
    cm.setColMajor(4, 2, 8);
    cm.setColMajor(4, 3, 9);
    cm.setColMajor(4, 4, 10);
 
    cm.Display(false);
 
    return 0;
}