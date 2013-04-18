#!/usr/bin/env python

import threading
import sys
import subprocess

class AttackThread(threading.Thread):
  def __init__(self):
    threading.Thread.__init__(self)

  def run(self):
    subprocess.Popen("./UserStorage_client", shell = True)


def main(argv):
  threads = [AttackThread() for i in range(int(argv[1]))]

  for thread in threads:
    thread.daemon = True

  [thread.start() for thread in threads]
  [thread.join() for thread in threads]

if __name__ == '__main__':
  main(sys.argv)
