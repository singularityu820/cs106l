#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  int c = ' ';
  Corpus tokens;
  auto begin = source.begin();
  auto end = source.end();
  auto is_space = [](char ch) { return std::isspace(static_cast<unsigned char>(ch)); };
  auto iters = find_all(begin, end, is_space);
  std::transform(iters.begin(), iters.end() - 1, iters.begin() + 1, std::inserter(tokens,tokens.begin()),
                 [&](auto it1, auto it2) { return Token(source, it1, it2); });
  std::erase_if(tokens, [](const Token& t) { return t.content.empty(); });
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  auto view = source
      | rv::filter([&](const Token& t) { return !dictionary.contains(t.content); })
      | rv::transform([&](const Token& t) {
          auto suggestions_view = dictionary
              | rv::filter([&](const std::string& word) {
                  return levenshtein(t.content, word) == 1;
                });
          std::set<std::string> suggestions(suggestions_view.begin(), suggestions_view.end());
          return Misspelling{ t, suggestions };
        })
      | rv::filter([](const Misspelling& m) { return !m.suggestions.empty(); });
  return std::set<Misspelling>(view.begin(), view.end());

};

/* Helper methods */

#include "utils.cpp"
