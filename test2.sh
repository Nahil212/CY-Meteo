#!/bin/bash

help() {
if [[ "$1" = "--help" ]]; then
	cat alaide.txt
	exit 0
fi

}

help "$@"