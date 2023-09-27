#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

void say_hi(int n) 
{
  cout << "Thread :" << n << endl;
  /*std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";*/
}
 
int main() 
{
    cout << "Summoning threads >:D" << endl;
    for(int i=0; i<10; i++){
        thread (say_hi,i).detach();
    }
  return 0;
}