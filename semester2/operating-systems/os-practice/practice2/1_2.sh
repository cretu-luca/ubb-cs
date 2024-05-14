#!/bin/bash

find $1 -type f | grep -E -c "\.txt$"
