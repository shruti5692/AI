#include <iostream>
using namespace std;

void towerOfHanoi(int n, char s_rod, char d_rod, char a_rod) {
    if (n == 1) {
        cout << "Move disk 1 from rod " << s_rod << " to rod " << d_rod << endl;
        return;
    }
    towerOfHanoi(n - 1, s_rod, a_rod, d_rod);
    cout << "Move disk " << n << " from rod " << s_rod << " to rod " << d_rod << endl;
    towerOfHanoi(n - 1, a_rod, d_rod, s_rod);
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
