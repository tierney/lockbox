#!/bin/bash

./client_main -host localhost -port 9876 -email me1@you.com -password password -config_path $HOME/.lockbox -register_user -register_top_dir $HOME/Lockboxes/1 -nodaemon

./client_main -host localhost -port 9876 -email me2@you.com -password password -config_path $HOME/.lockbox2 -register_user -register_top_dir $HOME/Lockboxes/2 -nodaemon

./client_main -host localhost -port 9876 -email me1@you.com -password password -config_path $HOME/.lockbox -share $HOME/Lockboxes/1,me2@you.com -nodaemon
