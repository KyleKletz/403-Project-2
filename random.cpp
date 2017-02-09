#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "random.h"
#include <iostream>
#include <fstream>

void random_seed(long int seed){
	if (seed > 0){
		srand(seed);
	}
	
	else if (seed == 0){
		srand(time(NULL));
	}
	
	else{
		seed == 0;
		random_seed(seed);
	}
}

double random_uniform(){
	long int j = rand();
	random_seed(j);
	double a = (double)rand();
	double b = (double)RAND_MAX;
	double uniform = (a/b);
	return uniform;
}

double random_range(double min, double max){
	long int j = rand();
	random_seed(j);
	double random;
	double minimum = min;
    double maximum = max;

    random = maximum + rand() / (RAND_MAX / (minimum - maximum + 1) + 1);
    return random;
}

double random_normal(double mean, double dev){
	long int j = rand();
	random_seed(j);
	//double min = INT_MIN;
	double two_pi = 2.0 * (3.14159265359);
	double rand_one = 0.0; 
	double rand_two = 0.0;
	double normal = 0.0;
	rand_one = (double)rand() * (1.0 / (double)RAND_MAX);
	rand_two = (double)rand() * (1.0 / (double)RAND_MAX);
	
	normal = sqrt(-2.0 * log(rand_one)) * cos(two_pi * rand_two);
	return normal * dev + mean;	
}

double random_exponential(double mean){
	long int j = rand();
	random_seed(j);
	double a;                  
	double exp;    
	

		a = random_uniform();
	
	
	exp = -mean * log(a);
	return exp;
}

int main(){
	int i = 0;
	std::ofstream outFile; // opens an ofstream for output
	outFile.open("uniform2.txt");
	for (i =0; i < 2000; i++){
		double x = random_uniform();
		outFile << x << std::endl;
		printf("%f\n", x);
	}
	outFile.close();
	outFile.open("normal2.txt");
	int j = 0;
	for (j =0; j < 2000; j++){
		double y = random_normal(5.0,2.0);
		outFile << y << std::endl;
		printf("%f\n", y);
	}
	outFile.close();
	outFile.open("exp2.txt");
	int k = 0;
	for (k =0; k < 1000; k++){
		double z = random_exponential(5.0);
		outFile << z << std::endl;
		printf("%f\n", z);
	}
	outFile.close();
	outFile.open("range2.txt");
	int l = 0;
	for (l =0; l < 2000; l++){
		double w = random_range(1.0,500.0);
		outFile << w << std::endl;
		printf("%f\n", w);
	}
	outFile.close();
}