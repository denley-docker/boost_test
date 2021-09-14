#!/usr/bin/env bash

readonly cur_path=$(pwd)
readonly work_path=$(cd $(dirname $0); pwd)

rm -fr ${work_path}/../build
cd ${cur_path}
