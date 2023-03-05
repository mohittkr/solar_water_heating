#include<bits/stdc++.h>
#include<iostream>

#include "global_variable.h"
using namespace std;


// Module for collector
// Input: T_n
// Output: T_c
double collector_temp(double T_N){

    double T_c = 0.0;
    double q_A =(F_r_t_alpha * I_solar - F_r_U_L * (T_N - T_a));
    T_c = T_N + (A_c * q_A) / (m_dot * Cp);
    return T_c;

}

// Print temperature profile
void print_profile(vector<double> profile, int n){

    for (int i = 0; i < n; i++)
        cout << profile[i] << endl;
}

// compute sum in a vector
double sum_vec(vector<double> vec){

    if (vec.empty()) return 0;
    int len = vec.size();
    double sum = 0.0;
    for (int i = 0; i < len; i++)
        sum = sum + vec[i];

    return sum;
}

//generating a sub vector
vector<double> slicing(vector<double> arr,
                    int X, int Y)
{
 
   vector <double> result;
   for(int i = X; i <= Y; i++)
        result.push_back(arr[i]);
   
   return result;
}
 


// Module for computing the temperature profile in a tank
// Input : Initial temperature profile
// Output: Instantaneous temperature profile
vector<double> temp_profile_storage_tank(vector<double> &init_temp_profile, double time){

    double dt = time/ no_of_time_steps;

    vector<double> temp_profile;
    // Initialize the temp_profile
    for (int i = 0; i< n; i++)
        temp_profile.push_back(init_temp_profile[i]);

    // In temperature for the collector
    double T_in = init_temp_profile[n-1];

    // get the collector temperature
    double T_c = collector_temp(T_in);

    // compute the collector control function
    vector<double> B_i;
    B_i.push_back(1.0);
    for (int i = 1; i < n; i++){
        if (init_temp_profile[i] < T_c && T_c < init_temp_profile[i-1]) 
            B_i.push_back(1.0);
        else  B_i.push_back(0.0);
    }
    
    
    // compute the flow rate for each node
    vector<double> gamma_i;
    for (int i = 0; i < n; i++){
        gamma_i.push_back(m_dot * sum_vec(slicing(B_i, 0, i)));
    }
    
    vector<double> R;
    for (int i = 0; i< n; i++)
        R.push_back(1.0);

    // storing the temperature profile with time
    vector<double> temp_N_0;
    vector<double> temp_N_n_minus_1;
    

    // get profile at time t
    for (int j = 0; j < no_of_time_steps; j++){
        init_temp_profile[0] = T_c;
        temp_profile[0] = T_c;
        for (int i = 1; i < n; i++){
            R[i] = U * A * (T_a - init_temp_profile[i]) + B_i[i] * m_dot * Cp * (T_c -init_temp_profile[i] ) + 
                gamma_i [i]* Cp * (init_temp_profile[i-1] - init_temp_profile[i]);
            temp_profile[i] = init_temp_profile[i] + R[i] * dt / (m_s * Cp);
            //init_temp_profile[i] = temp_profile[i];
        }  

        // re-initialize the temperature profile
        for (int i = 1; i < n; i++)
            init_temp_profile[i] = temp_profile[i];

        T_in = init_temp_profile[n-1];
        T_c = collector_temp(T_in);
        temp_N_0.push_back(temp_profile[0]);
        temp_N_n_minus_1.push_back(temp_profile[n-1]);
        
    }
   
    // get collector and inlet temperature
    cout << T_c << '\t' << T_in << endl;

    // Writing temperature profile for node 0
    
    ofstream myfile;
    myfile.open("temperature_node0.txt");
    for (int i =0; i< no_of_time_steps ;i++){
        myfile << i  << '\t' <<  temp_N_0[i] << endl;
    }
    myfile.close();

    // Writing temperature profile for last node
    ofstream myfile_1;
    myfile_1.open("temperature_node_last.txt");
    for (int i =0; i< no_of_time_steps ;i++){
        myfile_1 << i  << '\t' <<  temp_N_n_minus_1[i] << endl;
    }
    myfile_1.close();
    
 
    return temp_profile;

}



int main(){

    // intitial temperature profile
    vector<double> init_temp_profile;
    for (int i = 0; i < n; i++)
        init_temp_profile.push_back(T_a);

    vector<double> temperature_profile;
    temperature_profile = temp_profile_storage_tank(init_temp_profile, 10.0);

    // Print temperature profile
    print_profile(temperature_profile, n);

    // Write to a file to plot
    ofstream myfile;
    myfile.open("temperature_profile.txt");
    for (int i =0; i< n ;i++){
        myfile << (i+1)  << '\t' << temperature_profile[i] << endl;
    }
    myfile.close();
    

    

    return 0;
}