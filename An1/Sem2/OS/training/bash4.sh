#!/bin/bash
fname=""
while [ ! -f "$fname" ]; do
    read -p "Enter name: " fname
done
