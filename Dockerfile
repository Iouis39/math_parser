FROM debian:11-slim

RUN apt update && \
    apt install -y cmake g++ git doctest-dev

COPY . /home/math_parser

RUN cd /home/math_parser &&  \
    mkdir -p build &&  \
    cd build &&  \
    rm -rf * &&  \
    cmake .. &&  \
    make &&  \
    make test

FROM debian:11-slim

COPY --from=0 /home/math_parser/build/math_parser-bin /usr/bin

CMD math_parser-bin
