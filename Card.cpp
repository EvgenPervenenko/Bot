#include "Card.h"

Card::Card()
{
	
}

Card::Card(Nominal nominal, Lead lead) :
    _nominal( nominal )
  , _lead( lead )
{
	
}

Lead Card::GetLead() const
{
	return _lead;
}

void Card::SetLead(const Lead &lead)
{
	_lead = lead;
}

Nominal Card::GetNominal() const
{
	return _nominal;
}

void Card::SetNominal(const Nominal &nominal)
{
	_nominal = nominal;
}


bool IsPair(const QPair<Card, Card> &hand)
{
	return hand.first.GetNominal() == hand.second.GetNominal();
}

bool IsOneLead(const QPair<Card, Card> &hand)
{
	return hand.first.GetLead() == hand.second.GetLead();
}
