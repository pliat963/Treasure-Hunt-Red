//taken from here:
// https://www.geeksforgeeks.org/program-find-simple-moving-average/

 //C++ program to calculate
// Simple Moving Average
#include <bits/stdc++.h>
//using namespace std;
 
class SimpleMovingAverage {
 
  // queue used to store list so that we get the average
  std::queue<double> Dataset;
  int period;
  double sum;
 
  public:
  // constructor to initialize period
  SimpleMovingAverage(int per) { period = per; }
 
  // function to add new data in the
  // list and update the sum so that
  // we get the new mean
  void addData(double num)
  {
    sum += num;
    Dataset.push(num);
 
    // Updating size so that length
    // of data set should be equal
    // to period as a normal mean has
    if (Dataset.size() > period) {
      sum -= Dataset.front();
      Dataset.pop();
    }
  }
 
  // function to calculate mean
  double getMean() { return sum / period; }
};
 

 
// This code is contributed by phasing17