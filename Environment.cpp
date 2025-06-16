#include "Environment.h"
#include <cmath>
#include <algorithm>

Environment::Environment(int state_dim, double noise, double goal_attr)
    : noise_level(noise), goal_attraction(goal_attr) {
    state.resize(state_dim, 0.0);
    goal_state.resize(state_dim, 0.0);
    std::random_device rd;
    rng.seed(rd());
    std::normal_distribution<double> dist(0.0, 1.0);
    for (auto& s : state) {
        s = dist(rng);
    }
    for (auto& g : goal_state) {
        g = dist(rng) * 2.0; // Goal state is further away
    }
}

std::vector<double> Environment::get_sensory_input() {
    std::vector<double> sensory_input(state.size());
    std::normal_distribution<double> noise_dist(0.0, noise_level);
    for (size_t i = 0; i < state.size(); ++i) {
        sensory_input[i] = state[i] + noise_dist(rng);
    }
    return sensory_input;
}

void Environment::step(const std::vector<double>& action) {
    // Environment state is affected by agent's action and attracted to goal state
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] += action[i];
        // Attract to goal state
        state[i] += goal_attraction * (goal_state[i] - state[i]);
        // Keep state values within reasonable bounds
        state[i] = std::max(-5.0, std::min(5.0, state[i]));
    }
}

void Environment::update_state() {
    // For compatibility: random walk
    std::normal_distribution<double> dist(0.0, 0.1);
    for (auto& s : state) {
        s += dist(rng);
        s = std::max(-5.0, std::min(5.0, s));
    }
}

std::vector<double> Environment::get_state() const {
    return state;
}

std::vector<double> Environment::get_goal_state() const {
    return goal_state;
} 