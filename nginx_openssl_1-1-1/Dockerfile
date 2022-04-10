FROM ubuntu:20.04
LABEL Vendor="NGINX openssl1.1.1j"

# Install packages
RUN apt-get update && apt-get install -y gcc ca-certificates build-essential wget libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev libperl-dev

# Compile OpenSSL
ENV OPENSSL_VERSION ${OPENSSL_VERSION:-1_1_1j}
RUN wget http://www.openssl.org/source/openssl-1.1.1g.tar.gz \
  && tar -xvzf openssl-1.1.1g.tar.gz \
  && cd openssl-1.1.1g \
  && ./config \
    --prefix=/usr/local \
    --openssldir=/usr/local/openssl \
&& make && make install

# Install/compile NGINX
RUN wget http://nginx.org/download/nginx-1.20.0.tar.gz \
  && tar -xzf nginx-1.20.0.tar.gz
  
COPY conf /nginx-1.20.0/auto/lib/openssl/
 
# add nginx user and nginx group
RUN addgroup nginx \
  && adduser --system --no-create-home --disabled-login --disabled-password --group nginx
  
RUN cd nginx-1.20.0 \
  && ./configure \
    --prefix=/usr/local/nginx-1.20.0 \
    --sbin-path=/usr/sbin/nginx \
    --conf-path=/etc/nginx/nginx.conf \
    --http-log-path=/var/log/nginx/access.log \
    --error-log-path=/var/log/nginx/error.log \
    --user=nginx \
    --with-pcre \
    --with-openssl=/usr/local \
    --pid-path=/var/run/nginx.pid \
    --with-http_ssl_module \
    --modules-path=/etc/nginx/modules \
    --with-http_v2_module \
    --with-stream \
  && make \
&& make install

RUN apt-get purge build-essential -y \
&& apt-get autoremove -y

# redirect nginx logs to docker log collector
RUN ln -sf /dev/stdout /var/log/nginx/access.log
RUN ln -sf /dev/stderr /var/log/nginx/error.log

RUN rm -rf /etc/nginx/nginx.conf
ADD nginx.conf /etc/nginx/nginx.conf

EXPOSE 8080 443

CMD ["nginx"]
