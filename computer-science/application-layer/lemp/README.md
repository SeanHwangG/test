# README

* [Source](https://www.youtube.com/watch?v=f1iJCj-gCB8)

```sh
# 1. LP setup
sudo apt update
sudo apt install nginx
sudo apt install php-fpm php-mysql
sudo nginx -t  # Test nginx configuration
sudo service nginx restart

# 2. MySQL setup
sudo apt install mysql-server-5.7
sudo mysql_secure_installation  # y, 0, password, password, y...
sudo mysql

CREATE USER 'mayanksanghvi'@'localhost' IDENTIFIED BY 'P@$$w0rd';
GRANT ALL PRIVILEGES ON *.* TO 'mayanksanghvi'@'localhost'
  REQUIRE NONE WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0
  MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;
```
