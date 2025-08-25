import random
import itertools


def generate_all_subsets(weights, total_weights):
    # First we get all combinations of weights using itertools.combinations
    weight_combinations = [
        itertools.combinations(weights, r) for r in range(total_weights + 1)
    ]
    # Then we flatten the list of combinations using itertools.chain
    return itertools.chain.from_iterable(weight_combinations)


def brute_force_weights(weight_combinations, capacity):
    # We start with a max weight sum = 0 and an empty list of weight combinations.
    max_w_sum = 0
    best_subsets = []
    for w_subset in weight_combinations:
        # Iterate through every subset of the weight combinations and obtain
        # the sum of the weights
        subset_weight = sum(w_subset)
        if subset_weight <= capacity:
            # If the sum of weights is less than capacity, compare with the largest
            # subset we have found so far.
            if subset_weight > max_w_sum:
                # If it's greater than, replace previous
                # largest subset with the newest largest subset found.
                max_w_sum = subset_weight
                best_subsets = [w_subset]
            elif subset_weight == max_w_sum:
                # If the weight of the new subset is the same as the largest subset(s) found
                # so far, append that to the list.
                best_subsets.append(w_subset)
    return best_subsets


def main():
    # Random number of random weights and a random total W
    total_weights = random.randint(5, 12)
    weights = [random.randint(1, 20) for _ in range(total_weights)]
    capacity = random.randint(max(weights), sum(weights) // 2)

    print(f"There are {total_weights} weights w_i and W = {capacity}.\n")
    print(f"The weights are {weights}.\n")

    weight_combinations = generate_all_subsets(weights, total_weights)

    best_subset = brute_force_weights(weight_combinations, capacity)
    print(f"Best subset(s): {best_subset}.\nMax_w = {sum(best_subset[0])}.\n")


if __name__ == "__main__":
    main()
