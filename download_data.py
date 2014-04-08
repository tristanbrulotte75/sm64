import subprocess

url_base = 'https://googledrive.com/host/0B_WJBlETj-zLN0lNRUpaQzg0WGs/'

for i in range(121):
    subprocess.call(['wget', '-nc', '-P', 'data', url_base + 'star_%s.dat' % i])
