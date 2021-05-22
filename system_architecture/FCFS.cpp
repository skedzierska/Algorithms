#include <iostream>
#include <cstdlib>

using namespace std;

// funkcja znajdujca czas oczekiwania na rozpoczcie procesu
void waiting_time(int processes[], int number_of_processes, int bt[], int wt[]) {
    wt[0] = 0; // czas oczekiwania dla pierwszego procesu jest rwny 0

    // do czasu wykonania poprzedniego procesu dodajemy czas oczekiwania poprzedniego procesu
    for (int i=1; i<number_of_processes; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
}

// funkcja znajdujca czas zakoczenia procesu
void turnaround_time(int processes[], int number_of_processes, int bt[], int wt[], int tat[]){
    // do czasu wykonania dodajemy czas oczekiwania
    for (int i=0; i<number_of_processes; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// funkcja znajdujca redni czas oczekiwania oraz zakoczenia procesu
void fcfs_algorithm(int processes[], int number_of_processes, int bt[]) {
    int wt[number_of_processes];
    int tat[number_of_processes];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // wywoujemy funkcj znajdujc czas oczekiwania dla wszystkich procesw
    waiting_time(processes, number_of_processes, bt, wt);

    // wywoujemy funkcj zajdujc czas zakoczenia dla wszystkich procesw
    turnaround_time(processes, number_of_processes, bt, wt, tat);


    cout << "Process: \t"<< "Burst time: \t" << "Waiting time: \t" << "Turnaround time: " << endl;

    // obliczamy redni czas oczekiwania i zakoczonia procesu
    for (int  i=0; i<number_of_processes; i++){
        total_waiting_time = total_waiting_time + wt[i];
        total_turnaround_time = total_turnaround_time + tat[i];
    }

    double average_wt = total_waiting_time/number_of_processes;
    double average_tat = total_turnaround_time/number_of_processes;

    // wywietlamy informacje o kadym procesie
    for (int i=0; i< number_of_processes; i++) {
        cout << "P" << processes[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] <<endl;
    }

    cout << endl;
    cout << "Average waiting time: " << average_wt << endl;
    cout << "Average turnaround time: " << average_tat << endl;
}

int main()
{
    int number_of_processes = 30;
    // int N = 20;
    // int N = 40;
    int N = 60;
    // int N = 80;
    // int N = 100;

    int processes[number_of_processes];
    int burst_time[number_of_processes];

    for (int i=0; i<number_of_processes; i++) {
        // id procesu
        processes[i] = i+1;

        // losowa dugo czasu wykonania (liczba z zakresu 1-N)
        int a = rand() % N + 1;
        burst_time[i] = a;
    }

    fcfs_algorithm(processes, number_of_processes, burst_time);
    return 0;
}
