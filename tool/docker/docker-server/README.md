# Docker Server

```sh
""" 1. Docker """
# https://docs.docker.com/samples/django/
# Create the Django project project (make sure have correct ownership)
sudo docker-compose run web django-admin startproject composeexample .

ls -l
total 32
-rw-r--r--  1 user  staff  145 Feb 13 23:00 Dockerfile
drwxr-xr-x  6 user  staff  204 Feb 13 23:07 composeexample
-rw-r--r--  1 user  staff  159 Feb 13 23:02 docker-compose.yml
-rwxr-xr-x  1 user  staff  257 Feb 13 23:07 manage.py
-rw-r--r--  1 user  staff   16 Feb 13 23:01 requirements.txt

docker-compose up

# Check status
$ docker ps

CONTAINER ID  IMAGE       COMMAND                  CREATED         STATUS        PORTS                    NAMES
def85eff5f51  django_web  "python3 manage.py..."   10 minutes ago  Up 9 minutes  0.0.0.0:8000->8000/tcp   django_web_1
678ce61c79cc  postgres    "docker-entrypoint..."   20 minutes ago  Up 9 minutes  5432/tcp                 django_db_1

# Close
docker-compose down
Stopping django_web_1 ... done
Stopping django_db_1 ... done
Removing django_web_1 ... done
Removing django_web_run_1 ... done
Removing django_db_1 ... done
Removing network django_default

""" 2. Node """
# https://nodejs.org/en/docs/guides/nodejs-docker-webapp/

# Build / Run image
docker build . -t <your username>/node-web-app
docker images
docker run -p 49160:8080 -d <your username>/node-web-app
docker logs <container id>

Running on http://localhost:8080

# Enter container
docker exec -it <container id> /bin/bash
docker ps

ID            IMAGE                                COMMAND    ...   PORTS
ecce33b30ebf  <your username>/node-web-app:latest  npm start  ...   49160->8080

# Test connection
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
