#!/usr/bin/env python

"""
Compare two log files to find differences in API monitoring. Use that on an old and a new log.
"""

import json

class Compare():
    def __init__(self):
        self.base_raw = None
        self.new_raw = None
        self.base_apis = None
        self.new_apis = None

    def add_report(self, filename, base=True):
        with open(filename)as fh:
            data = json.load(fh)
            if base:
                self.base_raw = data
            else:
                self.new_raw = data

    def _parse_old(self, report):
        apis = []
        for p in report["behavior"]["processes"]:
                for c in p["calls"]:
                    apis.append(c["api"])
        return apis

    def _parse_new(self, report):
        apis = []
        for pid in report["behavior2"]["processes"][0]["processes"]:
            for tid in report["behavior2"]["processes"][0]["processes"][pid]["calls"]:
                for c in report["behavior2"]["processes"][0]["processes"][pid]["calls"][tid]:
                    apis.append(c["api"])
        return apis

    def _parse_one(self, report):
        if "behavior" in report:
            return self._parse_old(report)
        elif "behavior2" in report:
            return self._parse_new(report)


    def parse(self):
        """ Parse reports
        :return:
        """

        self.base_apis = self._parse_one(self.base_raw)
        self.new_apis = self._parse_one(self.new_raw)

    def find_first_crashes(self):
        crashes = []
        for i in self.base_apis:
            if not i in self.new_apis:
                if not i in crashes:
                    crashes.append(i)
        return crashes





if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description='Compare old Cuckoo json report and new one')
    parser.add_argument('base', help='the base report')
    parser.add_argument('new', help='the new one')
    parser.add_argument("--missing_api", default=False, action="store_true", help="List API calls in base that are not in new. chronological ordering. Start fixing them from top to bottom.")

    args = parser.parse_args()
    c = Compare()
    c.add_report(args.base, base=True)
    c.add_report(args.new, base=False)
    c.parse()
    if args.missing_api:
        print ("\n".join(c.find_first_crashes()))
