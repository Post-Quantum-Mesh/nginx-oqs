### NOTE:
This was cloned from the OpenQuantumSafe demo [repositories](https://github.com/open-quantum-safe/oqs-demos)


Run the following commands in this directory:

1. `docker build --build-arg SIG_ALG=<SIG> -t oqs-nginx-img .` (`<SIG>` can be any of the authentication algorithms listed [here](https://github.com/open-quantum-safe/openssl#authentication)). An alternative, simplified build instruction is `docker build -t oqs-nginx-img .`: This will generate the image with a default QSC algorithm (dilithium3 -- see Dockerfile to change this).
2. `docker run --detach --rm --name oqs-nginx -p 4433:4433 oqs-nginx-img` will start up the resulting container with QSC-enabled nginx running and listening for TLS 1.3 connections on port 4433.

### Usage:
Complete information how to use the image is [available in the separate file USAGE.md](USAGE.md).
