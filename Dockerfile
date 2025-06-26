# Dockerfile
FROM ubuntu:20.04

# Install build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
      build-essential cmake

WORKDIR /app
COPY . /app

# Build and run tests; tests are expected to fail
RUN g++ -std=c++17 kvstore.cpp test_kvstore.cpp -o test_kv

CMD ["./test_kv"]

