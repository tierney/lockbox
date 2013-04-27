#!/bin/bash

echo "Generating the automake contents for the thrift-generated libraries."
./generate_thrift_automake.py *.thrift > thrift.mk
