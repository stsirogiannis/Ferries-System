// import libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// declaration of global variable
int pelates=0; // the total number of clients who can sign up


// function declarations
void user_signup(void);
void get_new_user(void);
int username_exists(char answer_username[20]);
void user_login(int p);
int check_login(void);
void input_routes(void);
void view_routes(void);
void book_trip(int p);
int compare_trips(int p, int sygkekrimeno_taksidi);
void generate_trip_id(int p);
void payment(int p);
void confirmed_trips(int p);


// struct declarations
struct USER{
    char name[20];
    char surname[20];
    int age;
    long long int card_number;
    int uni_student;
    char username[20];
    char password[8];
}user[30];

struct ROUTE{
    char port[15];
    char port_code[4];
    int deck_price;
    int airplane_type_price;
    int cabin_price;
    int vehicle_price;
}route[13];

struct date{
    int dd;
    int mm;
    int yyyy;
};

struct TRIP{
    int sinolika_taksidia;
    struct Booked_trip{
        char destination[15];
        char anagnoristiko[30];
        double total_cost;
        struct date dojD;
        struct date dojR;
        int trip_type;
        char trip_status[10];
    }booked_trip[50];
}client_trip[30];


int main(void) {

    input_routes(); // input_routes is called to assign the destination data

    // set the 'sinolika_taksidia' member to 0 for each client
    // since they haven't made any trip yet
    for (int i = 0; i<30; i++)
        client_trip[i].sinolika_taksidia = 0;

    while(1){ // infinite loop until the user presses 0
		
        // initial selection menu
        printf("*************************************\n");
        printf("*              DS FERRIES           *\n");
        printf("*************************************\n");
        printf("*                                   *\n");
        printf("*             0 -> EXIT             *\n");
        printf("*             1 -> SIGN UP          *\n");
        printf("*             2 -> LOGIN            *\n");
        printf("*                                   *\n");
        printf("*************************************\n\n");

        char answer[1];
        printf("Place your answer: ");
        scanf("%s", answer);

        // check for correct input
        if(strcmp(answer, "1") == 0) {
            if(pelates<30){
                user_signup(); // user_signup() is called
                get_new_user(); // get_new_user() is called
            } 
            else{
            	system("cls");
                printf("The maximum amount of clients has been reached");
			}
        }
        else if (strcmp(answer, "2") == 0) {
            int p; // p is the number of the client who is about to log in
            p = check_login();// check_login() is called and p receives the client's number
            user_login(p); // user_login() is called after the user is verified (argument p, i.e. the client's number)
        }
        else if (strcmp(answer, "0") == 0)
            break; // exit the program
        else{
        	system("cls");
        	printf("Invalid input. Please enter '0', '1', or '2'.\n\n");
		}
            
    }

    return 0;

}//return to main


void user_signup(void){
	
	system("cls");

    // the user is asked to enter their details
    printf("\nPlease enter your credentials below:\n");
    printf("**************************************\n");

    printf("Name: ");
    scanf("%s", user[pelates].name);
    printf("Surname: ");
    scanf("%s", user[pelates].surname);

    printf("Age: ");
    int answer_age;
    scanf("%d", &answer_age);
    while(answer_age<18){ // age check
        printf("User must be at least 18 years old\n");
        printf("Age: ");
        scanf("%d", &answer_age);
    }
    user[pelates].age = answer_age;

    long long int answer_card;
    printf("Card number (without blanks): ");
    scanf("%lld", &answer_card);
    while(answer_card < 1000000000000000 || answer_card > 9999999999999999){ // the card number must be 16 digits
        printf("\nEnter a valid 16-digit card number: ");
        printf("Card number (without blanks): ");
        scanf("%lld", &answer_card);
    }

    printf("Are you a university student?(yes/no): ");
    char answer_uni[3];
    scanf("%s", answer_uni);
    while(1) { // check the answer and then assign the appropriate value: 0/1
        if (strcmp(answer_uni, "yes") == 0){
            user[pelates].uni_student = 1;
            break;
        }
        else if (strcmp(answer_uni, "no") == 0){
            user[pelates].uni_student = 0;
            break;
        }
        else{
            printf("\nInvalid input. Please type 'yes' or 'no' \n");
            scanf("%s", answer_uni);
        }
    }

}//return to main


void get_new_user(void){

    char answer_username[20];
    printf("Username: ");
    scanf("%s", answer_username);

    while(1){

        int flag1;
        flag1 = username_exists(answer_username);
        if (flag1==1){
            printf("Username has already been taken. Please select another username: ");
            scanf("%s", answer_username);
        }
        else{
            strcpy(user[pelates].username, answer_username);
            break;
        }

    }

    printf("Password: ");
    int i=0;
    char answer_password[8];
    while(i != 7){ // infinite loop until the password length is 7

        scanf("%s", answer_password);
        for (i = 0; answer_password[i] != '\0'; ++i); // counts the characters of the password
        if(i != 7){ // checks that the password length is 7
            printf("The password must me 7 characters!\n");
            printf("Password: ");
        }
        else{
            strcpy(user[pelates].password, answer_password);
            break;
        }

    }

    pelates++; // client counter, so as not to exceed 30

    printf("User created successfully\n\n");
	system("pause");
	system("cls");

}//return to main


int username_exists(char answer_username[20]) {

    int flag=0;
    for (int i = 0; i < 30; i++) {
        if (strcmp(answer_username, user[i].username) == 0){
            flag=1;
            break;
        }
    }
    if (flag==0)
        return 0; // the username does not already exist
    else
        return 1;// the username already exists

}//return to get_new_user


int check_login(void){
	
	system("cls");
	
    printf("\n********************************\n");
    printf("Please enter your credentials:\n");
    printf("********************************\n");

    char answer_username[20], answer_password[8];
    printf("Username: ");
    scanf("%s", answer_username);
    printf("Password: ");
    scanf("%s", answer_password);

    // check the entered username & password
    while(1) {

        int i, flag=0;

        for (i = 0; i < 30; i++) { // all elements of the user struct are accessed
            if (strcmp(answer_username, user[i].username) == 0 && strcmp(answer_password, user[i].password) == 0) {
                flag=1; // if flag is 1, the user entered the correct details
                break; 
            }
        }
        if (flag==1)
            return i; // returns the client's number
        else{
            printf("Invalid input. Please try again.\n");
            printf("Username: ");
            scanf("%s", answer_username);
            printf("Password: ");
            scanf("%s", answer_password);
        }

    }

}//return to main


void user_login(int p){
	
	system("cls");

    while(1){ // infinite loop until the user types 'e'
		
        printf("\n*************************************\n");
        printf("*           USER DASHBOARD          *\n");
        printf("*************************************\n");
        printf("*                                   *\n");
        printf("*     a -> View Available Routes    *\n");
        printf("*     b -> Book Trip                *\n");
        printf("*     c -> Payment                  *\n");
        printf("*     d -> Confirmed Trips          *\n");
        printf("*     e -> Logout                   *\n");
        printf("*                                   *\n");
        printf("*************************************\n\n");

        char answer[1];
        printf("Place your answer: ");
        scanf("%s", answer);

        if (strcmp(answer, "a") == 0) // check for correct input
            view_routes(); // view_routes() is called
        else if (strcmp(answer, "b") == 0){
                if (client_trip[p].sinolika_taksidia < 30)
                    book_trip(p); // book_trip() is called with argument p, the client's number
                else{
                	system("cls");
                	printf("User cannot book more than 50 trips.\n");
				}
        }
        else if (strcmp(answer, "c") == 0){
            if(client_trip[p].sinolika_taksidia > 0){
                int flag1 = 0; // whether there is a trip in "Pending" status
                for (int i = 0; i < client_trip[p].sinolika_taksidia; i++){
                    if (strcmp(client_trip[p].booked_trip[i].trip_status, "PENDING") == 0)
                        flag1 = 1; // there is a trip in "Pending" status
                }
                if (flag1 == 1)
                    payment(p); // payment() is called with argument p, the client's number
                else{
                	system("cls");
                	printf("You have no payments due.\n"); // no pending payments
				}
            }
            else{
            	system("cls");
            	printf("You must book at least one trip first.\n");
			}
        }
        else if (strcmp(answer, "d") == 0){
            if(client_trip[p].sinolika_taksidia > 0){
                int flag2 = 0; // whether there is a trip in "Confirmed" status
                for (int i = 0; i < client_trip[p].sinolika_taksidia; i++){
                    if (strcmp(client_trip[p].booked_trip[i].trip_status, "CONFIRMED") == 0)
                        flag2 = 1; // there is a trip in "Confirmed" status
                }
                if (flag2 == 1)
                    confirmed_trips(p); // confirmed_trips() is called with argument p, the client's number
                else{
                	system("cls");
                    printf("You have not yet confirmed trips.\n");
                }
            }
            else{
            	system("cls");
                printf("You must book at least one trip first.\n");
			}
        }
        else if (strcmp(answer, "e") == 0){
        	system("cls");
            break; // return to main
        }
        else{
			system("cls");
            printf("Invalid input. Please type 'a', 'b', 'c', 'd' or 'e' \n\n");
        }


    }

}//return to main


void input_routes(void){

    // ASSIGNING DATA

    //KOS
    strcpy(route[0].port, "Kos");
    strcpy(route[0].port_code, "KOS");
    route[0].deck_price = 60;
    route[0].airplane_type_price = 80;
    route[0].cabin_price = 120;
    route[0].vehicle_price = 100;

    //RODOS
    strcpy(route[1].port, "Rodos");
    strcpy(route[1].port_code, "RHO");
    route[1].deck_price = 80;
    route[1].airplane_type_price = 100;
    route[1].cabin_price = 140;
    route[1].vehicle_price = 100;

    //KALYMNOS
    strcpy(route[2].port, "Kalymnos");
    strcpy(route[2].port_code, "KAL");
    route[2].deck_price = 60;
    route[2].airplane_type_price = 80;
    route[2].cabin_price = 120;
    route[2].vehicle_price = 100;

    //PATMOS
    strcpy(route[3].port, "Patmos");
    strcpy(route[3].port_code, "PAT");
    route[3].deck_price = 55;
    route[3].airplane_type_price = 75;
    route[3].cabin_price = 115;
    route[3].vehicle_price = 100;

    //ASTYPALAIA
    strcpy(route[4].port, "Astypalaia");
    strcpy(route[4].port_code, "AST");
    route[4].deck_price = 50;
    route[4].airplane_type_price = 70;
    route[4].cabin_price = 110;
    route[4].vehicle_price = 100;

    //KASOS
    strcpy(route[5].port, "Kasos");
    strcpy(route[5].port_code, "KAS");
    route[5].deck_price = 65;
    route[5].airplane_type_price = 85;
    route[5].cabin_price = 125;
    route[5].vehicle_price = 100;

    //KASTELORIZO
    strcpy(route[6].port, "Kastelorizo");
    strcpy(route[6].port_code, "KST");
    route[6].deck_price = 100;
    route[6].airplane_type_price = 120;
    route[6].cabin_price = 160;
    route[6].vehicle_price = 120;

    //LEROS
    strcpy(route[7].port, "Leros");
    strcpy(route[7].port_code, "LER");
    route[7].deck_price = 60;
    route[7].airplane_type_price = 80;
    route[7].cabin_price = 120;
    route[7].vehicle_price = 100;

    //KARPATHOS
    strcpy(route[8].port, "Karpathos");
    strcpy(route[8].port_code, "KAR");
    route[8].deck_price = 70;
    route[8].airplane_type_price = 90;
    route[8].cabin_price = 130;
    route[8].vehicle_price = 100;

    //SYMI
    strcpy(route[9].port, "Symi");
    strcpy(route[9].port_code, "SYM");
    route[9].deck_price = 80;
    route[9].airplane_type_price = 100;
    route[9].cabin_price = 140;
    route[9].vehicle_price = 120;

    //XALKI
    strcpy(route[10].port, "Xalki");
    strcpy(route[10].port_code, "XAL");
    route[10].deck_price = 70;
    route[10].airplane_type_price = 90;
    route[10].cabin_price = 130;
    route[10].vehicle_price = 100;

    //TILOS
    strcpy(route[11].port, "Tilos");
    strcpy(route[11].port_code, "TIL");
    route[11].deck_price = 75;
    route[11].airplane_type_price = 95;
    route[11].cabin_price = 135;
    route[11].vehicle_price = 100;

    //PSERIMOS
    strcpy(route[12].port, "Pserimos");
    strcpy(route[12].port_code, "PSE");
    route[12].deck_price = 60;
    route[12].airplane_type_price = 80;
    route[12].cabin_price = 120;
    route[12].vehicle_price = 100;

}//return to main


void view_routes(void){
	
	system("cls");
		
    // print the available routes
    printf("\n***********************************************************\n");
    printf("*               AVAILABLE TRIPS FROM PIRAEUS              *\n");
    printf("***********************************************************\n\n");

    for (int i=0; i<13; i++){

        printf("PORT: %s (%s)\n", route[i].port, route[i].port_code);
        printf("DECK PRICE: %d  //  AIRPLANE TYPE PRICE: %d  //  CABIN PRICE: %d\n", route[i].deck_price,
               route[i].airplane_type_price, route[i].cabin_price);
        printf("VEHICLE PRICE: %d", route[i].vehicle_price);
        printf("\n*********************************************************************\n");

    }
    
    system("pause");
	system("cls");
	
}//return to user_login


void book_trip(int p){

    int sygkekrimeno_taksidi = client_trip[p].sinolika_taksidia;// assign the trip index to a variable for convenience
	system("cls");

    while(1){
        
        int flag1 = 0; // flag1 becomes 1 if the date entered by the user is valid

        printf("Please choose the departure date: (dd/mm/yyyy)\n");// given that the user will enter a sensible date

        printf("Day: ");
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.dd); // assign the date typed
        printf("Month: ");                                                      // by the user into the departure date struct, based on
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm); // variable p, the user's number, as well as
        printf("Year: ");                                                       // the member sinolika_taksidia, which is the number
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy);// of trips each client has made

        // CHECK THAT THE DATES DO NOT COINCIDE
        if (sygkekrimeno_taksidi > 0){
            flag1 = compare_trips(p, sygkekrimeno_taksidi); // compare_trips() is called with arguments the client number (p) and
        }                                                   // the specific trip the client is booking (=client_trip[p].sinolika_taksidia)
        else
            break;// this is the user's first trip booking, so there is no need to compare dates

        if (flag1 == 1)
            break;
        else
            printf("\nThe dates you have entered cannot be on top of a previous booking date. Please try again.\n");

    }

    char answer[5];
    printf("\nSelect your destination (e.g. RHO): ");
    scanf("%s", answer);

    int proorismos, flag = 0; // flag indicates whether the port exists or not
    while(1) {

        for (int i = 0; i < 13; i++) {
            if (strcmp(route[i].port_code, answer) == 0){ // check that the entered destination is valid
                flag = 1;
                proorismos = i; // store the destination
                break;
            }
        }
        if (flag == 1)
            break;
        else {
            printf("\nInvalid input. Please try again.\n");
            scanf("%s", answer);
        }

    }


    printf("\nChoose between 1 and 3 for your preferred seat/cabin: \n");
    printf("****************************\n");
    printf("*     1 -> Deck            *\n");
    printf("*     2 -> Airplane Type   *\n");
    printf("*     3 -> Cabin           *\n");
    printf("****************************\n\n");

    char seat_type[1];
    printf("Place your answer: ");
    scanf("%s", seat_type);
    double arxiko_kostos;

    while(1){ // check for correct input - seat type selection
        if (strcmp(seat_type, "1") == 0){
            arxiko_kostos = route[proorismos].deck_price;
            break;
        }
        else if (strcmp(seat_type, "2") == 0){
            arxiko_kostos = route[proorismos].airplane_type_price;
            break;
        }
        else if (strcmp(seat_type, "3") == 0){
            arxiko_kostos = route[proorismos].cabin_price;
            break;
        }
        else{
            printf("Invlid input. Please type '1' , '2' or '3'. \n");
            printf("Place your answer: ");
            scanf("%s", seat_type);
        }
    }

    int vehicle_flag = 0;

    printf("\nDo you want to include your vehicle in your trip? (yes/no): ");
    char answer_vehicle[3];
    scanf("%s", answer_vehicle);
    while(1) { // check the answer and then assign the appropriate value to the flag: 0/1
        if (strcmp(answer_vehicle, "yes") == 0){
            vehicle_flag = 1;
            break;
        }
        else if (strcmp(answer_vehicle, "no") == 0)
            break;
        else{
            printf("\nInvalid input. Please type 'yes' or 'no' \n");
            scanf("%s", answer_vehicle);
        }
    }

    int return_flag = 0;

    if (vehicle_flag == 1)
        arxiko_kostos += route[proorismos].vehicle_price;

    printf("Are you planning a return trip also? (yes/no): ");
    char return_answer[3];
    scanf("%s", return_answer);
    while(1){
        if (strcmp(return_answer, "yes") == 0){ // check for correct input
            return_flag = 1;
            printf("Please choose the return date: (dd/mm/yyyy): \n");// given that the user will enter a valid date
            printf("Day: ");
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.dd);  // assign the date typed
            printf("Month: ");                                                                   // by the user into the return date struct, based on
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.mm);  // variable p, the user's number, as well as
            printf("Year: ");                                                                    // the member sinolika_taksidia, which is the number
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.yyyy);// of trips each client has made
            break;
        }
        else if (strcmp(return_answer, "no") == 0)
            break;
        else{
            printf("\nInvalid input. Please type 'yes' or 'no' \n");
            scanf("%s", return_answer);
        }

    }

    if (return_flag == 1) {// assign 0/1 to the trip_type of the client's current trip
        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type = 1;
    }
    else
        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type = 0;

    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].destination, route[proorismos].port); // copy the port string

    double return_kostos, synoliko_kostos;

    if (return_flag == 1)
        return_kostos = (75.00/100.00)*arxiko_kostos;
    else
        return_kostos = 0.00;

    synoliko_kostos = arxiko_kostos + return_kostos;

    // if the user is a student, apply the discount
    if (user[p].uni_student == 1)
        synoliko_kostos = synoliko_kostos/2;

    // assign the total amount to the user's current trip
    client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].total_cost = synoliko_kostos;

    // initialize the booking status as pending
    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_status, "PENDING");

    // generate_trip_id() is called to create the unique booking number
    generate_trip_id(p);
    
    system("cls");

    printf("\n*************************************************\n");
    printf("           TOTAL COST OF TRIP: %.2f\n", synoliko_kostos);
    printf("*************************************************\n");
    printf("          Destination: %s\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].destination);
    printf("          User: %s\n", user[p].username);
    printf("          Departure date: %02d/%02d/%d\n",  client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.dd,
                                                        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.mm,
                                                        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.yyyy);
    if (return_flag == 1) // if a return route exists
        printf("          Return date: %02d/%02d/%d\n",  client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.dd,
                                                         client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.mm,
                                                         client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.yyyy);

    printf("          Trip type: %d\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type);
    printf("          Trip status: %s\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_status);
    printf("          Trip ID: %s\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].anagnoristiko);
    printf("*************************************************\n");


    client_trip[p].sinolika_taksidia += 1; // increase the user's trip count
    
    system("pause");
    system("cls");

}//return to user_login


int compare_trips(int p, int sygkekrimeno_taksidi){

    int flag = 0;

    // compare day, month and year of the current booking with the previous one
    if(client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.dd != 0){ // if the previous trip had a return 

        if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.dd <= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.dd){
            if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm > client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.mm &&
                client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.yyyy){
                    
                flag = 1;
            }
        }
        else {
             if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.mm &&
                client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.yyyy){
                    
                flag = 1;
            }

        }
    }
    else{ // if the previous trip has no return (it's one-way)
        if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.dd <= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojD.dd){     
            if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm > client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojD.mm &&
                client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojD.yyyy){
                    
                flag = 1;
            }
        }
        else {
            if (client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojD.mm &&
                client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy >= client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojD.yyyy){
                    
                flag = 1;
            }

        }

    }

    if (flag == 1)
        return 1; //
    else
        return 0;


}//return to book_trip


void generate_trip_id(int p){

    // convert the ints to strings and
    // add a leading 0 for days and months < 10

    char day[3], month[3], year[5], special_char[] = "-";

    if (client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.dd < 10) 
        sprintf(day, "0%d", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.dd);
    else
        sprintf(day, "%d", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.dd);

    if (client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.mm < 10) 
        sprintf(month, "0%d", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.mm);
    else
        sprintf(month, "%d", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.mm);

    sprintf(year, "%d", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojD.yyyy); 

    char anagnoristiko[30]; // temporary variable

    // merge all the strings into one, to create the booking identifier

    sprintf(anagnoristiko, "%s%s%s%s%s", day, month, year, special_char, user[p].username);

    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].anagnoristiko, anagnoristiko);

}//return to book_trip


void payment(int p){
	
	system("cls");

    while(1){

        // pending payments
        printf("\n****************************************\n");
        printf("*            PAYMENTS DUE              *\n");
        printf("****************************************\n\n");

        int flag = 0; // flag indicates there are still pending payments, so their data is printed
        for(int i = 0; i < client_trip[p].sinolika_taksidia; i++){ 

            if (strcmp(client_trip[p].booked_trip[i].trip_status, "PENDING") == 0){ // prints all trips that are in PENDING status

                flag = 1;
            
                printf("          Destination: %s\n", client_trip[p].booked_trip[i].destination);
                printf("          Total Cost of Trip: %.2f\n", client_trip[p]. booked_trip[i].total_cost);
                printf("          User: %s\n", user[p].username);
                printf("          Departure date: %02d/%02d/%d\n",  client_trip[p].booked_trip[i].dojD.dd,
                                                                    client_trip[p].booked_trip[i].dojD.mm,
                                                                    client_trip[p].booked_trip[i].dojD.yyyy);
                if (client_trip[p].booked_trip[i].dojR.dd != 0)
                    printf("          Return date: %02d/%02d/%d\n", client_trip[p].booked_trip[i].dojR.dd,
                                                                    client_trip[p].booked_trip[i].dojR.mm,
                                                                    client_trip[p].booked_trip[i].dojR.yyyy);

                printf("          Trip type: %d\n", client_trip[p].booked_trip[i].trip_type);
                printf("          Trip status: %s\n", client_trip[p].booked_trip[i].trip_status);
                printf("          Trip ID: %s\n", client_trip[p].booked_trip[i].anagnoristiko);
                printf("*************************************************\n");

            }

        }

        if (flag == 0){
        	system("cls");
        	printf("There are no more unconfirmed bookings.\n");
        	break;
		}
        



        int katohos = -2; // -2 if a wrong answer is entered, -1 if an ID that has already been confirmed is entered. Any
                          // other value means the entered ID is in PENDING status
        char answer[30];
        printf("\nPlease enter the unique Trip ID in order to complete your booking OR\n");
        printf("type 0 to return to USER DASHBOARD\n");
        scanf("%s", answer);

        if (strcmp(answer, "0") == 0){
            break; // return to user dashboard
        }

        int k; // counter for the user's trips


        for (k = 0; k < client_trip[p].sinolika_taksidia; k++ ){

            if (strcmp(answer, client_trip[p].booked_trip[k].anagnoristiko) == 0){
                if (strcmp(client_trip[p].booked_trip[k].trip_status, "PENDING") == 0)
                    katohos = k;
                else{
                    katohos = -1;
                    printf("The Trip ID you have entered has already been confirmed.\n");
                }
                break;
            }
        
            
        
        }

        if (katohos == -2)
            printf("\nInvalid input. Please try again.\n");
        else if (katohos == -1)
            printf("Please choose among the unconfirmed trips below.\n");
        else{
            strcpy(client_trip[p].booked_trip[katohos].trip_status, "CONFIRMED"); // the trip becomes 'confirmed'
            system("cls");
            printf("\nYour trip %s has successfully been confrimed\n", client_trip[p].booked_trip[katohos].anagnoristiko);
        }

    }
    
    system("pause");

}//return to user_login


void confirmed_trips(int p){

	system("cls");
	
    char answer[5];
    if (client_trip[p].sinolika_taksidia > 1){ // if the user has made at least 2 trips, they are given the option to sort by date
        printf("\nPlease choose how would you like to sort your confirmed bookings.\n ");
        printf("LOW: descending order.\n"); // descending order
        printf("HIGH: ascending order.\n"); // ascending order
        while(1){
            printf("Place your answer: ");
            scanf("%s", answer);
            if (strcmp(answer, "LOW") == 0 || strcmp(answer, "HIGH") == 0)// check for correct input
                break;
            else
                printf("Invalid input. please type 'HIGH' or 'LOW'.\n");
        }

        system("cls");

        if (strcmp(answer, "HIGH") == 0 ){
            
            for(int i = 0; i < client_trip[p].sinolika_taksidia; i++){

                if (strcmp(client_trip[p].booked_trip[i].trip_status, "CONFIRMED") == 0){
            
                    printf("          Destination: %s\n", client_trip[p].booked_trip[i].destination);
                    printf("          Total Cost of Trip: %.2f\n", client_trip[p]. booked_trip[i].total_cost);
                    printf("          User: %s\n", user[p].username);
                    printf("          Departure date: %02d/%02d/%d\n",  client_trip[p].booked_trip[i].dojD.dd,
                                                                        client_trip[p].booked_trip[i].dojD.mm,
                                                                        client_trip[p].booked_trip[i].dojD.yyyy);
                    if (client_trip[p].booked_trip[i].dojR.dd != 0) // if a return route exists
                        printf("          Return date: %02d/%02d/%d\n", client_trip[p].booked_trip[i].dojR.dd,
                                                                        client_trip[p].booked_trip[i].dojR.mm,
                                                                        client_trip[p].booked_trip[i].dojR.yyyy);

                    printf("          Trip type: %d\n", client_trip[p].booked_trip[i].trip_type);
                    printf("          Trip status: %s\n", client_trip[p].booked_trip[i].trip_status);
                    printf("          Trip ID: %s\n", client_trip[p].booked_trip[i].anagnoristiko);
                    printf("*************************************************\n");

                }

            }

        }
        else if(strcmp(answer, "LOW") == 0 ){

            for(int i = client_trip[p].sinolika_taksidia - 1; i >=0; i--){
                
                if (strcmp(client_trip[p].booked_trip[i].trip_status, "CONFIRMED") == 0){
            
                    printf("          Destination: %s\n", client_trip[p].booked_trip[i].destination);
                    printf("          Total Cost of Trip: %.2f\n", client_trip[p]. booked_trip[i].total_cost);
                    printf("          User: %s\n", user[p].username);
                    printf("          Departure date: %02d/%02d/%d\n",  client_trip[p].booked_trip[i].dojD.dd,
                                                                        client_trip[p].booked_trip[i].dojD.mm,
                                                                        client_trip[p].booked_trip[i].dojD.yyyy);
                    if (client_trip[p].booked_trip[i].dojR.dd != 0) // if a return route exists
                        printf("          Return date: %02d/%02d/%d\n", client_trip[p].booked_trip[i].dojR.dd,
                                                                        client_trip[p].booked_trip[i].dojR.mm,
                                                                        client_trip[p].booked_trip[i].dojR.yyyy);

                    printf("          Trip type: %d\n", client_trip[p].booked_trip[i].trip_type);
                    printf("          Trip status: %s\n", client_trip[p].booked_trip[i].trip_status);
                    printf("          Trip ID: %s\n", client_trip[p].booked_trip[i].anagnoristiko);
                    printf("*************************************************\n");
                }
            }
        }
    }
    else{// print the single booking that is in CONFIRMED status

        printf("          Destination: %s\n", client_trip[p].booked_trip[0].destination);
        printf("          Total Cost of Trip: %.2f\n", client_trip[p]. booked_trip[0].total_cost);
        printf("          User: %s\n", user[p].username);
        printf("          Departure date: %02d/%02d/%d\n",  client_trip[p].booked_trip[0].dojD.dd,
                                                            client_trip[p].booked_trip[0].dojD.mm,
                                                            client_trip[p].booked_trip[0].dojD.yyyy);
        if (client_trip[p].booked_trip[0].dojR.dd != 0)
            printf("          Return date: %02d/%02d/%d\n", client_trip[p].booked_trip[0].dojR.dd,
                                                            client_trip[p].booked_trip[0].dojR.mm,
                                                            client_trip[p].booked_trip[0].dojR.yyyy);

        printf("          Trip type: %d\n", client_trip[p].booked_trip[0].trip_type);
        printf("          Trip status: %s\n", client_trip[p].booked_trip[0].trip_status);
        printf("          Trip ID: %s\n", client_trip[p].booked_trip[0].anagnoristiko);
        printf("*************************************************\n");

    }
    
    system("pause");
    system("cls");

}//return to user_login
