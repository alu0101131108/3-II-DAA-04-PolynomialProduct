#include <vector>
#include <iostream>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <chrono>
#include "../include/polynomial.hpp"
#include "../include/classic-product.hpp"
#include "../include/divide-conquer-product.hpp"

int main(int argc, char const *argv[])
{
  srand(time(NULL));
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  std::vector<int> sizes = {50, 100, 500, 1000, 5000, 10000};

  for (int i = 0; i < sizes.size(); i++) 
  {
    std::cout << "Size: " << sizes[i] << std::endl;
    Polynomial randPolA, randPolB;
    randPolA.generateRandom(sizes[i], 100);
    randPolB.generateRandom(sizes[i], 100);

    randPolA.setProductStrategy(new DivideAndConquerProduct());
    start = std::chrono::high_resolution_clock::now();
    Polynomial res2(randPolA * randPolB);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "DyV Strategy: " << elapsed_seconds.count() << "s" << std::endl;
    
    randPolA.setProductStrategy(new ClassicProduct());
    start = std::chrono::high_resolution_clock::now();
    Polynomial res1(randPolA * randPolB);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Classic Strategy: " << elapsed_seconds.count() << "s" << std::endl;
  }

  return 0;
}