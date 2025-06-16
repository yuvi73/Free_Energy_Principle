#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <cmath>
#include <random>

class Agent {
private:
    // Internal state of the agent
    std::vector<double> internal_state;
    // Sensory input from environment
    std::vector<double> sensory_input;
    // Generative model parameters
    std::vector<double> model_parameters;
    // Learning rate for state update
    double state_learning_rate;
    // Learning rate for model update
    double model_learning_rate;
    // Random number generator
    std::mt19937 rng;

public:
    Agent(int state_dim, int sensory_dim, double state_lr = 0.01, double model_lr = 0.01);
    
    // Update internal state based on sensory input
    void update_state(const std::vector<double>& input);
    
    // Calculate free energy
    double calculate_free_energy() const;
    
    // Update model parameters to minimize free energy
    void update_model();
    
    // Get current internal state
    std::vector<double> get_state() const;
    
    // Predict sensory input based on internal state
    std::vector<double> predict_sensory_input() const;
    
    // Get agent action
    std::vector<double> act() const;
};

#endif // AGENT_H 