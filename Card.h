#ifndef CARD_H
#define CARD_H

#include <QtGlobal>
#include <QPair>

enum class Lead : quint8
{
	Heards = 0,
	Diamonds, 
	Clubs, 
	Spades
};

enum class Nominal : quint8
{
	Two = 0,
	Three, 
	Four, 
	Five, 
	Six, 
	Seven, 
	Eight, 
	Nine, 
	Ten, 
	Jack, 
	Queen, 
	King, 
	Ace
};

class Card
{
public:
	explicit Card();
	Card( Nominal nominal, Lead lead );
	
	Lead GetLead() const;
	Nominal GetNominal() const;
	
	void SetLead(const Lead &lead);
	void SetNominal(const Nominal &nominal);
	
private:
	Lead _lead;
	Nominal _nominal;
};

bool IsPair(const QPair<Card, Card> &hand);
bool IsOneLead(const QPair<Card, Card> &hand);

#endif // CARD_H
