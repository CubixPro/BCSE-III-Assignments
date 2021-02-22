### Setup the Server
Run the server with the following terminal command `python server_multiple.py [port number](optional)`
Default port number is `1233`

### Setup the Clients
Run a client with the following terminal commands `python client_multiple.py [ip address] [port number] [more than one queries]`

While setting up the clients from the terminal, it opens in guest mode and supports only the `get/put` queries. You can access the guest key value pairs from an admin session using the given _ID_ at the beginning. 

To continue the session press `y`

The commands supported now are
* `get [username](optional) [key]`
* `put [username](optional) [key] [value]`
* `upgrade [admin password]`
* `login [username] [password]`

##### Put one query in each prompt.

