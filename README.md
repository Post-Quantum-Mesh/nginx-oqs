# Post-Quantum Prototype Layer 7 Proxy

Open source implementation of quantum-resistant encryption algorithms for modular TLS communication

- [Components](https://github.com/Post-Quantum-Mesh/nginx-oqs#components)
- [Overview](https://github.com/Post-Quantum-Mesh/nginx-oqs#overview)
  - [L7 Proxy](https://github.com/Post-Quantum-Mesh/nginx-oqs#l7-proxy)
- [Quick Start](https://github.com/wsu-cpts421-sp22/f5-quantum/tree/main#quick-start)
  - [Local Environment Setup](https://github.com/Post-Quantum-Mesh/nginx-oqs#local-environment-setup)
  - [TLS Demo](https://github.com/Post-Quantum-Mesh/nginx-oqs#tls-demo)

## Components

### Quantum-Resistant Library/TLS Protocol
- [liboqs](https://github.com/open-quantum-safe/liboqs)
- [openssl-liboqs fork](https://github.com/open-quantum-safe/openssl)
- [openssl-1.1.1](https://github.com/openssl/openssl/tree/OpenSSL_1_1_1-stable)


### NGINX Build
- [nginx-1.20.0 open source](https://github.com/nginx/nginx/tree/branches/stable-1.20)


## Overview

### NGINX-OQS L7 Proxy

![NGINX TLS Handshake Diagram](https://drive.google.com/uc?id=1hASfFvcxFHRVDw9Yi2F1NEN0hPWkRAAN)

## Quick Start

### Local Environment Setup

Note: ./configure commands followed by indented parameters (ex: ./configure --prefix=/usr/local) are all one-line commands

1. Update package manager

        apt update

2. Install Dependencies and Compiler

        apt-get update
        apt-get install -y gcc build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev libgd-dev \
          libxml2 libxml2-dev uuid-dev astyle doxygen zlib1g zlib1g-dev liperl-dev wget make git autoconf \
          automake unzip patch virtualenv docker-compose jq libunwind-dev pkg-config python3 python3-pip python3-psutil

3. Install bazelisk as bazel (paths use /usr/local, modify to your desired directory)

        wget -O /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-$([ $(uname -m) = "aarch64" ] && echo "arm64" || echo "amd64")
        chmod +x /usr/local/bin/bazel

4. Install PCRE

        wget https://github.com/PhilipHazel/pcre2/releases/download/pcre2-10.39/pcre2-10.39.tar.gz
        tar -xzf pcre2-10.39.tar.gz
        cd pcre2-10.39
        ./configure
        make
        make install

5. Install zlib

        wget http://zlib.net/zlib-1.2.12.tar.gz
        tar -xzf zlib-1.2.12.tar.gz
        cd zlib-1.2.12
        ./configure
        make
        make install
	
6. Install OpenSSL

        wget http://www.openssl.org/source/openssl-1.1.1g.tar.gz
        tar -xzf openssl-1.1.1g.tar.gz
        cd openssl-1.1.1g
        ./config
        make
        make install

7. Install OQS-OpenSSL Fork (with liboqs) - < DIR > is a directory of your choosing (ex: /usr/local) - < OPENSSL_DIR > is the liboqs-openssl fork directory

        cd <DIR>
        git clone --branch OQS-OpenSSL_1_1_1-stable https://github.com/open-quantum-safe/openssl.git
        git clone --branch main https://github.com/open-quantum-safe/liboqs.git
        cd liboqs
        mkdir build
        cd build
        cmake -GNinja -DCMAKE_INSTALL_PREFIX=< OPENSSL_DIR >/openssl/oqs ..
        ninja
        ninja install
        cd ..
        cd <OPENSSL_DIR>
        ./config --openssldir=/usr/local/ssl
        make

9. Install NGINX Stable From Source (currently using stable 1.20.2)

        wget http://nginx.org/download/nginx-1.20.2.tar.gz 
        tar -xzf nginx-1.20.2.tar.gz
        cd nginx-1.20.2
        ./configure
	    --prefix=/usr/local/nginx
	    --sbin-path=/usr/sbin/nginx
	    --with-debug
	    --with-pcre
	    --with-zlib=/usr/local/zlib-1.2.12
	    --without-http_gzip_module
	    --with-http_stub_status_module
	    --with-http_ssl_module
	    --modules-path=/etc/nginx/modules
	    --with-cc-opt="-I/usr/local/openssl/oqs/include"
	    --with-ld-opt="-L/usr/local/openssl/oqs/lib"
        sed -i "s/libcrypto.a/libcrypto.a -loqs/g" objs/Makefile
        make
        make install

10. Verify Installation

        nginx -V

## TLS Demo

### Startup TLS Server:

Open one terminal and run the following command:

    ./init.sh
	
The following commands will be run by the shell script:

    sudo docker build -t tls-test-img .
    sudo docker network create test_net
    sudo docker run --network test_net --name tls-test-img -p 4433:4433 tls-test-img
	
### Query TLS Server:

In a second terminal, run the following command:
	
    ./query.sh

The following command retrieves the [curl](https://hub.docker.com/r/openquantumsafe/curl) image enabled with quantum-safe crypto operations. It can be used to retrieve data from any OQS-enabled TLS1.3 server as follows:

    sudo docker run --network test_net -it openquantumsafe/curl curl -k https://tls-test-img:4433 -e SIG_ALG=dilithium3

### Terminate TLS Server:

In a second terminal, run the following command:
    
    ./kill.sh

The following commands will be run by the shell script:

    sudo docker kill tls-test-img
    sudo docker container prune -f
    sudo docker network prune -f

### Benchmarking:

Simple performance metrics can be retrieved from the SSL/TLS handshake using openSSL's s_time function. In a second terminal, run the following command:

    ./test.sh -t <TEST_TIME> -s <SIG_ALG>
    
The flags -s and -t allow for passing parameters to the performance test script. TEST_TIME (default = 10) dictates how long (in seconds) that connections are established. SIG_ALG (default = dilithium3) dictates which quantum-safe cryptographic signing should be used. It is not advised to change the SIG_ALG without first changing the Dockerfile for the TLS/SSL server -- it uses dilithium3 as a default.
