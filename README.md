# moDRACfucker

## Requirements

* libssh

## Usage

```
$ ./modracfucker 
missing operand
 ./modracfucker <host> <port> <user> <password> [defaultpassword]
```

## Example

```
$ ./modracfucker 1.2.3.4 22 root password
OK - DRAC 1.2.3.4
$ ./modracfucker 1.2.3.4 22 root notvalidpassword
WARNING - DRAC 1.2.3.4 with default password(calvin)
$ ./modracfucker 1.2.3.4 23 root badportdemo
CRITICAL - DRAC 1.2.3.4: Error connecting to localhost: Remote host closed connection
```
