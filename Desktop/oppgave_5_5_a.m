%Relevant variables
w_0 = 0.7823; %Found in 5.2.c
lambda = 0.085; %Found in 5.2.d
sigma = sqrt(0.0015); %Found in 5.2.d. sigma^2 is maxvalue of estimated PSD
K = 0.15613; %Found in 5.1.b
T = 72.4659; %Found in 5.1.b
K_w = 2*lambda*w_0*sigma; %Defined in 5.2.d
f = 10; %Sample frequency is 10 Hz. Period is 1/f

%Matrices A, B, E and C found in 5.4:
A = [0,1,0,0,0;
    -w_0^2, -2*lambda*w_0, 0, 0, 0;
    0,0,0,1,0;
    0,0,0,-1/T, -K/T;
    0,0,0,0,0];

B = [0;
    0;
    0;
    K/T;
    0];

E = [0,0;
    K_w,0;
    0,0;
    0,0;
    0,1];

C = [0,1,1,0,0];

%Discretizing the system
[Ad,Bd]= c2d(A,B,1/f);
Cd = C;
[Ad,Ed] = c2d(A,E,1/f);

%Find variance of the measurement noise
var_MN = var(ship*pi/180);
Rd = var_MN*f; %Discretized R matrix (1/f = T)