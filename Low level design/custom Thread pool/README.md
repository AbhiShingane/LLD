Problem Statement:
    We need to design a reusable thread pool that manages a fixed number of worker threads and executes submitted tasks asynchronously


Requirments:
    Function:
        Submit tasks.
        Execute tasks asynchronously using worker thread
        Reuse thread
        gracefully shutdown.

    Non-Functional:
        low-latency
        thread safe
        no busy waiting
        Scalable


3. High Level Design

    Components:
    1. Task queue (shared)
    2. worker thread
    3. Thread pool manager


    Flow:
        Submit()->shared queue->worker thread->execute task.

4. Core Design Decisions:

    tasks representation:

        std::function<void()>

    Queue Type:
        Blocking queue with mutex and condition variable.


    Thread life cycle:
        . Thread created once
        . runs in infinite loop
        . Exit on shutdown

    
5. The issue with this current implementation is below:
    - Single shared queue - contention
    - lock bottleneck

    So, avoid this issue, the current threadpool implementaion can be converted to the work stealing thread pool which maintaines separate queue per thread + stealing from other queues if there is no work in the respective queue of worker thread.
    advantages:
        -  Less locking
        -  Better cache locality
        -  automatic load balancing


6. High level Design of Work-stealing thread pool
    components:
        1. worker threads
        2. Deque per worker thread
        3. Stealing mechanism
        4. Thread pool manager

    Flow:
      Submit() task and assigned to worker queue
      worker - pop the task in LIFO direction
      steal task from other workers if no tasks in the respective worker thread

7. Key Design Decisions:
    Operations              pop operations
    worker thread           pop from the back
    stealer thread          pop from the front

    pop from the back(worker thread) gives the better locality of reference and faster execuation.

    pop from the front(stealer thread) avoid stealing from fresh task and reduces contention.

    


    

