#include "Table.h"
#include "Card.h"

Table::Table() :
    _stage( Stage::PreFlop )
{
	
}

void Table::AddCards(const QVector<Card> &cards)
{
	for( const auto &c : cards )
		_cards.push_back( c );
	
	SetStage();
}

void Table::ClearTable()
{
	_cards.clear();
	_stage = Stage::PreFlop;
}

void Table::SetStage()
{
	if ( _stage == Stage::Tern )
	{
		_stage = Stage::PreFlop;
		return;
	}
		
	_stage = static_cast<Stage>( static_cast<quint8>( _stage ) + 1 );
}

