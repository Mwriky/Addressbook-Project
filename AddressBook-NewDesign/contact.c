#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria using strcmp
    if(addressBook->contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }
    
    // Bubble sort by name using strcmp
    for(int i = 0; i < addressBook->contactCount - 1; i++) {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++) {
            // strcmp returns negative if first < second, positive if first > second, 0 if equal
            if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0) {
                // Swap contacts
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    
    printf("\n--- All Contacts (Sorted by Name) ---\n");
    printf("%-20s %-15s %-25s\n", "Name", "Phone", "Email");
    printf("--------------------------------------------------------\n");
    
    
    for(int i = 0; i < addressBook->contactCount; i++) {
        printf("%-20s %-15s %-25s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("---------------------------------------------------------\n");
    printf("\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// validation functions

int ValidName(const char *name) //name
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!(name[i] >= 'A' && name[i] <= 'Z') &&
            !(name[i] >= 'a' && name[i] <= 'z') &&
            name[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int ValidPhone(const char *phone) // phone
{
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }
    return 1;
}

int ValidEmail(const char *email) //email
{
    int len = strlen(email);

    // must end with @gmail.com
    if (len < 10 || strcmp(email + len - 10, "@gmail.com") != 0)
        return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (!(email[i] >= 'a' && email[i] <= 'z') &&
            !(email[i] >= '0' && email[i] <= '9') &&
            email[i] != '.' &&
            email[i] != '_' &&
            email[i] != '@')
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{

	/* Define the logic to create a Contacts */
    
     // Check address book capacity
       printf("\n========== CREATE NEW CONTACT ==========\n");

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("❌ Address book is full.\n");
        return;
    }

    char name[50], phone[50], email[50];

    while (1)
    {
        printf("Enter Name  : ");
        scanf(" %[^\n]", name);

        if (!ValidName(name))
        {
            printf("❌ Invalid name (alphabets and spaces only).\n");
            continue;
        }
        break;
    }


    while (1)
    {
        int duplicate = 0;

        printf("Enter Phone : ");
        scanf(" %[^\n]", phone);

        if (!ValidPhone(phone))
        {
            printf("❌ Invalid phone number (10 digits only).\n");
            continue;
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                printf("❌ Phone number already exists.\n");
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
            break;   
    }


    while (1)
    {
        int duplicate = 0;

        printf("Enter Email : ");
        scanf(" %[^\n]", email);

        if (!ValidEmail(email))
        {
            printf("❌ Invalid email (lowercase, @gmail.com only).\n");
            continue;
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                printf("❌ Email already exists.\n");
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
            break;  
    }


    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    printf("✅ Contact created successfully.\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search using strcmp and strstr */
    int choice;
    char searchTerm[50];
    int flag = 0;
    
    printf("1. Name  2. Phone  3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        printf("Enter name: ");
    }
    else if(choice == 2) {
        printf("Enter phone number: ");
    }
    else if(choice == 3) {
        printf("Enter email: ");
    }
    else {
        printf("Invalid choice!\n");
        return;
    }
    
    scanf("%s", searchTerm);
    
    printf("\n--- Search Results ---\n");
    printf("Name\t\tPhone\t\tEmail\n");
    printf("---------------------------------------------\n");
    
    for(int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;
        
        if(choice == 1) {
            if(strstr(addressBook->contacts[i].name, searchTerm) != NULL) {
                match = 1;
            }
        }
        else if(choice == 2) {
            if(strcmp(addressBook->contacts[i].phone, searchTerm) == 0) {
                match = 1;
            }
        }
        else if(choice == 3) {
            if(strcmp(addressBook->contacts[i].email, searchTerm) == 0) {
                match = 1;
            }
        }
        
        if(match) {
            printf("%s\t\t%s\t%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            flag++;
        }
    }
    
    if(flag == 0) {
        printf("No contacts found matching '%s'\n", searchTerm);
    } else {
        printf("\nTotal matches found: %d\n", flag);
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    /*Search the contact and edit the contact */
    int choice;
    char searchTerm[50];
    char newValue[50];
    int found = 0;
    
    printf("1. Name  2. Phone  3. Email\n");
    printf("Enter search criteria: ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        printf("Enter name to search: ");
    }
    else if(choice == 2) {
        printf("Enter phone number to search: ");
    }
    else if(choice == 3) {
        printf("Enter email to search: ");
    }
    else {
        printf("Invalid choice!\n");
        return;
    }
    
    scanf("%s", searchTerm);
    
    for(int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;
        
        if(choice == 1 && strstr(addressBook->contacts[i].name, searchTerm) != NULL) {
            match = 1;
        }
        else if(choice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) {
            match = 1;
        }
        else if(choice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0) {
            match = 1;
        }
        
        if(match) {
            printf("\nContact found: %s | %s | %s\n", 
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            
            printf("What do you want to edit? (1. Name  2. Phone  3. Email): ");
            int editChoice;
            scanf("%d", &editChoice);
            
            if(editChoice == 1) {
                printf("Enter new name: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].name, newValue);
            }
            else if(editChoice == 2) {
                printf("Enter new phone: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].phone, newValue);
            }
            else if(editChoice == 3) {
                printf("Enter new email: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].email, newValue);
            }
            
            printf("Contact updated successfully!\n");
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("Contact not found!\n");
    } 
}

void deleteContact(AddressBook *addressBook)

{
    int choice;
    printf("Delete by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);

    char key[50];
    int indices[10];
    int matchCount = 0;

    printf("Enter value to search: ");
    scanf(" %[^\n]", key);

    // Search for matching contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strstr(addressBook->contacts[i].name, key)) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, key) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, key) == 0))
        {
            indices[matchCount++] = i;
        }
    }

    if (matchCount == 0)
    {
        printf("No matching contact found.\n");
        return;
    }

    // Display matching contacts
    printf("\nMatching Contacts:\n");
    printf("No\tName\t\tPhone\t\tEmail\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < matchCount; i++)
    {
        int idx = indices[i];
        printf("%d\t%s\t\t%s\t\t%s\n",
               i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }

    int select;
    printf("\nSelect contact number to delete: ");
    scanf("%d", &select);

    if (select < 1 || select > matchCount)
    {
        printf("Invalid selection.\n");
        return;
    }

    int deleteIndex = indices[select - 1];

    // Show selected contact
    printf("\nSelected Contact:\n");
    printf("Name  : %s\n", addressBook->contacts[deleteIndex].name);
    printf("Phone : %s\n", addressBook->contacts[deleteIndex].phone);
    printf("Email : %s\n", addressBook->contacts[deleteIndex].email);

    char confirm;
    printf("\nAre you sure you want to delete this contact? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    // Shift contacts left
    for (int i = deleteIndex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}