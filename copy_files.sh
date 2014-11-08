#!/bin/bash

# Script to copy engine files to a game directory

if [[ $# == 1 ]]; then
  # Copy files to dollar one
  cp -r src/pge $1
  echo "Copied files to $1"
else
  red='\033[0;31m'
  nocolor='\033[0m'
  echo -e "${red}ERROR: Please specify a destination src location!${nocolor}"
fi