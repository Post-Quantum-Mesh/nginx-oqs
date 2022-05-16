## Envoy-liboqs TLS Proxy (in progress)

Above are two different variations of an envoy layer 7 proxy:

1) [/complete_docker_build](https://github.com/wsu-cpts421-sp22/f5-quantum/tree/daniel_dev/envoy_tls/complete_docker_build) installs all relevant dependencies (liboqs, liboqs-OpenSSL fork, OpenSSL-1.1.1g, etc), generates a self-signed 2048-bit RSA certificate and key, and initializes a TLS server

2) [/tls_only](https://github.com/wsu-cpts421-sp22/f5-quantum/tree/daniel_dev/envoy_tls/complete_docker_build) comes with various keys and certificates pre-generated, initializing a TLS server using whatever certificate and key are in the /tls_only/certs directory


### Note:
Currently, only standard encryption methods are functional with Envoy. Further development and integration using Istio and it's built-in certificate authority Citadel will result in functionality with oqs and hybrid-oqs protocols.


### Commands:

Initialize Server:

        ./init.sh

Kill Servers:

        ./kill.sh
