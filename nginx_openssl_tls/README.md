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

Performance metrics can be retrieved from the SSL/TLS handshake using openSSL's s_time function. In a second terminal, run the following command:

    ./test.sh -t <TEST_TIME> -s <SIG_ALG>
    
The flags -s and -t allow for passing parameters to the performance test script. TEST_TIME (default = 10) dictates how long (in seconds) that connections are established. SIG_ALG (default = dilithium3) dictates which quantum-safe cryptographic signing should be used. It is not advised to change the SIG_ALG without first changing the Dockerfile for the TLS/SSL server -- it uses dilithium3 as a default.

### Diagram of NGINX TLS Handshake

![NGINX TLS Handshake Diagram](https://drive.google.com/uc?id=1hASfFvcxFHRVDw9Yi2F1NEN0hPWkRAAN)
