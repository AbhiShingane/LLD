Rate Limiter is one of the most frequently asked LLD problems in FAANG interviews.

1. Requirement Clarfication:

Functional

    Limit number of requests per user/API key/IP

    Example: 100 requests per minute per user

    Return:

        Allow request

        Reject request (429 Too Many Requests)

Non-Functional

    Low latency (critical path)

    High throughput

    Thread-safe

    Scalable (millions of users)

2. Main APIs to Expose

        class IRateLimiter {
        public:
            virtual bool allowRequest(const std::string& key) = 0;
            virtual int getRemainingQuota(const std::string& key) = 0;
            virtual void reset(const std::string& key) = 0;
            virtual ~IRateLimiter() = default;
        };


Key design decisions:

    - key = userId / IP / API key

    - Stateless interface, state managed internally


3. Which Rate Limiting Algorithm to Use?

    a) Fixed Window counter:
        Count requests per window (e.g., per minute)

        Problem: Burst at window boundary

    
    b) Sliding Window Log

        Store timestamps of each request

        Remove old timestamps

        Accurate but Memory heavy

    c) Sliding Window Counter
        Combine current + previous window

            Balanced
            Less memory
            Interview favorite

    d) Token Bucket:

        Handles bursts
        Smooth rate limiting
        Widely used in real systems
        We will be using Token Bucket.

    
5. Data Structures

    PER USER/ PER BUCKET:

    struct TokenBucket {
    int capacity;
    double tokens;
    double refillRate; // tokens per second
    std::chrono::steady_clock::time_point lastRefillTime;
    std::mutex mtx;
    };

    Storage:

    std::unordered_map<std::string, TokenBucket> buckets;


