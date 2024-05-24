#include <FliwaCord/fliwacord.h>

#include <iostream>

#include "utility.h"

int main() {
  FliwaBot::dotenv::init(FliwaBot::dotenv::Preserve);

  std::cout << "Token: " << FliwaBot::dotenv::getenv("TOKEN");

  return 0;
}