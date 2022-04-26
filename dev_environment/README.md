# ENVIRONMENT SETUP INSTRUCTIONS:

Note: ./configure commands followed by indented parameters (ex: ./configure --prefix=/usr/local) are all one-line commands

1. Update package manager

        apt update

2. Install Dependencies and Compiler

        apt-get install gcc build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev libgd-dev libxml2 libxml2-dev uuid-dev astyle doxygen

3. Install PCRE

        wget https://github.com/PhilipHazel/pcre2/releases/download/pcre2-10.39/pcre2-10.39.tar.gz
        tar -xzf pcre2-10.39.tar.gz
        cd pcre2-10.39
        ./configure
        make
        make install

4. Install zlib

        wget http://zlib.net/zlib-1.2.12.tar.gz
        tar -xzf zlib-1.2.12.tar.gz
        cd zlib-1.2.12
        ./configure
        make
        make install
	
5. Install OpenSSL

        wget http://www.openssl.org/source/openssl-1.1.1g.tar.gz
        tar -xzf openssl-1.1.1g.tar.gz
        cd openssl-1.1.1g
        ./configure
        make
        make install


6. Install OQS-OpenSSL Fork (with liboqs) - < OPENSSL_DIR > is a directory of your choosing (ex: /usr/local)

        cd <OPENSSL_DIR>
        git clone --branch OQS-OpenSSL_1_1_1-stable https://github.com/open-quantum-safe/openssl.git
        git clone --branch main https://github.com/open-quantum-safe/liboqs.git
        cd liboqs
        mkdir build
        cd build
        cmake -GNinja -DCMAKE_INSTALL_PREFIX=< OPENSSL_DIR >/oqs ..
        ninja
        ninja install
        cd ..
        cd <DIR>
        ./Configure no-shared linux-x86_64 -lm
        make


7. Install NGINX Stable From Source (currently using stable 1.20.0)

        wget http://nginx.org/download/nginx-1.20.0.tar.gz 
        tar -xzf nginx-1.20.0.tar.gz
        cd nginx-1.20.0
        ./configure 
            --prefix=/usr/local/nginx
            --sbin-path=/usr/sbin/nginx
            --conf-path=/etc/nginx/nginx.conf
            --http-log-path=/var/log/nginx/access.log
            --error-log-path=/var/log/nginx/error.log
            --with-pcre
            --with-zlib=/usr/local/zlib-1.2.12
            --pid-path=/var/run/nginx.pid
            --with-http_ssl_module
            --modules-path=/etc/nginx/modules
            --with-http_v2_module
            --with-stream
        make
        make install

8. Verify Installation and Configurations

       nginx -V
      
      
Sample output
![Screenshot from 2022-04-12 06-29-36](https://user-images.githubusercontent.com/56026339/162973512-37a8b464-0357-42ea-be3f-00357345e0ed.png)
