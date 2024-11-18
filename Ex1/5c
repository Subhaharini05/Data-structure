#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the linked list node
typedef struct Song {
    char title[50];
    struct Song* next;
} Song;

// Function prototypes
Song* createSong(const char* title);
void addSong(Song** head, const char* title);
void removeSong(Song** head, const char* title);
void displayPlaylist(Song* head);

int main() {
    Song* playlist = NULL;  // Initialize an empty playlist

    int choice;
    char title[50];

    while (1) {
        printf("\nMusic Playlist Menu:\n");
        printf("1. Add Song\n");
        printf("2. Remove Song\n");
        printf("3. Display Playlist\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character

        switch (choice) {
            case 1:
                printf("Enter song title to add: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;  // Remove newline character
                addSong(&playlist, title);
                break;
            case 2:
                printf("Enter song title to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;  // Remove newline character
                removeSong(&playlist, title);
                break;
            case 3:
                displayPlaylist(playlist);
                break;
            case 4:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to create a new song node
Song* createSong(const char* title) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newSong->title, title);
    newSong->next = NULL;
    return newSong;
}

// Function to add a song to the playlist
void addSong(Song** head, const char* title) {
    Song* newSong = createSong(title);
    if (*head == NULL) {
        *head = newSong;
    } else {
        Song* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Song '%s' added to the playlist.\n", title);
}

// Function to remove a song from the playlist
void removeSong(Song** head, const char* title) {
    if (*head == NULL) {
        printf("The playlist is empty. Cannot remove song.\n");
        return;
    }

    Song* temp = *head;
    Song* prev = NULL;

    // Check if the song to remove is the first in the list
    if (strcmp(temp->title, title) == 0) {
        *head = temp->next;
        free(temp);
        printf("Song '%s' removed from the playlist.\n", title);
        return;
    }

    // Search for the song to remove
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the song was not found
    if (temp == NULL) {
        printf("Song '%s' not found in the playlist.\n", title);
        return;
    }

    // Remove the song
    prev->next = temp->next;
    free(temp);
    printf("Song '%s' removed from the playlist.\n", title);
}

// Function to display the playlist
void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    printf("Current Playlist:\n");
    Song* temp = head;
    while (temp != NULL) {
        printf("- %s\n", temp->title);
        temp = temp->next;
    }
}
