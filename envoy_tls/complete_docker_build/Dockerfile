# Define global arguments
ARG DEBIAN_FRONTEND=noninteractive
ARG OPENSSL_PATH=/usr/local/openssl
ARG MAKE_DEFINES="-j 9"					  # 8 virtual cores + 1 manager


FROM ubuntu:20.04 as first_stage


# Take in global arguments
ARG DEBIAN_FRONTEND
ARG OPENSSL_PATH
ARG MAKE_DEFINES


#---------- First installation stage: full build image ----------#



# Build base dependencies - MUST include apt-get update before install -y
RUN apt-get update \
    && apt-get install -y cmake gcc ninja-build libunwind-dev pkg-config python3 python3-pip python3-psutil \
      golang-go libtool libssl-dev make git autoconf automake unzip patch virtualenv docker-compose jq \
      wget libpcre3 ninja-build libpcre3-dev zlib1g zlib1g-dev libperl-dev doxygen


# Get sources for /usr/local
WORKDIR /usr/local
RUN git clone --branch main --single-branch --depth 1 https://github.com/open-quantum-safe/liboqs.git \
    && git clone --depth 1 --branch OQS-OpenSSL_1_1_1-stable https://github.com/open-quantum-safe/openssl.git \
    && git clone --branch release/v1.21 --single-branch https://github.com/envoyproxy/envoy.git \
    && wget http://www.openssl.org/source/openssl-1.1.1g.tar.gz \
    && tar -zxvf openssl-1.1.1g.tar.gz


# Build OpenSSL
WORKDIR /usr/local/openssl-1.1.1g
RUN ./config \
      --prefix=/usr/local \
      --openssldir=/usr/local/openssl \
    && make -j \
    && make install


# Build liboqs (static only) into openssl-oqs fork
#   - BUILD_SHARED_LIBS - build as static library - default = off
WORKDIR /usr/local/liboqs
RUN mkdir build-static \
    && cd build-static \
    && cmake -G"Ninja" \
      -DOQS_DIST_BUILD=ON \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_INSTALL_PREFIX=${OPENSSL_PATH}/oqs .. \
    && ninja \
    && ninja install


# Finish openssl-liboqs install
WORKDIR /usr/local/openssl
RUN ./Configure no-shared linux-x86_64 -lm \
    && make -j


RUN apt-get purge build-essential -y \
    && apt-get autoremove -y


# Generate self-signed certificates for tls endpoint
WORKDIR /etc/example/certs
RUN ${OPENSSL_PATH}/apps/openssl req -x509 \
      -newkey rsa:2048 \
      -keyout front-proxy-key.pem \
      -out front-proxy-crt.pem \
      -days 3650 \
      -nodes \
      -subj "/CN=front-envoy" \
      -config /usr/local/openssl/openssl.cnf



#---------- Second installation stage: minimal build image ----------#



FROM envoyproxy/envoy:v1.21.2


COPY ./envoy-https-http.yaml /etc/envoy.yaml


WORKDIR /etc/example
COPY --from=first_stage /etc/example/certs/ /etc/example/certs/
RUN chmod go+r /etc/example/certs/front-proxy-crt.pem
RUN chmod go+r /etc/example/certs/front-proxy-key.pem
RUN chmod go+r /etc/envoy.yaml


CMD ["/usr/local/bin/envoy", "-c /etc/envoy.yaml"]
