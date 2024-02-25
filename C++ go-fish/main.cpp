#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>

using namespace std;

vector<string> splitAtSapce(string str){
    vector<string> splitString;
    string curr = "";
    int i = 0;
    for(char c : str){
        if(c != ' '){
            curr+=str[i];
        }
        else{
            splitString.push_back(curr);
            curr = "";
        }
        i++;
    }
   
    if(curr!=""){
        splitString.push_back(curr);
    }
   
    return splitString;
}

class Card{
    public:
        string name;
        string value;
       
        //Null card
        Card(){
            name="";
            value="";
        }
       
        Card(string n, string v){
            name = n;
            value = v;
        }
       
        //Getters
        string getName(){
            return name;
        }
        string getValue(){
            return value;
        }
        //Helpers
        string getCardInfo(){
            return value + " of " + name;
        }
        bool compareCard(Card x){
            return getCardInfo() == x.getCardInfo();
        }
};

class Player{
    public:
        string name;
        vector<Card> inv = {};
        vector<Card> matchInv = {};
        int pairs = 0;
       
        Player(string n){
            name = n;
        }
        Player(string n, vector<Card> i){
            name = n;
            inv = i;
        }
       
        //Getters
        string getName(){
            return name;
        }
        vector<Card> getInv(){
            return inv;
        }
        vector<Card> getMatchInv(){
            return matchInv;
        }
        string getInvStr(){
            string str="[";
            for(int i=0; i<getInv().size(); i++){
                if(i+1 == getInv().size()){
                    str+=getInv()[i].getCardInfo() + "]";
                }
                else{
                    str+=getInv()[i].getCardInfo() + ", ";
                }
            }
            return str;
        }
        string getMatchInvStr(){
            string str="[";
            for(int i=0; i<getMatchInv().size(); i++){
                if(i+1 == getMatchInv().size()){
                    str+=getMatchInv()[i].getCardInfo() + "]";
                }
                else{
                    str+=getMatchInv()[i].getCardInfo() + ", ";
                }
            }
            return str;
        }
       
        //Helpers
        bool checkForCard(string info){
            for(int i=0; i<inv.size(); i++){
                if(info == inv[i].getCardInfo()){
                    removeCard(info);
                    return true;
                }
            }
            return false;
        }
        Card getCard(string info){
            for(int i=0; i<inv.size(); i++){
                if(info == inv[i].getCardInfo()){
                    return inv[i];
                }
            }
            return Card();
        }
        void removeCardSet(string name){
            for(int i=0; i<inv.size(); i++){
                if(splitAtSapce(inv[i].getName())[2] == name){
                    inv.erase(inv.begin()+i);
                }
            }
        }
        void addCard(Card x){
            inv.push_back(x);
        }
        void removeCard(string info){
            for(int i=0; i<inv.size(); i++){
                if(inv[i].getCardInfo() == info){
                    inv.erase(inv.begin()+i);
                }
            }
        }
        bool checkForSet(){
            //for every card loop our inv and see if 3 others have the same name
            bool matched = false;
            for(int i=0; i<inv.size(); i++){
                Card currentCard = inv[i];
                int matches = 0;
                for(int z=i; z<inv.size(); z++){
                    if(z!=i){
                        Card checkCard = inv[z];
                        if(currentCard.getName() == checkCard.getName()){
                            matches++;
                        }
                    }
                }
                if(matches==3){
                    pairs++;
                    matchInv.push_back(currentCard);
                    removeCardSet(currentCard.getName());
                }
                matches=0;
            }
            return matched;
        }
       
};

class Deck{
  public:
    std::vector<string> cards = {
        "Ace of Hearts", "2 of Hearts", "3 of Hearts", "4 of Hearts", "5 of Hearts", "6 of Hearts", "7 of Hearts", "8 of Hearts", "9 of Hearts", "10 of Hearts", "Jack of Hearts", "Queen of Hearts", "King of Hearts", "Ace of Diamonds", "2 of Diamonds", "3 of Diamonds", "4 of Diamonds", "5 of Diamonds","6 of Diamonds", "7 of Diamonds", "8 of Diamonds", "9 of Diamonds", "10 of Diamonds","Jack of Diamonds", "Queen of Diamonds", "King of Diamonds","Ace of Clubs", "2 of Clubs", "3 of Clubs", "4 of Clubs", "5 of Clubs","6 of Clubs", "7 of Clubs", "8 of Clubs", "9 of Clubs", "10 of Clubs","Jack of Clubs", "Queen of Clubs", "King of Clubs","Ace of Spades", "2 of Spades", "3 of Spades", "4 of Spades", "5 of Spades","6 of Spades", "7 of Spades", "8 of Spades", "9 of Spades", "10 of Spades","Jack of Spades", "Queen of Spades", "King of Spades"};
   
    Card pullCard(){
        vector<string> info = splitAtSapce(cards[rand() % cards.size()]);
        return Card(info[2], info[0]);
    }
   
};

int main() {
    srand(time(0));
   
    Deck deck;
    Player p1 = Player("P1");
    Player p2 = Player("P2");
   
    //Give 7 cards to each player
    for(int i=0; i<7; i++){
        p1.addCard(deck.pullCard());
        p2.addCard(deck.pullCard());
    }
   
    //Game loop
    while(true){
        //******P1 turn******
        while(true){
            //Get asking card
            string p1AskingCard;
            cout << "P1's turn!" << "\n" << "Your cards: " << p1.getInvStr() << endl;
            cout << "What card would you like to ask for? ";
            getline(cin, p1AskingCard);
            if(p1.checkForCard(p1AskingCard)){
                //Check if p2 has card and p1 has card
                if(p2.checkForCard(p1AskingCard)){
                    //Has card
                    cout << "P2 has that card!" << endl << endl;
                    Card p2Card = p2.getCard(p1AskingCard);
                    p2.removeCard(p1AskingCard);
                    p1.addCard(p2Card);
                    break;
                }
                else{
                    //Go fish
                    cout << "Nope! go-fish!" << endl << endl;
                    p1.addCard(deck.pullCard());
                    break;
                }
                //Check for set
                if(p1.checkForSet()){
                    cout << "You have matches! Here is you match pile: " << p1.getMatchInvStr() << endl << endl;
                }
                //Check for win
                if(p1.getInv().size() <= 0){
                    cout << "P1 wins! game over..." << endl << endl;
                    exit;
                }
            }
            else{
                cout << "You dont have that card in your hand! try again..." << endl;
            }
        }
        //******P2 turn******
        while(true){
            //Get asking card
            string p2AskingCard;
            cout << "P2's turn!" << "\n" << "Your cards: " << p2.getInvStr() << endl;
            cout << "What card would you like to ask for? ";
            getline(cin, p2AskingCard);
            //Check if p1 has card and p2 has card
       
            if(p2.checkForCard(p2AskingCard)){
                if(p1.checkForCard(p2AskingCard)){
                    //Has card
                    cout << "P1 has that card!" << endl << endl;
                    Card p1Card = p1.getCard(p2AskingCard);
                    cout << p2AskingCard << endl;
                    p1.removeCard(p2AskingCard);
                    p2.addCard(p1Card);
                    cout << "we are adding " << p1Card.getCardInfo() << " to p2 cards" << endl << endl;
                    break;
                }
                else{
                    //Go fish
                    cout << "Nope! go-fish!" << endl << endl;
                    p2.addCard(deck.pullCard());
                    break;
                }
            }
            else{
                cout << "You dont have that card in your hand! try again..." << endl;
            }
        }
       
        //Check for set
        if(p2.checkForSet()){
            cout << "You have matches! Here is you match pile: " << p2.getMatchInvStr() << endl;
        }
        //Check for win
        if(p2.getInv().size() <= 0){
            cout << "P2 wins! game over..." << endl << endl;
            exit;
        }

    }

    return 0;
}