#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
Prosta sprawdzarka. Przykłady użycia:

1. Uruchomienie wszystkich testów dla danego zadania:
  `python validator.py zad1 python rozwiazanie.py`

2. Uruchomienie wybranych testów
  `python validator.py --cases 1,3-5 zad1 a.out`

3. Urochomienie na innych testach
  `python validator.py --testset large_tests.yaml zad1 python rozwiazanie.py`

4. Wypisanie przykładowego wejścia/wyjścia:
  `python validator.py --show_example zad1`

5. Wypisanie informacji o rozwiązaniu:
  `python validator.py --verbose zad1 python rozwiazanie.py`

6. Wymuszenie użycia STDIN/STDOUT do komunikacji:
  `python validator.py --stdio zad1 python rozwiazanie.py`

7. Ustawienie mnożnika dla limitów czasowych:
  `python validator.py --timeout-multiplier 2.5 zad1 python rozwiazanie.py`


'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import argparse
import os
import signal
import subprocess
import sys
import threading
import time

import numpy as np

import yaml


VERBOSE = False

# Tests embedded into the validator.
DEFAULT_TESTSET_YAML = (
    u'''
zad1:
  defaults:
    timeout: 3 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: perlines_validator
  cases:
    - inp: |
        5 5
        5
        1 1 1
        3
        2 2
        5
        2 2
        1 3
        3 1
        1 3
        2 2
      out: |
        #####
        #.#.#
        .###.
        ##.##
        #####
    - inp: |
        9 9
        1 1 1
        5 1
        1 1 1 1
        5 1
        6 1
        7
        6
        1 3
        2 4
        4
        1 2 1
        8
        1 4
        7 1
        5
        5
        4
        6
      out: |
        #...#...#
        #####...#
        #.#.#...#
        #####...#
        .######.#
        ..#######
        ..######.
        ..#..###.
        .##.####.
    - inp: |
        6 10
        3
        1 1
        4
        1 3
        6
        6
        1
        3
        1 1
        5
        2
        3
        3
        3
        2
        1
      out: |
        .###......
        .#.#......
        ####......
        ...#.###..
        ...######.
        ....######
    - inp: |
        10 10
        3
        3
        1
        3
        6
        3
        3
        3 3
        2 2
        2 1
        1
        1 2
        1 2
        1 1
        2 5
        7
        2 5
        1
        2
        2
      out: |
        ....###...
        ....###...
        .....#....
        ....###...
        .######...
        ....###...
        ....###...
        ..###.###.
        .##.....##
        ##.......#
    - inp: |
        10 10
        4
        6
        3 4
        4 5
        4 5
        5 4
        5 2
        6
        6
        2 2
        3
        5
        9
        10
        2 4
        5 3
        6 3
        9
        5
        3
      out: |
        ...####...
        ..######..
        .###.####.
        ####.#####
        ####.#####
        #####.####
        .#####.##.
        ..######..
        ..######..
        ..##..##..
    - inp: |
        10 10
        3 3
        2 4 2
        1 2 1
        1 1
        2 2
        3 3
        3 3
        6
        4
        2
        5
        2 3
        1 3
        2 3
        2 3
        2 3
        2 3
        1 3
        2 3
        5
      out: |
        .###..###.
        ##.####.##
        #...##...#
        #........#
        ##......##
        ###....###
        .###..###.
        ..######..
        ...####...
        ....##....
    - inp: |
        14 10
        4
        1 1
        2
        1 2 1
        10
        1 2 1
        2
        2
        2
        2 2 2
        2 2 2
        8
        6
        2
        1 2
        3 3
        1 2
        2 1 2
        1 12
        1 12
        2 1 2
        1 2
        3 3
        1 2
      out: |
        ...####...
        ...#..#...
        ....##....
        .#..##..#.
        ##########
        .#..##..#.
        ....##....
        ....##....
        ....##....
        ##..##..##
        ##..##..##
        .########.
        ..######..
        ....##....
    - inp: |
        10 15
        4
        1 1 6
        1 1 6
        1 1 6
        4 9
        1 1
        1 1
        2 7 2
        1 1 1 1
        2 2
        4
        1 2
        1 1
        5 1
        1 2
        1 1
        5 1
        1 1
        4 1
        4 1
        4 2
        4 1
        4 1
        4 2
        4
      out: |
        ...####........
        ...#..#.######.
        ...#..#.######.
        ...#..#.######.
        ####..#########
        #.............#
        #.............#
        ##..#######..##
        .#..#.....#..#.
        ..##.......##..
    - inp: |
        15 15
        5
        9
        5 5
        13
        3 5 3
        15
        1 5 5 1
        15
        2 2
        2 2
        1 1
        1 1
        1 1
        2 2
        5
        3
        3 1
        6
        7
        3 3 5
        10 2
        9 1
        2 3 1 1
        9 1
        10 2
        3 3 5
        7
        6
        3 1
        3
      out: |
        .....#####.....
        ...#########...
        ..#####.#####..
        .#############.
        .###.#####.###.
        ###############
        #.#####.#####.#
        ###############
        .....##.##.....
        ....##...##....
        ....#.....#....
        ....#.....#....
        ....#.....#....
        ....##...##....
        .....#####.....
    - inp: |
        15 15
        5
        2 2
        1 1
        1 1
        4 4
        2 2 1 2
        1 3 1
        1 1 1 1
        2 7 2
        4 1 5
        2 1 1
        1 1 2
        1 1 1
        2 5 2
        3 4
        4
        2 2
        1 5
        1 2 2
        5 2 1
        2 1 1 2
        1 3 1
        1 1 6
        1 3 1
        2 1 2 2
        4 2 1
        1 1 1
        1 3 2
        2 2 3
        4
      out: |
        .....#####.....
        ....##...##....
        ....#.....#....
        ....#.....#....
        .####.....####.
        ##..##...#...##
        #.....###.....#
        #.....#.#.....#
        ##..#######..##
        .####..#.#####.
        ..##...#....#..
        ..#....#....##.
        ..#....#.....#.
        ..##.#####..##.
        ...###...####..
    - inp: |
        15 15
        4
        2 2
        2 2
        2 4 2
        2 1 1 2
        2 4 2
        1 2
        4 4 4
        1 1 1 1 1 1
        4 1 1 4
        1 1 1
        1 1 3
        10
        2 1
        4 1
        5 1
        2 1 1 1
        2 1 1 2
        2 3 3
        2 1
        2 3 6
        1 1 1 1 1
        1 1 1 1 1
        2 3 6
        2 1
        2 3 1
        2 1 1 1
        2 1 1 4
        7
        1 1
      out: |
        .....####......
        ....##..##.....
        ...##....##....
        ..##.####.##...
        .##..#..#..##..
        ##...####...##.
        #............##
        ####.####.####.
        #..#.#..#.#..#.
        ####.#..#.####.
        .....#..#....#.
        .....#..#...###
        ...##########..
        ..##........#..
        ####........#..
    - inp: |
        20 20
        7 1
        1 1 2
        2 1 2
        1 2 2
        4 2 3
        3 1 4
        3 1 3
        2 1 4
        2 9
        2 1 5
        2 7
        14
        8 2
        6 2 2
        2 8 1 3
        1 5 5 2
        1 3 2 4 1
        3 1 2 4 1
        1 1 3 1 3
        2 1 1 2
        1 1 1 2
        3 1 2 1 1
        1 4 2 1 1
        1 3 2 4
        1 4 6 1
        1 11 1
        5 1 6 2
        14
        7 2
        7 2
        6 1 1
        9 2
        3 1 1 1
        3 1 3
        2 1 3
        2 1 5
        3 2 2
        3 3 2
        2 3 2
        2 6
      out: |
        #######............#
        .#....#...........##
        .##...#..........##.
        ..#...##........##..
        ####..##.......###..
        ..###..#.....####...
        ...###.#....###.....
        ....##.#..####......
        ##..#########.......
        .##..#.#####........
        ..##.#######........
        ...##############...
        ....########....##..
        ....######.##....##.
        .##.########.#...###
        #..#####...#####..##
        #..###.##....####..#
        .###..#.##....####.#
        ...#..#..###...#.###
        ....##.....#...#..##
'''
    # Backtracking
    u'''
zad2:
  defaults:
    timeout: 300 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: perlines_validator
  cases:
    - inp: |
        20 15
        3
        1 2
        1 4
        1 1 2
        1 1 1 1
        1 3 2
        2 3 1
        1 1 1 2
        2 2 2
        1 1 2 2
        1 1 2 2
        1 1 1 1
        4 1 1
        2 2 2 1
        2 3 3
        2 2 3
        1 3 1 1
        2 1 1 1 2
        1 2 3
        1 6
        4 3
        6 1 2 3
        2 3
        6
        1 2 2
        1 1 2
        2 4 1 1
        1 1 2 2 2 1
        1 1 1 2 1 1
        1 3 2 3
        3 2 2
        4 3 4 2
        1 3 4 5
        2 2
        3
      out: |
        ..........###..
        .#........##...
        .#......####...
        .#.....#...##..
        .#....#.#...#..
        .#..###....##..
        .##....###.#...
        ..#.#....#.##..
        ...##...##..##.
        #..#...##...##.
        #..#..##...##..
        #..#..#....#...
        ####..#....#...
        ..##..##...##.#
        .##....###..###
        ##.......##.###
        #....###..#.#..
        ##..#..#.#.##..
        .#..##...###...
        .#...######....
    - inp: |
        20 20
        1 1 4
        1 6
        1 1 1 1 2 3
        1 1 2 3
        3 1 2 3
        4 5 2 2
        7 3 2
        3 5 1 2
        2 2 4 1
        2 2 3 4
        2 5 2
        2 1 5 1
        2 2 3 1
        6 2 2
        1 7
        2 2 2
        1 4
        3 1 1
        1 1
        1 1
        6 1
        8 3
        3 2 1
        1 1 2 2 1
        1 2 2 1 1
        1 1 1 1
        2 3
        4 1 2 2
        5 2 1
        8 1 1
        7 2
        3 5 2
        2 5
        2 1 4
        2 2 2 2
        2 2 1 1 1
        3 1 1 1 1
        5 4 2 1
        7 4 1 1
        4
      out: |
        ...#.#........####..
        ....#........######.
        ...#.#.#.#..##..###.
        .......#.#.##....###
        .......###.#..##.###
        .####..#####..##..##
        #######.###.......##
        ###...#####....#.##.
        ##.##...####.....#..
        ##.##....###..####..
        ##........#####..##.
        ##..#...#####.....#.
        .##....##..###....#.
        ..######....##...##.
        ......#....#######..
        ......##..##.##.....
        .#.....####.........
        ###.............#.#.
        .#...............#..
        ................#.#.
    - inp: |
        25 25
        1 1 2 2
        5 5 7
        5 2 2 9
        3 2 3 9
        1 1 3 2 7
        3 1 5
        7 1 1 1 3
        1 2 1 1 2 1
        4 2 4
        1 2 2 2
        4 6 2
        1 2 2 1
        3 3 2 1
        4 1 15
        1 1 1 3 1 1
        2 1 1 2 2 3
        1 4 4 1
        1 4 3 2
        1 1 2 2
        7 2 3 1 1
        2 1 1 1 5
        1 2 5
        1 1 1 3
        4 2 1
        3
        2 2 3
        4 1 1 1 4
        4 1 2 1 1
        4 1 1 1 1 1 1
        2 1 1 2 3 5
        1 1 1 1 2 1
        3 1 5 1 2
        3 2 2 1 2 2
        2 1 4 1 1 1 1
        2 2 1 2 1 2
        1 1 1 3 2 3
        1 1 2 7 3
        1 2 2 1 5
        3 2 2 1 2
        3 2 1 2
        5 1 2
        2 2 1 2
        4 2 1 2
        6 2 3 2
        7 4 3 2
        7 4 4
        7 1 4
        6 1 4
        4 2 2
        2 1
      out: |
        .#.#..............##.##..
        #####....#####...#######.
        #####...##...##.#########
        .###...##...###.#########
        ..#....#..###.##.#######.
        ......###......#..#####..
        #######....#.#.#...###...
        #.....##...#.#.##...#....
        .####..##.....####.......
        ..#.....##...##..##......
        ...####.######....##.....
        ....#..##..##......#.....
        .....###.###.......##..#.
        ####..#...###############
        #...#.#..###......#.#....
        ##..#.#.##.##.....###....
        .#.####...####.....#.....
        .#.....####.###...##.....
        .#..........#.##.##......
        ..#######..##..###..#.#..
        ....##.#...#....#..#####.
        ....#.....##.......#####.
        ....#.#...#.........###..
        ....####.##..........#...
        .......###...............
'''
    # Sudoku
    """
zad4:
  defaults:
    timeout: 2 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: prolog_validator
  cases:
    - inp: |
        89.356.1.
        3...1.49.
        ....2985.
        9.7.6432.
        .........
        .6389.1.4
        .3298....
        .78.4....
        .5.637.48
      out: |
        [8,9,4,3,5,6,7,1,2,3,2,5,7,1,8,4,9,6,7,1,6,4,2,9,8,5,3,9,8,7,1,6,4,3,2,5,2,4,1,5,7,3,6,8,9,5,6,3,8,9,2,1,7,4,4,3,2,9,8,1,5,6,7,6,7,8,2,4,5,9,3,1,1,5,9,6,3,7,2,4,8]
    - inp: |
        53..7....
        6..195...
        .98....6.
        8...6...3
        4..8.3..1
        7...2...6
        .6....28.
        ...419..5
        ....8..79
      out: |
        [5,3,4,6,7,8,9,1,2,6,7,2,1,9,5,3,4,8,1,9,8,3,4,2,5,6,7,8,5,9,7,6,1,4,2,3,4,2,6,8,5,3,7,9,1,7,1,3,9,2,4,8,5,6,9,6,1,5,3,7,2,8,4,2,8,7,4,1,9,6,3,5,3,4,5,2,8,6,1,7,9]
    - inp: |
        3.......1
        4..386...
        .....1.4.
        6.924..3.
        ..3......
        ......719
        ........6
        2.7...3..
      out: |
        [3,8,2,4,5,9,6,7,1,4,7,1,3,8,6,2,9,5,5,9,6,7,2,1,8,4,3,6,1,9,2,4,7,5,3,8,7,5,3,1,9,8,4,6,2,8,2,4,5,6,3,7,1,9,1,3,5,8,7,4,9,2,6,2,6,7,9,1,5,3,8,4,9,4,8,6,3,2,1,5,7]
"""

    # Burze
    """
zad5:
  defaults:
    timeout: 8 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: prolog_validator
  cases:
    - inp: |
        4 4 0 5 5 5
        5 5 3 5 5 0
        5 5 0
      out: |
        [1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0]
    - inp: |
        3 8 5 3 3 5 5 5 2 2
        0 2 7 7 2 2 0 7 7 7
        0 5 0
        0 6 0
        1 5 1
        1 6 0
      out: |
         [0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0]
    - inp: |
        2 2 7 7 4 4 3 5 2 8 8 8 8 6 0
        4 4 6 6 2 9 9 9 2 0 2 7 7 7 0
        13 10 0
        13 11 1
        14 10 0
        14 11 0
        3 0 1
        3 1 1
        4 0 1
        4 1 1
        3 13 0
        3 14 0
        4 13 1
        4 14 0
        9 4 0
        9 5 1
        10 4 0
        10 5 1
        2 1 1
        2 2 0
        3 1 1
        3 2 0
      out: |
        [0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    - inp: |
        4 4 12 10 8 0 8 11 8 7 11 7 7 5 0
        10 10 3 9 9 3 8 8 5 4 10 6 9 5 3
        13 11 1
        13 12 1
        14 11 0
        14 12 0
        3 9 1
        3 10 1
        4 9 0
        4 10 0
        2 0 1
        2 1 1
        3 0 0
        3 1 0
        11 13 0
        11 14 0
        12 13 0
        12 14 0
        7 6 1
        7 7 1
        8 6 1
        8 7 1
      out: |
        [1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    - inp: |
        11 11 3 5 5 11 8 8 10 8 6 4 0 7 12 7 7 7
        0 5 9 9 9 4 8 10 9 11 6 4 13 13 10 7 3 0
        2 1 0
        2 2 0
        3 1 0
        3 2 0
        3 3 0
        3 4 0
        4 3 0
        4 4 0
        13 1 0
        13 2 1
        14 1 0
        14 2 1
        15 1 0
        15 2 0
        16 1 0
        16 2 0
        1 3 1
        1 4 1
        2 3 0
        2 4 0
        15 5 0
        15 6 0
        16 5 0
        16 6 0
        14 10 0
        14 11 1
        15 10 0
        15 11 1
        0 2 1
        0 3 1
        1 2 1
        1 3 1
        9 2 1
        9 3 1
        10 2 0
        10 3 0
        7 13 0
        7 14 0
        8 13 0
        8 14 0
      out: |
        [0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,0]
 """

)
DEFAULT_TESTSET = yaml.load(DEFAULT_TESTSET_YAML)

# Comparison functions


class ValidatorException(Exception):
    pass


def fail(message):
    raise ValidatorException(message)


def compare(returned, expected, message="Contents"):
    if returned != expected:
        fail('%s differ. Got: "%s", expceted: "%s"' % (
             message, returned, expected))


def whitespace_relaxed_validator(case, process_out):
    """
    Compare two strings ignoring whitespaces and trailing newlines.
    """
    ref_out = whitespace_normalize(case['out'])
    process_out = whitespace_normalize(process_out)
    return compare(process_out, ref_out, "Outputs")


def perlines_validator(case, process_out, line_compare_fun=compare):
    """
    Compare two strings line by line, ignoring whitespaces.
    """
    ref_lines = whitespace_normalize(case['out']).split('\n')
    process_lines = whitespace_normalize(process_out).split('\n')
    compare(len(process_lines), len(ref_lines), "Number of lines")
    for lnum, (proc_line, ref_line) in enumerate(
            zip(process_lines, ref_lines)):
        line_compare_fun(proc_line, ref_line, "Line %d contents" % (lnum + 1,))


def prolog_validator(case, process_out, line_compare_fun=compare):
    """
    Compare two strings line by line, ignoring whitespaces.
    """
    ref_lines = whitespace_normalize(case['out']).split('\n')
    with open('solution.pl', 'w') as prolog_file:
        prolog_file.write(process_out)

    os.system('swipl -q -c solution.pl > prolog_result.txt')

    with open('prolog_result.txt', 'r') as prolog_result:
        process_out = prolog_result.read()

    process_lines = whitespace_normalize(process_out).split('\n')
    compare(len(process_lines), len(ref_lines), "Number of lines")
    for lnum, (proc_line, ref_line) in enumerate(
            zip(process_lines, ref_lines)):
        line_compare_fun(proc_line, ref_line, "Line %d contents" % (lnum + 1,))

# Comparison function utils


def ensure_unicode(obj):
    if sys.version_info[0] == 3:
        if isinstance(obj, str):
            return obj
        elif isinstance(obj, bytes):
            return obj.decode('utf8')
        else:
            return str(obj)
    else:
        if isinstance(obj, unicode):
            return obj
        elif isinstance(obj, str):
            return obj.decode('utf8')
        else:
            return unicode(obj)
    return obj


def whitespace_normalize(obj):
    """
    Optionally convert to string and normalize newline and space characters.
    """
    string = ensure_unicode(obj)
    lines = string.replace('\r', '').strip().split('\n')
    lines = [' '.join(l.strip().split()) for l in lines]
    return '\n'.join(lines)


# Subprocess handling utils
try:  # py3
    from shlex import quote as shellquote
except ImportError:  # py2
    from pipes import quote as shellquote


if os.name == 'nt':
    def shellquote(arg):
        return subprocess.list2cmdline([arg])

    def kill_proc(process):
        if process.poll() is None:
            print('Killing subprocess.')
            subprocess.call(['taskkill', '/F', '/T', '/PID', str(process.pid)])
else:
    def kill_proc(process):
        if process.poll() is None:
            print('Killing subprocess.')
            os.killpg(os.getpgid(process.pid), signal.SIGTERM)


def run_and_score_case(program, defaults, case_def, validator, timeout_multiplier):
    opts = dict(defaults)
    opts.update(case_def)
    opts['timeout'] *= timeout_multiplier
    process_out, elapsed_time = run_case(program, **opts)
    if VERBOSE:
        print("Got output:")
        print(process_out)
    measurements = validator(opts, process_out)
    measurements = measurements or {}
    measurements['time'] = elapsed_time
    return measurements


def run_case(program, inp, out=None,
             input_file='<stdin>', output_file='<stdout>',
             timeout=1.0):
    del out  # unused
    inp = ensure_unicode(inp)
    if inp[-1] != '\n':
        inp += '\n'
    inp = inp.encode('utf8')

    if input_file != '<stdin>':
        with open(input_file, 'wb') as in_f:
            in_f.write(inp)
        inp = None
    try:
        if output_file != '<stdout>':
            os.remove(output_file)
    except:
        pass

    stdin = subprocess.PIPE if input_file == '<stdin>' else None
    stdout = subprocess.PIPE if output_file == '<stdout>' else None
    process_out = ''
    process = None

    try:
        if os.name == 'nt':
            kwargs = {}
        else:
            kwargs = {'preexec_fn': os.setpgrp}

        process = subprocess.Popen(
            program, shell=True, stdin=stdin, stdout=stdout, **kwargs)
        start = time.time()
        if timeout > 0:
            timer = threading.Timer(timeout, kill_proc, [process])
            timer.start()

        process_out, _ = process.communicate(inp)
        elapsed = time.time() - start
    except Exception as e:
        fail(str(e))
    finally:
        if process:
            kill_proc(process)
        if timeout > 0:
            timer.cancel()
    if process.poll() != 0:
        fail("Bad process exit status: %d" % (process.poll(),))

    if output_file != '<stdout>':
        if not os.path.isfile(output_file):
            fail("Output file %s does not exist" % (output_file, ))
        with open(output_file, 'rb') as out_f:
            process_out = out_f.read()
    process_out = process_out.decode('utf8')

    return process_out, elapsed


def ensure_newline_string(obj):
    obj = ensure_unicode(obj)
    if obj[-1] != '\n':
        obj += '\n'
    return obj


def show_example(defaults, case_def):
    opts = dict(defaults)
    opts.update(case_def)
    print("Input is passed using %s and contains:" % (opts['input_file'],))
    print(ensure_newline_string(opts["inp"]))
    print("Output is expected in %s with contents:" % (opts['output_file'],))
    print(ensure_newline_string(opts["out"]))


def get_argparser():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--cases', default='',
        help='Comma-separated list of test cases to run, e.g. 1,2,3-6.')
    parser.add_argument(
        '--testset', default='',
        help='Path to a YAML test set definition.')
    parser.add_argument(
        '--show_example', default=False, action='store_true',
        help='Print a sample input/output pair.')
    parser.add_argument(
        '--timeout-multiplier', '-tm',
        help='Multiply timeout by provided amount, e.g. 2.13')
    parser.add_argument(
        '--verbose', default=False, action='store_true',
        help='Print more information about solutions.')
    parser.add_argument(
        '--stdio', default=False, action='store_true',
        help='Use stdin/stdout for communication.')
    parser.add_argument(
        'problem',
        help='Problem form this homework, one of: %s.' %
        (', '.join(sorted(DEFAULT_TESTSET.keys())),))
    parser.add_argument(
        'program', nargs=argparse.REMAINDER,
        help='Program to execute, e.g. python solution.py.')
    return parser


def get_program(args):
    return ' '.join([shellquote(a) for a in args])


def get_cases(problem_def, cases):
    problem_cases = problem_def['cases']
    if cases == '':
        for case in enumerate(problem_cases, 1):
            yield case
        return
    cases = cases.strip().split(',')
    for case in cases:
        if '-' not in case:
            case = int(case) - 1
            if case < 0:
                raise Exception('Bad case number: %d' % (case + 1,))
            yield case + 1, problem_cases[case]
        else:
            low, high = case.split('-')
            low = int(low) - 1
            high = int(high)
            if low < 0 or high > len(problem_cases):
                raise Exception('Bad case range: %s' % (case,))
            for case in range(low, high):
                yield case + 1, problem_cases[case]


if __name__ == '__main__':
    parser = get_argparser()
    args = parser.parse_args()
    VERBOSE = args.verbose

    if args.testset:
        with open(args.testset) as testset_f:
            testset = yaml.load(testset_f)
    else:
        testset = DEFAULT_TESTSET
    if args.problem not in testset:
        print('Problem not known: %s. Choose one of %s.' %
              (args.problem, ', '.join(sorted(testset.keys()))))

    problem_def = testset[args.problem]
    problem_validator = eval(problem_def['validator'])
    problem_cases = get_cases(problem_def, args.cases)
    program = get_program(args.program)

    if args.show_example:
        show_example(problem_def['defaults'], next(problem_cases)[1])
        sys.exit()

    failed_cases = []
    ok_cases = []
    for case_num, case_def in problem_cases:
        print('Running case %d... ' % (case_num,), end='')
        try:
            timeout_multiplier = float(args.timeout_multiplier) if args.timeout_multiplier and float(args.timeout_multiplier) > 1 else 1
            if args.stdio:
                case_def['input_file'] = '<stdin>'
                case_def['output_file'] = '<stdout>'
            case_meas = run_and_score_case(
                program, problem_def['defaults'], case_def, problem_validator, timeout_multiplier)
            ok_cases.append((case_num, case_meas))
            print('OK!')
        except ValidatorException as e:
            failed_cases.append(case_num)
            print('Failed:')
            print(str(e))

    print('\nValidation result: %d/%d cases pass.\n' % (
        len(ok_cases), len(ok_cases) + len(failed_cases)))

    tot_meas = {}
    for nc, meas in ok_cases:
        for k, v in meas.items():
            tot_meas[k] = tot_meas.get(k, 0) + v
    for k, v in tot_meas.items():
        print("For passing cases total %s: %s" % (k, v))

    if failed_cases:
        print('\nSome test cases have failed. '
              'To rerun the failing cases execute:')
        misc_opts = ''
        if args.verbose:
            misc_opts = ' --verbose'
        if args.timeout_multiplier:
            misc_opts += ' --timeout-multiplier ' + args.timeout_multiplier
        if args.testset:
            misc_opts = '%s --testset %s' % (
                misc_opts, shellquote(args.testset),)
        cases_opt = '--cases ' + ','.join([str(fc) for fc in failed_cases])
        print('python validator.py%s %s %s %s' %
              (misc_opts, cases_opt, args.problem, program))
