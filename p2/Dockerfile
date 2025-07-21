FROM php:8.2-apache

# Install required system packages for sqlite3
RUN apt-get update && \
    apt-get install -y libsqlite3-dev pkg-config && \
    docker-php-ext-install pdo_sqlite

WORKDIR /var/www/html
COPY . /var/www/html
# Allow Apache (www-data) to create/write data.db at runtime
RUN chown -R www-data:www-data /var/www/html

EXPOSE 80

