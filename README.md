# Philosophers

A multithreaded solution to the classic **Dining Philosophers Problem** using POSIX threads and mutexes. This project simulates philosophers sitting at a round table who must alternate between eating, sleeping, and thinking while sharing forks with their neighbors.

## 📋 Table of Contents

- [Project Description](#project-description)
- [Technology Stack](#technology-stack)
- [Project Architecture](#project-architecture)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Key Features](#key-features)
- [Algorithm Details](#algorithm-details)
- [Contributing](#contributing)
- [License](#license)

## Project Description

The Dining Philosophers Problem is a classic synchronization problem in computer science. This implementation demonstrates:

- Thread synchronization using mutexes
- Deadlock prevention strategies
- Race condition handling
- Resource sharing between concurrent processes

Each philosopher is represented by a thread that:
1. **Thinks** - contemplates life
2. **Gets hungry** - needs to eat
3. **Takes forks** - acquires left and right fork (mutex)
4. **Eats** - consumes spaghetti for a set time
5. **Releases forks** - puts down both forks
6. **Sleeps** - rests after eating
7. **Repeats** - cycle continues until death or meal quota is met

## Technology Stack

- **Language**: C
- **Compiler**: GCC/Clang with flags: `-Wall -Wextra -Werror -pthread -O2`
- **Threading**: POSIX threads (pthread)
- **Synchronization**: Mutexes (pthread_mutex_t)
- **Build System**: Makefile
- **Standard Libraries**:
  - `pthread.h` - Thread management
  - `sys/time.h` - Time tracking
  - `unistd.h` - System calls
  - `stdio.h` - I/O operations
  - `stdlib.h` - Memory management

## Project Architecture

### Core Components

```
┌──────────────────────────────────────────┐
│           Main Program                   │
│  - Argument validation                   │
│  - Simulation initialization             │
│  - Thread creation & management          │
└──────────────────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        │                       │
┌───────▼─────────┐    ┌────────▼──────────┐
│  Philosopher    │    │    Monitor        │
│   Threads       │    │    Thread         │
│                 │    │                   │
│ - Think         │    │ - Check deaths    │
│ - Take forks    │    │ - Check meal      │
│ - Eat           │    │   quotas          │
│ - Sleep         │    │ - End simulation  │
└─────────────────┘    └───────────────────┘
         │
    ┌────┴────┐
    │ Mutexes │
    ├─────────┤
    │ Forks   │ ← Prevent simultaneous fork access
    │ Print   │ ← Prevent message interleaving
    │ End     │ ← Protect simulation state
    │ Meal    │ ← Protect meal tracking
    └─────────┘
```

### Data Structures

**t_data** (Simulation Configuration)
- Number of philosophers
- Time constraints (die, eat, sleep)
- Optional meal quota
- Shared mutexes and simulation state

**t_philo** (Philosopher State)
- Unique ID
- Last meal timestamp
- Meals eaten counter
- Thread handle
- Fork references (left/right mutexes)
- Personal meal mutex

## Getting Started

### Prerequisites

- GCC or Clang compiler
- POSIX-compliant operating system (Linux, macOS, etc.)
- Make build tool

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/peda-cos/Philosophers.git
   cd Philosophers/philo
   ```

2. **Compile the project**
   ```bash
   make
   ```

3. **Clean build artifacts** (optional)
   ```bash
   make clean    # Remove object files
   make fclean   # Remove object files and executable
   make re       # Rebuild from scratch
   ```

## Usage

### Command Syntax

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter                                   | Description                                                                  | Unit         |
| ------------------------------------------- | ---------------------------------------------------------------------------- | ------------ |
| `number_of_philosophers`                    | Number of philosophers and forks                                             | Integer      |
| `time_to_die`                               | Time before a philosopher dies without eating                                | Milliseconds |
| `time_to_eat`                               | Time it takes for a philosopher to eat                                       | Milliseconds |
| `time_to_sleep`                             | Time a philosopher spends sleeping                                           | Milliseconds |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times | Integer      |

### Examples

**Basic simulation** (4 philosophers, will run until death):
```bash
./philo 4 410 200 200
```

**Simulation with meal quota** (5 philosophers, stops after each eats 7 times):
```bash
./philo 5 800 200 200 7
```

**Testing edge cases**:
```bash
# Single philosopher (should die - only one fork)
./philo 1 800 200 200

# Tight timing (philosophers should die)
./philo 4 310 200 100

# Relaxed timing (philosophers should survive)
./philo 5 800 200 200 10
```

### Output Format

```
[timestamp_in_ms] [philosopher_id] [action]
```

**Possible actions:**
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

**Example output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
200 1 is sleeping
200 3 is sleeping
```

## Project Structure

```
Philosophers/
├── LICENSE               # MIT License
├── README.md             # This file
└── philo/                # Main program directory
    ├── Makefile          # Build configuration
    ├── philo.h           # Header file with structures and prototypes
    ├── main.c            # Entry point and thread orchestration
    ├── init.c            # Simulation and philosopher initialization
    ├── routine.c         # Philosopher thread routine
    ├── actions.c         # Philosopher actions (eat, sleep, think)
    ├── monitor.c         # Death and completion monitoring
    └── utils.c           # Utility functions (time, print, atoi)
```

### File Responsibilities

| File        | Purpose                                                    |
| ----------- | ---------------------------------------------------------- |
| `main.c`    | Argument validation, thread creation, cleanup              |
| `init.c`    | Initialize simulation data, philosophers, and mutexes      |
| `routine.c` | Main philosopher thread loop                               |
| `actions.c` | Philosopher actions: take/release forks, eat, sleep, think |
| `monitor.c` | Monitor philosopher deaths and meal completion             |
| `utils.c`   | Helper functions for time, printing, and parsing           |
| `philo.h`   | Type definitions and function prototypes                   |

## Key Features

### ✅ Thread Safety
- **Mutex-protected resources**: All shared data is protected by mutexes
- **Deadlock prevention**: Philosophers acquire forks in a specific order (even IDs: left→right, odd IDs: right→left)
- **Race condition prevention**: Meal tracking and simulation state are mutex-protected

### ✅ Precise Timing
- Millisecond-accurate timestamps using `gettimeofday()`
- Microsecond-precision delays using `usleep()`
- Death detection within 10ms of actual death time

### ✅ Resource Management
- Proper mutex initialization and destruction
- Memory allocation and deallocation
- Thread creation and joining
- Clean simulation termination

### ✅ Edge Case Handling
- **Single philosopher**: Special handling (dies with only one fork)
- **Simulation end**: Graceful shutdown when a philosopher dies
- **Meal quota**: Automatic termination when all philosophers have eaten enough
- **No data races**: Thread-safe message printing

## Algorithm Details

### Deadlock Prevention Strategy

The implementation uses **resource ordering** to prevent deadlocks:

```c
// Even-numbered philosophers: left fork first
if (philo->id % 2 == 0)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
}
// Odd-numbered philosophers: right fork first
else
{
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
}
```

This ensures that at least one philosopher can always acquire both forks, preventing circular wait conditions.

### Monitoring System

The monitor runs in the main thread and checks:
1. **Death condition**: If any philosopher hasn't eaten within `time_to_die` milliseconds
2. **Completion condition**: If all philosophers have eaten `must_eat` times (when specified)

The monitor polls every 1ms to ensure timely death detection while minimizing CPU usage.

### Synchronization Points

| Mutex         | Protects               | Used By                      |
| ------------- | ---------------------- | ---------------------------- |
| `forks[]`     | Fork availability      | Philosophers (eating)        |
| `print_mutex` | Console output         | All threads (printing)       |
| `end_mutex`   | Simulation end flag    | All threads                  |
| `meal_mutex`  | Last meal time & count | Philosopher thread + Monitor |

## Contributing

Contributions are welcome! This project follows the 42 School coding standards:

### Coding Standards
- **Norm compliance**: Code follows 42's Norm (indentation, line length, function length)
- **Function limit**: Maximum 25 lines per function
- **Variable declarations**: At the beginning of functions
- **Naming conventions**: Snake_case for functions, lowercase for variables
- **Comments**: Header comments in 42 style

### How to Contribute

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Make your changes following the coding standards
4. Test thoroughly with various parameters
5. Commit your changes (`git commit -m 'Add some improvement'`)
6. Push to the branch (`git push origin feature/improvement`)
7. Open a Pull Request

### Testing Checklist

- [ ] No data races (use `valgrind --tool=helgrind`)
- [ ] No memory leaks (use `valgrind --leak-check=full`)
- [ ] Philosophers don't die when they shouldn't
- [ ] Death is detected within 10ms
- [ ] Single philosopher case handled correctly
- [ ] Simulation ends properly with meal quota
- [ ] No segmentation faults with various inputs

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Pedro Monteiro

---

<div align="center">

**Made with ☕ and 🍝 by [peda-cos](https://github.com/peda-cos)**

*Part of the 42 School curriculum*

</div>
