#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

    FILE *fp = fopen("contact.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "File not Found\n");
        return;
    }

    while (fscanf(fp,
                  "%49[^,],%19[^,],%49[^\r\n] ",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}
