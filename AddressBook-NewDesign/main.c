/*Name:Madhan kumar P
Start Date:10-12-25
End Date:15-12-25
Description:Address Book

(Create Contact)
Input:
User enters:
1. Name
2. Phone number
3. Email ID

Output:
Contact details are stored successfully in the address book.

(List Contact)
Input:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit

Input: 5

Output:
All saved contacts are displayed in sorted order by name.

(Edit Contact)
Input:
User selects search option:
1. Name
2. Phone
3. Email
Then enters the search value.

Output:
If contact is found, contact details are displayed.
Else, message "No contacts found matching" is printed.

(Delete Contact)
Input:
User selects delete option:
1. Name
2. Phone
3. Email
Then enters the value.

Output:
If contact exists, it is deleted successfully.
Else, message "No contacts found matching" is displayed.
*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice, sortChoice=0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf(">>>>>>>>| Welcome to the Address Book Application |<<<<<<<<\n");
        printf("===================>Address Book Menu<=====================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving\n");
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
