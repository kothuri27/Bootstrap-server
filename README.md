# Multi-Server File Transfer System

## Disclaimer:

Please follow the sequence of steps as given below. Bootstrap is designed to accept all four servers first and then handle multiple clients.

### HACK:

To run multiple servers, execute the fileserver program multiple times, each time with different IP addresses and port numbers. Instead of writing separate code for each server, we have utilized the same code and created multiple instances, thereby handling multiple clients.

Please note that Bootstrap can handle only up to four file servers, as specified in the project requirements.

Clients are closed after receiving the file, as authentication is required again for subsequent operations.

Store the file you want to send in the same local folder.

---

## Steps for Execution:

1. **Compile Bootstrap Program**:
    - Compile the Bootstrap program using the g++ compiler.

2. **Bind the File Server (Text File)**:
    - After Bootstrap is ready, bind the Text File Server.

3. **Bind the Image Server**:
    - Bind the Image Server.

4. **Bind the Video Server**:
    - Bind the Video Server.

5. **Bind the PDF Server**:
    - Bind the PDF Server.

    *Note: The order of binding is user-defined.*

6. **Run the Client Program**:
    - Execute the client program and take input (type of server) from the client.

7. **Repeat Step 6**:
    - Run Step 6 for multiple times to accommodate multiple clients.

---

This README provides a basic overview of the system and instructions for execution. Ensure that all steps are followed sequentially for proper functionality.

For any further inquiries or issues, please refer to the project documentation or contact the project team.

--- 
