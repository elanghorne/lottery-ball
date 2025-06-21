#include <iostream>
#include <vector>
#include <random>
#include <numeric>


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
int perSimOrderedGuesses[100000];


// variables to hold total number of guesses (for calculating average)
int totalRandomGuesses{0};
int totalConstGuesses{0};
int totalAlternatingGuesses{0};
int totalOrderedGuesses{0};

for (int i = 0; i < 100000; i++) {
    int constGuessCount{1};
    int randomGuessCount{1};
    int alternatingGuessCount{1};
    int orderedGuessCount{1};
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
    lotteryNum = dist(gen);                     // reset lottery number for alternating guess


    // next strategy: guess 1 through 100 in order on repeat
    std::vector<int> orderedGuesses(100);
    std::iota(orderedGuesses.begin(), orderedGuesses.end(), 1);
    int orderedGuess = orderedGuesses[0];
    int timesThroughAllGuesses{0};

    while (orderedGuess != lotteryNum) {
        bool numHasBeenGuessed = false;

        for (int k = 1; k < 100; k++) {
            orderedGuess = orderedGuesses[k];
            lotteryNum = dist(gen);
            orderedGuessCount += 1;

            if (orderedGuess == lotteryNum) {
                numHasBeenGuessed = true;
                break;
            } else {
                continue;
            }
        }
        if (!numHasBeenGuessed) {
            timesThroughAllGuesses += 1;
        }
    }
    orderedGuessCount += (100 * timesThroughAllGuesses);
    perSimOrderedGuesses[i] = orderedGuessCount;
    totalOrderedGuesses += orderedGuessCount;

}


double averageConstGuesses;
double averageRandomGuesses;
double averageAlternatingGuesses;
double averageOrderedGuesses;


averageConstGuesses = (totalConstGuesses / 100000.0);
averageRandomGuesses = (totalRandomGuesses / 100000.0);
averageAlternatingGuesses = (totalAlternatingGuesses / 100000.0);
averageOrderedGuesses = (totalOrderedGuesses / 100000.0);


std::cout << "Average number of guesses when guessing the same number every time: " << averageConstGuesses << std::endl;
std::cout << "Average number of guesses when guessing a random number every time: " << averageRandomGuesses << std::endl;
std::cout << "Average number of guesses when alternating between 2 guesses: " << averageAlternatingGuesses << std::endl;
std::cout << "Average number of guesses when guessing 1-100 in order: " << averageOrderedGuesses << std::endl;




}