#! /usr/bin/python
import s, sys, subprocess

if __name__ == '__main__':
  
    command = sys.argv[1]
    if not command:
        command = ["ls"]
    print "cmd is" +  str(command)
    
    def f (changed_files, removed_files):
        print changed_files
        if changed_files:
	    for fileName in changed_files:
		commandToexec = command.split(' ')
		commandToexec.append(fileName)
		subprocess.call(commandToexec)
	    print 'Removed', removed_files

    dirs = sys.argv[2:]
    if not dirs:
        dirs = ["."]
    
    dirwatch.Dirwatch(dirs, f, 1).watch()
    