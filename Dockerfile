FROM ubuntu:bionic AS build-env

#prepare build environment
RUN apt-get update && apt-get install -y build-essential cmake ninja-build git curl unzip tar
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN git clone https://github.com/Microsoft/vcpkg.git /home/build/vcpkg
RUN /home/build/vcpkg/bootstrap-vcpkg.sh
RUN touch /home/build/vcpkg/downloads/AlwaysAllowEverything
RUN /home/build/vcpkg/vcpkg install cpprestsdk

#compile
COPY . /home/build/hello-cpprest/src/

WORKDIR /home/build/hello-cpprest/build
RUN cmake -DCMAKE_TOOLCHAIN_FILE="/home/build/vcpkg/scripts/buildsystems/vcpkg.cmake" ../src
RUN cmake --build .

#create image
FROM ubuntu:bionic

COPY --from=build-env /home/build/hello-cpprest/build/hello-cpprest /usr/hello-cpprest/

EXPOSE 8888

WORKDIR /usr/hello-cpprest

ENTRYPOINT ["./hello-cpprest"]