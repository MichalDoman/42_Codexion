*This project has been created as part of the 42 curriculum by mdomansk.*

# Codexion
## Description

Codexion is a multithreaded simulation.
The program simulates a group of coders competing for shared dongles. Each coder requires two dongles to compile. After compiling, the coder proceeds through debugging and refactoring before attempting to compile again.

The goal of the project is to practice concurrent programming in C using POSIX threads, mutexe and condition variables, priority queues.

The simulation supports two schedulings:

- **FIFO** — coders acquire dongles according to the order in which they entered the queue.
- **EDF** — coders with the earliest burnout deadline receive higher priority.

Each dongle also has a cooldown period after being released. During this period, it cannot be acquired by another coder.

The simulation ends when:
- one coder burns out, or
- every coder completes the required number of compilations.

## Instructions

### Compilation

To compile the project run:

```
make
```

This will create an executable **./codexion**.

Other available Makefile rules:

- **make clean** — removes object files
- **make fclean** — removes object files and the executable
- **make re** — rebuilds the project

### Execution

Run the program with:

```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Arguments:

- **number_of_coders** — number of coders and dongles
- **time_to_burnout** — maximum time in milliseconds between the starts of two compilations
- **time_to_compile** — compilation duration in milliseconds
- **time_to_debug** — debugging duration in milliseconds
- **time_to_refactor** — refactoring duration in milliseconds
- **number_of_compiles_required** — number of compilations each coder must complete
- **dongle_cooldown** — time in milliseconds during which a released dongle is unavailable
- **scheduler** — scheduling strategy: **fifo** or **edf**

### Example

```
./codexion 5 800 200 200 200 3 100 fifo
```

Example output:

    0 1 has taken a dongle
    0 1 has taken a dongle
    0 1 is compiling
    200 1 is debugging
    400 1 is refactoring

Each output line contains:

- the timestamp in milliseconds since the simulation started,
- the coder identifier,
- the current coder action.

## Program overview

Each coder repeatedly performs the following cycle:

1. Enter the queues of the required dongles.
2. Wait until both dongles can be acquired.
3. Start compiling.
4. Release both dongles after compilation.
5. Debug.
6. Refactor.
7. Attempt to acquire the dongles again.

The monitor thread continuously checks:

- whether any coder has exceeded the burnout deadline,
- whether every coder has completed the required number of compilations.

When one of these conditions is met, the monitor stops the simulation and wakes all threads waiting on condition variables.

## Blocking cases handled

Deadlocks are prevented by manipulating the order, in which donles are locked by coders. Odd-numbered coders take the right dongle first, while even-numbered coders take the left one. This breaks the circular wait condition.

Starvation is prevented through queues for each donlge that are heap based. FIFO prioritizes by the order of coders requesting the dongle, while EDF coders with the earliest burnout deadline.

Dongle cooldown is handled with **pthread_cond_timedwait**, allowing threads to sleep until the resource becomes available.

Burnout is detected by a monitor thread using each coder's last compilation start time. Shared timestamps and counters are protected by a mutex.

Logging is serialized with a log_mutex, preventing mixed output and ensuring the burnout message is always the final log.

When simulation stops all waiting condition are broadcast. All threads, are joind, conds and mutexex are destroyed, and all resouces free properly.

## Thread synchronization mechanisms

The project uses **pthread_mutex_t** and **pthread_cond_t** to manage access to shared resources.

Each dongle has its own mutex and condition variable that protects variables like cooldown time, priority queue and FIFO counter. A coder can acquire a dongle only after locking its mutex and after verifying that the dongle is available and that the coder is first in the queue.

A simulation mutex protects the running state, compilation counters and last compilation timestamps.

A logging mutex serializes output, and a start mutex and condition variable ensure that all threads begin with the same simulation start time.

Condition variables are used to wait for occupied dongles, queue priority changes, cooldown completion and simulation shutdown. All conditions are checked in loops to safely handle spurious wakeups.

The monitor, when simulation needs to stop, changes the running state and broadcasts all dongle condition variables, allowing wainting coder threads to wake up and exit.

## Heap

The heap was implemented as a separate module, independent of Codexion.

It can be initialized as either a minimum heap or a maximum heap by passing the 0 or 1 flag to **heap_init** and its maximum size can be configured during initialization as well.

Each heap item contains a coder_id and a priority value. When two items have the same priority, the coder_id is used as a tie-breaker.

The heap used by dongle queues is a minimum heap.

## Resources

Resources used while working on the project:

- POSIX Threads documentation
- Linux manual pages
- Materials about binary heaps and priority queues
- Other 42 students

### Use of AI

AI was used as a supporting tool during development.

It was used for:
- teaching how to use mutex and condition-variables,
- checking cleanup lines,
- improving naming and code readability,
- preparing the initial structure of this README.
