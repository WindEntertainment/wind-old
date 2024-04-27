#!/bin/bash

checksum=$(find . -type f -exec md5sum {} + | sort | md5sum | awk '{print $1}')
echo $checksum
