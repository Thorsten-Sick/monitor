#!/usr/bin/env python

"""
Compare two log files to find differences in API monitoring. Use that on an old and a new log.
"""

import json

class Compare():
    def __init__(self):
        self.base = {}
        self.new = {}

    def add_report(self, filename, base=True):
        with open(filename)as fh:
            data = json.load(fh)
            if base:
                self.base["raw"] = data
            else:
                self.new["raw"] = data

    def _parse_old(self, report):
        apis = []
        processes = []
        pcount = 0
        for p in report["behavior"]["processes"]:
            for c in p["calls"]:
                apis.append(c["api"])
            pcount += 1
        self.base["apis"] = apis
        self.base["pcount"] = pcount

    def _parse_new(self, report):
        apis = []
        pcount = 0
        for pid in report["behavior2"]["processes"][0]["processes"]:
            pcount += 1
            for tid in report["behavior2"]["processes"][0]["processes"][pid]["calls"]:
                for c in report["behavior2"]["processes"][0]["processes"][pid]["calls"][tid]:
                    apis.append(c["api"])
        self.new["apis"] = apis
        self.new["pcount"] = pcount

    def _parse_one(self, report):
        if "behavior" in report:
            return self._parse_old(report)
        elif "behavior2" in report:
            return self._parse_new(report)


    def parse(self):
        """ Parse reports
        :return:
        """
        self._parse_one(self.base["raw"])
        self._parse_one(self.new["raw"])

    def find_first_crashes(self):
        """ Identify API calls in old, but not in new, sorted by appearance in old. These are the first suspects for crashes

        :return:
        """
        crashes = []
        for i in self.base["apis"]:
            if not i in self.new["apis"]:
                if not i in crashes:
                    crashes.append(i)
        return crashes




if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description='Compare old Cuckoo json report and new one')
    parser.add_argument('base', help='the base report')
    parser.add_argument('new', help='the new one')
    parser.add_argument("--missing_api", default=False, action="store_true", help="List API calls in base that are not in new. chronological ordering. Start fixing them from top to bottom.")
    parser.add_argument("--processes", default=False, action="store_true", help="List monitored processes")

    args = parser.parse_args()
    c = Compare()
    c.add_report(args.base, base=True)
    c.add_report(args.new, base=False)
    c.parse()
    if args.missing_api:
        print ("\n".join(c.find_first_crashes()))
    if args.processes:
        print ("Number processes Old: %d New %d\n" % (c.base["pcount"], c.new["pcount"]))
