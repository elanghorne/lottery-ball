#include <iostream>
#include <vector>
#include <random>


int main() {
// rng 
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 100);



const int CONST_GUESS{dist(gen)};   // constant guess
int random_guess{dist(gen)};        // random guess
int lotteryNum;                     // initialize random lottery number variable

int perSimConstGuesses[100000];      // array for number of guesses per simulation  (same guess each time)
int perSimRandomGuesses[100000];       // array for number of guesses per simulation (new random guess each time)
int perSimAlternatingGuesses[100000];

// variables to hold total number of guesses (for calculating average)
int totalRandomGuesses{0};
int totalConstGuesses{0};
int totalAlternatingGuesses{0};

for (int i = 0; i < 100000; i++) {
    int constGuessCount{1};
    int randomGuessCount{1};
    int alternatingGuessCount{1};
    lotteryNum = dist(gen);

    // same guess strategy
    while (CONST_GUESS != lotteryNum) {
        constGuessCount += 1;                   // count guess
        lotteryNum = dist(gen);                 // generate new lottery number
    }
    perSimConstGuesses[i] = constGuessCount;     // assign total number of guesses to array at current index
    totalConstGuesses += constGuessCount;        // add this iterations guess count to total guess count
    lotteryNum = dist(gen);                      // reset lottery number for random guessle

    // random guess strategy
    while (random_guess != lotteryNum) {
        randomGuessCount += 1;                  // count guess  
        lotteryNum = dist(gen);                 // generate new lottery number
        random_guess = dist(gen);               // generate new guess
    }
    perSimRandomGuesses[i] = randomGuessCount;
    totalRandomGuesses += randomGuessCount;
    lotteryNum = dist(gen);                     // reset lottery number for alternating guess

    // alternating guess strategy 
    const int guess1{7};
    const int guess2{84};
    bool guessToggle{true};
    int alternating_guess = guess1;

    while (alternating_guess != lotteryNum) {
        alternatingGuessCount += 1; // count guess
        guessToggle = !guessToggle; // toggle guess
        lotteryNum = dist(gen);     // generate new lotto number
    }
    perSimAlternatingGuesses[i] = alternatingGuessCount;
    totalAlternatingGuesses += alternatingGuessCount;
}


double averageConstGuesses;
double averageRandomGuesses;
double averageAlternatingGuesses;


averageConstGuesses = (totalConstGuesses / 100000.0);
averageRandomGuesses = (totalRandomGuesses / 100000.0);
averageAlternatingGuesses = (totalAlternatingGuesses / 100000.0);


std::cout << "Average number of guesses when guessing the same number every time: " << averageConstGuesses << std::endl;
std::cout << "Average number of guesses when guessing a random number every time: " << averageRandomGuesses << std::endl;
std::cout << "Average number of guesses when guessing a random number every time: " << averageAlternatingGuesses << std::endl;



}