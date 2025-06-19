#include <iostream>
#include <vector>
#include <random>


int main() {
// rng 
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 100);



const int CONST_GUESS{dist(gen)};   // constant guess
int random_guess{dist(gen)};
int lotteryNum{dist(gen)};          // random lottery number

int perSimConstGuesses[100000];      // array for number of guesses per simulation  (same guess each time)
int perSimRandomGuesses[100000];       // array for number of guesses per simulation (new random guess each time)

// variables to hold total number of guesses (for calculating average)
int totalRandomGuesses{0};
int totalConstGuesses{0};

for (int i = 0; i < 100000; i++) {
    int constGuessCount{1};
    int randomGuessCount{1};

    // same guess strategy
    while (CONST_GUESS != lotteryNum) {
        constGuessCount += 1;                   // count guess
        lotteryNum = dist(gen);                 // generate new lottery number
    }
    perSimConstGuesses[i] = constGuessCount;     // assign total number of guesses to array at current index
    totalConstGuesses += constGuessCount;

    // random guess strategy
    while (random_guess != lotteryNum) {
        randomGuessCount += 1;                  // count guess  
        lotteryNum = dist(gen);                 // generate new lottery number
        random_guess = dist(gen);               // generate new guess
    }
    perSimRandomGuesses[i] = randomGuessCount;
    totalRandomGuesses += randomGuessCount;
}


double averageConstGuesses;
double averageRandomGuesses;


averageConstGuesses = (totalConstGuesses / 100000.0);
averageRandomGuesses = (totalRandomGuesses / 100000.0);


std::cout << "Average number of guesses when guessing the same number every time: " << averageConstGuesses << std::endl;
std::cout << "Average number of guesses when guessing a random number every time: " << averageRandomGuesses << std::endl;


}