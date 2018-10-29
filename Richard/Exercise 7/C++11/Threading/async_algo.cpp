#include <algorithm>
#include <iterator>
#include <chrono>
#include <future>
#include <iostream>
#include <ostream>
#include <vector>

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

void do_thread_work()
{
  
}

int main(int argc, char* argv[])
{
	std::cout << "Hello" << std::endl;
	int i = 0;
	int n = 10000000; // Change at your leasure
	std::vector<int> data;
	data.reserve(n);
	generate_n(back_inserter(data), n, [&i]() {return i++; });
	random_shuffle(data.begin(), data.end());

	/* Insert code here ... */	
  std::thread th1(do_thread_work);

	std::cout << "Goodbye" << std::endl;
	return 0;
}
