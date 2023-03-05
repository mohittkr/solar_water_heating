int n = 10; // Number of layers in a tank
int no_of_time_steps = 100;
double I_solar = 93.75; // Solar radiation rate: W/m^2
double F_r_t_alpha = 0.84; 
double F_r_U_L  = 1.89; // W / s m^2 C
double m_dot = 0.1; // Mass flow rate: Kg / s
double T_a = 25.0; // Ambient temperature
double Cp = 1.1630555555556 ; // Specific heat coefficient og water: W / Kg / C
//double U = 0.694;
double U = 0.0;
double H = 1; // Height of tank  = 1m
double d = 0.5; // Diameter of tank = 0.5m
double A = 2 * 3.14 * (d/2) * (H /n); // Surface area of water
double A_c = 0.0419354; // in m^2 Typical dimension: 65 inches by 39 inches
double m_s = 0.997 * (3.14 * (d/2) * (d/2)* (H * 1./n)); // mass of water in a layer of tank

