#!/bin/bash

gdb --args ./client_main -host localhost -port 9876 -email me1@you.com -password password -config_path $HOME/.lockbox
