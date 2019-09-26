#!/bin/bash

readonly SCRIPT_NAME="$0"

readonly PROJECT_ROOT="$1"
readonly MODE="$2"

function main()
{
  tput reset

  ensure_project_root_was_informed "$PROJECT_ROOT"
  ensure_mode_was_informed "$MODE"

  if [ "$MODE" = "--test" ];
  then
    run_tests
  elif [ "$MODE" = "--compile" ];
  then
    compile_only
  else
    echo -e "\n\tERROR\n"
    echo -e "Unknown mode!\n"
    print_usage
    exit 1
  fi

  echo
  print_line

  run_git_status_if_available

  echo
  date
}

function run_tests()
{
  echo "Running tests..."
  print_line
  make -C "$PROJECT_ROOT" test
}

function compile_only()
{
  echo "Compiling..."
  print_line
  make -C "$PROJECT_ROOT"
}

function run_git_status_if_available()
{
  if [ -x "$(command -v git)" ]
  then
    echo "Running GIT Status..."
    print_line
    git -C "$PROJECT_ROOT" status -sb
  fi
}

function ensure_project_root_was_informed()
{
  end_if_empty "$1" "Missing project root path!"
}

function ensure_mode_was_informed()
{
  end_if_empty "$1" "Missing mode!"
}

function end_if_empty()
{
  if [ -z "$1" ]
  then
    echo -e "\n\tERROR\n"
    echo -e "$2\n"
    print_usage
    exit 1
  fi
}

function print_usage()
{
  echo -e "\nUsage:"
  echo "    $SCRIPT_NAME path/to/project/root [--compile|--test]"
}

function print_line()
{
  echo "=================================================="
}

main "$@"
