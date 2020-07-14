#!/bin/bash
SIGKILL_handler() {
	echo "SIGKILL"
}
trap SIGKILL_handler SIGKILL

for ((i = 0; i < 20; i++)); do
	echo "."
	sleep 1
done

