# -*- coding: UTF-8 -*-
# the above line is for limited Python2 compatibility
# this script is intended for Python3
#
import argparse
import datetime
from distutils.spawn import find_executable
import getpass
import logging
import os
import os.path
from os.path import expanduser
import platform

try:
    from shutil import which
except ImportError as e:
    print(e)
    print("You are probably using Python2.x which is obsolete")
    print("Run this script with Python3 for better results")

import socket
import subprocess
import sys


class DoubleLog():
    """
        setup  full logging in a single call using a kind-of Façade pattern
    """

    def __init__(self, filename):
        logger = logging.getLogger()
        logger.setLevel(logging.DEBUG)
        # log file
        file_formatter = logging.Formatter('%(message)s')
        file_handler = logging.FileHandler(filename, mode='w')
        file_handler.setLevel(logging.DEBUG)
        file_handler.setFormatter(file_formatter)
        logger.addHandler(file_handler)
        # console
        stream_handler = logging.StreamHandler()
        stream_handler.setLevel(logging.DEBUG)
        stream_formatter = logging.Formatter('%(message)s', "%H:%M:%S")
        stream_handler.setFormatter(stream_formatter)
        logger.addHandler(stream_handler)
# class DoubleLog


d = {}  # a global dict to remember already collected info


def remember(**kwargs):
    """update the dict with the collected info pieces"""
    for k, v in kwargs.items():
        d[k] = v


def checkPlatform():
    logging.info("\n\n -- Platform --\n")
    try:
        remember(_os=os.name)
    except Exception as e:
        remember(_os="Unknown-os")
        logging.error(e)

    try:
        remember(_system=platform.system())
    except Exception as e:
        remember(_system="Unknown-system")
        logging.error(e)

    try:
        remember(_release=platform.release())
    except Exception as e:
        remember(_release="Unknown-release")
        logging.error(e)

    try:
        remember(_homepath=os.path.expanduser("~"))
    except Exception as e:
        remember(_homepath="Unknown-homepath")
        logging.error(e)

    logging.info("OS: %s %s, aka \"%s\"" %
                 (d["_system"], d["_release"], d["_os"]))
    logging.info("Home path: %s" % (d["_homepath"]))


def checkPath(p):
    """
        p is a string, made of space-separated words.
        checkPath retrieves the PATH entries containing at least one of
        these words
    """
    def isRelated(w):
        ref = p.upper().split(" ")
        for r in ref:
            return r in w.upper()
    try:
        l = [w for w in filter(isRelated, os.getenv("PATH", "").split(";"))]
    except Exception:
        l = []
    if l:
        s = "PATH includes (%s)-related values:\n " % (p)
        s += ("\n ").join(l)
        logging.info(s)


def getPythonPath():
    exe = "python.exe" if d["_system"] == "Windows" else "python"
    try:
        ep = find_executable("python")
    except Exception:
        ep = None
    if ep is not None:
        return ep.replace(exe, "")
    return ""


def checkProg(p):
    """
        p is a string, the verb of a command entered from shell/cli
        tells if this command is available and if its leads to an
        executable file
    """
    try:
        wp = which(p)
    except Exception:
        wp = None
    try:
        ep = find_executable(p)
    except Exception:
        ep = None
    if wp is not None:
        logging.info("Command %s is available at:\n %s" % (p, wp))
    if ep is not None:
        logging.info("%s is executable from:\n %s" % (p, ep))
    return not(wp is None and ep is None)


def runProg(*args):
    """
        In some cases its easier to run the program, to check
        its presence and details
        args denotes the items in the command line
        ret is 0 for normal and non 0 for errors
    """
    try:
        ret = subprocess.run(args, stdout=subprocess.PIPE,
                             encoding='utf-8')
        logging.info("\"%s\" :\n %s" % (" ".join(args), ret.stdout[:72]+"..."))
        return ret.returncode
    except Exception as e:
        return 1


def checkPython():
    logging.info("\n\n -- Python --\n")
    try:
        remember(_pythonVersion=sys.version_info)
        logging.info("Python version %s.%s.%s" % (
            sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
        if sys.version_info[0] < 3:
            logging.info("You are using an obsolete version of Python")
            logging.info("Use Python 3 !")
    except Exception as e:
        remember(_PythonVersion="Unknown-version")
        logging.error(e)

    for p in "py python python2 python3".split(" "):
        checkProg(p)

    checkPath("python py")


def checkPip():
    logging.info("\n\n -- Pip --\n")
    for p in "pip pip2 pip3".split(" "):
        if checkProg(p):
            r = runProg(p, "--version")


def checkJupyter():
    logging.info("\n\n -- Jupyter --\n")
    ed = d.get("_envFolder", "")
    if ed == "":
        return
    for w in ["jupenv", "envjup", "jup", "jupyter"]:
        f = os.path.join(ed, w)
        if os.path.isdir(f):
            logging.info("Jupyter is installed at:\n %s" % (f))
            remember(_jupenv=f)
            break


def checkVenv():
    logging.info("\n\n -- Venv --\n")
    for py in "python python3 python2".split(" "):
        r = runProg(py, "-m", "venv", "-h")
        if r == 0:
            break
    if r:
        logging.error("The \"venv\" tool is missing")

    hd = d["_homepath"]
    for w in ["environments", "environnements", "environment", "environnement"]:
        f = os.path.join(hd, w)
        if os.path.isdir(f):
            logging.info("Environnement folder is: %s" % (f))
            remember(_envFolder=f)
            break


def checkIdle():
    logging.info("\n\n -- Idle --\n")
    if d["_system"] == "Windows":
        #
        # Python Path + Lib/idlelib/idle.pyw
        #
        first = True
        pp = getPythonPath()
        idledir = os.path.join(pp, "Lib", "idlelib")
        if os.path.isdir(idledir):
            for w in "idle.py idle.pyw".split(" "):
                f = os.path.join(idledir, w)
                if os.path.isfile(f):
                    if first:
                        logging.info("Found at:")
                        first = False
                    logging.info("%s" % (f))
    else:
        checkProg("idle")


def checkNppp():
    logging.info("\n\n -- Notepad++ --\n")
    first = True
    for f in [
        "C:\\Program Files (x86)\\Notepad++\\notepad++.exe",
        "C:\\Program Files\\Notepad++\\notepad++.exe"]:
        if os.path.isfile(f):
            if first:
                logging.info("Found at:")
                first = False
            logging.info("%s" % (f))
    if first:
        logging.error("Could not find notepad++ in its usual locations")


def checkPycharm():
    logging.info("\n\n -- PyCharm --\n")
    if d["_system"] == "Windows":
        pcdir = "C:\\Program Files\\JetBrains\\"
        if os.path.isdir(pcdir):
            #
            #Example: "Pycharm Community Edition 2019.2\bin"
            #
            for f in os.listdir(pcdir):
                if f.startswith("PyCharm Community Edition 20"):
                    g = os.path.join(pcdir, f)
                    if os.path.isdir(g):
                        logging.info("Found at:\n %s" % (g))
                    else:
                        logging.error("Could not find Pycharm")
                else:
                    logging.error("Could not find Pycharm")
        else:
            logging.error("Could not find Pycharm")
    else:
        logging.info("Cannot check PyCharm installation @ %s" % (d["_system"]))


def main():
    #
    # Parse cmd line
    #
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--dump",
                        action='store_true',
                        help="dumps the dictionary at the end of the report")
    args = parser.parse_args()
    #
    # collect minimal info, to setup log file
    #
    remember(_isodate=datetime.datetime.now().strftime("%Y-%m-%d"))
    remember(_timestamp="%s" %
             (datetime.datetime.now().strftime("%d-%m-%Y %H:%M:%S")))
    try:
        remember(_username=getpass.getuser())
    except Exception:
        remember(_username="Unknown-user")

    try:
        remember(_hostname=socket.gethostname())
    except Exception:
        remember(_username="Unknown-host")
    remember(_logFile="%s@%s.log" % (d["_username"], d["_hostname"]))
    DoubleLog(d['_logFile'])
    #
    # initial message
    #
    s = "Analysis of %s@%s started at %s" % (
        d["_username"], d["_hostname"], d["_timestamp"])
    logging.info(s)
    #
    # show basic platform info
    #
    checkPlatform()
    #
    # Python installation and versions
    #
    checkPython()
    #
    # Pip availability
    #
    checkPip()
    #
    # Venv availability
    #
    checkVenv()
    #
    # Idle availability
    #
    checkIdle()
    #
    # On windows only, check Notepad++
    #
    if d["_system"] == "Windows":
        checkNppp()
    #
    #
    #
    checkJupyter()
    #
    #
    #
    checkPycharm()
    #
    # final message
    #
    s = "\n\nAnalysis of %s@%s completed at %s" % (d["_username"], d["_hostname"],
                                                   "%s" % (datetime.datetime.now().strftime("%d-%m-%Y %H:%M:%S")))
    logging.info(s)
    #
    #
    #
    if args.dump:
        logging.info("\n")
        for k, v in sorted(d.items()):
            logging.info("%s --> %s" % (k, v))


if __name__ == "__main__":
    main()