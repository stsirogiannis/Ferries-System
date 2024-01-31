
//eisagogi bibliothikon
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//dilosi global metavliton
int pelates=0; //oi sinolikoi pelates pou mporoun na eggrafoun


//dilosi sinartiseon
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


// dilosi domon
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

    input_routes(); //kaleitai i sinartisi input_routes gia na ekhorithoun ta dedomena ton proorismon

    //ekhorisi tis timis 0 sto member 'sinolika_taksidia' kathe pelati
    //afou den exei pragmatopoihsei kapoio taksidi akoma
    for (int i = 0; i<30; i++)
        client_trip[i].sinolika_taksidia = 0;

    while(1){ //atermon broxos mexri o user na patisei 0
		
        //arxiko menou epilogis
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

        // elegxos orthis eisagosis
        if(strcmp(answer, "1") == 0) {
            if(pelates<30){
                user_signup(); //kaleitai i sinartisi user_signup()
                get_new_user(); //kaleitai i sinartisi get_new_user()
            } 
            else{
            	system("cls");
                printf("The maximum amount of clients has been reached");
			}
        }
        else if (strcmp(answer, "2") == 0) {
            int p; // opou p o arithmos tou pelati pou prokeitai na sindethei
            p = check_login();// kaleitai i sinartisi check_login() kai to p pairnei ton arithmo tou pelati
            user_login(p); //kaleitai i sinartisi user_login() afou o hristis epivaiveothike (orisma to p, diladi o arithmos pelati)
        }
        else if (strcmp(answer, "0") == 0)
            break; //eksodos apo to programma
        else{
        	system("cls");
        	printf("Invalid input. Please enter '0', '1', or '2'.\n\n");
		}
            
    }

    return 0;

}//end main


void user_signup(void){
	
	system("cls");

    //zitountai apo ton user na eisagei ta stoixeia tou
    printf("\nPlease enter your credentials below:\n");
    printf("**************************************\n");

    printf("Name: ");
    scanf("%s", user[pelates].name);
    printf("Surname: ");
    scanf("%s", user[pelates].surname);

    printf("Age: ");
    int answer_age;
    scanf("%d", &answer_age);
    while(answer_age<18){ //elegxos ilikias
        printf("User must be at least 18 years old\n");
        printf("Age: ");
        scanf("%d", &answer_age);
    }
    user[pelates].age = answer_age;

    long long int answer_card;
    printf("Card number (without blanks): ");
    scanf("%lld", &answer_card);
    while(answer_card < 1000000000000000 || answer_card > 9999999999999999){ // prepei to card number na einai 16-digit
        printf("\nEnter a valid 16-digit card number: ");
        printf("Card number (without blanks): ");
        scanf("%lld", &answer_card);
    }

    printf("Are you a university student?(yes/no): ");
    char answer_uni[3];
    scanf("%s", answer_uni);
    while(1) { // elegxos apantisis kai epeita ekxorisi tis katallilis timis: 0/1
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

}//epistrofi sti main


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
    while(i != 7){ //atermon brohos mexri ta psifia tou password na einai 7

        scanf("%s", answer_password);
        for (i = 0; answer_password[i] != '\0'; ++i); // metraei ta psifia tou password
        if(i != 7){ // elegxei ta psifia tou password na einai 7
            printf("The password must me 7 characters!\n");
            printf("Password: ");
        }
        else{
            strcpy(user[pelates].password, answer_password);
            break;
        }

    }

    pelates++; //metritis gia tous pelates, etsi oste na min kseperasoun tous 30

    printf("User created successfully\n\n");
	system("pause");
	system("cls");

}//epistrofi sti main


int username_exists(char answer_username[20]) {

    int flag=0;
    for (int i = 0; i < 30; i++) {
        if (strcmp(answer_username, user[i].username) == 0){
            flag=1;
            break;
        }
    }
    if (flag==0)
        return 0; //den yprxei idi to username
    else
        return 1;//yparxei idi to username

}//epistrofi stin get_new_user


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

    //elegxos eisagogis username & password
    while(1) {

        int i, flag=0;

        for (i = 0; i < 30; i++) { //ginetai prospelasi olon ton stoxeion tou struct user
            if (strcmp(answer_username, user[i].username) == 0 && strcmp(answer_password, user[i].password) == 0) {
                flag=1; // an to flag einai 1, tote o hristis eisigage sosta stoixeia
                break; 
            }
        }
        if (flag==1)
            return i; // epistrefei ton arithmo tou pelati
        else{
            printf("Invalid input. Please try again.\n");
            printf("Username: ");
            scanf("%s", answer_username);
            printf("Password: ");
            scanf("%s", answer_password);
        }

    }

}//epistrofi sti main


void user_login(int p){
	
	system("cls");

    while(1){ //atermon brohos mexri o user na pliktrologisei 'e'
		
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

        if (strcmp(answer, "a") == 0) //elegxos orthis eisagogis
            view_routes(); //kaleitai i sinartisi view_routes()
        else if (strcmp(answer, "b") == 0){
                if (client_trip[p].sinolika_taksidia < 30)
                    book_trip(p); //kaleitai i sinartisi book_trip() me orisma to p, pou einai o arithmos tou pelati
                else{
                	system("cls");
                	printf("User cannot book more than 50 trips.\n");
				}
        }
        else if (strcmp(answer, "c") == 0){
            if(client_trip[p].sinolika_taksidia > 0){
                int flag1 = 0; // an yparxei taksidi se katastasi "Pending"
                for (int i = 0; i < client_trip[p].sinolika_taksidia; i++){
                    if (strcmp(client_trip[p].booked_trip[i].trip_status, "PENDING") == 0)
                        flag1 = 1; //yparxei taksidi se katastasi "Pending"
                }
                if (flag1 == 1)
                    payment(p); //kaleitai i sinartisi payment() me orisma to p, pou einai o arithmos tou pelati
                else{
                	system("cls");
                	printf("You have no payments due.\n"); //den iparxoun ekkremhs pliromes
				}
            }
            else{
            	system("cls");
            	printf("You must book at least one trip first.\n");
			}
        }
        else if (strcmp(answer, "d") == 0){
            if(client_trip[p].sinolika_taksidia > 0){
                int flag2 = 0; // an yparxei taksidi se katastasi "Confirmed"
                for (int i = 0; i < client_trip[p].sinolika_taksidia; i++){
                    if (strcmp(client_trip[p].booked_trip[i].trip_status, "CONFIRMED") == 0)
                        flag2 = 1; //yparxei taksii se atastasi "Confirmed"
                }
                if (flag2 == 1)
                    confirmed_trips(p); //kaleitai i sinartisi confirmed_trips() me orisma to p, pou einai o arithmos tou pelati
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
            break; //epistrofi sti main
        }
        else{
			system("cls");
            printf("Invalid input. Please type 'a', 'b', 'c', 'd' or 'e' \n\n");
        }


    }

}//epistrofi sti main


void input_routes(void){

    //EKHORISI DEDOMENON

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

}//epistrofi sti main


void view_routes(void){
	
	system("cls");
		
    //Ektiposi diathesimon diadromon
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
	
}//epistrofi stin user login


void book_trip(int p){

    int sygkekrimeno_taksidi = client_trip[p].sinolika_taksidia;//ekhorisi tou a/a tou taksidiou se mia metavliti gia logoys dieykolynsis
	system("cls");

    while(1){
        
        int flag1 = 0; //to flag1 tha ginei 1 an i imerominia pou eisagei o user einai sosti

        printf("Please choose the departure date: (dd/mm/yyyy)\n");// dedomenou oti o hristis tha valei mia imerominia pou vgazei noima

        printf("Day: ");
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.dd); // ekhorisi tis imeromminias pou pliktrologise
        printf("Month: ");                                                      // o hristis sti domi departure date, me vasi tin
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.mm); // metavliti p, opou einai o arithos tou user kathos
        printf("Year: ");                                                       // kai to member sinolika_taksidia pou einai o arithmos
        scanf("%d", &client_trip[p].booked_trip[sygkekrimeno_taksidi].dojD.yyyy);//ton taksidion pou exei kanei o kathe pelatis

        //ELEGXOS OI HMEROMHNIES NA MHN SIMPIPTOUN
        if (sygkekrimeno_taksidi > 0){
            flag1 = compare_trips(p, sygkekrimeno_taksidi); //kaleitai i sinartisi compare_trips() me orismata ton arithmo pelati (p) kai 
        }                                                   //to sygkekrimeno taksidi pou kanei o pelatis (=client_trip[p].sinolika_taksidia)
        else
            break;//ginetai kratisi tou protou taksidiou to user, ara den xreiazetai na sygkrithoun oi imerominies

        if (flag1 == 1)
            break;
        else
            printf("\nThe dates you have entered cannot be on top of a previous booking date. Please try again.\n");

    }

    char answer[5];
    printf("\nSelect your destination (e.g. RHO): ");
    scanf("%s", answer);

    int proorismos, flag = 0; // to flag episimanei an yparxei to limani i oxi
    while(1) {

        for (int i = 0; i < 13; i++) {
            if (strcmp(route[i].port_code, answer) == 0){ //elegxos oti o proorismos pou eisigage einai sostos
                flag = 1;
                proorismos = i; // apothikefsi tou proorismou
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

    while(1){ //elegxos orthis eisagogis - epilogi tipou thesis
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
    while(1) { // elegxos apantisis kai epeita ekxorisi tis katallilis timis sto flag: 0/1
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
        if (strcmp(return_answer, "yes") == 0){ //elegxos orthis eisagogis
            return_flag = 1;
            printf("Please choose the return date: (dd/mm/yyyy): \n");// dedomenou oti o hristis tha valei sosti imerominia
            printf("Day: ");
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.dd);  // ekhorisi tis imeromminias pou pliktrologise
            printf("Month: ");                                                                   // o hristis sti domi arrival date, me vasi tin
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.mm);  // metavliti p, opou einai o arithos tou user kathos
            printf("Year: ");                                                                    // kai to member sinolika_taksidia pou einai o arithmos
            scanf("%d", &client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.yyyy);//ton taksidion pou exei kanei o kathe pelatis
            break;
        }
        else if (strcmp(return_answer, "no") == 0)
            break;
        else{
            printf("\nInvalid input. Please type 'yes' or 'no' \n");
            scanf("%s", return_answer);
        }

    }

    if (return_flag == 1) {// ekhorisi timis 0/1 sto trip_type tou sygkekrimenou taksidiou tou ekastote pelati
        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type = 1;
    }
    else
        client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type = 0;

    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].destination, route[proorismos].port); //antigrafi string tou limaniou

    double return_kostos, synoliko_kostos;

    if (return_flag == 1)
        return_kostos = (75.00/100.00)*arxiko_kostos;
    else
        return_kostos = 0.00;

    synoliko_kostos = arxiko_kostos + return_kostos;

    //an o user einai foititis, efarmozetai i ekptosi
    if (user[p].uni_student == 1)
        synoliko_kostos = synoliko_kostos/2;

    //ekhorisi tou sinolikou posou sto sygkekrimeno taksidi tou user
    client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].total_cost = synoliko_kostos;

    //arxikopoihsh katastasi kratisis os ekremmhs
    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_status, "PENDING");

    //kaleitai i sinartisi generate_trip_id() gia na dimiourgithei o monadikos arithmos kratisis
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
    if (return_flag == 1) //an yparxei diadromi epistrofis
        printf("          Return date: %02d/%02d/%d\n",  client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.dd,
                                                         client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.mm,
                                                         client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].dojR.yyyy);

    printf("          Trip type: %d\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_type);
    printf("          Trip status: %s\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].trip_status);
    printf("          Trip ID: %s\n", client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].anagnoristiko);
    printf("*************************************************\n");


    client_trip[p].sinolika_taksidia += 1; //afksisi tou arithmou ton taksidion tou user
    
    system("pause");
    system("cls");

}//epistrofi stin user login


int compare_trips(int p, int sygkekrimeno_taksidi){

    int flag = 0;

    //sygkrisi meras, mina kai etous tis trexon kratisis, me tin proigoumeni
    if(client_trip[p].booked_trip[sygkekrimeno_taksidi - 1].dojR.dd != 0){ //an to proigoumeno taksidi eixe return 

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
    else{ // an to proigoumeno taksidi den eexei return (einai one-way)
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


}//epistrofi stin book_trip


void generate_trip_id(int p){

    //metatropi ton int se string kai
    //eisagogi tou 0 mprosta apo imeres kai mines <10

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

    char anagnoristiko[30]; //prosorini metavliti

    //sygxonefsi olon ton string se 1, etsi oste na dimiourgithei to anagnoristiko kratisis

    sprintf(anagnoristiko, "%s%s%s%s%s", day, month, year, special_char, user[p].username);

    strcpy(client_trip[p].booked_trip[client_trip[p].sinolika_taksidia].anagnoristiko, anagnoristiko);

}//epistrofi sto book_trip


void payment(int p){
	
	system("cls");

    while(1){

        //ekkremhs pliromes
        printf("\n****************************************\n");
        printf("*            PAYMENTS DUE              *\n");
        printf("****************************************\n\n");

        int flag = 0; //to flag episimainei oti yparxoun akoma ekkremhs pliromes, ara ektiponei ta dedomena auton
        for(int i = 0; i < client_trip[p].sinolika_taksidia; i++){ 

            if (strcmp(client_trip[p].booked_trip[i].trip_status, "PENDING") == 0){ //ektiponei ola ta taskidia pou einai se katastasi PENDING

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
        



        int katohos = -2; //-2 an eisagei lathos apantisi, -1 an eisagei ID poy exei ginei confirmed. Opoiosdipote
                          // allos arithmos simainei oti eisigage ID pou einai se katastasi PENDING
        char answer[30];
        printf("\nPlease enter the unique Trip ID in order to complete your booking OR\n");
        printf("type 0 to return to USER DASHBOARD\n");
        scanf("%s", answer);

        if (strcmp(answer, "0") == 0){
            break; //epistrofi sto user dashboard
        }

        int k; //metritis gia ta taksidia tou users


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
            strcpy(client_trip[p].booked_trip[katohos].trip_status, "CONFIRMED"); //to taksidi ginetai 'confirmed'
            system("cls");
            printf("\nYour trip %s has successfully been confrimed\n", client_trip[p].booked_trip[katohos].anagnoristiko);
        }

    }
    
    system("pause");

}//epistrofi stin user_login


void confirmed_trips(int p){

	system("cls");
	
    char answer[5];
    if (client_trip[p].sinolika_taksidia > 1){ //an o user exei kanei touylaxiston 2 taksidia, tou dinetai i dinatotita taksinomisis me vasi tin imerominia
        printf("\nPlease choose how would you like to sort your confirmed bookings.\n ");
        printf("LOW: descending order.\n"); //fthinousa seira
        printf("HIGH: ascending order.\n"); //afksousa seira
        while(1){
            printf("Place your answer: ");
            scanf("%s", answer);
            if (strcmp(answer, "LOW") == 0 || strcmp(answer, "HIGH") == 0)//elegxos orthis eisagogis
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
                    if (client_trip[p].booked_trip[i].dojR.dd != 0) //an yparxei return diadromi
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
                    if (client_trip[p].booked_trip[i].dojR.dd != 0) //an yparxei return diadromi
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
    else{//ektiponetai i monadiki kratisi pou einai se katastasi CONFIRMED

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

}//epistrofi stin user_login

