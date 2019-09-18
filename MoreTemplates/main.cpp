/**
 * Demonstrate a generic way for returning a buffer that can be filled using different algorithms.
 */

#include <iostream>
#include <string>
#include <array>

static const int maxSize = 20;  // Visual Studio 2013 is dumb and doesn't like constexpr

/**
 * All algorithms must write to a plain array, but some algorithms need to write more elements than other algorithms;
 * therefore, allocate enough space for all alogrithms to use and say how much of that array is actually written.
 */
struct CommonReturnType
{
   std::array<int, maxSize> buffer;  // We'll have some fun and use std::array instead of plain array
   size_t length;
};

/**
 * Fill up an array using different algorithms
 */
template<class Algorithm>
class ThinkerBox
{
public:
   CommonReturnType result() { return mAlgorithm.result(); }
private:
   Algorithm mAlgorithm{};
};

/**
 * Fill the whole array with twos.
 */
struct AlgorithmTwo
{
   CommonReturnType result()
   {
      CommonReturnType answer{};
      answer.length = maxSize;
      answer.buffer.fill(2);
      return answer;
   }
};

/**
* Fill a fourth of the array with fours.
*/
struct AlgorithmFour
{
   CommonReturnType result()
   {
      CommonReturnType answer{};
      answer.length = maxSize / 4;
      std::fill_n(std::begin(answer.buffer), maxSize, 4);
      return answer;
   }
};

/**
* Fill half of the array with incrementing values.
*/
struct AlgorithmFancy
{
   CommonReturnType result()
   {
      CommonReturnType answer{};
      answer.length = maxSize / 2;

      int number = 0;

      for (size_t i = 0; i < answer.length; i++)
      {
         answer.buffer[i] = number++;
      }
      return answer;
   }
};

/**
* Print out the hard work of the mysterious algorithm.
*/
void print(CommonReturnType c)
{
   for (size_t i = 0; i < c.length; i++)
   {
      std::cout << c.buffer[i] << std::endl;
   }
}

int main()
{
   print(ThinkerBox<AlgorithmTwo>{}.result());
   print(ThinkerBox<AlgorithmFour>{}.result());
   print(ThinkerBox<AlgorithmFancy>{}.result());

   std::string name;
   getline(std::cin, name);
   std::cout << "Hello, " << name << "!\n";
}
