#include <iostream>
#include <cmath>
#include <iomanip>
#include <time.h>

#define M_PI    3.14159265358979323846 //deklrasi nilai phi

using namespace std;

//fungsi yang digunakan untuk menghitung nilai
double hitung_Nilai(double x1, double x2){
    return -abs(sin(x1) * cos(x2) * exp(abs(1 - (sqrt(pow(x1,2) + pow(x2,2))) / M_PI)));
}

int main()
{
    srand(time(NULL));
    double T = 1997; //initial temperatur awal untuk annealing schedule
    double T_akhir = 0.00023; //temperatur akhir
    double delta_T = 0.008; // nilai pengurangan temperatur

    double x1 = (rand() / (double)RAND_MAX * 20) -10; //merandom x1 awal
    double x2 = (rand() / (double)RAND_MAX * 20) -10; //merandom x2 awal

    double current_state = hitung_Nilai(x1,x2); //nilai awal diinisiasi dengan nilai dari fungsi hitung_Nilai
    double best = current_state; //best so far diinisialisasi dengan nilai_current

    double deltaE;

    //perulanangan temperatur awal hingga sampai temperatur akhir
    while (T >= T_akhir){
        x1 = (rand() / (double)RAND_MAX * 20) -10; //membuat x1 baru
        x2 = (rand() / (double)RAND_MAX * 20) -10; //membuat x2 baru
        double new_state = hitung_Nilai(x1, x2); //nilai_baru diinisialisasi dengan nila
        deltaE = new_state - current_state; //menghitung cost dari nilai_baru dengan nilai_current
        //jika cost < 0 nilai_baru menjadi nilai_current dan best so far
        if (deltaE < 0){
            current_state = new_state; //terima new state sebagai current state
            best = new_state; //new state menjadi best so fat
        }
        //jika cost >= 0 nilai
        else if (deltaE >= 0){
            double P = exp(-deltaE/T); //rumus menghitung probability
            double Random = (rand()); //merandom nilai antara 1 dan 0
            if (P >= Random){ //jika nilai random <= probability nilai baru menjadi nilai current
                current_state = new_state; //new state tetap menjadi current state, bsf tetap di state sebelumnya
            }
        }
        T = T- delta_T; //suhu awal dikurangi dengan nilai pegurang
    }

    cout << "Nilai x1 = " << x1 << endl;
    cout << "Nilai x2 = " << x2 << endl;
    cout << "Nilai DeltaE = " << deltaE << endl;
    std::cout <<"Best So Far = " << std::setprecision(12) << best << endl;

    return 0;
}
