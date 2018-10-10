#include <algorithm>
#include <iterator>
#include <chrono>
#include <future>
#include <iostream>
#include <ostream>
#include <vector>
#include <thread>

class Algo
{
public:
  Algo(std::vector<int> v)
    : data_(std::move(v))
  {}
    
  void doAlgo()
  {
    std::chrono::time_point<std::chrono::high_resolution_clock> commence = std::chrono::high_resolution_clock::now();
    std::sort(data_.begin(), data_.end());
    std::chrono::time_point<std::chrono::high_resolution_clock> complete = std::chrono::high_resolution_clock::now();
    duration_ = std::chrono::nanoseconds(complete - commence);
  }
    
  std::chrono::duration<long double> processingTime()
  {
    return duration_;
  }
    
    
  void print()
  {
    std::copy(data_.begin(), data_.end(), std::ostream_iterator<int>(std::cout, " "));
  }
private:
  Algo(const Algo&) = delete; // No copy construction is allowed
    
  Algo& operator=(const Algo&) = delete; // No copy assignment is allowed

  std::vector<int>                    data_;
  std::chrono::nanoseconds            duration_;
};




typedef Algo SmartAlgo;
typedef Algo CoolAlgo;
typedef Algo FantasticAlgo;


/*void runThread(vector<int> data_, std::shared_ptr<algo> algoType, std::shared_ptr<std::chrono::duration> dur){
  Algo OBJ = decltype(algoType)(data_);
  OBJ.doAlgo();
  dur = OBJ.processingTime();
}*/

int main(int argc, char* argv[])
{
  printf("Run\n");

  int i = 0;
  int n = 10000000; // Change at your leasure
    
  std::vector<int> data;
  data.reserve(n);
  generate_n( back_inserter( data ), n, [&i](){return i++;}  );
  random_shuffle( data.begin (), data.end () );



  /* Insert code here ... */
  std::chrono::duration SAD = std::chrono::duration();
  Algo OBJ = Algo(data);
  OBJ.doAlgo();
  SAD = OBJ.processingTime();
  std::cout << SAD << std::endl;


  /*
  std::shared_ptr<SmartAlgo> SA_ptr = std::make_shared<SmartAlgo>();
  std::shared_ptr<std::chrono::duration> SAD_ptr = std::make_shared<std::chrono::duration> SAD;

  std::thread th1(runThread, data, SA_ptr, SAD_ptr;
  */
  
  
  //std::thread th2(runThread, data);
  //std::thread th3(runThread, data);

  
  printf("\nDone\n");
  return 0;
}
