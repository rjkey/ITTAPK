




#include <iostream>
using namespace std;


// protectiong cout, and defening events
void test(const char inp)
{
  cout << inp;
}//*/




int main()
{
  const char arr[] = {'t', 'e', 's', 't', '\n'};

  for(int i=0; i<5; i++) {
    test(arr[i]);
  }

  //cout << "hello world" << endl;
  
  return 0;
}
