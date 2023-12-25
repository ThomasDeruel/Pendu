#include <cstring>
#include <cwchar>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "random_word/random_word.hpp"


// The script doesn't work with special chars
// The script doesn't work with special chars
// The script doesn't work with special chars
// The script doesn't work with special chars
// The script doesn't work with special chars

void live_lost(int& live) {
  live -= 1;
  std::cout << "Vous avez perdu 1 vie, il ne vous reste plus que " << live
            << " vie(s)." << std::endl;
}

std::set<char> get_unique_letters(std::string word) {
  std::set<char> uniques_letters;
  for(char letter : word) {
    uniques_letters.insert(letter);
  }
  return uniques_letters;
};

void delete_vector_char(std::vector<char*>& vector_char) {
  while(!vector_char.empty()) {
    char* ptr = vector_char.back(); // Récupération du pointeur à la fin
    delete[] ptr;                   // Libération de la mémoire allouée
    vector_char.pop_back(); // Suppression de l'élément à la fin du vecteur
  }
}

void validator_input(std::string& input, std::vector<char> validate_input) {
  while(std::cout << "Veuillez entre une lettre: " && (std::cin >> input)) {
    if(std::cin.fail()) {
      std::cout << "Une erreur est survenue, veuillez recommencer" << std::endl;
      continue;
    }

    if(input == "quitter" || input == "quit" || input == "stop") {
      std::cout << "Fin de la partie" << std::endl;
      exit(0);
    }

    // if input was already found
    if(std::find(validate_input.begin(), validate_input.end(), input[0]) !=
    validate_input.end()) {
      std::cout << "La lettre est déjà présente(" << input << ")" << std::endl;
      continue;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    break;
  }
}


void display_game(std::string& word) {
  //////// variables ////////
  int live = 5;
  std::vector<char> validate_input;
  std::vector<char> letters(word.begin(), word.end());
  std::set<char> unique_letters = get_unique_letters(word);

  std::cout << "Le mot à trouver contient (" << word.length()
            << ") caractères. A toi de jouer !" << std::endl;

  //////// CORE ////////

  // CHEAT & DEBUG

  // std::cout << word << std::endl;

  std::string input;
  while(true) {
    std::cout << word << std::endl;
    validator_input(input, validate_input);
    char letter_inpit = input[0];

    if(unique_letters.contains(letter_inpit)) {
      validate_input.push_back(letter_inpit);
    } else {
      live_lost(live);
    }

    bool are_u_winning = unique_letters.size() == validate_input.size();
    if(live == 0) {
      std::cout << "Vous avez perdu !";
      break;
    }
    if(!are_u_winning) {
      std::cout << "Mot mystère en cours: ";


      for(const char letter : word) {
        std::vector<char>::iterator it;
        // std::wcout << letter << std::endl;
        it = std::find(validate_input.begin(), validate_input.end(), letter);
        if(it != validate_input.end()) {
          std::cout << " " << letter << " ";
        } else {
          std::cout << " _ ";
        }
      }
      std::cout << std::endl;
    } else {
      // End of the party
      // you win
      std::cout << "Vous avez trouvé le mot [\"" << word << "\"]" << std::endl;
      std::cout << "Bravo";
      break;
    }
  }
}
int main() {
  std::string word;

  std::cout << "Chargement..." << std::endl;
  random_word::get_random_word(word);
  std::cout << "Chargement terminé." << std::endl;

  display_game(word);

  return 0;
};