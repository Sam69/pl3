import ftplib
import pysftp
import os
import sys

os.system("ifconfig eth0 192.168.5.96 netmask 255.255.224.0")
os.system("ifconfig")
while True:
	op=input("Enter 1 to transfer file from BBB to M.\n2 to transfer M to BBB.\n3 to upload to FTP.\n4 to downlaod from FTP.\n")
	if op==1:
	        print "Sending file from BBB to M."
	  	dest_ip=raw_input("enter ip address of destination...:")
	  	user_name=raw_input("enter user name of destination...:")
	  	os.system("ls -l")
	  	src_file=raw_input("enter file to transfer from beagle bone ")
	  	dest_path=raw_input("enter destination path....")
	  	os.system("scp "+src_file+" "+user_name+"@"+dest_ip+":"+dest_path)
	
	elif op==2:
		print "Sending file from M to BBB"
		ip=raw_input("enter ip adress of machine from where you want to get file..:")
		user_login=raw_input("enter user login of the above machine...:")
		os.system("ssh "+user_login+"@"+ip+" ls -l /home/cnlab/")
		file_name=raw_input("enter file name to copy..(with path)")
		os.system("scp "+user_login+"@"+ip+":"+file_name+" /root")
		print("file successfully copied..now exiting from remote login")
		os.system("exit")	

	elif op==3:
                os.system("ls")
                fname=raw_input("Enter File Name: ")
                os.system("sftp cnlab@192.168.5.31")
                os.system("ls "+fname)

        elif op==4:
                os.system("sftp cnlab@192.168.5.31")
                os.system("ls")	

---option 3----------------------
3
B2.py		  merge.py		      x.py
b5.cpp		  mit.py		      yoyo.csv
b8.c		  n4_b17.py		      y.py
b8.cpp		  n4b17.py		      z.py
bas1.py		  n4b2.py

Enter File Name: y.py
cnlab@192.168.5.31's password: 
Connected to 192.168.5.31.

sftp> put ur.py
Uploading ur.py to /home/cnlab/ur.py
ur.py                                         100%   40     0.0KB/s   00:00    

sftp> ls
scan0028.pdf                           1                                       
y.py                                   vecadd.c                                
vij.py                                  workspace                               
x.py                                    y.py                                    

sftp> exit
ur.py

------option 4--------------------
4
cnlab@192.168.5.31's password: 
Connected to 192.168.5.31.

sftp> ls
scan0028.pdf                           1                                       
y.py                                   vecadd.c                                
vij.py                                  workspace                               
x.py 

sftp> get x.py
local: x.py remote: x.py 
200 PORT command successful. Consider using PASV.
150 Opening BINARY mode data connection for file (33 bytes).
226 File send OK.
33 bytes received in x.xx secs (1.192 MB/s).

sftp> exit

