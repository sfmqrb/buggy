# Dockerfile
FROM php:8.2-apache

RUN apt-get update && \
    apt-get install -y iputils-ping libsqlite3-dev pkg-config && \
    docker-php-ext-install pdo_sqlite

WORKDIR /var/www/html
COPY . /var/www/html

RUN chown -R www-data:www-data /var/www/html

EXPOSE 80
