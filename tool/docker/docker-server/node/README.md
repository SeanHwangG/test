
```sh
# https://nodejs.org/en/docs/guides/nodejs-docker-webapp/

# 1. Build image
docker build . -t <your username>/node-web-app
docker images

REPOSITORY                      TAG        ID              CREATED
node                            14         1934b0b038d1    5 days ago
<your username>/node-web-app    latest     d64d3505b0d2    1 minute ago

# 2. Run image
docker run -p 49160:8080 -d <your username>/node-web-app
docker logs <container id>

Running on http://localhost:8080

# 3. Enter container
docker exec -it <container id> /bin/bash
docker ps

ID            IMAGE                                COMMAND    ...   PORTS
ecce33b30ebf  <your username>/node-web-app:latest  npm start  ...   49160->8080

# 4. Test connection
curl -i localhost:49160

HTTP/1.1 200 OK
X-Powered-By: Express
Content-Type: text/html; charset=utf-8
Content-Length: 12
ETag: W/"c-M6tWOb/Y57lesdjQuHeB1P/qTV0"
Date: Mon, 13 Nov 2017 20:53:59 GMT
Connection: keep-alive

Hello world
```
