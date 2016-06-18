# -*- coding: utf-8 -*-

from distance import word_distance
import codecs
from mpi4py import MPI
import sys
import pprint
import time

pp = pprint.PrettyPrinter()

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
nodes_count = comm.Get_size()

TAG_REQUEST = 1
TAG_RESPONSE = 2

MASTER = 0


def read_dictionary(filename):
    content = codecs.open(filename, mode='r', encoding='utf-8').read()
    return content.split()


def master():
    dictname = "malutki.txt"
    term = "miud"

    if len(sys.argv) >= 3:
        dictname = sys.argv[1]
        term = sys.argv[2]
    prettyprint = len(sys.argv) != 4

    slave_count = nodes_count - 1
    dictionary = read_dictionary(dictname)
    words_per_slave = len(dictionary) // slave_count

    start = time.perf_counter()

    for i in range(0, nodes_count - 1):
        part_of_dict = dictionary[i * words_per_slave:i * words_per_slave + words_per_slave]
        if i == nodes_count - 2:
            part_of_dict = dictionary[i * words_per_slave:]
        initmsg = {'offset': i * words_per_slave,
                   'term': term,
                   'dictionary': part_of_dict}

        comm.send(initmsg, dest=i + 1, tag=TAG_REQUEST)
    checkpoint = time.perf_counter()

    best_index = -1
    best_distance = 9999999
    best_match = None
    for i in range(1, nodes_count):
        data = comm.recv(source=MPI.ANY_SOURCE, tag=TAG_RESPONSE)
        if data["distance"] < best_distance:
            best_distance = data['distance']
            best_match = data['word']
            best_index = data['index']

    stop = time.perf_counter()
    if prettyprint:
        print("Got response {} on offset {} with score {}".format(best_match, best_index, best_distance))
        print("Elapsed time {}s".format(stop - start))
        print("Checkpoint time {}s".format(checkpoint - start))
    else:
        print("{} {}".format(stop - start, checkpoint - start))


def slave():
    query = comm.recv(source=0, tag=TAG_REQUEST)
    term = query['term']
    best_index = -1
    best_distance = 9999999
    best_match = term

    for i, x in enumerate(query['dictionary']):
        d = word_distance(x, term)
        if d < best_distance:
            best_distance = d
            best_match = x
            best_index = i

    comm.send(
        {'word': best_match,
         'index': best_index + query['offset'],
         'distance': best_distance},
        dest=MASTER,
        tag=TAG_RESPONSE
    )


if rank == 0:
    master()
else:
    slave()

MPI.Finalize()
