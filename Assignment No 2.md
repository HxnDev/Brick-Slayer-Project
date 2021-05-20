

CS 201/218 D ATA STRUCTURES

**Assignment # 02**

**Guidelines**

\1. Submit the zip folder (18X-XXXX) containing the code files only.

\2. Any plagiarism in assignment will lead to **zero** marks.

\3. Use of STL is not allowed under any circumstances.

\4. Only the submissions with executable code (i.e. code without any errors) will be accepted.

\5. The marks division will be as follows;

a. 50 Marks if the code is generating the right output for the given files.

b. 50 Marks if the code generates right output for different files.

\6. Submission sent to the emails will not be graded.

\7. Late submission of the assignment will be open for 1 day and will be marked with 30% penalty.

**Due Date and Time:**

**Submission Policy**

All the submissions MUST be uploaded on slate. Solutions sent to the emails will not be graded.

To avoid last minute problems (unavailability of slate, load shedding, network down etc.), you are

strongly advised to start working on the assignment from day one.

**Plagiarism Policy**

Solutions of all the sections will be placed in a central repository and will be scanned for plagiarism. All

the plagiarized solutions will be marked zero.

**Description**

Printers typically can print only a single document at a time and require seconds or minutes to do so. If

more than one application requires printer’s access, it might result in delay and slow down the

application for as long as the printer is busy in serving other application. ‘**Printer spooling**’ has overcome

this delay, as the documents formatted for printing are stored into an area on a disk and retrieved and

printed by a printer at its own rate. With spooling, multiple processes can write documents to a print

queue without waiting. As soon as a process has written its document to the spool device, the process

can perform other tasks, while a separate printing process operates the printer.

In this activity, you are required to implement printer spooler for a working environment which is

equipped with **3 printers** using concepts of Linked Lists and Queues. Each node in the linked list





**PrinterSpooler** depicts a **printer** with a **printer\_id**, **current\_load percentage (**value will be calculated at

each insertion of the document from max capacity and current\_load. The formula is as follows;

current\_load = current\_load + (

( no.of page / max\_capacity ) \*100

)

**), maximum capacity & documentQueue**. Document Queue can have multiple documents and each

document will have **doc\_id, no.of pages.** There will be an ordered linked list of **users** as well with

**user\_id, priority and DocumentQueue (**Queue might contain more than one document**).** The **document**

**Queue** in user list will have documents in the first come first serve order whereas; the document Queue

of printers will be filled by facilitating the documents coming from the high priority users.

*Insertion:*

·

Every time when a high priority user sends a document to print; the spooler identifies the

suitable printer between the first 2 printers (Suitable printer will be the one having the

current\_load less than 50% and space to accommodate the new document i.e. no. of pages in

the document must not be greater than the available limit of the printer.). if both of the first

two printers are not suitable for printing the document then the document will be added into

the Document Queue of the third printer.

*Deletion:*

·

·

If all the documents in a user ordered linked list gets printed and the user’s **DocumentQueue** is

empty then User node gets deleted.

Once the printer has completed the print of a certain document; the node of the document will

be deleted from both User document queue and spooler document queue after writing the

status in the out.txt file.





**Figure1: printerSpooler** Printer1

Following is the format of user.txt file;

User\_ID Priority TotalDocuments [Doc\_ID TotalPages]List

Following is the format of printer.txt file;

Printer\_ID MaxCapacity

The format of out.txt should be as follows;

User\_ID Doc\_ID Printer\_ID

