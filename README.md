# Philosophers
Summary: In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

# Description
1- Five philosophers are sitting at a rounded dining table.

2- There is one chopstick between each pair of adjacent philosophers.

3- Philosophers are either thinking or eating.

4- Whenever a philosopher wishes to eat, she first needs to find two chopsticks.

5- If the hungry philosopher does not have two chopsticks (i.e. one or two of her neighbors already picked up the chopstick) she will have to wait until both chopsticks are available.

6- When a philosopher finishes eating, she puts down both chopsticks to their original places, and resumes thinking.

7- There is an infinite amount of food on their plate, so they only need to worry about the chopsticks.

# There are a few conditions:
1.Philosophers are either thinking or eating. They do not talk to each other.

2.Philosophers can only fetch chopsticks placed between them and their neighbors.

3.Philosophers cannot take their neighbors’ chopsticks away while they are eating.

4.Hopefully no philosophers should starve to death (i.e. wait over a certain amount of time before she acquires both chopsticks).


| function        | Description
|-----------------|--------------------------------------------------------|
| gettimeofday    | is a function for obtaining the current time. It is defined in the header file sys/time.h and provides the time with microsecond resolution.
|                 |                                                                                                                             |
| pthread_join.   |  function allows a calling thread to block and wait for the termination of another thread                                   | 


# External functs
free

write

printf

memset

malloc

usleep

gettimeofday

pthread_join

pthread_create

pthread_detach

pthread_mutex_init

pthread_mutex_lock

pthread_mutex_unlock

pthread_mutex_destroy

# pthread_mutex_lock
locks the given mutex. If the mutex is currently unlocked, it becomes locked and owned by the calling thread, and pthread_mutex_lock returns immediately. If the mutex is already locked by another thread, pthread_mutex_lock suspends the calling thread until the mutex is unlocked.
