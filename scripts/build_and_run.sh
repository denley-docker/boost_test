#!/usr/bin/env bash

readonly cur_path=$(pwd)
readonly work_path=$(cd $(dirname $0); pwd)

mkdir -p ${work_path}/../build
cd ${work_path}/../build && cmake ..
make
./boost_test
cd ${cur_path}
