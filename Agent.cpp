#include "Agent.h"
#include <iostream>
#include <algorithm>

Agent::Agent(int state_dim, int sensory_dim, double state_lr, double model_lr)
    : state_learning_rate(state_lr), model_learning_rate(model_lr) {
    // Initialize internal state
    internal_state.resize(state_dim, 0.0);
    sensory_input.resize(sensory_dim, 0.0);
    model_parameters.resize(state_dim * sensory_dim, 0.1);
    
    // Initialize random number generator
    std::random_device rd;
    rng.seed(rd());
    
    // Initialize internal state with small random values
    std::normal_distribution<double> dist(0.0, 0.1);
    for (auto& state : internal_state) {
        state = dist(rng);
    }
}

void Agent::update_state(const std::vector<double>& input) {
    sensory_input = input;
    
    // Simple gradient descent to minimize free energy
    for (size_t i = 0; i < internal_state.size(); ++i) {
        double gradient = 0.0;
        for (size_t j = 0; j < sensory_input.size(); ++j) {
            // Calculate prediction error
            double prediction = predict_sensory_input()[j];
            double error = sensory_input[j] - prediction;
            
            // Update gradient based on prediction error
            gradient += error * model_parameters[i * sensory_input.size() + j];
        }
        
        // Update internal state
        internal_state[i] -= state_learning_rate * gradient;
    }
}

double Agent::calculate_free_energy() const {
    double free_energy = 0.0;
    
    // Calculate prediction error
    std::vector<double> prediction = predict_sensory_input();
    for (size_t i = 0; i < sensory_input.size(); ++i) {
        double error = sensory_input[i] - prediction[i];
        free_energy += 0.5 * error * error;  // Squared error term
    }
    
    // Add prior term (simplified)
    for (const auto& state : internal_state) {
        free_energy += 0.1 * state * state;  // Simple Gaussian prior
    }
    
    return free_energy;
}

void Agent::update_model() {
    // Update model parameters to better predict sensory input
    for (size_t i = 0; i < internal_state.size(); ++i) {
        for (size_t j = 0; j < sensory_input.size(); ++j) {
            double prediction = predict_sensory_input()[j];
            double error = sensory_input[j] - prediction;
            
            // Update model parameters using gradient descent
            model_parameters[i * sensory_input.size() + j] += 
                model_learning_rate * error * internal_state[i];
        }
    }
}

std::vector<double> Agent::get_state() const {
    return internal_state;
}

std::vector<double> Agent::predict_sensory_input() const {
    std::vector<double> prediction(sensory_input.size(), 0.0);
    
    // Generate prediction using current internal state and model parameters
    for (size_t i = 0; i < internal_state.size(); ++i) {
        for (size_t j = 0; j < sensory_input.size(); ++j) {
            // Nonlinear prediction (tanh activation)
            prediction[j] += std::tanh(internal_state[i]) * model_parameters[i * sensory_input.size() + j];
        }
    }
    
    return prediction;
}

std::vector<double> Agent::act() const {
    // Simple action: move towards reducing prediction error
    std::vector<double> prediction = predict_sensory_input();
    std::vector<double> action(prediction.size(), 0.0);
    for (size_t i = 0; i < prediction.size(); ++i) {
        action[i] = prediction[i] - sensory_input[i]; // Try to correct error
        action[i] = std::clamp(action[i], -1.0, 1.0); // Limit action magnitude
    }
    return action;
} 