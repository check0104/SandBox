#!/usr/bin/python3

import os
import sys
import shutil

def _check_sudo_permissions():
    try:
        test_file_path = "/etc/sbxtest"
        with open(test_file_path, 'w') as fout:
            pass
        os.remove(test_file_path)
    except PermissionError:
        sys.stderr.write("Please run this script as sudo!\n")
        quit(1)

def _safe_remove_dir(dir_path):
    try:
        shutil.rmtree(dir_path)
    except FileNotFoundError:
        print("Dir {} not found".format(dir_path))

def _safe_remove(file_path):
    try:
        os.remove(file_path)
    except FileNotFoundError:
        print("File {} not found".format(file_path))

def main():
    _check_sudo_permissions()
    ans = input("Do you really want to remove all configuration files of SandBox (yes/no)?")
    if ans != "Yes" and ans != 'y' and ans != 'yes':
        print("Aborting")
        quit(0)
    print("Disabling services")
    os.system("systemctl disable sandbox.service")
    os.system("systemctl disable librespot.service")
    os.system("systemctl stop sandbox.service")
    os.system("systemctl stop sandbox.service")
    print("Removing files")
    _safe_remove("/etc/systemd/system/librespot.service")
    _safe_remove("/etc/systemd/system/sandbox.service")
    _safe_remove("/opt/sandbox/start_librespot.sh")
    _safe_remove("/opt/sandbox/config.ini")
    _safe_remove("/opt/sandbox/sandbox.log")
    _safe_remove_dir("/opt/sandbox/cache")
    print("success! It is now safe to uninstall the sandbox")

if __name__=='__main__':
    main()
