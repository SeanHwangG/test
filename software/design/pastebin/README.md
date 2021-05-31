# Requirement

## Functional

* Users should be able to upload or “paste” their data and get a unique URL to access it
* Users will only be able to upload text
* Data and links will expire after a specific timespan automatically; users can specify expiration time
* Users should optionally be able to pick a custom alias for their paste

## Non-Functional

* The system should be highly reliable, any data uploaded should not be lost
* The system should be highly available → If our service is down, users can’t access their Pastes
* Users should be able to access their Pastes in real-time with minimum latency
* Paste links should not be guessable (not predictable)

## Extended

* Analytics, e.g., how many times a paste was accessed?
* Our service should also be accessible through REST APIs by other services
