/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Bosen Miao"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */

std::set<std::string> get_applicants(const std::string& filename) {
  std::set<std::string> names;
  std::ifstream file(filename);
  if (!file) return names;

  for (std::string line; std::getline(file, line); ) {
    if (!line.empty())
      names.insert(std::move(line));
  }
  return names;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */

// Helper function to get initials (first letter of first and last word)
std::string get_initials(const std::string& name) {
  std::string initials;
  size_t first = name.find_first_not_of(' ');
  if (first != std::string::npos) {
    initials += std::toupper(name[first]);
    size_t last_space = name.find_last_of(' ');
    if (last_space != std::string::npos && last_space + 1 < name.size()) {
      initials += std::toupper(name[last_space + 1]);
    } else if (name.size() > 1) {
      initials += std::toupper(name[1]);
    }
  }
  return initials;
}

std::queue<const std::string*> find_matches(const std::string& name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string target_initials = get_initials(name);
  for (const auto& student : students) {
    if (get_initials(student) == target_initials) {
      matches.push(&student);
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  // Select the match whose name is lexicographically smallest (alphabetically first)
  const std::string* best_match = matches.front();
  matches.pop();
  while (!matches.empty()) {
    if (*matches.front() < *best_match) {
      best_match = matches.front();
    }
    matches.pop();
  }
  return *best_match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
