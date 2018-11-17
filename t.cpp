#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector< vector<int> > test = {
        {7,2,6,  3,5,9,  4,1,8},
        {4,5,8,  1,6,7,  2,3,9},
        {9,1,3,  8,2,4,  7,6,5},

        {1,6,2,  9,7,5,  3,8,4},
        {3,9,4,  2,8,6,  1,5,7},
        {8,7,5,  4,1,3,  9,2,6},

        {5,3,7,  6,4,1,  8,9,2},
        {6,8,9,  7,3,2,  5,4,1},
        {2,4,1,  5,9,8,  6,7,3} };

    int count = 0; int i = 0; int j = 0;
    while (j != 9 && i != 9)
    {
        cout << test[i][j] << ", ";
        if ( (j+1) % 3 == 0 )
        {
            if ( (j+1) % 3 == 0 )
            {
                if (count == 0) {cout << "TOP-LEFT";} if (count == 3) {cout << "TOP-MIDDLE";} if (count == 6) {cout << "TOP-RIGHT";}
                if (count == 9) {cout << "MIDDLE-LEFT";} if (count == 12) {cout << "MIDDLE-MIDDLE";} if (count == 15) {cout << "MIDDLE-RIGHT";}
                if (count == 18) {cout << "BOTTOM-LEFT";} if (count == 21) {cout << "BOTTOM-MIDDLE";} if (count == 24) {cout << "BOTTOM-RIGHT";}

                count ++;
                i++;

                if (count <= 2) {j = -1;}
                if (count >= 3 && count <= 5) {j = 2;}
                if (count >= 6 && count <= 8) {j = 5;}                
                if (count % 3 == 0 && count < 9) {i = 0; cout << endl;}
                
                if (count == 9 || count == 18 || count == 27) {cout << endl;} // Prints new lines only
            
                if (count >= 9 && count <= 11) {j = -1;}
                if (count >= 12 && count <= 14) {j = 2;}
                if (count >= 15 && count <= 17) {j = 5;}
                if (count % 3 == 0 && count > 9 && count < 18) {i = 3; cout << endl;}

                if (count >= 18 && count <= 20) {j = -1;}
                if (count >= 21 && count <= 23) {j = 2;}
                if (count >= 24 && count <= 26) {j = 5;}
                if (count % 3 == 0 && count > 18 && count < 30) {i = 6; cout << endl;}
                cout << endl;
            }
        }
        j++;
    }
    return 0;
}

