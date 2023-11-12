FROM alpine:latest

RUN apk update && \
    apk add --no-cache git g++ libgomp

WORKDIR /app

RUN git clone https://github.com/KATEHOK/parvpo_1.git && \
    cd parvpo_1 && \
    g++ -fopenmp lab1.cpp -o lab1_executable

CMD ["./parvpo_1/lab1_executable"]

# docker build --no-cache -t my-alpine:latest .