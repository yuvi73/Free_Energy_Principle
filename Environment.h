#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <random>

class Environment {
private:
    std::vector<double> state;
    std::vector<double> goal_state;
    std::mt19937 rng;
    double noise_level;
    double goal_attraction;

public:
    Environment(int state_dim, double noise = 0.1, double goal_attr = 0.05);
    
    // Generate sensory input based on current state
    std::vector<double> get_sensory_input();
    
    // Update environment state
    void step(const std::vector<double>& action);
    
    // Update environment state
    void update_state();
    
    // Get current state
    std::vector<double> get_state() const;
    
    // Get goal state
    std::vector<double> get_goal_state() const;
};

#endif // ENVIRONMENT_H 