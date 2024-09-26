import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8826  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall("Hello\0".encode())
    data = s.recv(1024)
    print(data.decode())


    # Register process
    print("enter 1 to login 2 for signup ")
    register_choise = input()
    if  register_choise == 1:
        login()
    else:    
        signup()
    print("whelcom to trivia.com\n \
           enter 1 for create room\n\
           2 for join room\n \
           3 for statistic\n \
           4 for exit tha game")
    menue_choise = input()
    


def signup():
    pass

def login():
    pass
