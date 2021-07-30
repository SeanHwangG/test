# Security

> Terms

* Mac filtering: only allow for connections from a specific set of MAC addresses belonging to devices you trust

* WEP (Wired equivalent privacy): Web uses 40 bit for encryption keys → cracked in few minutes
  * Wi-Fi Protected Access uses 128 bits for encryption keys
  * WPA2 uses 256 bits for keys
  * Encryption technology that provides a very low level of privacy
* OWASP: produces free articles, methodologies, documentation, tools, and technologies in web application security
  * Open Web Application Security Project is an online community

{% tabs %}
{% tab title='amazon' %}

![GuardDuty](images/20210504_183239.png)

* GuardDuty is a threat detection service that continuously monitors for malicious activity and unauthorized behavior
* to protect your AWS accounts, workloads, and data stored in S3

{% endtab %}
{% endtabs %}

## Firewall

* Filtering access control list
  * Port number: [ex] only DNS server of a company should receive UDP segments whose destination port is set to 53
  * Host-based: [ex] black lists
  * Network-based
* external interface connected to the global Internet
* internal interface connected to a trusted network

> Term

* dmz: physical, logical subnetwork that contains, exposes organization's external-facing services to untrusted network
  * Add additional layer of security to an organization's LAN

* Network-based: Hardware based and generally deployed on network
  [+] Easy to scale and simple to maintain
* Host-based: deployed on end-systems
* Stateless: doesn't maintain state of flows passing through
* Stateful: See first packet in flow that is allowed by the configured security rules it creates a session state for it
  * [+] Filtering is more efficient

{% tabs %}
{% tab title='shell' %}

* ufw: Uncomplicated firewall for linux ([ex] default)
  * status
  * allow/deny: [ex] port 22, outgoing, incoming
  * disable: disable firewall
  * enable: enable firewall

* Mac
  ![Settings](images/20210628_174309.png)

{% endtab %}
{% endtabs %}

### NAT

![NAT](images/20210316_154232.png)

* Network address translation allows a gateway (router, firewall) to rewrite source IP of outgoing IP datagram
* retaining the original IP in order to rewrite it into the response
* to solve IPv4 exhaustion by using non-routable address space in the late 80s to early 90s
* One to many NAT masquerade IP
* [-] Not easily possible for external hosts to open TCP connections with hosts behind NAT
* [-] NAT breaks the end-to-end transparency of the network

> Term

* TURN: Traversal using relays around nat allows host to control relay operation, exchange packets with peers using relay
  * If host is behind NAT, then it might be impossible for that host to communicate directly with peers
  * In these situations, it's necessary for host to use services of intermediate node that acts as communication relay
  * Designed to be used as part of the ICE (Interactive Connectivity Establishment
* STUN: Relay Extensions to Session Traversal Utilities for NAT
  * allows NAT clients ([ex] IP Phones behind a firewall) to set up phone calls to VoIP provider hosted outside
* ICE: candidate Internet Connectivity Establishment configuration which may be used to establish an RTCPeerConnection
* Signaling Server: server that manages the connections between devices ([ex] one user to find another in network)
* TURN server: Traversal Using Relay NAT, is protocol for relaying network traffic
  * Most WebRTC apps to function, server that relays traffic between peers is required
  * Since a direct socket is often not possible between clients

> Reference

<https://datatracker.ietf.org/doc/html/rfc5766>

## XSS

* Cross-site Scripting attack: aka XSS attack, a malicious script is added to a website
  * Installing browser-based Keyloggers to capture keystrokes of the victim
  * Capturing session cookies of the user, which can be used to trigger some other kind of attack, like a CSRF attack
  * Redirecting users to other malicious websites
  * inputs are validated before they are stored into the database
  ![Stored Cross-site Scripting Attack](images/20210628_180902.png)

* Reflected Cross-site Scripting Attack: attacker tricks user into clicking a link that contains the malicious script
  ![Reflected Cross-site Scripting Attack](images/20210628_180925.png)

## DOS

* denial of service attack is attacker tries to crash app so that legitimate users are not able to access app
* main purpose of this attack is to harm an organization
* first DoS attack was done by 13-year old David Dennis in 1974

## JWT

![JWT](images/20210628_204554.png)

* Store user information in encrypted format which can be stored on client side

1. The client sends a request to the server with a username/password
1. The application validates the credentials and generates a secure, signed token for the client
1. The token is sent back to the client and stored there
1. When the client needs to access something new on the server, it sends the token through the HTTP header.
1. The server decodes and verifies the attached token. If it is valid, the server sends a response to the client.
1. When the client logs out, the token is destroyed.

* [+] more secure than cookies and scalable as server does not store any client information
* [+] token generation process can be done on a separate server or by a different company

> Term

* HMAC: Hashing for Message Authentication code
  ![HMAC](images/20210628_204915.png)

* Payload
  * iss: identifies principal that issued JWT
  * sub: identifies principal that is subject of JWT
  * aud: identifies recipients that JWT is intended for
  * exp: identifies expiration time at or after which JWT MUST NOT be accepted for processing
  * nbf: identifies time before which JWT MUST NOT be accepted for processing
  * iat: identifies time at which JWT was issued
  * jti: The JWT ID is a unique identifier for the JWT

## Oauth

![Oauth](images/20210628_181429.png)

* 2.0 focuses on client developer simplicity while providing specific authorization flows for web, desktop, IoT apps

### OpenID

* extension of OAuth
* Identity token
  * iss - Client must validate that the issuer of this token is the Authorization Server.
  * aud - Client must validate that the token is meant for the client itself.
  * exp - Client must validate that the token is not expired

## TLS

* Transport layer security, successor of the now-deprecated Secure Sockets Layer (SSL)
* also authenticate server, client and encrypts data

### HTTPS

* Use port 443 with SSL-encrypted message body
* uses the private and public keys encryption method to encrypt the communication between website and server
* [+] protected from man-in-the-middle attacks, including the session hijacking
* [-] virtual hosts cannot be used with SSL ([ex] shared hosting or running multiple sites on the same server)
* [-] Speed: require SSL handshakes to establish the connection -> subsequent connections are faster so not much issue

> Terms

* Certificate
  * Domain validated: cheap (50$) but do not verify as much information as their counterparts ([ex] let's encrypt)
  * Extended Validation: validate you as domain’s owner and verify identity and legitimacy of domain owner
* /usr/bin/ssl/yourApp.key: RSA Key
* /usr/bin/ssl/yourApp.csr: certificate signing request

> Reference

<https://letsencrypt.org/>

### SSL

* Certificate: used to authenticate the identity of a website
* Certified Authors: GlobalSign, Cloud Flare (Free), Comodo (Paid/Free), GeoTrust (Free Trial), DigiCert
* Openssl: Transport Layer Security
  * uses systemwide default certificate store /etc/ssl/certs

{% tabs %}
{% tab title='shell' %}

* openssl
  * genrsa -out yourApp.key 1024
  * req -new -key yourApp.key -out yourApp.csr
  * -showcerts
  * -verify
  * connect: [ex] exampleserver.com:443

```sh
/private/etc/ssl/openssl.cnf
```

{% endtab %}
{% endtabs %}

> Reference

<badssl.com>

## Wireless

* WEP: wired equivalent privacy is earlieset wireless security protocol, 40 bit encryption key is easily hackable
* WPA: wifi-protected access, uses TKIP (temporal key integrity protocol) has some vulnerability
* WPA2: adopted by US govnernment, require to use stronger encryption uses AES (advanced encryption stnadard)
  * Some allows mixed options with WPA for compatibility with risk
* WPA3: introduced 2018, increased protections from password guessing
* WPS: Designed to make as easy as possible for devices to join a secrue wireless
