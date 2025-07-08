#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

User::User(const User& user)
  : _name(user._name)
  , _friends(nullptr)
  , _size(user._size)
  , _capacity(user._capacity)
{
    _friends = new std::string[user._capacity];
    for (size_t i = 0; i < _size; ++i) {
        _friends[i] = user._friends[i];
    }
}

User::~User() {
    delete[] _friends;
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

User& User::operator=(const User& user) {
    if (this != &user) {
        delete[] _friends; // Free existing resources
        _name = user.get_name();
        _size = user.size();
        _capacity = user._capacity;
        _friends = new std::string[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _friends[i] = user._friends[i];
        }
    }
    return *this;
}

User& User::operator+=(User& rhs) {
  if (this->_name != rhs._name) {
    this->add_friend(rhs._name);
    rhs.add_friend(this->_name);
  }
  return *this;
}

bool User::operator<(const User& rhs) const {
  return _name < rhs._name;
}

std::ostream& operator<<(std::ostream& os, const User& us) {
  os << "User(name=" << us.get_name() << ", friends=[";

  for (size_t i = 0; i < us.size(); ++i) {
    if (i == us.size() - 1) {
      os << us._friends[i];
    } else {
      os << us._friends[i] << ", ";
    }
  }
  os << "])";
  return os;
}
