#!/bin/sh

# Run from CWD using "./test.sh"
# Flags:	-t test time
#		-s sig algo

TEST_TIME=10
SIG_ALG=dilithium3
PWD=$PWD
SUBPATH="/testing/perftest.sh"
FULLPATH=$PWD$SUBPATH


while getopts t:s: flag
do
    case "${flag}" in
    	t) TEST_TIME=${OPTARG};;
    	s) SIG_ALG=${OPTARG};;
    esac
done

echo
echo "Beginning SSL performance timing program. Flags: {test_time = $TEST_TIME; sig_alg = $SIG_ALG}"
echo

# Execute perftest.sh
$FULLPATH -t $TEST_TIME -s $SIG_ALG
