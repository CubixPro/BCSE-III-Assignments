### Follow me guide
* start the server and then start one or multiple clients (all in different terminals)
* You will be promted with some options for the clients...fill them accordingly
* Now you should land upon cyan or red colored terminal showing your username
* Now you need to bind with the server with following command.(The command is same irrespective of your role)</br>
```
bind 127.0.0.1 9000
```
* You are logged into the server(see server prompt)
* Now you can enter your commands. The commands follow a **specific and different order** for guest(cyan) and manager(red) users.

```
# an example of perfect command for guest
# general outline is: operation attribute value(only for put)
get cityname get phone put roll 98
```
```
# an example of perfect command for manager
# general outline is: operation username attribute value(for put)
get bob cityname put my roll 89 put bob age 65 get my age
```
* guest has a special command ```upgrademe`` which upgrades their privillage to manager. When promted with a password put ```iammanager``` as password.
* ```end``` ends the session with server and should be used as a single command.
* Feel free to mess with the code! but **DON'T MESS WITH THE SLEEPS**
