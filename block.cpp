#include "blockchain.h"
#include "json/json.hpp"
#include "argon2/argon2.h"
#include <iostream>
using namespace std;
// THERE IS SOME SORT OF PROBLEM WITH WHERE THE HASHES GO

string Block::get_timestamp() {
  time_t t = time(0);
  tm* now = localtime(&t);
  string year = to_string((now->tm_year + 1900));
  string month = to_string((now->tm_mon + 1));
  string day = to_string(now->tm_mday);
  string hour = to_string(now->tm_hour);
  string min = to_string(now->tm_min);
  string sec = to_string(now->tm_sec);
  string c_time = year + "-" + month + "-" + day + " @ " + hour + ":" + min + ":" + sec;
  return c_time;
}
string current_hash;
string timestamp;
string data;
string previous_hash;
int Block::init(int index, string data, string previous_hash, bool from_import, string timestamp, string current_hash) {
  this->index = index;
  this->data = data;
  this->previous_hash = previous_hash;
  if (from_import) {
    this->timestamp = timestamp;
    this->current_hash = current_hash;
  } else {
    this->timestamp = get_timestamp();
    string contents = to_string(this->index) + this->timestamp + this->data + this->previous_hash /* + this->current_hash */;
    this->current_hash = hash_block(contents);
  }

  return 0;
}

int Block::print_block(bool spacing) {
  if (spacing) { cout << endl; }
  cout << "Previous block: " << this->previous_hash << endl;
  cout << "Index:          " << this->index << endl;
  cout << "Timestamp:      " << this->timestamp << endl;
  cout << "Data:           " << this->data << endl;
  cout << "This block:     " << this->current_hash << endl;
  if (spacing) { cout << endl; }
  return 0;
}
