# API Rate Limiter

* Functional Requirements:
  * Limit the number of requests an entity can send to an API within a time window, e.g., 15 requests per second.
  * APIs are accessible through a cluster, so rate limit should be considered across different servers
  * User should get an error message when cross defined threshold within single server or across combination of servers
* Non-Functional Requirements:
  * The system should be highly available, should always work since it protects our service from external attacks
  * Our rate limiter should not introduce substantial latencies affecting the user experience.

## Architecture

* Sliding window: Keep track of each request per user, store time of request in Redis Sorted Set in ‘value’ field of hash-table

> Example

* How should we limit
  * IP: If we have to rate limit on the login API itself?
  * User: Multiple users share a single public IP like in an internet cafe or smartphone users that are using same gateway

## DB
