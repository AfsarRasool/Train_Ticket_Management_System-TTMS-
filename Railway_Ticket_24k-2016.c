#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAIN_COUNT 100
#define MAX_SCHEDULES 100

int login(const char *filename, char username[], char password[]);
void signup(const char *filename, char name[], char pass[]);
void update_password(const char *filename, char search_user_name[], char search_pass[]);
void display_booked_tickets(const char *filename, char username[], char password[]);
void wait_for_user();
void header();

// Trains Functions

char train_names[MAX_TRAIN_COUNT][50];
int train_count = 0;
char schedules[MAX_TRAIN_COUNT][MAX_SCHEDULES][200];
int schedule_count[MAX_TRAIN_COUNT] = {0};
int trains_revenue[MAX_TRAIN_COUNT][MAX_SCHEDULES] = {0};

void load_data(const char *filename);
void display_trains(const char *filename);
void update_train(const char *filename, int train_number);
void save_data(const char *filename);
void add_train(int train_number);

// User Functions
void book_ticket(const char *filename, const char *filename1, int train_number, char name[], char password[]);
void cancel_ticket(const char *filename, const char *filename1, int train_number, char name[], char password[]);
void display_cancelled_tickets(const char *filename, char username[], char password[]);
int main()
{
    int train_number;
    int choice, u_choice, a_choice;
    char user_name[50], password[50];
    const char *filename1 = "Trains.txt";
    const char *filename = "user_pass.txt"; // opening files
    const char *filename2 = "Admin.txt";
    load_data(filename1);

    do
    {
        system("cls");
        header();
        printf("1. User   2. Admin   3. Exit\n"); // HomePage
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
        { // user login system
            do
            {
                load_data(filename1); // Train Function Load Data
                system("cls");
                header();
                printf("1. Sign In   2. Log In   0. Exit\nEnter Your choice: "); // User options Home Page
                scanf("%d", &u_choice);
                getchar();
                system("cls");
                switch (u_choice)
                {
                case 1: // sign up
                    header();
                    printf("Enter Username: ");
                    fgets(user_name, sizeof(user_name), stdin);
                    int len = strlen(user_name);
                    if (user_name[len - 1] == '\n')
                    {
                        user_name[len - 1] = '\0';
                    }
                    printf("Enter Password: ");
                    fgets(password, sizeof(password), stdin);
                    len = strlen(password);
                    if (password[len - 1] == '\n')
                    {
                        password[len - 1] = '\0';
                    }
                    signup(filename, user_name, password);
                    wait_for_user();
                    break;
                case 2: // login by user
                    header();
                    printf("Enter Username: ");
                    fgets(user_name, sizeof(user_name), stdin);
                    len = strlen(user_name);
                    if (user_name[len - 1] == '\n')
                    {
                        user_name[len - 1] = '\0';
                    }
                    printf("Enter Password: ");
                    fgets(password, sizeof(password), stdin);
                    len = strlen(password);
                    if (password[len - 1] == '\n')
                    {
                        password[len - 1] = '\0';
                    }
                    if (login(filename, user_name, password))
                    { // logged into account
                        do
                        {
                            system("cls");
                            header();
                            printf("Welcome to Your Account\n\n");
                            printf("1. View Trains\n2. Book Ticket\n3. Cancel Ticket\n4. View Booked Tickets\n5. Update Password\n6.Cancelled Tickets\n0. Exit\n\nEnter Your Choice: ");
                            scanf("%d", &u_choice);
                            getchar();
                            switch (u_choice)
                            {
                            case 1:
                                display_trains(filename1);
                                wait_for_user();
                                break;
                            case 2:
                                display_trains(filename1);
                                printf("Enter Train Number:");
                                scanf("%d", &train_number);
                                getchar();
                                book_ticket(filename, filename1, train_number, user_name, password);
                                wait_for_user();
                                break;
                            case 3:
                                display_booked_tickets(filename, user_name, password);
                                printf("Enter Train Number:");
                                scanf("%d", &train_number);
                                getchar();

                                cancel_ticket(filename, filename1, train_number, user_name, password);
                                load_data(filename1);
                                wait_for_user();
                                break;
                            case 4:
                                system("cls");
                                header();
                                display_booked_tickets(filename, user_name, password);
                                wait_for_user();
                                break;
                            case 5: // update password by user
                                system("cls");
                                header();
                                printf("Enter Old Password: ");
                                fgets(password, sizeof(password), stdin);
                                password[strcspn(password, "\n")] = '\0';
                                update_password(filename, user_name, password);
                                wait_for_user();
                                break;
                            case 6: //  view cancelled tickets
                                system("cls");
                                header();
                                display_cancelled_tickets(filename, user_name, password);
                                wait_for_user();
                                break;

                            default:
                                if (u_choice != 0)
                                {
                                    printf("Invalid Choice\n");
                                    wait_for_user();
                                }
                                break;
                            }
                        } while (u_choice != 0);
                    }
                    else
                    {
                        system("cls");
                        header();
                        printf("Username or Password is incorrect\n");
                        wait_for_user();
                    }
                    break;
                case 0:
                    break;
                default:
                    printf("Have a nice day!\n");
                    wait_for_user();
                    break;
                }
            } while (u_choice != 0);
        }
        else if (choice == 2)
        { // Admin

            do
            {

                system("cls");
                header();
                printf("1. Sign In   2. Log In   0. Exit\nEnter Your choice: "); // Admin options Home Page
                scanf("%d", &a_choice);
                getchar();
                system("cls");
                switch (a_choice)
                {
                case 1: // sign up
                    header();
                    printf("Enter Admin Name: ");
                    fgets(user_name, sizeof(user_name), stdin);
                    int len = strlen(user_name);
                    if (user_name[len - 1] == '\n')
                    {
                        user_name[len - 1] = '\0';
                    }
                    printf("Enter Password: ");
                    fgets(password, sizeof(password), stdin);
                    len = strlen(password);
                    if (password[len - 1] == '\n')
                    {
                        password[len - 1] = '\0';
                    }
                    signup(filename2, user_name, password);
                    wait_for_user();
                    break;
                case 2: // login by Admin
                    header();
                    printf("Enter Admin Name: ");
                    fgets(user_name, sizeof(user_name), stdin);
                    len = strlen(user_name);
                    if (user_name[len - 1] == '\n')
                    {
                        user_name[len - 1] = '\0';
                    }
                    printf("Enter Password: ");
                    fgets(password, sizeof(password), stdin);
                    len = strlen(password);
                    if (password[len - 1] == '\n')
                    {
                        password[len - 1] = '\0';
                    }
                    if (login(filename2, user_name, password))
                    { // logged into account admin
                        do
                        {

                            system("cls");
                            header();
                            printf("Welcome to Your Account\n\n");
                            printf("1. View Trains\n2. Update Train\n3.Add New Train\n0. Exit\n\nEnter Your Choice: ");
                            scanf("%d", &a_choice);
                            getchar();
                            switch (a_choice)
                            {
                            case 1: // view trains
                                display_trains(filename1);
                                wait_for_user();
                                break;
                            case 2: // update trains
                            system("cls");
                                display_trains(filename1);
                                printf("Enter Train Number:");
                                scanf("%d", &train_number);
                                getchar();
                                update_train(filename1, train_number);
                                load_data(filename1);
                                wait_for_user();
                                break;
                            case 3: // add new train
                                printf("Enter Train Number: ");
                                scanf("%d", &train_number);
                                getchar();
                                add_train(train_number);
                                save_data(filename1);
                                wait_for_user();
                                break;
                            default:
                                break;
                            }
                        } while (a_choice != 0);
                    }
                    else
                    {
                        printf("Username or Password is incorrect\n");
                        wait_for_user();
                    }
                    break;
                default:
                    if (a_choice != 0)
                    {
                        printf("Invalid Choice\n");
                        wait_for_user();
                    }
                    break;
                }
            } while (a_choice != 0);
        }
        else if (choice == 3)
        {
            printf("Have a nice day!\n");
            return 1;
        }
        else
        {
            printf("Invalid Choice\n");
            wait_for_user();
        }
    } while (choice != 3);

    return 0;
}
// Trains Functions  Start

void cancel_ticket(const char *filename, const char *filename1, int train_number, char name[], char password[])
{
    FILE *user_file = fopen(filename, "r"); // user_pass.txt
    if (user_file == NULL)
    {
        printf("User file not opening\n");
        return;
    }

    FILE *temp_user = fopen("temp_user.txt", "w");
    if (temp_user == NULL)
    {
        printf("Temp user file not opening\n");
        fclose(user_file);
        return;
    }

    char fileline[200], userdata[200];
    char *fileUsername, *filePassword;
    int file_train_number, user_authentication = 0, booked_train_found = 0;
    char file_name[50], file_departure[50], file_destination[50], file_date[20], file_departure_time[20];
    int file_ticket_price,file_available_seats;
    char canceled_train_data[200] = "";

    // Check user credentials and remove the booked train
    while (fgets(fileline, sizeof(fileline), user_file) != NULL)
    {
        strcpy(userdata, fileline);
        userdata[strcspn(userdata, "\n")] = '\0';
        fileUsername = strtok(fileline, ";");
        filePassword = strtok(NULL, "\n");

        if (user_authentication && strcmp(userdata, "booked") == 0)
        {
            fprintf(temp_user, "%s\n", userdata);
            while (fgets(fileline, sizeof(fileline), user_file))
            {
                strcpy(userdata, fileline);
                userdata[strcspn(userdata, "\n")] = '\0';
                if (strcmp(userdata, "#") == 0)
                {
                    fprintf(temp_user, "%s\n", userdata);
                    break;
                }
                sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d", &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time, &file_ticket_price);
                if (file_train_number == train_number)
                {
                    booked_train_found = 1;
                    strcpy(canceled_train_data, userdata);
                    continue; // Skip adding this line to temp_user
                }
                else
                {
                    fprintf(temp_user, "%s\n", userdata);
                }
            }
            if (booked_train_found){   // it was necessary
                continue;
            }
            
            if (!booked_train_found)
            {
                printf("You have not booked this train yet!\n");
                fclose(user_file);
                fclose(temp_user);
                remove("temp_user.txt");
                return;
            }
        }

        else if (fileUsername != NULL && filePassword != NULL && strcmp(fileUsername, name) == 0 && strcmp(filePassword, password) == 0)
        {
            user_authentication = 1;
        }

        
            fprintf(temp_user, "%s\n", userdata);
            
    }

    fclose(user_file);
    fclose(temp_user);

    if (!user_authentication)
    {
        printf("Username or password incorrect.\n");
        remove("temp_user.txt");
        return;
    }

    if (remove(filename) != 0 || rename("temp_user.txt", filename) != 0)
    {
        perror("Error updating user file at Cancel Train");
        return;
    }

    if (!booked_train_found)
    {
        return;
    }

    FILE *train_file = fopen(filename1, "r"); // Trains.txt
    if (train_file == NULL)
    {
        printf("Train file not opening\n");
        return;
    }

    FILE *temp_train = fopen("temp_train.txt", "w");
    if (temp_train == NULL)
    {
        printf("Temp train file not opening\n");
        fclose(train_file);
        return;
    }
     char Cancelled_train_data[200];
    // Update the available seats in the train file
    while (fgets(fileline, sizeof(fileline), train_file) != NULL)
    {
        strcpy(userdata, fileline);
        userdata[strcspn(userdata, "\n")] = '\0';
        sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d", &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time,& file_available_seats ,&file_ticket_price);
        if (file_train_number == train_number)
        {
            file_available_seats++; // Increase available seats
           
            sprintf(Cancelled_train_data,"%d;%s;%s;%s;%s;%s;%d;%d",file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time, file_available_seats, file_ticket_price);
             fprintf(temp_train, "%s\n",Cancelled_train_data);
        }
        else
        {
            fprintf(temp_train, "%s\n", userdata);
        }
    }

    fclose(train_file);
    fclose(temp_train);

    if (remove(filename1) != 0 || rename("temp_train.txt", filename1) != 0)
    {
        perror("Error updating train file");
    }
    else
    {
        printf("Ticket cancelled successfully and seats updated!\n");
    }

    // Re-opening user file to update cancel information
    user_file = fopen(filename, "r");
    if (user_file == NULL)
    {
        printf("Error opening user file at Cancel Train cancel portion\n");
        return;
    }

    temp_user = fopen("user_temp.txt", "w");
    if (temp_user == NULL)
    {
        printf("Error opening user_temp file at Cancel Train cancel portion\n");
        fclose(user_file);
        return;
    }

    int found = 0, found1 = 0;
    while (fgets(fileline, sizeof(fileline), user_file) != NULL)
    {
        strcpy(userdata, fileline);
        userdata[strcspn(userdata, "\n")] = '\0';
        fileUsername = strtok(fileline, ";");
        filePassword = strtok(NULL, "\n");

         if (found1)
        {
            fprintf(temp_user, "%s\n", userdata);
            found1 = 0;
            found = 0;
        }

        else if (found && strcmp(userdata, "cencelled") == 0)
        {
            fprintf(temp_user, "%s\n", userdata);
            fprintf(temp_user, "%s\n", canceled_train_data);
            found1 = 1;
        }

        else if (fileUsername != NULL && filePassword != NULL && strcmp(fileUsername, name) == 0 && strcmp(filePassword, password) == 0)
        {
            fprintf(temp_user, "%s\n", userdata);
            found = 1;
        }
        else
        {
            fprintf(temp_user, "%s\n", userdata);
        }
    }

    fclose(user_file);
    fclose(temp_user);

    if (remove(filename) != 0 || rename("user_temp.txt", filename) != 0)
    {
        perror("Error updating user file at Cancel Train cancel portion");
    }
}


void book_ticket(const char *filename, const char *filename1, int train_number, char name[], char password[])
{
    FILE *user_file = fopen(filename, "r"); // user_pass.txt
    if (user_file == NULL)
    {
        printf("User file not opening\n");
        return;
    }

    FILE *train_file = fopen(filename1, "r"); // Trains.txt
    if (train_file == NULL)
    {
        printf("Train file not opening\n");
        fclose(user_file);
        return;
    }

    FILE *temp_user = fopen("temp.txt", "w");
    if (temp_user == NULL)
    {
        printf("Temp user file not opening\n");
        fclose(user_file);
        fclose(train_file);
        return;
    }

    char fileline[200], saveline[200], found_train[200];
    int file_train_number, file_available_seats, file_ticket_price;
    int user_authentication = 0, found_train_number = 0;
    char file_name[50], file_departure[50], file_destination[50], file_date[20], file_departure_time[20];

    // Look for the train schedule
    while (fgets(fileline, sizeof(fileline), train_file) != NULL)
    {
        strcpy(saveline, fileline);
        saveline[strcspn(saveline, "\n")] = '\0';
        sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d",
               &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time,
               &file_available_seats, &file_ticket_price);
        if (file_train_number == train_number)
        {
            printf("Train Number Found: %d\n", file_train_number);
            file_available_seats--; // Decrease available seats
            sprintf(found_train, "%d;%s;%s;%s;%s;%s;%d;%d", file_train_number, file_name, file_departure,
                    file_destination, file_date, file_departure_time, file_available_seats, file_ticket_price);
            found_train_number = 1;
            break;
        }
    }

    if (!found_train_number)
    {
        printf("Train not found!\n");
        fclose(user_file);
        fclose(train_file);
        fclose(temp_user);
        remove("temp.txt");
        return;
    }

    char userdata[200], *fileUsername, *filePassword;
    int booked_section = 0;

    while (fgets(fileline, sizeof(fileline), user_file) != NULL)
    {
        strcpy(userdata, fileline);
        userdata[strcspn(userdata, "\n")] = '\0';
        fileUsername = strtok(fileline, ";");
        filePassword = strtok(NULL, "\n");

        if (booked_section)
        {
            fprintf(temp_user, "%s\n", found_train);
            booked_section = 0;
        }

        if (user_authentication && strcmp(userdata, "booked") == 0)
        {
            fprintf(temp_user, "%s\n", userdata);
            booked_section = 1;
            continue;
        }

        if (fileUsername != NULL && filePassword != NULL && strcmp(fileUsername, name) == 0 && strcmp(filePassword, password) == 0)
        {
            fprintf(temp_user, "%s\n", userdata);
            user_authentication = 1;
        }
        else
        {
            fprintf(temp_user, "%s\n", userdata);
        }
    }

    fclose(user_file);
    fclose(temp_user);
    fclose(train_file);

    // Update the seats of the booked train
    train_file = fopen(filename1, "r");
    if (train_file == NULL)
    {
        printf("Error at booking trains file\n");
        return;
    }

    FILE *temp_train = fopen("temp_trains.txt", "w");
    if (temp_train == NULL)
    {
        printf("Book_ticket temp_train\n");
        fclose(train_file);
        return;
    }

    while (fgets(fileline, sizeof(fileline), train_file) != NULL)
    {
        strcpy(saveline, fileline);
        saveline[strcspn(saveline, "\n")] = '\0';
        sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d",
               &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time,
               &file_available_seats, &file_ticket_price);
        if (file_train_number == train_number)
        {
            fprintf(temp_train, "%s\n", found_train);
        }
        else
        {
            fprintf(temp_train, "%s\n", saveline);
        }
    }

    fclose(train_file);
    fclose(temp_train);

    if (user_authentication)
    {
        if (remove(filename) != 0)
        {
            perror("Error removing old user file");
        }
        else if (rename("temp.txt", filename) != 0)
        {
            perror("Error renaming temporary user file");
        }
        else if (remove(filename1) != 0)
        {
            perror("Error removing old train file");
        }
        else if (rename("temp_trains.txt", filename1) != 0)
        {
            perror("Error renaming temporary train file");
        }
        else
        {
            printf("Ticket booked successfully!\n");
        }
    }
    else
    {
        printf("Username or password incorrect.\n");
        remove("temp.txt");
        remove("temp_trains.txt");
    }
}

void add_train(int train_number)
{
    int available_seats, ticket_price;
    char name[50], departure[50], destination[50], date[20], departure_time[20];

    printf("Enter Train Name:");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Departure: ");
    fgets(departure, sizeof(departure), stdin);
    departure[strcspn(departure, "\n")] = '\0';

    printf("Enter Destination: ");
    fgets(destination, sizeof(destination), stdin);
    destination[strcspn(destination, "\n")] = '\0';

    printf("Enter Date: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    printf("Enter Departure Time: ");
    fgets(departure_time, sizeof(departure_time), stdin);
    departure_time[strcspn(departure_time, "\n")] = '\0';

    printf("Enter Available Seats: ");
    scanf("%d", &available_seats);
    getchar();

    printf("Enter Ticket Price: ");
    scanf("%d", &ticket_price);
    getchar();

    int train_index = -1;
    for (int i = 0; i < train_count; i++)
    {
        if (strcmp(train_names[i], name) == 0)
        {
            train_index = i;
            break;
        }
    }

    if (train_index == -1)
    {
        train_index = train_count++;
        strcpy(train_names[train_index], name);
    }

    char new_schedule[200];
    sprintf(new_schedule, "%d;%s;%s;%s;%s;%s;%d;%d\n", train_number, name, departure, destination, date, departure_time, available_seats, ticket_price);

    // Check if the schedule already exists to avoid duplication
    int schedule_exists = 0;
    for (int i = 0; i < schedule_count[train_index]; i++)
    {
        if (strcmp(schedules[train_index][i], new_schedule) == 0)
        {
            schedule_exists = 1; // flag to indicate that the schedule already exists
            break;
        }
    }

    if (!schedule_exists)
    {
        strcpy(schedules[train_index][schedule_count[train_index]++], new_schedule);
        printf("Train schedule added successfully!\n");
    }
    else
    {
        printf("Train schedule already exists!\n");
    }
}

// save data Function
void save_data(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < train_count; i++)
    {
        for (int j = 0; j < schedule_count[i]; j++)
        {
            fprintf(file, "%s", schedules[i][j]);
        }
    }

    fclose(file);
}

// Update Train




void update_train(const char *filename, int train_number)
{
    FILE *file = fopen(filename, "r");  // train file
    if (file == NULL)
    {
        printf("Error At Update_train Function");
        return;
    }

    FILE *temp_train=fopen("temp_train.txt","w");
    

    

    int file_train_number,train_found=0;
    int new_train_number, available_seats, ticket_price;
    char name[50], departure[50], destination[50], date[20], departure_time[20];
    char fileline[200],save_train_data[200],saveline[200];
    //
    char file_name[50], file_departure[50], file_destination[50], file_date[20], file_departure_time[20];
     int file_ticket_price,file_available_seats;
    while (fgets(fileline,sizeof(fileline),file)!=NULL)
    {    
          strcpy(saveline,fileline);
          saveline[strcspn(saveline,"\n")]='\0';
        sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d", &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time,& file_available_seats ,&file_ticket_price);
        if (file_train_number==train_number)
        {  printf("Train Found Successfully!\n\n");
           
           strcpy(name,file_name);
            name[strcspn(name, "\n")] = '\0';
            train_found=1;
           printf("Enter New Train Number:");
                scanf("%d", &new_train_number);
                getchar();


                printf("Enter Departure (CITY): ");
                fgets(departure, sizeof(departure), stdin);
                departure[strcspn(departure, "\n")] = '\0';

                printf("Enter Destination(CITY): ");
                fgets(destination, sizeof(destination), stdin);
                destination[strcspn(destination, "\n")] = '\0';

                printf("Enter Date (DD-MM-YY): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = '\0';

                printf("Enter Departure Time(00:00 AM/PM): ");
                fgets(departure_time, sizeof(departure_time), stdin);
                departure_time[strcspn(departure_time, "\n")] = '\0';

                printf("Enter Available Seats: ");
                scanf("%d", &available_seats);
                getchar();

                printf("Enter Ticket Price: ");
                scanf("%d", &ticket_price);
                getchar();
            
             sprintf(save_train_data,"%d;%s;%s;%s;%s;%s;%d;%d",new_train_number,name,departure,destination,date,departure_time,available_seats,ticket_price);
             save_train_data[strcspn(save_train_data,"\n")]='\0';
             fprintf(temp_train,"%s\n",save_train_data);
        }

        else 
        {
            fprintf(temp_train,"%s\n",saveline);
        }

        
    }
    if (!train_found)
    {
       printf("The Train is not scheduled yet!\n");
       fclose(temp_train);
       fclose(file);
       remove("temp_train.txt");
       return;
    }
   
   fclose(temp_train);
   fclose(file);


   if (remove(filename) != 0 || rename("temp_train.txt", filename)!= 0)
    {
        perror("Error updating train file");
    }
    else
    {
        printf("Train successfully Updated\n");
    }
    

}

void display_trains(const char *filename) //
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR AT display_trains\n");
        return;
    }

    char line[200];
    int file_train_number, file_available_seats, file_ticket_price;
    char file_name[50], file_departure[50], file_destination[50], file_date[20], file_departure_time[20];
    char previous_train_name[50] = "";

    printf("Train Name\tTrain No.\tDeparture\tDestination\tDate\t\tDeparture Time\tAvailable Seats\tTicket Price\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d", &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time, &file_ticket_price, &file_available_seats);
        //  sscanf(fileline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d", &file_train_number, file_name, file_departure, file_destination, file_date, file_departure_time, &file_available_seats, &file_ticket_price);

        if (strcmp(previous_train_name, file_name) != 0)
        {
            strcpy(previous_train_name, file_name);
            printf("%-12s\n", file_name);
        }

        printf("\t\t%-12d\t%-12s\t%-12s\t%-10s\t%-15s\t%d\t\t%d\n", file_train_number, file_departure, file_destination, file_date, file_departure_time, file_ticket_price, file_available_seats);
    }

    fclose(file);
}

void load_data(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No existing data found. Starting fresh. At Load data Function\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        char name[50];
        int train_number;
        sscanf(line, "%d;%49[^;];", &train_number, name);

        int train_index = -1;
        for (int i = 0; i < train_count; i++)
        {
            if (strcmp(train_names[i], name) == 0)
            {
                train_index = i;
                break;
            }
        }

        if (train_index == -1)
        {
            train_index = train_count++;
            strcpy(train_names[train_index], name);
        }

        strcpy(schedules[train_index][schedule_count[train_index]++], line);
    }

    fclose(file);
}

// Trains Functions End
void display_cancelled_tickets(const char *filename, char username[], char password[])
{
    FILE *file = fopen(filename, "r");
    int found = 0, found2 = 0;
    if (file == NULL)
    {
        printf("Error opening file Display booked tickets\n");
        return;
    }

    char fileLine[200], saveline[200], *fileUsername, *filePassword;
    int u_file_train_number, u_file_ticket_price, u_file_available_seats;
    char u_file_name[50], file_departure[50], u_file_destination[50], u_file_date[20], u_file_departure_time[20];
    printf("Train Name\tTrain No.\tDeparture\tDestination\tDate\t\tDeparture Time\tTicket Price\t\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    while (fgets(fileLine, sizeof(fileLine), file) != NULL)
    {
        strcpy(saveline, fileLine);
        fileUsername = strtok(fileLine, ";");
        filePassword = strtok(NULL, "\n");
        fileLine[strcspn(fileLine, "\n")] = '\0';

        if (found2)
        {
            if (fileLine[0] == '$')
            {
                found2 = 0;
                break;
            }
            else
            {
                sscanf(saveline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d",
                       &u_file_train_number, u_file_name, file_departure, u_file_destination, u_file_date, u_file_departure_time,
                       &u_file_available_seats, &u_file_ticket_price);
                printf("%s\t\t%-12d\t%-12s\t%-12s\t%-10s\t%-15s\t%d\n",
                       u_file_name, u_file_train_number, file_departure, u_file_destination, u_file_date, u_file_departure_time,
                       u_file_ticket_price);
            }
        }

        if (found)
        {
            if (strcmp(fileLine, "cencelled") == 0)
            {
                found2 = 1;
            }
        }

        if (fileUsername != NULL && filePassword != NULL)
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
            {
                found = 1;
            }
        }
    }

    fclose(file);
}

void display_booked_tickets(const char *filename, char username[], char password[])
{
    FILE *file = fopen(filename, "r");
    int found = 0, found2 = 0;
    if (file == NULL)
    {
        printf("Error opening file Display booked tickets\n");
        return;
    }

    char fileLine[200], saveline[200], *fileUsername, *filePassword;
    int u_file_train_number, u_file_ticket_price, u_file_available_seats;
    char u_file_name[50], file_departure[50], u_file_destination[50], u_file_date[20], u_file_departure_time[20];
    printf("Train Name\tTrain No.\tDeparture\tDestination\tDate\t\tDeparture Time\tTicket Price\t\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    while (fgets(fileLine, sizeof(fileLine), file) != NULL)
    {
        strcpy(saveline, fileLine);
        fileUsername = strtok(fileLine, ";");
        filePassword = strtok(NULL, "\n");
        fileLine[strcspn(fileLine, "\n")] = '\0';

        if (found2)
        {
            if (fileLine[0] == '#')
            {
                found2 = 0;
                break;
            }
            else
            {
                sscanf(saveline, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%19[^;];%d;%d",
                       &u_file_train_number, u_file_name, file_departure, u_file_destination, u_file_date, u_file_departure_time,
                       &u_file_available_seats, &u_file_ticket_price);
                printf("%s\t %-12d\t%-12s\t%-12s\t%-10s\t%-15s\t%d\n",
                       u_file_name, u_file_train_number, file_departure, u_file_destination, u_file_date, u_file_departure_time,
                       u_file_ticket_price);
            }
        }

        if (found)
        {
            if (strcmp(fileLine, "booked") == 0)
            {
                found2 = 1;
            }
        }

        if (fileUsername != NULL && filePassword != NULL)
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
            {
                found = 1;
            }
        }
    }

    fclose(file);
}

void update_password(const char *filename, char search_user_name[], char search_pass[])
{

    // Open the database file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error in opening file of user.txt at update password \n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Error in creating temp file at update password\n");
        fclose(file);
        return;
    }

    char file_line[256], saveline[200], *file_pass, *file_user_n, updated_pass[50];
    int found = 0;

    while (fgets(file_line, sizeof(file_line), file) != NULL)
    {
        strcpy(saveline, file_line);
        saveline[strcspn(saveline, "\n")] = '\0';
        // here i was stucking bcz i removed newline but new line was doing in spliting the whole (\n ,;)
        file_user_n = strtok(file_line, ";");
        file_pass = strtok(NULL, "\n");

        if (strcmp(search_user_name, file_user_n) == 0 && strcmp(search_pass, file_pass) == 0)
        {
            // Prompt user for the replacement password
            printf("Enter New Password: ");
            fgets(updated_pass, sizeof(updated_pass), stdin);
            int len2 = strlen(updated_pass);
            if (updated_pass[len2 - 1] == '\n')
            {
                updated_pass[len2 - 1] = '\0';
            }

            // Write updated username and password to temp file
            fprintf(temp, "%s;%s\n", file_user_n, updated_pass);
            found = 1;
        }
        else
        {
            // Write original username and password to temp file
            fprintf(temp, "%s\n", saveline);
        }
    }

    fclose(file);
    fclose(temp);

    // Replace the original file with the temporary file
    remove(filename);
    rename("temp.txt", filename);

    if (found)
    {
        printf("Yes, the Password '%s' was found and replaced.\n", search_pass);
        printf("Your New Password: %s\n", updated_pass);
    }
    else
    {
        printf("No, Old Password is incorrect.\n");
    }
    wait_for_user();
}

// sign up
void signup(const char *filename, char name[], char pass[])
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file at sign up\n");
        return;
    }

    fprintf(file, "%s;%s\n", name, pass); // we are using a delimiter that will not appear in the username or password
    strcpy(name, "booked");
    name[strcspn(name, "\n")] = '\0';

    fprintf(file, "%s\n", name);
    strcpy(name, "#");
    name[strcspn(name, "\n")] = '\0';
    fprintf(file, "%s\n", name);

    strcpy(name, "cencelled");
    name[strcspn(name, "\n")] = '\0';

    fprintf(file, "%s\n", name);
    strcpy(name, "$");
    name[strcspn(name, "\n")] = '\0';
    fprintf(file, "%s\n", name);
    fclose(file);
    printf("User registered successfully\n");
    wait_for_user();
}

// Login By User And Admin
int login(const char *filename, char username[], char password[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file at login\n");
        return 0;
    }

    char fileLine[100], *fileUsername, *filePassword;
    while (fgets(fileLine, sizeof(fileLine), file) != NULL)
    {
        fileUsername = strtok(fileLine, ";");
        filePassword = strtok(NULL, "\n");

        if (fileUsername != NULL && filePassword != NULL)
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
            {
                fclose(file);
                return 1; // Login successful
            }
        }
    }

    fclose(file);
    return 0; // Login failed
}

void wait_for_user()
{
    printf("Press any key to proceed...\n");
    getchar(); // Waits for the user to press a key
    getchar(); // Handles the newline character after the previous input
}

void header()
{
    printf("\n");
    printf("                ===========================================\n");
    printf("                ||                                       ||\n");
    printf("                ||    WELCOME TO RAILWAY TICKET          ||\n");
    printf("                ||       MANAGEMENT SYSTEM               ||\n");
    printf("                ||                                       ||\n");
    printf("                ===========================================\n");
    printf("\n");
}