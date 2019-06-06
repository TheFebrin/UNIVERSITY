#!/bin/bash

echo "Press ENTER after each test case"

for task_file in task*txt
do
    python show_optimal_policy.py $task_file
done
