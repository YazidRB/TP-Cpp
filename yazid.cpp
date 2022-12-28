
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
 
 
 
// class declarations
 
class Personne
{
    public:
         std::string id;
        std::string nom;
        std::string zonegeo;
 
};
 
class Facteur : public Personne
{
    public :
        Facteur(std::string Aid , std::string Anom , std::string Azonegeo ){
            id = Aid;
            nom = Anom;
            zonegeo = Azonegeo;
        }
 
       
};
 
class Habitant : public Personne{
 
    public :
        Habitant(std::string Aid , std::string Anom , std::string Azonegeo ){
            id = Aid;
            nom = Anom;
            zonegeo = Azonegeo;
        }
 
     
};
 
class Recommande {
    public :
        std::string id;
        std::string type;
        std::string idFacteur;
        std::string idDestinataire;
   
    Recommande(std::string Aid , std::string Atype , std::string AidFacteur, std::string AidDestinataire ){
        id = Aid;
        type = Atype;
        idFacteur = AidFacteur;
        idDestinataire = AidDestinataire;
 
    }
 
 
};
 
using namespace std;
 
// return true if file exist false otherwise
inline bool is_file_exist (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
};  
 
 

string ChiperXor(std::string& originalstring,char xorKey ) {
   std::string hashPass = originalstring;
        for (int i = 0; i < originalstring.size(); i++){
          hashPass[i] = originalstring[i] ^ xorKey;
        }
        return hashPass;

};
 
// create the database
bool create_a_file(std::string filename,std::string password ){
     
    std::ofstream outfile(filename);
    std::string hashPass = ChiperXor(password,password[0]);
    cout << hashPass;
    outfile << hashPass << std::endl;
    outfile.close();
 
    if(is_file_exist(filename)) return true ;
    return false ;
};
 
int main(int argc, char const *argv[]){
 
    char choice ;
    std::string filename,password ;
    bool access = false;
    // read the file name
    system("CLS");
    cout << "the name of the database : " << endl;
    getline(cin,filename);
    filename = filename + ".txt";
 
    // check if the file exist or not
 
    // if the file  exist
    if (is_file_exist( filename )){
        system("CLS");
        cout << "Password : "<< endl;
        getline(cin, password);
        std::string hashPass = ChiperXor(password,password[0]);
        system("CLS");

        fstream newfile;
        newfile.open((filename),ios::in); //open a file to perform read operation using file object
        if (newfile.is_open()){ //checking whether the file is open
           std::string tp;
           getline(newfile, tp);
           if(tp == hashPass) access=true;

           newfile.close(); //close the file object.
        }

    }
    // if the file is not exist  
    else{
        system("CLS");
        cout << "The file doesn't exist !"<< endl << "we will create it" << endl<< endl ;
        cout << "make a strong password : " << endl ;
        getline( cin , password );
       
 
        // generated the database :
        system("CLS");
        if (create_a_file(filename,password))
        cout << " your database is generated ! " << endl;
        else
        cout << " Erreur ! something is wrong ... " << endl;
        access = true;
 
    }
 
    // after enter to database
    if(access){
        string factNom,factID,factZone ;
    do{
        cout<< "chose the action :  "<< endl<< endl;
        cout<< " 1 : Add a line   "<< endl;
        cout<< " 2 : Remove a line   "<< endl;
        cout<< " 3 : Print the database   "<< endl;
        cout<< " 0: Exit"<< endl;
        std::cin >> choice;
 
        // add a line
        if( choice == '1'){
            system("CLS");
            cout << "what you want to add ? "<< endl << endl;
            cout << "1: facteur "<<endl;
            cout << "2: habitant  "<<endl;
            cout << "3: Recommand "<<endl;
 
            char choice2;  
            std::cin >> choice2;
            fstream newfile;
 
            string test ;

            if(choice2=='1'){
                system("CLS");
                cout << " - Facteur Informations - \n  \n";
                getline(cin,test);

                cout <<"Donner le nom de Facteur : \n";
                getline(cin,factNom);
                cout << "Donner la zone de Facteur : \n";
                getline(cin,factZone);
                cout << "Donner le id de Facteur : \n";
                getline(cin,factID);

                newfile.open(filename,ios::app);  // open a file to perform write operation using file object
                if(newfile.is_open()) {//checking whether the file is open {
                    
                    Facteur fact =  Facteur(factID,factNom,factZone);
                    string factLine = "Facteur : "+ fact.nom +' ' + fact.id  + ' ' + fact.zonegeo +'\n';
                    newfile<<ChiperXor(factLine,password[0]); //inserting text
                    newfile.close(); //close the file object
                }
            }
            // add Habitant
            else if(choice2 == '2'){
                string habNom, habID,habZone ;
                string test;
                system("CLS");
                cout << " - Habitant Informations - \n  \n";
                getline(cin,test);

                cout << " donner le nom de l'Habitant : \n";
                getline(std::cin,habNom);
                cout << " donner la zone de l'Habitant : \n";
                getline(std::cin,habZone);
                cout << " donner le id de l'Habitant : \n";
                getline(std::cin,habID);
                    newfile.open(filename,ios::app);  // open a file to perform write operation using file object            
                    if(newfile.is_open()) {//checking whether the file is open {
                        Habitant habitant =  Habitant(habID,habNom,habZone);
                        string habline = "Habitant : "+ habitant.nom +' ' + habitant.id  + ' ' + habitant.zonegeo +'\n';
                        newfile<<ChiperXor(habline,password[0]); //inserting text
                        newfile.close(); //close the file object
                    }
            }
            //add Recommande
            else if(choice2=='3'){
                std::string idRec;
                std::string typeRec;
                std::string idFacteurRec;
                std::string idDestinataireRec;
                system("CLS");
                cout << " - Recommande Informations - \n  \n";
                getline(cin,test);

                do{
                 cout << " donner le id de Recommande 1: lettre  2: colis  \n";
                 getline(std::cin,idRec);
                 if(idRec!="1" && idRec!="2"){
                    cout << " wrong choice ! Please '1' or '2'  "<< endl;
                 }
                } while(idRec!="1" && idRec!="2");

                if(idRec=="1") idRec = "lettre";
                else idRec ="colis";

                cout << " donner le type de Recommande: \n";
                getline(std::cin,typeRec);
                cout << " donner  idFacteur de Recommande : \n";
                getline(std::cin,idFacteurRec);
                cout << " donner  idDestinataire de Recommande : \n";
                getline(std::cin,idDestinataireRec);

                    newfile.open(filename,ios::app);  // open a file to perform write operation using file object            
                    if(newfile.is_open()) {//checking whether the file is open {
                        Recommande recommande =  Recommande(idRec,typeRec,idFacteurRec,idDestinataireRec);
                        string recline = "Recommande : "+ recommande.type +' ' + recommande.id  + ' ' + recommande.idFacteur + recommande.idDestinataire +'\n';
                        newfile<< ChiperXor(recline,password[0]); //inserting text
                        newfile.close(); //close the file object
                    }

                
 
            }   //invalide choice
            else{
                system("CLS");
                cout << " invalide choice !! "<< endl;
 
            }
        }
     

         
        // read the database
         else if (choice == '3')
        {   
              system("CLS");
              cout << "The file content : "<< endl;
              cout << "****************************"<< endl;
              cout << " "<< endl << endl;
              fstream newfile;
                newfile.open((filename),ios::in); //open a file to perform read operation using file object
                if (newfile.is_open()){ //checking whether the file is open
                    std::string tp;
                    while(getline(newfile, tp)){ //read data from file object and put it into std::string.
                        if(ChiperXor(tp,password[0])!=password)
                            {
                                cout <<  ChiperXor(tp,password[0]).substr(1) << "\n"; //print the data of the std::string
                                
                            }
                    }
                    newfile.close(); //close the file object.
                }
              cout << "****************************"<< endl;
        }
        else if(choice=='0'){
            return 0;
        }
        else {

            system("CLS");
            cout << " invalide choice ! " << endl ;
         }
        }// invalide access is false
        while(true); }

        else{
    
            system("CLS");
            cout << "Password in incorrect ! " << endl ;
    
        }
  
 
    }
