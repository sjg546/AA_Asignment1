#include <iostream>
#include <random>
#include <vector>

double OfferRound(std::vector<double> house_valuations, double px,
                  int *current_best, int offer_round_number) {

  int house_with_access = 0;
  double current_value = 0;
  if (offer_round_number == house_valuations.size() ||
      px == 1.0 / *current_best) {
    return px;
  }

  for (auto &value : house_valuations) {
    if (value > px) {
      house_with_access++;
      current_value += px;
    }
  }

  std::cout << "House With Access: " << house_with_access << ", Px: " << px
            << ", Current Value: " << current_value << std::endl;
  if (house_with_access > *current_best) {
    *current_best = house_with_access;
  }

  if (current_value >= 1.0) {
    return OfferRound(house_valuations,
                      px - ((current_value - 1.0) / house_valuations.size()),
                      current_best, offer_round_number + 1);
  } else {
    return OfferRound(house_valuations,
                      px + ((1.0 - current_value) / house_valuations.size()),
                      current_best, offer_round_number + 1);
  }
}

int main() {
  const int n = 10;
  double px = 1.0 / n;
  int houses_with_access = 0;
  double total_raised = 0;

  // Set up the uniform distribution generator
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  // Set the seed
  generator.seed(time(NULL));

  // Storage for the individual house valuations
  std::vector<double> house_valuations;

  // Generate house valuations
  for (int i = 0; i < n; ++i) {
    house_valuations.push_back(distribution(generator));
  }

  for (auto &valuation : house_valuations) {
    std::cout << valuation << std::endl;
  }

  std::cout << OfferRound(house_valuations, px, &houses_with_access, 0) << " : "
            << houses_with_access << std::endl;

  return 1;
}