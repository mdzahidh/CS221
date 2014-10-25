import sys
import csv

class mapreader:
    def __init__(self, fileobj):
        self.csvreader = csv.reader(fileobj)

    def read(self):
        mapvals = []
        for row in self.csvreader:
            vals = [float(x) for x in row]
            mapvals.append(vals)

        return mapvals

