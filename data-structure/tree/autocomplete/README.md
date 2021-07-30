# README

* Functional: As user types query, our service should suggest top 10 terms starting with whatever user has typed
* Non-function: Suggestions should appear in real-time. User should be able to see the suggestions within 200ms

## Database

* Per data
  * 100 million * 30 bytes => 3 GB
* Per year
  * 3GB + (0.02 \* 3 GB \* 365 days) => 25 GB

> Question

* What will happen when a trie server goes down?
  * primary-secondary configuration; if primary dies, secondary can take over after failover
  * Any server that comes back up, can rebuild trie based on last snapshot
* Permanent storage?
  * Take a snapshot of our trie periodically and store it in a file, rebuild if server goes down

## Architecture

* Add and subtract frequencies based on Exponential Moving Average (EMA) of each term
* Find top suggestion traverse the sub-tree under it
  * Can we store top suggestions with each node? This can surely speed up our searches but will require extra storage
  * We can store top 10 suggestions at each node that we can return to the
* log every 1000th query
* Map-Reduce (MR) set-up to process all the logging data periodically say every hour

> Qustion

* Optimize
  * The client should only try hitting the server if the user has not pressed any key for 50ms.
  * Client can cancel the in-progress requests
  * Can store the recent history of suggestions locally. Recent history has a very high rate of being reused
  * Establishing an early connection with the server
  * Server can push some part of their cache to CDNs and Internet Service Providers (ISPs) for efficiency
* Filtering for inappropriate words
  * Filtering layer on each server which will remove any such term before sending them to users
* Can we store top suggestions with each node?
  * Speed up our searches but will require a lot of extra storage. Store top 10 suggestions at each node
* How to update the trie?
  * Update our trie offline after a certain interval.
  * Exponential Moving Average (EMA) of each term. In EMA, we give more weight to the latest data

## Future work

* Personalization
  * Users will receive some typeahead suggestions based on their historical searches, location, language, etc
  * We can store the personal history of each user separately on the server and also cache them on the client
  * The server can add these personalized terms in the final set before sending it to the user
  * Personalized searches should always come before others.
