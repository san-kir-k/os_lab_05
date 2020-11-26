#! /usr/bin/env bash

function log_info()
{
  log_ "info" "$@"
}

function log_error()
{
  log_ "error" "$@"
}

function log_()
{
  local type=$1
  local message=$2
  local date_str=; date_str=$(date +'%Y-%m-%d %H:%M:%S')
  echo "[${type}] [${date_str}] ${message}"
}

function main()
{
  log_info "Stage #1.1 Compiling task1..."
  if ! ( cd ../src/task1 && make ) ; then
    log_error "Failed to compile task1."
    return 1
  fi
  log_info "Stage #1.2 Compiling task2..."
  if ! ( cd ../src/task2 && make ) ; then
    log_error "Failed to compile task2."
    return 2
  fi

  cd ../../test && mkdir tests_n_ans_t1 && mkdir tests_n_ans_t2
  log_info "Stage #2.1 Test generating for task1..."
  if ! python3 generator_t1.py . ; then
    log_error "Failed to generate tests for task1."
    return 3
  fi
  log_info "Stage #2.2 Test generating for task2..."
  if ! python3 generator_t2.py . ; then
    log_error "Failed to generate tests for task2."
    return 4
  fi

  log_info "Stage #3.1 Checking task1..."
  tests1=tests_n_ans_t1
  cd ../src/task1
  for test_file in $( cd ../../test/tests_n_ans_t1 && ls *.txt ) ; do
    echo ">>Checking "${test_file}"..."
    ./lab5_t1 < ../../test/${tests1}/${test_file}
    ret=$?
    if [ ${ret} -gt 0 ]; then
      log_error "Failed to run test "${test_file}  
      return 1
    fi
  done
  log_info "Stage #3.2 Checking task2..."
  tests2=tests_n_ans_t2
  cd ../task2
  for test_file in $( cd ../../test/tests_n_ans_t2 && ls *.txt ) ; do
    echo ">>Checking "${test_file}"..."
    ./lab5_t2 < ../../test/${tests2}/${test_file}
    ret=$?
    if [ ${ret} -gt 0 ]; then
      log_error "Failed to run test "${test_file}  
      return 1
    fi
  done

  cd ../task1 && make clean && cd ../task2
  make clean && cd ../../test
}

main $@
