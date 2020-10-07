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
import math
import timeit

import numpy as np

import yaml

VERBOSE = False

# Tests embedded into the validator.
DEFAULT_TESTSET_YAML = (
    u'''
zad1:
  defaults:
    timeout: 60 # second
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
'''
    # Sokobany
    u'''
zad2:
  defaults:
    timeout: 10 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: sokoban_validator
  cases:
    - inp: |
        WWWWWW
        W.GWWW
        W..WWW
        W*K..W
        W..B.W
        W..WWW
        WWWWWW
      out: 33
    - inp: |
        WWWWWW
        W....W
        W.WK.W
        W.B*.W
        W.G*.W
        W....W
        WWWWWW
      out: 16
    - inp: |
        WWWWWWWWW
        WWW..WWWW
        W.....B.W
        W.W..WB.W
        W.G.GWK.W
        WWWWWWWWW
      out: 41
    - inp: |
        WWWWWWWW
        W......W
        W.G**BKW
        W......W
        WWWWW..W
        WWWWWWWW
      out: 23
    - inp: |
        WWWWWWWWWWWW
        WWWWWW.WWWWW
        W....WWW...W
        W.BB.....WKW
        W.B.WGGG...W
        W...WWWWWWWW
        WWWWWWWWWWWW
      out: 107
    - inp: |
        WWWWWWWW
        WWW.GGKW
        WWW.BB.W
        WWWW.WWW
        WWWW.WWW
        WWWW.WWW
        WWWW.WWW
        W....WWW
        W.W...WW
        W...W.WW
        WWW...WW
        WWWWWWWW
      out: 97
    - inp: |
        WWWWWW
        WG..WW
        WKBB.W
        WW...W
        WWW..W
        WWWWGW
        WWWWWW
      out: 30
    - inp: |
        WWWWWWWWWWW
        WWWWWWWG..W
        WWWWWWWGW.W
        WWWWWWWGW.W
        W.K.B.B.B.W
        W.W.W.W.WWW
        W.......WWW
        WWWWWWWWWWW
      out: 89
    - inp: |
        WWWWWWWWW
        WWW....WW
        WWW.WWKWW
        WWW.W.B.W
        W.GGW.B.W
        W.......W
        W..WWWWWW
        WWWWWWWWW
      out: 78
    - inp: |
        WWWWWWWW
        W.....WW
        WKBBB.WW
        W..WGGGW
        WW....WW
        WWWWWWWW
      out: 50
zad3:
  defaults:
    timeout: 10 # second
    input_file: zad_input.txt
    output_file: zad_output.txt
  validator: sokoban_validator
  cases:
    - inp: |
        WWWWWWW
        W.....W
        W.GBG.W
        W.BGB.W
        W.GBG.W
        W.BGB.W
        W..K..W
        WWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWW
        WWW..WWWW
        W.......W
        WKB***G.W
        W.......W
        WWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWW
        WWW..WW
        WWG.BWW
        WWGB.WW
        WWGB.WW
        WWGB.WW
        WWG.BWW
        WW...KW
        WWW...W
        WWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWWWWW
        WWWWWWW....W
        WWWWWWW.G..W
        WWW..WWWG..W
        W.B..B..G.WW
        W.KBB.W.G.WW
        WW....WWWWWW
        WWWWWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWWWWWW
        W..........WW
        W.WWWWWWW.KWW
        W.W.........W
        W.W..B...W..W
        W.BB.WWWWW..W
        WWW..W.W.GGGW
        WWWWWW.W....W
        WWWWWWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWWWWWW
        WWWW....WW..W
        W..BBBGGGGBKW
        W......WWW..W
        W...WWWW.WWWW
        WWWWWWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWWW
        WW....WWWW
        W...B.WWWW
        W..BB.WWWW
        WWW.GWWWWW
        WWWWGW.K.W
        WWWWG..B.W
        WWWWG.WWWW
        WWWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWW
        WWW....WW
        WWW..B.WW
        WWWWWB.WW
        WW.B.B.WW
        WGGGGW.WW
        W.....K.W
        WW..W...W
        WWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWW
        WWWWKWWWW
        WWWWBWWWW
        WW..G..WW
        W..W.W..W
        W.W...W.W
        W.W...W.W
        W.W...W.W
        W..W.W..W
        WW.B.B.WW
        WWWG.GWWW
        WWW...WWW
        WWW...WWW
        WWWWWWWWW
      out: 1000000
    - inp: |
        WWWWWWWWWWWWWWW
        WWWWWW.WWWWWWWW
        W.....W....WWWW
        WGWW..WBWW..WWW
        W...W.....W..WW
        WB..W.WWW..W..W
        W.W......W..W.W
        W.W.WWWW..W.W.W
        WG.K....B.*.G.W
        WWWWWWWWWWWWWWW
      out: 1000000
'''
# Komandos
'''
zad4:
  validator: komandos_validator
  defaults:
    timeout: 10 # seconds
    input_file: zad_input.txt
    output_file: zad_output.txt
  cases:
    - inp: |
        ###########
        #BSSSSSSSS#
        ###########
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSS##SSSSSS#
        #SSSSSSSSSSSS##SSSSSS#
        #SSSSSS###SSSSSSSSS#B#
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #####SSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSSSSSSSSBS#
        #SSSSSSSSSSSS##SSSSSS#
        #SSSSSSSS#############
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSSSS#SSSSSSSSSSS#
        ##S#######SSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSS##SSSSSS#
        #SSSSSSSSSSSS##SSSSSS#
        #SSSSSS###SSSSSSSSS#B#
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #####SSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSS##SSSSBS#
        #SSSSSSSS#SSS##SSSSSS#
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #####SSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSSSSSSSSS#SSBS#
        #SSBSSSSBSSSSSSS#SSSS#
        #########S#######S####
        #SSSSS#SSSSSSSSSSSSSB#
        ##SSS##SSSS###########
        #SSSS#SSSSSSSSSSSSSSS#
        #S##S###########SSSSS#
        #SSSS#SSSSSSSSSSSSSSS#
        #SSSSSSSS###SS####SSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSSSSSSSSBS#
        #SSSSSSSSSSSS##SSSSSS#
        #SSSSSSSS#############
        ###SSSSSS###SSSSSSSSB#
        ###SSSSSS#S#SSSSSSSSS#
        #SSSSSSSS#SSSSSSSSSSS#
        ##S############SSS####
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSS#SSSSSSSSSBS#
        #SSSSSSSSSSSS##SSSSSS#
        #SSSSSSSS#############
        #SSSSSS###SSSSSSSSSSS#
        #SSSSSS###SSS#SSSSSSS#
        #SSSSSSSS#SSS#SSSSSSS#
        ##S#######SSS####SSSS#
        #SSSSSSSSSSSSSSS#SSSS#
        #SSSSSSSSSSSSSSS##SSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSS#################
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSS#
        ######################
      out: 150
    - inp: |
        ######################
        #SSSSSSSSSSSSSSSSSSBS#
        #SSBSSSSBSSSSSSSSSSSS#
        #########S#######S####
        #SSSSS#SSSSSSSSSSSSSB#
        ##SSS##SSSS###########
        #SSSS#SSSSSSSSSSSSSSS#
        #S##S###########SSSSS#
        #SSSS#SSSSSSSSSSSSSSS#
        #SSSSSSSSSS####SSSSSS#
        ######################
      out: 150
    - inp: |
        ##########################
        #SSSSSSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSS############S###
        #SSSSSSSSSSSSSSSSS#SSSSSS#
        #SSSSSSSSSSSSSSSSS#SSSBSS#
        ##########SSSSSSSS#SBSSSS#
        #SSSSSSSSSSSSSSSSS#SSSBSS#
        ##########################
      out: 150
    - inp: |
        #######################
        #SSSSSSS#BSSSS#BSS#SSB#
        #SSSSSSSSSSSSSSSSSSSSS#
        #SSSSSSSSS#####SSSSSSS#
        #SSSSSSSSS#####SSSSSSS#
        #SSSSSSSSS#####SSSSSSS#
        #SSSSSSSSSSSSSSSSSSSSS#
        #SS##########SSSSSSSSS#
        #SS##########SSSSSSSSS#
        #SS##########SSSSSSSSS#
        #SSSSSSSSSSSSSSSSSSSSS#
        #######################
      out: 150
zad5:
  validator: komandos_validator
  defaults:
    timeout: 20 # seconds
    input_file: zad_input.txt
    output_file: zad_output.txt
  cases:
    - inp: |
        #####
        #G  #
        #   #
        #  G#
        #S# #
        #   #
        #SSS#
        #####
      out: 5
    - inp: |
        #####
        #G# #
        # S #
        #  G#
        #S# #
        #   #
        #SSS#
        #####
      out: 7
    - inp: |
        #####
        #B#S#
        #SSS#
        #SSB#
        #S#S#
        #SSS#
        #SSS#
        #####
      out: 9
    - inp: |
        ############
        #   SSS#   #
        #  #####   #
        #    #   G #
        #   SSS    #
        ############
      out: 17
    - inp: |
        ############
        #   SSS    #
        ########## #
        #    G     #
        # ##########
        #   SSS    #
        ############
      out: 23
    - inp: |
        ######################
        #        #   ##S     #
        #            ##      #
        #      ###         #G#
        #      ###           #
        #                    #
        #####         S      #
        #                    #
        ######################
      out: 12
    - inp: |
        ######################
        #        #   ##S     #
        #            ##      #
        #      ###         #G#
        #S     ###           #
        #                    #
        #####         S      #
        # S                  #
        ######################
      out: 26
    - inp: |
        ######################
        #        #         G #
        #            ##      #
        #       S#############
        #      ###           #
        #      ###           #
        #        #           #
        ## #######           #
        #   S                #
        #                    #
        #                    #
        #                    #
        #                    #
        #                    #
        #                  S #
        ######################
      out: 50
    - inp: |
        ######################
        #        #   ##S     #
        # S          ##      #
        #    S ###         #G#
        #      ###           #
        #                    #
        #####        SS      #
        #S                   #
        ######################
      out: 28
    - inp: |
        ######################
        #        # SS##    G #
        #        # SS##      #
        #      ###           #
        #      ###           #
        #                    #
        #####                #
        #S                   #
        ######################
      out: 26
    - inp: |
        ######################
        #     S         #  G #
        #  G    G       #    #
        ######### ####### ####
        #     #             G#
        ##   ##    ###########
        #    #               #
        # ## ###########     #
        #    #    S          #
        #        ###  ####   #
        ######################
      out: 22
    - inp: |
        ######################
        #                  G #
        #  G    G            #
        ######### ####### ####
        #     #             G#
        ##   ##    ###########
        #    #   S           #
        # ## ###########     #
        #    #    S          #
        #S         ####      #
        ######################
      out: 34
    - inp: |
        ######################
        #                  G #
        #  G    G            #
        ######### ####### ####
        #     #   S         G#
        ##   ##    ###########
        #    #   S           #
        # ## ###########     #
        #    #    S          #
        #S         ####      #
        ######################
      out: 34
    - inp: |
        ######################
        #        #         G #
        #            ##      #
        #       S#############
        #      ###          G#
        #      ###           #
        #        #           #
        ## #######           #
        #   S                #
        #                    #
        #                  S #
        ######################
      out: 22
    - inp: |
        ######################
        #        #         G #
        #            ##      #
        #       S#############
        #      ###           #
        #      ###   #       #
        #        #   #       #
        ## #######   ####S   #
        #   S           #    #
        #               ##   #
        #                    #
        #    #################
        #                    #
        #                    #
        #                  S #
        ######################
      out: 55
    - inp: |
        ######################
        #  SS              G #
        #  G    G            #
        ######### ####### ####
        #     #             G#
        ##   ##    ###########
        #    #   S           #
        # ## ###########     #
        #    #    S          #
        #S         ####      #
        ######################
      out: 38
    - inp: |
        ######################
        #  SS              G #
        #  G    G            #
        ######### ####### ####
        #     #             G#
        ##   ##    ###########
        #    #   S           #
        # ## ###########     #
        #    #    S      SS  #
        #S         ####      #
        ######################
      out: 39
    - inp: |
        ############
        #SSSSSS#SSS#
        #SS#####SSS#
        #SSSS#SSSBS#
        #SSSSSSSSSS#
        ############
      out: 18
    - inp: |
        ############
        #SSSSSS#SSS#
        #SS#####SSS#
        #SSSS#SSSBS#
        #SSSSSS#SSS#
        #SS##SSSSSS#
        ############
      out: 20
    - inp: |
        ##################
        #SSSSSSSSSSSSSSSS#
        ######SSSS###SSSS#
        #SSSSSSSSS###SSSS#
        #SSS###SSSSSSSSSS#
        #SSS###SSSS#####S#
        #SS####SSSS#SSSSS#
        #SSSSSSSSSS#SSSSB#
        #SSSSSSSSSS#SSSSB#
        ##################
      out: 28
    - inp: |
        ############
        #SSSSSS#SSS#
        #SS#####SSS#
        #SSSS#SSSBS#
        #BBSSSS#SSS#
        #SS##SSSSSS#
        #SS##SSSSSS#
        ############
      out: 18
      timeout: 200
'''
)
DEFAULT_TESTSET = yaml.load(DEFAULT_TESTSET_YAML)


# Custom comparison functions

# Sokoban logic
class Sokoban(object):
    EMPTY = 0
    GOAL = 1
    WALL = 2
    KEEPER = 3
    BOX = 4
    BOX_ON_GOAL = 5
    KEEPER_ON_GOAL = 6
    char2id = {
        '.': EMPTY,
        'G': GOAL,
        'W': WALL,
        'K': KEEPER,
        'B': BOX,
        '*': BOX_ON_GOAL,
        '+': KEEPER_ON_GOAL
        }
    id2char = {v: k for k, v in char2id.items()}

    MOVES = {
        "U": (-1, 0),
        "D": (1, 0),
        "L": (0, -1),
        "R": (0, 1),
        }

    @staticmethod
    def read_map(lines):
        map = []
        for line in lines:
            map.append([Sokoban.char2id[c] for c in line.strip()])
        map = np.array(map)
        b_locs = set(zip(*(map == Sokoban.BOX_ON_GOAL).nonzero()))
        for br, bc in b_locs:
            map[br, bc] = Sokoban.GOAL
        b_locs.update(zip(*(map == Sokoban.BOX).nonzero()))
        b_locs = frozenset(b_locs)

        k_loc = tuple(zip(*(map == Sokoban.KEEPER_ON_GOAL).nonzero()))
        if k_loc:
            assert not tuple(zip(*(map == Sokoban.KEEPER).nonzero()))
            map[k_loc[0][0], k_loc[0][1]] = Sokoban.GOAL
        else:
            k_loc = zip(*(map == Sokoban.KEEPER).nonzero())
        k_loc, = k_loc

        map[map > Sokoban.WALL] = Sokoban.EMPTY
        return map, (k_loc, b_locs)

    @staticmethod
    def map_to_string(empty_map, state):
        k_loc, b_locs = state
        strings = [[Sokoban.id2char[i] for i in r] for r in empty_map]
        if empty_map[k_loc[0], k_loc[1]] == Sokoban.GOAL:
            strings[
                k_loc[0]][k_loc[1]] = Sokoban.id2char[Sokoban.KEEPER_ON_GOAL]
        else:
            strings[k_loc[0]][k_loc[1]] = Sokoban.id2char[Sokoban.KEEPER]
        for br, bc in b_locs:
            if empty_map[br, bc] == Sokoban.GOAL:
                strings[br][bc] = Sokoban.id2char[Sokoban.BOX_ON_GOAL]
            else:
                strings[br][bc] = Sokoban.id2char[Sokoban.BOX]
        return '\n'.join([''.join(r) for r in strings])

    @staticmethod
    def keeper_moves(empty_map, state, moves="UDLR"):
        k_loc, b_locs = state
        kr, kc = k_loc
        for m in moves:
            dr, dc = Sokoban.MOVES[m]
            nl = (kr + dr, kc + dc)
            n = empty_map[nl[0], nl[1]]
            if n != Sokoban.WALL:
                if nl not in b_locs:  # move to GOAL/EMPTY
                    yield m, (nl, b_locs)
                else:  # maybe move BOX
                    nbl = (nl[0] + dr, nl[1] + dc)
                    if empty_map[nbl[0], nbl[1]] <= Sokoban.GOAL:
                        nb_locs = set(b_locs)
                        nb_locs.remove(nl)
                        nb_locs.add(nbl)
                        yield m, (nl, frozenset(nb_locs))

    @staticmethod
    def moves_to_strings(empty_map, state, k_moves):
        if VERBOSE:
            print(Sokoban.map_to_string(empty_map, state))
        for m in k_moves:
            possible_moves = Sokoban.keeper_moves(empty_map, state, m)
            possible_moves = tuple(possible_moves)
            if not possible_moves:
                fail("Keeper move %s is illegal!" % (m,))
            (_, state), = possible_moves
            if VERBOSE:
                print("Keeper move %s" % (m,))
                print(Sokoban.map_to_string(empty_map, state))
        return state


def sokoban_validator(case, process_out, message=""):
    k_moves = whitespace_normalize(process_out)
    max_num_moves = int(whitespace_normalize(case['out']))

    empty_map, state = Sokoban.read_map(case['inp'].strip().split('\n'))
    state = Sokoban.moves_to_strings(
        empty_map, state, k_moves)

    g_locs = set(zip(*(empty_map == Sokoban.GOAL).nonzero()))
    solved = g_locs == state[1]
    if solved:
        if len(k_moves) > max_num_moves:
            fail("Level solved, but path is too long!")
        else:
            if VERBOSE:
                print(message + "Level solved!")
            return {'num_steps': len(k_moves)}
    else:
        fail("All moves were legal, but puzzle not solved")


# Komandos

class Maze:
    _dirs = {'U': (0, -1), 'D': (0, 1), 'R': (1, 0), 'L': (-1, 0)}

    def __init__(self, maze_str):
        self.m = []
        self.goals = set()
        self.starts = set()
        self.states = set()

        for x in maze_str.split('\n'):
            x = x.strip()
            if x:
                self.m.append(list(x))

        for y in range(len(self.m)):
            raw = self.m[y]
            for x in range(len(raw)):
                if self.m[y][x] == 'S':
                    self.start = (x, y)
                    self.starts.add((x, y))
                if self.m[y][x] == 'G':
                    self.goals.add((x, y))
                if self.m[y][x] == 'B':
                    self.start = (x, y)
                    self.starts.add((x, y))
                    self.goals.add((x, y))
                if self.m[y][x] != '#':
                    self.states.add((x, y))

    def to_str(self, s):
        lines = []
        for y, line in enumerate(self.m):
            cs = []
            for x, c in enumerate(line):
                if (x, y) in s:
                    if c in 'BG':
                        c = 'B'
                    else:
                        c = 'S'
                else:
                    if c in 'S':
                        c = ' '
                cs.append(c)
            lines.append(''.join(cs))
        return '\n'.join(lines)

    def do(self, state, action):
        dx, dy = Maze._dirs[action]
        x, y = state
        if self.m[y+dy][x+dx] != '#':
            return (x+dx, y+dy)
        else:
            return state

    def do_belief(self, states, action):
        return {self.do(s, action) for s in states}


def komandos_validator(case, process_out, message=""):
    k_moves = whitespace_normalize(process_out)
    max_num_moves = int(whitespace_normalize(case['out']))

    maze = Maze(case['inp'])

    states = maze.starts

    if VERBOSE:
        print(maze.to_str(states))

    for c in k_moves:
        states = maze.do_belief(states, c)
        if VERBOSE:
            print(maze.to_str(states))

    solved_fraction = len(states & maze.goals) / len(states)

    if solved_fraction == 1:
        if len(k_moves) > max_num_moves:
            fail(message + "Level solved, but path is too long!")
        else:
            if VERBOSE:
                print("Level solved!")
            return {'num_moves': len(k_moves)}
    else:
        fail("%sLevel solved in %f%% only!" % (
             message, solved_fraction * 100.0))


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


def simple_benchmark():
    product = 1.0
    for counter in range(1, 1000, 1):
        for dex in list(range(1, 360, 1)):
            angle = math.radians(dex)
            product *= math.sin(angle)**2 + math.cos(angle)**2

    sys.stdout.write('.')
    sys.stdout.flush()
    return product


def start_benchmark():
        print('Executing CPU benchmark. It may take some time ...')
        print('0%', '.'*96, '100%')
        sys.stdout.write('|')
        sys.stdout.flush()

        result = timeit.repeat('validator.simple_benchmark()', setup='import validator', number=10, repeat=10)
        result = list(sorted(result))
        result = sum(result[:3])/3.0
        return (result - 1.0) / 1.5 + 1.0  # some tweaks


if __name__ == '__main__':
    benchmark_file = '.benchmark_result'
    benchmark_result = 1.0
    if not os.path.isfile(benchmark_file):
        benchmark_result = start_benchmark()
        print('|\nResult = ', benchmark_result)
        with open(benchmark_file, 'w') as outFile:
            outFile.write(str(benchmark_result))
    else:
        with open(benchmark_file) as inputFile:
            benchmark_result = float(inputFile.readline())

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
                program, problem_def['defaults'], case_def, problem_validator, timeout_multiplier*benchmark_result)
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
