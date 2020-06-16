#!/bin/bash

today=$(date +%Y%m%d)
ls /usr -al > log.$today
