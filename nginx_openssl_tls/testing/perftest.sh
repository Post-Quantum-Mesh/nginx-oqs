#!/bin/sh

# Default values
TEST_TIME=10
SIG_ALG=dilithium3

# Pre-load SIG, KEM
while getopts t:s: flag
do
    case "${flag}" in
    	t) TEST_TIME=${OPTARG};;
    	s) SIG_ALG=${OPTARG};;
    esac
done

export PWD=$PWD
export SUBPATH="/testing/pki"
export FULLPATH=$PWD$SUBPATH

export OPENSSL="/usr/local/openssl/apps"

echo "Running SSL performance test with SIG_ALG=$SIG_ALG for TIME=$TEST_TIME"
echo

# Run handshakes for $TEST_TIME seconds
$OPENSSL/openssl s_time -connect :4433 -new -cert $FULLPATH/dilithium3_srv.crt -key $FULLPATH/dilithium3_srv.key -time $TEST_TIME -verify 1 | grep connections


