# 🍽️ Philosophers - Dining Philosophers Problem

A multithreaded C implementation of Edsger Dijkstra's classic **Dining Philosophers Problem**, demonstrating thread synchronization, mutexes, and deadlock prevention.

## 🎯 Overview

This project simulates the famous **Dining Philosophers Problem** where `n` philosophers sit around a circular table with `n` forks between them. Each philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat, a philosopher needs two forks (left and right), creating potential race conditions and deadlocks that must be carefully managed.

## 🧠 The Problem

The Dining Philosophers Problem illustrates:
- **Race conditions** when multiple threads access shared resources
- **Deadlock prevention** strategies
- **Thread synchronization** using mutexes
- **Resource allocation** in concurrent systems

### Rules:
- Philosophers can only **eat**, **sleep**, or **think**
- To eat, a philosopher needs **both** adjacent forks
- Philosophers release both forks after eating
- If a philosopher doesn't eat within `time_to_die`, they die
- Simulation ends when a philosopher dies OR all have eaten `must_eat` times

## ✨ Features

- 🔒 **Thread-safe** implementation with proper mutex usage
- 🚫 **Deadlock prevention** using alternating fork pickup order
- ⚡ **Optimized performance** with minimal CPU usage
- 📊 **Real-time logging** of all philosopher actions
- 🎛️ **Configurable parameters** for different scenarios
- 🧪 **Edge case handling** (single philosopher, impossible scenarios)

## 🔧 Prerequisites

- **Clang** or compatible C compiler
- **POSIX threads** (pthread) library
- **Unix-like OS** (Linux, macOS)
- **Make** build system

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 📝 Arguments

| Argument | Description | Required | Range |
|----------|-------------|----------|-------|
| `number_of_philosophers` | Number of philosophers (and forks) | ✅ | 1-200 |
| `time_to_die` | Time (ms) before a philosopher dies without eating | ✅ | 60+ |
| `time_to_eat` | Time (ms) a philosopher spends eating | ✅ | 60+ |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping | ✅ | 60+ |
| `number_of_times_each_philosopher_must_eat` | Optional stopping condition | ❌ | 1+ |

## 🎮 Examples

### Basic Simulation
```bash
# 4 philosophers, die in 410ms, eat for 200ms, sleep for 200ms
./philo 4 410 200 200
```

### Limited Meals
```bash
# Each philosopher must eat exactly 5 times
./philo 5 800 200 200 5
```

### Edge Cases
```bash
# Single philosopher (should die immediately)
./philo 1 410 200 200

# Tight timing (challenging scenario)
./philo 4 310 200 100
```

## 📁 Project Structure

```
philo/
├── philo.h          # Header file with structures and function declarations
├── main.c           # Entry point, argument validation, thread management
├── init.c           # Initialization of data structures and philosophers
├── routine.c        # Main philosopher routine and lifecycle
├── actions.c        # Individual philosopher actions (eat, sleep, think)
├── monitor.c        # Death detection and simulation monitoring
├── utils.c          # Utility functions (time, printing, parsing)
├── Makefile         # Build configuration
└── README.md        # This file
```

## 🧮 Algorithm

### Deadlock Prevention Strategy
1. **Alternating Fork Order**: Even-numbered philosophers pick left fork first, odd-numbered pick right fork first
2. **Mutex Protection**: Each fork is protected by a mutex
3. **Atomic Operations**: Meal time and count updates are atomic

### Key Data Structures
```c
typedef struct s_philo {
    int              id;
    long long        last_meal;
    int              meals_eaten;
    pthread_t        thread;
    pthread_mutex_t  *left_fork;
    pthread_mutex_t  *right_fork;
    pthread_mutex_t  meal_mutex;
    t_data           *data;
} t_philo;
```

## 🔨 Building & Development

### Build Commands
```bash
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Clean rebuild
```

### Compiler Flags
- `-Wall -Wextra -Werror`: Strict error checking
- `-pthread`: Enable POSIX threads
- `-O2`: Optimization level 2

### Development Tips
- Use `valgrind` to check for memory leaks and race conditions
- Test with various argument combinations
- Monitor CPU usage during execution
- Use `helgrind` for thread analysis

## 🧪 Testing

### Basic Tests
```bash
# Test cases that should not die
./philo 1 800 200 200     # Should die (only 1 philosopher)
./philo 5 800 200 200     # Should continue indefinitely
./philo 4 410 200 200     # Balanced scenario

# Test cases with meal limits
./philo 5 800 200 200 7   # Should stop after 7 meals each
./philo 2 400 200 200 10  # Quick completion
```

### Stress Tests
```bash
# High philosopher count
./philo 200 800 200 200

# Tight timing
./philo 4 310 200 100

# Long simulation
./philo 10 800 200 200 50
```

### Validation Checklist
- ✅ No data races
- ✅ No memory leaks
- ✅ Proper error handling
- ✅ Clean program termination
- ✅ Accurate timing
- ✅ No deadlocks

## ⚠️ Common Issues

### Issue: Philosophers Die Immediately
**Cause**: `time_to_die` is too small compared to `time_to_eat`
**Solution**: Ensure `time_to_die > time_to_eat + some_buffer`

### Issue: Deadlock Occurs
**Cause**: All philosophers try to pick up forks in the same order
**Solution**: Implemented alternating fork pickup order

### Issue: Race Conditions
**Cause**: Improper mutex usage
**Solution**: All shared data access is mutex-protected

### Issue: Performance Issues
**Cause**: Busy waiting or inefficient threading
**Solution**: Uses `usleep()` for timing and minimal active waiting

## 📜 License

This project is part of the 42 School curriculum. Feel free to study and learn from it, but please respect academic integrity policies.

---

## 🎯 Learning Objectives

After completing this project, you'll understand:
- **Multithreading** concepts and implementation
- **Mutex synchronization** and deadlock prevention
- **Race condition** identification and resolution
- **POSIX threads** (pthread) library usage
- **Resource allocation** in concurrent systems
- **Performance optimization** in threaded applications

## 📚 Further Reading

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Thread Synchronization](https://www.geeksforgeeks.org/thread-synchronization-in-c/)

---

**Happy Philosophizing! 🧠✨**
