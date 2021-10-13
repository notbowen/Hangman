// Hangman, Written in C++
// If u wanna change the word choices, edit line 108+ 

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

std::vector<std::string> guessed_words; // List of characters guessed correctly
                                        // Declared outside as we want it to be global
std::string word;

// random choice
std::string choice(std::vector<std::string> vec)
{
    srand(time(NULL));
    int len = vec.size();
    int index = rand() % len;

    return vec[index];
}

// convert char to string
std::string charToString(char character)
{
    std::stringstream ss;
    std::string str;

    ss << character;
    ss >> str;

    return str;
}

// get index of smth in a string
int index(std::string match, std::string word)
{
    int guess_index = -1;
    for (int i = 0; i < word.length(); i++)
    {
        if (charToString(word[i]) == match)
        {
            guess_index = i;
        }
    }

    return guess_index;
}

// prints out the progress,
// also determines whether game ends
bool progress()
{
    std::string output;

    if (guessed_words.size() == 0)
    {
        std::cout << "Progress: ";
        for (int i = 0; i < word.length(); i++)
        {
            std::cout << "_";
        }
        std::cout << std::endl;
        return true;
    }

    for (int i = 0; i < word.length(); i++)
    {
        bool isWord = true;
        for (int j = 0; j < guessed_words.size(); j++)
        {
            
            if (charToString(word[i]) == guessed_words[j])
            {
                output = output + charToString(word[i]);
                isWord = true;
                break;
            } else
            {
                isWord = false;
            }
        }
        if (isWord == false)
        {
            output = output + "_";
        }
    }
    std::cout << "Progress: " << output << std::endl;

    return (output.find("_") != std::string::npos);
}

// main
int main()
{
    bool isOngoing = true;

    /* 
    Word must NOT contain caps as it'll break the code
    Cuz I was too lazy to include lowercase formatting
    To add new words, write: choices.push_back(word);    
    */
    std::vector<std::string> choices;
    choices.push_back("word");
    choices.push_back("jojo");
    choices.push_back("lucky");
    choices.push_back("gizmo");

    word = choice(choices);
    std::string guess;

    std::cout << "Hangman :D" << std::endl;
    std::cout << "Hints:" << std::endl;
    std::cout << "- Word has " << word.length() << " letters." << std::endl;
    std::cout << std::endl;

    int tries = 0;

    while (isOngoing)
    {
        // get input
        std::cout << "\nGuess (input 1 letter pls): ";
        std::getline(std::cin, guess);

        // validate input
        while ((guess.length() != 1))
        {
            std::cout << "\nInvalid input ;-;\nGuess (input 1 letter pls): ";
            std::getline(std::cin, guess);
        }

        // lower input
        guess = boost::algorithm::to_lower_copy(guess);

        // process input
        int guess_index = index(guess, word); // returns -1 if no

        if (guess_index == -1)
        {
            std::cout << "Lmao the character was not in the answer ;-;" << std::endl;
        } else
        {
            if(std::find(guessed_words.begin(), guessed_words.end(), guess) == guessed_words.end()) // check if guess is in the guessed_words list
            {
                std::cout << "Nice, " << guess << " was in the answer" << std::endl;
                guessed_words.push_back(guess);
            } else
            {
                std::cout << "Bruh u already guessed that letter" << std::endl;
            }
        }
        isOngoing = progress();

        tries++;
    }

    std::cout << "\nCongrats, you guessed the word in " << tries << " tries :D" << std::endl;

    system("pause"); // for windows only :D

    return 0;
}