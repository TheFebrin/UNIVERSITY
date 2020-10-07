#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
Prosta sprawdzarka. Przykady użycia:

1. uruchomienie wszystkich testów dla danego zadania:
python validator.py zad1 python rozwiazanie.py

2. uruchomienie wybranych testów
python validator.py --cases 1,3-5 zad1 a.out

3. urochomienie na innych testach
python validator.py --testset large_tests.yaml zad1 python rozwiazanie.py

4. Wypisanie przykadowego wejścia/wyjścia:
python validator.py --show_example zad1
'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import argparse
import os
import signal
import subprocess
import threading
import yaml
import gzip
import sys


# Tests embedded into the validator.
DEFAULT_TESTSET_YAML = u'''
zad1:
  defaults:
    timeout: 10 # second
    input_file: zad1_input.txt
    output_file: zad1_output.txt
  validator: whitespace_relaxed_validator
  cases:
# single-line input and output can be formatted as:
    - inp: white h6 a4 d4
      out: 9
# multiline input and output can formatted as:
    - inp: |
        black b4 f3 e8
      out: |
        6
    - inp: white a1 e3 b7
      out: 9
    - inp: black h7 a2 f2
      out: 6
    - inp: black a2 e4 a4
      out: 8
    - inp: black g8 h1 c4
      out: 10
zad2:
  defaults:
    timeout: 60
    input_file: zad2_input.txt
    output_file: zad2_output.txt
  validator: "lambda opts, out: perlines_validator(opts, out, zad2_line_compare)"
  cases:
    - inp: |
        księgapierwsza
        gospodarstwo
        powrótpaniczaspotkaniesiępierwszewpokoikudrugieustołuważnasędziegonaukaogrzecznościpodkomorzegouwagipolitycznenadmodamipocząteksporuokusegoisokołażalewojskiegoostatniwoźnytrybunałurzutokanaówczesnystanpolitycznylitwyieuropy
        litwoojczyznomojatyjesteśjakzdrowie
        ileciętrzebacenićtentylkosiędowie
        ktocięstraciłdziśpięknośćtwąwcałejozdobie
        widzęiopisujębotęskniępotobie
        pannoświętacojasnejbroniszczęstochowy
        iwostrejświeciszbramietycogródzamkowy
        nowogródzkiochraniaszzjegowiernymludem
        jakmniedzieckodozdrowiapowróciłaścudem
        gdyodpłaczącejmatkipodtwojąopiekę
        ofiarowanymartwąpodniosłempowiekę
        izarazmogłempieszodotwychświątyńprogu
        iśćzawróconeżyciepodziękowaćbogu
        taknaspowróciszcudemnaojczyznyłono
        tymczasemprzenośmojąduszęutęsknioną
        dotychpagórkówleśnychdotychłąkzielonych
        szerokonadbłękitnymniemnemrozciągnionych
        dotychpólmalowanychzbożemrozmaitem
        wyzłacanychpszenicąposrebrzanychżytem
        gdziebursztynowyświerzopgrykajakśniegbiała
        gdziepanieńskimrumieńcemdzięcielinapała
        awszystkoprzepasanejakbywstęgąmiedzą
        zielonąnaniejzrzadkacichegruszesiedzą
        śródtakichpólprzedlatynadbrzegiemruczaju
        napagórkuniewielkimwebrzozowymgaju
        stałdwórszlacheckizdrzewaleczpodmurowany
        świeciłysięzdalekapobielaneściany
        tymbielszeżeodbiteodciemnejzieleni
      out: |
        księga pierwsza
        gospodarstwo
        powrót panicza spotkanie się pierwsze w pokoiku drugie u stołu ważna sędziego nauka o grzeczności podkomorzego uwagi polityczne nad modami początek sporu o kusego i sokoła żale wojskiego ostatni woźny trybunału rzut oka na ówczesny stan polityczny litwy i europy
        litwo ojczyznom o jaty jesteś jak zdrowie
        ile cię trzeba cenić ten tylko się dowie
        kto cię stracił dziś piękność twą w całej ozdobie
        widzę i opisuję bo tęsknię po tobie
        panno święta co jasnej bronisz częstochowy
        i w ostrej świecisz bramie ty co gród zamkowy
        nowogródzki ochraniasz z jego wiernym ludem
        jak mnie dziecko do zdrowia powróciłaś cudem
        gdy od płaczącej matki pod twoją opiekę
        ofiarowany martwą podniosłem powiekę
        i zaraz mogłem pieszo do twych świątyń progu
        iść zawrócone życie podziękować bogu
        tak nas powrócisz cudem na ojczyzny łono
        tymczasem przenoś moją duszę utęsknioną
        do tych pagórków leśnych do tych łąk zielonych
        szeroko nad błękitnym niemnem rozciągnionych
        do tych pól malowanych zbożem rozmaitem
        wyzłacanych pszenicą posrebrzanych żytem
        gdzie bursztynowy świerzop gry kajak śnieg biała
        gdzie panieńskim rumieńcem dzięcielina pała
        a wszystko przepasane jakby wstęgą miedzą
        zieloną na niej z rzadka ciche grusze siedzą
        śród takich pól przed laty nad brzegiem ruczaju
        na pagórku niewielkim we brzozowym gaju
        stał dwór szlachecki z drzewa lecz podmurowany
        świeciły się z daleka pobielane ściany
        tym bielsze że odbite od ciemnej zieleni
zad4:
  defaults:
    timeout: 10 # second
    input_file: zad4_input.txt
    output_file: zad4_output.txt
  validator: perlines_validator
  cases:
    - inp: |
        0010001000 5
        0010001000 4
        0010001000 3
        0010001000 2
        0010001000 1
        0010001000 0
        0010101000 5
        0010101000 4
        0010101000 3
        0010101000 2
        0010101000 1
        0010101000 0
      out: |
        3
        4
        3
        2
        1
        2
        2
        3
        2
        3
        2
        3
    - inp: |
        0000000001 1
        0000000010 1
        1000000000 1
        0100000000 1
      out: |
        0
        0
        0
        0
zad5:
  defaults:
    timeout: 30 # second
    input_file: zad5_input.txt
    output_file: zad5_output.txt
  validator: perlines_validator
  cases:
    - inp: |
        7 7
        7
        7
        7
        7
        7
        7
        7
        7
        7
        7
        7
        7
        7
        7
      out: |
        #######
        #######
        #######
        #######
        #######
        #######
        #######
    - inp: |
        7 7
        2
        2
        7
        7
        2
        2
        2
        2
        2
        7
        7
        2
        2
        2
      out: |
        ..##...
        ..##...
        #######
        #######
        ..##...
        ..##...
        ..##...
    - inp: |
        7 7
        2
        2
        7
        7
        2
        2
        2
        4
        4
        2
        2
        2
        5
        5
      out: |
        ##.....
        ##.....
        #######
        #######
        .....##
        .....##
        .....##
    - inp: |
        7 7
        7
        6
        5
        4
        3
        2
        1
        1
        2
        3
        4
        5
        6
        7
      out: |
        #######
        .######
        ..#####
        ...####
        ....###
        .....##
        ......#
    - inp: |
        7 7
        7
        5
        3
        1
        1
        1
        1
        1
        2
        3
        7
        3
        2
        1
      out: |
        #######
        .#####.
        ..###..
        ...#...
        ...#...
        ...#...
        ...#...
'''
DEFAULT_TESTSET = yaml.load(DEFAULT_TESTSET_YAML)


# Custom comparison functions
zad2_words = None
def load_word_list():
    global zad2_words
    if zad2_words:
        return zad2_words
    print("Loading wordlist...", end='')
    zad2_words = set()
    with gzip.open('zad2_words.txt.gz', 'rb') as gf:
        for line in gf:
            line = line.strip()
            if line:
                zad2_words.add(line.decode('utf8'))
    return zad2_words


def zad2_line_compare(returned, expected, message="Contents"):
    ret = compare(returned.replace(' ', ''), expected.replace(' ', ''),
                  message + ' string without spaces differs!')
    if ret:
        return ret
    expected_score = sum([len(w)**2 for w in expected.split()])
    returned_words = returned.split()
    returned_score = sum([len(w)**2 for w in returned_words])
    if returned_score < expected_score:
        return message + " split is suboptimal!"
    bad_words = set(returned_words) - load_word_list()
    if bad_words:
        return message + " has unknown words: " + str(bad_words)
    return None


# Comparison functions
def compare(returned, expected, message="Contents"):
    if returned != expected:
        return '%s differ. Got: "%s", expceted: "%s"' % (
            message, returned, expected)
    return None


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
    ret = compare(len(process_lines), len(ref_lines), "Number of lines")
    if ret:
        return ret
    for lnum, (proc_line, ref_line) in enumerate(
            zip(process_lines, ref_lines)):
        ret = line_compare_fun(proc_line, ref_line,
                               "Line %d contents" % (lnum + 1,))
        if ret:
            return ret
    return None


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


def run_and_score_case(program, defaults, case_def, validator):
    opts = dict(defaults)
    opts.update(case_def)
    process_out = run_case(program, **opts)
    return validator(opts, process_out)


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
        if timeout > 0:
            timer = threading.Timer(timeout, kill_proc, [process])
            timer.start()

        process_out, _ = process.communicate(inp)
    except Exception as e:
        raise
        return str(e)
    finally:
        if process:
            kill_proc(process)
        if timeout > 0:
            timer.cancel()
    if process.poll() != 0:
        return "Bad process exit status: %d" % (process.poll(),)

    if output_file != '<stdout>':
        with open(output_file, 'rb') as out_f:
            process_out = out_f.read()
    process_out = process_out.decode('utf8')

    return process_out


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
    for case_num, case_def in problem_cases:
        print('Running case %d... ' % (case_num,), end='')
        case_ret = run_and_score_case(
            program, problem_def['defaults'], case_def, problem_validator)
        if case_ret is None:
            print('OK!')
        else:
            failed_cases.append(case_num)
            print('Failed:')
            print(case_ret)

    if failed_cases:
        print('\nSome test cases have failed. '
              'To rerun the failing cases execute:')
        testset_opt = ''
        if args.testset:
            testset_opt = ' --testset %s' % (shellquote(args.testset),)
        cases_opt = '--cases ' + ','.join([str(fc) for fc in failed_cases])
        print('python validator.py%s %s %s %s' %
              (testset_opt, cases_opt, args.problem, program))
