# User Guide

 - First, in a terminal window, start the server by saying `python3 server.py`
 - Now, in a different terminal window, start a client by saying `python3 client_node.py`
 - Remember, you can open as many clients as you want, by simply running `python3 client_node.py` on separate terminal windows.
 - You need to enter your name, and then enter the server address and port no. which is **127.0.0.1** and **8000** .
 - **Every signup/signin is as a guest by default**
 - Now, you can execute **GET** and **PUT** , as required in any order.
	 

    GET city
	 

    PUT city Kolkata

 
 - To change into manager mode, type `makemanager` , and enter the password `changeadmin` .
 - As a manager, you can **GET** and **PUT** by following the command with the username, eg:

	 GET [username] city 
 

	PUT [username] city Kolkata
- Type `end` to end the client session.



