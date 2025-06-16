# Use Ubuntu as base image
FROM ubuntu:22.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt5-default \
    qtbase5-dev \
    qtcharts5-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy the source code
COPY . .

# Create build directory and build the project
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Set environment variable for Qt
ENV QT_X11_NO_MITSHM=1

# Command to run the application
CMD ["./build/fep_simulation"] 