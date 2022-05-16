# Define global arguments
ARG DEBIAN_FRONTEND=noninteractive
ARG NGINX_PATH=/usr/local/nginx
ARG OPENSSL_PATH=/usr/local/openssl
ARG MAKE_DEFINES="-j 9"					# 8 virtual cores + 1 manager
ARG SIG_ALG="dilithium3"			 		# liboqs default KEM
ARG LIBOQS_BUILD_DEFINES="-DOQS_DIST_BUILD=ON" 		# builds OQS for distribution -- when set to
								# off, builds for local machine only


FROM ubuntu:20.04 as first_stage


# Take in global arguments
ARG NGINX_PATH
ARG OPENSSL_PATH
ARG MAKE_DEFINES
ARG SIG_ALG
ARG LIBOQS_BUILD_DEFINES
ARG DEBIAN_FRONTEND



#---------- First installation stage: full build image ----------#



# Build dependencies - MUST include apt-get update before install -y
RUN apt-get update \
    && apt-get install -y gcc ca-certificates build-essential wget libpcre3 ninja-build \
       libpcre3-dev libtool zlib1g zlib1g-dev libssl-dev libperl-dev git cmake doxygen
  
      
# Get OQS sources
WORKDIR /usr/local
RUN git clone --depth 1 --branch main https://github.com/open-quantum-safe/liboqs.git \
    && git clone --depth 1 --branch OQS-OpenSSL_1_1_1-stable https://github.com/open-quantum-safe/openssl.git \ 
    && wget nginx.org/download/nginx-1.20.0.tar.gz \
    && wget http://www.openssl.org/source/openssl-1.1.1g.tar.gz \
    && tar -zxvf nginx-1.20.0.tar.gz \
    && tar -zxvf openssl-1.1.1g.tar.gz


# Build OpenSSL
WORKDIR /usr/local/openssl-1.1.1g
RUN ./config \
      --prefix=/usr/local \
      --openssldir=/usr/local/openssl \
    && make \
    && make install


# Build liboqs (static only)
#   - BUILD_SHARED_LIBS - build as static library - default = off
WORKDIR /usr/local/liboqs
RUN mkdir build-static \
    && cd build-static \
    && cmake -G"Ninja" ${LIBOQS_BUILD_DEFINES} \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_INSTALL_PREFIX=${OPENSSL_PATH}/oqs .. \
    && ninja \
    && ninja install


# Copy new conf file with correct lib paths
COPY conf /nginx-1.20.0/auto/lib/openssl/


# Build nginx-1.20.0 w/ OQS-OpenSSL
WORKDIR /usr/local/nginx-1.20.0
RUN ./configure \
      --prefix=${NGINX_PATH} \
      --with-debug \
      --with-http_ssl_module \
      --without-http_gzip_module \
      --with-http_stub_status_module \
      --with-openssl=/usr/local/openssl \
      --modules-path=/etc/nginx/modules \
      --with-cc-opt="-I${OPENSSL_PATH}/oqs/include" \
      --with-ld-opt="-L${OPENSSL_PATH}/oqs/lib" \
    && sed -i "s/libcrypto.a/libcrypto.a -loqs/g" objs/Makefile \
    && make ${MAKE_DEFINES} \
    && make install


RUN apt-get purge build-essential -y \
    && apt-get autoremove -y


# Generate:
#   - CA key and cert
#   - server CSR
#   - server cert
WORKDIR ${NGINX_PATH}


# Generate generically named cert, key
RUN set -x \
    && mkdir cacert \
    && mkdir pki \
    && ${OPENSSL_PATH}/apps/openssl req -x509 -new \
      -newkey ${SIG_ALG} \
      -keyout CA.key \
      -out cacert/CA.crt -nodes -subj "/CN=localhost" -days 365 \
      -config ${OPENSSL_PATH}/apps/openssl.cnf \
    && ${OPENSSL_PATH}/apps/openssl req -new \
      -newkey ${SIG_ALG} \
      -keyout pki/server.key \
      -out server.csr \
      -nodes \
      -subj "/CN=oqs-nginx" \
      -config ${OPENSSL_PATH}/apps/openssl.cnf \
    && ${OPENSSL_PATH}/apps/openssl x509 -req \
      -in server.csr \
      -out pki/server.crt \
      -CA cacert/CA.crt \
      -CAkey CA.key \
      -CAcreateserial \
      -days 365

# Generate named dilithium3 cert, key
#RUN set -x \
#    && mkdir cacert \
#    && mkdir pki \
#    && ${OPENSSL_PATH}/apps/openssl req -x509 -new \
#      -newkey ${SIG_ALG} \
#      -keyout ${SIG_ALG}_CA.key \
#      -out cacert/${SIG_ALG}_CA.crt -nodes -subj "/CN=localhost" -days 365 \
#      -config ${OPENSSL_PATH}/apps/openssl.cnf \
#    && ${OPENSSL_PATH}/apps/openssl req -new \
#      -newkey ${SIG_ALG} \
#      -keyout pki/${SIG_ALG}_srv.key \
#      -out ${SIG_ALG}_srv.csr \
#      -nodes \
#      -subj "/CN=oqs-nginx" \
#      -config ${OPENSSL_PATH}/apps/openssl.cnf \
#    && ${OPENSSL_PATH}/apps/openssl x509 -req \
#      -in ${SIG_ALG}_srv.csr \
#      -out pki/${SIG_ALG}_srv.crt \
#      -CA cacert/${SIG_ALG}_CA.crt \
#      -CAkey ${SIG_ALG}_CA.key \
#      -CAcreateserial \
#      -days 365



#---------- Second installation stage: create minimal image without build tooling ----------#



FROM ubuntu:20.04


# Take in global arguments
ARG NGINX_VERSION
ARG NGINX_PATH
ARG OPENSSL_PATH
ARG SIG_ALG
ARG LIBOQS_BUILD_DEFINES


# Build dependencies - MUST include apt-get update before install -y
RUN apt-get update \
    && apt-get install -y libpcre3 libpcre3-dev


# Only retain the ${*_PATH} contents in the final image
COPY --from=first_stage ${NGINX_PATH} ${NGINX_PATH}
COPY nginx-conf/ ${NGINX_PATH}/nginx-conf


WORKDIR ${NGINX_PATH}


# Redirect nginx request and error logs to docker log collector
RUN ln -sf /dev/stdout ${NGINX_PATH}/logs/access.log \
    && ln -sf /dev/stderr ${NGINX_PATH}/logs/access.log


# Expose port listed in nginx.conf
EXPOSE 4433


# Ensure nginx just runs
ENV PATH ${NGINX_PATH}/sbin:$PATH


STOPSIGNAL SIGTERM


# Enable user permissions to create new server keys off current CA
#   - '-g', '--uuid' : defines group/user ID = 1000
#   - '-s' : makes group/user in system
RUN addgroup --system --gid 1000 dev \
    && adduser --system --ingroup dev --uid 1000 dev  \
    && chown -R dev.dev ${NGINX_PATH}


USER dev


CMD ["nginx", "-c", "nginx-conf/nginx.conf", "-g", "daemon off;"]
