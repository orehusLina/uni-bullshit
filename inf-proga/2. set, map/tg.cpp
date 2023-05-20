#include <iostream>
using namespace std;
int main() {
    int objemTruma = 30;
    float vBig = 9*0.5, vSred = 6*0.5, vSmall = 0.5*0.5*0.5;
    float sideOfBottle = 0.075;
    int kolvoBig = int(3.0/sideOfBottle) * int (3.0/sideOfBottle);
    int kolvoSred = int(2.0/sideOfBottle) * int (3.0/sideOfBottle);
    int kolvoSmall = int(0.5/sideOfBottle) * int (0.5/sideOfBottle);
    int maximAmountBottle = 0;
    float CASH = 955*2 - 589;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 4; ++k) {
                if ((vBig*k + vSred*j + vSmall * i) <= objemTruma) {
                    if ((k*kolvoBig + j * kolvoSred + i*kolvoSmall) > maximAmountBottle) {
                        maximAmountBottle = k*kolvoBig + j * kolvoSred + i*kolvoSmall;
                    }
                }
            }
        }
    }
    cout << maximAmountBottle;
}