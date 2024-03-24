FROM alpine:3.19

RUN apk update && apk add --no-cache build-base valgrind

ENV DOCKER=1

WORKDIR	/app

COPY . .

RUN make && make test

CMD ["valgrind", "./test.run"]
