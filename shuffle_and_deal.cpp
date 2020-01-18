#include <iostream>
#include <algorithm>
#include <vector>


//Creating a class for card
class Card {
	public :
		std::string suit;
		std::string value;
		Card();
		Card(std::string s, std::string val);
};

Card::Card() {}
Card::Card(const std::string s,const std::string val) : suit(s),value(val){}


//Creating a Class for holding all the 52 cards
class Deck : public Card{
	
	int card_count = 52;
	int value_count =13;
	int suit_count = 4;
	
	std::vector<Card> *deck_of_cards;
	const std::string SUITS[4] = {"Hearts","Spade","Clubs","Diamonds"};
	const std::string VALUES[13] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
	
	public:
	Deck();
	void shuffle();
	void deal_card();
	void show();	
};

//Using a constructor to create a deck of cards by sequentially arranging them in order
Deck::Deck() {
	deck_of_cards = new std::vector<Card>();
	deck_of_cards->reserve(card_count);
	for(int i = 0;i<suit_count;++i)
		for(int j = 0;j<value_count;++j)
			deck_of_cards->emplace_back(Card(SUITS[i],VALUES[j]));
}


//Function to display a deck of cards
void Deck::show() {
	std::string show_card("");
	auto it = deck_of_cards->begin();

	while (it != deck_of_cards->end()) {
		show_card.append((it->suit));
		show_card.append(" of ");
		show_card.append((it->value));
		show_card.append("\n");
		it = std::next(it);
	}
	std::cout << show_card <<std::endl;
}


//Function to shuffle the cards randomly
void Deck::shuffle() {
	srand(time(NULL));
	deck_of_cards = new std::vector<Card>();
	deck_of_cards->reserve(card_count);
	
	
	std::vector<int> card_order;    //Creating a vector of 52 elements for random shuffling 
    for (int i = 0; i < card_count; i++) 
        card_order.push_back(i);
        
    // Shuffling 52 card positions randomly    
	for(int i = 0;i<card_count;++i) {     
        int j = i + (rand() % (card_count -i));   
        std::swap(card_order[i],card_order[j]);
	}
        
    
    // Get the suit index and value index from the shuffled cards 
    for(int i=0;i<card_count;++i) {
        int suit_index = card_order[i] / value_count;
        int value_index = card_order[i] % value_count;
        deck_of_cards->emplace_back(Card(SUITS[suit_index],VALUES[value_index]));      
	}
}


//Function to deal the cards
void Deck::deal_card() {
    
    if (deck_of_cards->empty())
       std::cout << "No more cards can be dealt\n" << std::endl;
    else {
        std::string show_card("");
    	auto it = deck_of_cards->begin();
        show_card.append((it->suit));
    	show_card.append(" of ");
    	show_card.append((it->value));
    	show_card.append("\n");
        
        deck_of_cards->erase(it);	//Removing each card as it is drawn
    	std::cout << show_card <<std::endl; 
    }       
}


int main() {
	Deck d;
	
	//Ordered cards
	std::cout << "Ordered deck of cards before shuffling: " << std::endl;
	d.show();
	
	//Shuffled cards
	std::cout << "Shuffled deck of cards: " << std::endl;
	d.shuffle();
	d.show();
	
	
	//Deal cards multiple times. After 52 instances, no cards are left to deal 
	for(int i=0;i<54;++i) {
	    std::cout << "Dealing a card: " << std::endl;
    	d.deal_card();
	}
}
