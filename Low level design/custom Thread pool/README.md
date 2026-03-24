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

    


