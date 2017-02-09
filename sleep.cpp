#include <math.h>
#include <limits.h>
#include "sleep.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

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

double random_exponential(double mean){
	long int j = rand();
	random_seed(j);
	double a;                  
	double exp;    
	

		a = random_uniform();
	
	
	exp = -mean * log(a);
	return exp;
}

double takeInput(){
	int iterations;
	double mean;
	std::cout << "Input the mean" << std::endl;
	std::cin >> mean;
	std::cout << "Input the number of iterations" << std::endl;
	std::cin >> iterations;
	
	psleep(mean, iterations);
}

double psleep(double mean, int iterations){
	for (int i = 0; i < iterations; i++){
		double asleep = random_exponential(mean);
		double realSleep, nsleep;
		int wholeSeconds;
		//ensures that no division by 0 happens
		if (asleep < 1.0){
			wholeSeconds = 0;
			nsleep = asleep;
		}
		
		else{
			wholeSeconds = (int) asleep; //finds the whole seconds needed to sleep
			nsleep = fmod (asleep,wholeSeconds); //finds the remaining fraction of a second
		}
	
		realSleep = (nsleep * 1000000000.0); // ensures nsleep is always less than 1 billion which is the max parameter for nanosleep()
		//std::cout << "real:" << (realSleep) << std::endl; //nanosecond sleep time for testing
		//std::cout << "whole seconds:" << (wholeSeconds) << std::endl; //seconds sleep time for testing
		
		//struct used to set start and end times for nanosleep()
		struct timespec req = {0};
		req.tv_sec = 0;
		req.tv_nsec = realSleep;
		
		//starts a timer to see how long the program sleeps
		auto start = std::chrono::high_resolution_clock::now();
		
		//blocks the signals
		sigset_t mask;
		sigfillset(&mask);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		
		//sleeps the program
		sleep(wholeSeconds);
		nanosleep(&req, (struct timespec *)NULL);
		
		//ends the timer that marks how the program sleeps
		auto finish = std::chrono::high_resolution_clock::now();
		
		//gets current time at nanosecond level in UTC
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<8>
		>::type> Days; /* UTC: +8:00 */
		Days days = std::chrono::duration_cast<Days>(duration);
			duration -= days;
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
			duration -= hours;
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
			duration -= minutes;
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
			duration -= seconds;
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

		//outputs the time and how long the program slept
		std::cout << hours.count() << ":"
        << minutes.count() << ":"
        << seconds.count() << ":" 
        << nanoseconds.count() << ",  ";
		std::cout << "sleep for: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "nsec\n";
	}
}

int main(){
	takeInput();
}