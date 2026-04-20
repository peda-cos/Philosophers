*This project has been created as part of the 42 curriculum by peda-cos.*

# Philosophers

## Description

This project is an implementation of the classic **Dining Philosophers Problem**, a concurrency thought experiment introduced by Edsger Dijkstra. A number of philosophers sit at a round table with a bowl of spaghetti in the middle. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must pick up two forks (one on each side). The challenge is to avoid deadlocks and starvation while ensuring all philosophers can eat.

The project is split into two parts:
- **philo** (mandatory): uses POSIX threads and mutexes to simulate the problem.
- **philo_bonus** (optional): uses processes and semaphores instead.

The goal is to understand and apply synchronization primitives, avoid race conditions, and reason carefully about concurrent execution.

## Instructions

### Compilation

```bash
# Compile the mandatory part
make -C philo

# Compile the bonus part
make -C philo_bonus
```

### Execution

```
./philo/philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

```
./philo_bonus/philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms before a philosopher dies if they haven't eaten |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

**Example:**
```bash
./philo/philo 5 800 200 200
./philo/philo 4 410 200 200 5
```

### Cleanup

```bash
make -C philo fclean
make -C philo_bonus fclean
```

## Resources

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex — Linux man pages](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [sem_overview — Linux man pages](https://man7.org/linux/man-pages/man7/sem_overview.7.html)

**AI Usage Disclosure:** AI assistance (GitHub Copilot / Claude) was used during the development of this project for code suggestions, debugging guidance, and documentation drafting, in accordance with 42 school's policy on AI tool usage.
