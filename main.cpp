#include <iostream>
#include <random>
#include <cstdlib> 
#include <ctime>

/*
Problem 2: 
  * Each Server has MTBF of 500 hours
  * Continuous uptimes (AVG is MTBF)
  * Follows EXP Dist
  * 10 hour restoration period
  a)
    * Show failure and restoration times for each server over 20 years.
    * 24 Hours per day
    * 365 days each year
    * 24 * 365 = 8,760 && 8,760 * 20 = 175,200 total hours
  b)
    * How long it takes for the whole system to fail
    * Both down at the same time
    * Take the avg of multiple runs
*/

int main() {
  //build random state
  std::default_random_engine generator;
  std::exponential_distribution<double> expDistribution(1.05);
  //build vars for each server
  int failureTime = 0;
  int numSysFailures = 0;
  int downTimeA = 0;
  int downTimeB = 0;
  int numFailuresA = 0;
  int numFailuresB = 0;
  //initiate first down time
  double downA = 500 * expDistribution(generator);
  double downB = 500 * expDistribution(generator);
  //loop through all the hours
  for (double i = 1; i <= 175200; i++) {
    //ServerA goes down
    if ((int)downA == i) {
      numFailuresA++;
      downTimeA = downTimeA + 10;
      downA = downA + (500 * expDistribution(generator));
      //Down while ServerB is down
      if ((int)downA - 10 <= downB && (int)downA + 10 >= downB) {
        failureTime = i;
        numSysFailures++;    
        //std::cout << (int)downB << " , " << (int)downA << std::endl;
        //std::cout << "System Failure" << std::endl;
      }
    } 
    //ServerB goes down
    else if ((int)downB == i) {
      numFailuresB++;
      downTimeB = downTimeB + 10;
      downB = downB + (500 * expDistribution(generator));
      //Down while ServerA is down
      if ((int)downB - 10 < downA && (int)downB + 10 > downA) {
        failureTime = i;
        numSysFailures++;    
        //std::cout << (int)downB << " , " << (int)downA << std::endl;
        //std::cout << "System Failure" << std::endl;        
      }
    }
  }
  std::cout << "Number of Failures for A: " << numFailuresA << std::endl;
  std::cout << "Restoration Time in hours for A: " << downTimeA << std::endl;
  std::cout << "Number of Failures for B: " << numFailuresB << std::endl;
  std::cout << "Restoration Time in hours for B: " << downTimeB << std::endl;
  std::cout << "Number of System Failures: " << numSysFailures << std::endl;
}