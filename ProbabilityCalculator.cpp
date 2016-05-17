#include "ProbabilityCalculator.h"
#include "Card.h"
#include <functional>
#include <QDebug>

ProbabilityCalculator::ProbabilityCalculator()
{
	
}

quint8 ProbabilityCalculator::CalculateCountCardsForBestCombination(const QPair<Card, Card> &hand, 
                                                                    const QVector<Card> &table)
{
	quint8 countCards( 0 );
	
	if ( IsFlashDraw( hand, table ) )
		countCards += 9;
	
	if ( IsStreatDraw( hand, table ) )
		countCards += 8;
	
	if ( countCards == 0 )
	{
		if ( IsPair( hand ) )
			countCards = 2;
		
		if ( IsOneLead( hand ) )
			countCards = 11;
	}
	
	if ( countCards == 0 )
		countCards = 3;
	
	return countCards;
}

bool ProbabilityCalculator::IsFlashDraw(const QPair<Card, Card> &hand, const QVector<Card> &table)
{
	quint8 countHeards( 0 );
	quint8 countDiamonds( 0 );
	quint8 countClubs( 0 );
	quint8 countSpades( 0 );
	
	auto processCardLead = [&]( const Card &card )
	{
		switch ( card.GetLead() )
		{
		case Lead::Heards:
			++countHeards;
			break;
		case Lead::Diamonds:
			++countDiamonds;
			break;
		case Lead::Clubs:
			++countClubs;
			break;
		default:
			++countSpades;
			break;
		}
	};
	
	for ( const Card &card : table )
		processCardLead( card );
	
	processCardLead( hand.first );
	processCardLead( hand.second );
	
	return ( ( countHeards > 3 ) 
	         || ( countDiamonds > 3 ) 
	         || ( countClubs > 3 ) 
	         || ( countSpades > 3 ) );
}

bool ProbabilityCalculator::IsStreatDraw(const QPair<Card, Card> &hand, 
                                         const QVector<Card> &table)
{
	if ( table.isEmpty() )
		return false;
	
	QVector<Card> temp = table;
	temp.push_back( hand.first );
	temp.push_back( hand.second );
	
	qSort( temp.begin(), temp.end(), [=]( const Card &c1, const Card &c2 )
	{
		return c1.GetNominal() < c2.GetNominal();
	}
	);
	
	bool isOrdered( false );
	for ( auto i = temp.count() - 1; i > 1 ; --i )//i > 1 - 0, 1, 2
	{
		auto first = temp.at( i ).GetNominal();
		auto second = temp.at( i - 1 ).GetNominal();
		auto third = temp.at( i - 2 ).GetNominal();
		
		if ( ( ( (quint8)third - (quint8)second ) == 1 ) && ( ( (quint8)second - (quint8)first ) == 1 ) )
		{
			isOrdered = true;
			break;
		}
	}
	
	return isOrdered;
}

bool ProbabilityCalculator::IsGotShot(const QPair<Card, Card> &hand, 
                                      const QVector<Card> &table)
{
	if ( table.isEmpty() )
		return false;
	
	QVector<Card> temp = table;
	temp.push_back( hand.first );
	temp.push_back( hand.second );
	
	qSort( temp.begin(), temp.end(), [=]( const Card &c1, const Card &c2 )
	{
		return c1.GetNominal() < c2.GetNominal();
	}
	);
	
	bool firstPair( false );
	bool secondPair( false );
	
	for ( auto i = 1; i < temp.size(); ++i )
	{
		auto first = (quint8)temp.at( i - 1 ).GetNominal();
		auto second = (quint8)temp.at( i ).GetNominal();
		
		if ( firstPair == false )
			firstPair = ( ( second - first ) == 1 );
		else if ( ( second - first ) == 1 )
		{
			secondPair = true;
			break;
		}
	}
	
	return ( firstPair && secondPair );
}

bool ProbabilityCalculator::IsFlashDrawOnTable(const QVector<Card> &table)
{
	quint8 countHeards( 0 );
	quint8 countDiamonds( 0 );
	quint8 countClubs( 0 );
	quint8 countSpades( 0 );
	
	auto processCardLead = [&]( const Card &card )
	{
		switch ( card.GetLead() )
		{
		case Lead::Heards:
			++countHeards;
			break;
		case Lead::Diamonds:
			++countDiamonds;
			break;
		case Lead::Clubs:
			++countClubs;
			break;
		default:
			++countSpades;
			break;
		}
	};
	
	for ( const Card &card : table )
		processCardLead( card );
	
	return ( ( countHeards > 1 ) 
	         || ( countDiamonds > 1 ) 
	         || ( countClubs > 1 ) 
	         || ( countSpades > 1 ) );
}

bool ProbabilityCalculator::IsStreatDrawOnTable(const QVector<Card> &table)
{
	if ( table.isEmpty() )
		return false;
	
	QVector<Card> temp = table;
	
	qSort( temp.begin(), temp.end(), [=]( const Card &c1, const Card &c2 )
	{
		return c1.GetNominal() < c2.GetNominal();
	}
	);
	
	bool isOrdered(false);
	for ( auto i = temp.count() - 1; i > 0 ; --i )//i > 1 - 0, 1, 2
	{
		auto first = temp.at( i ).GetNominal();
		auto second = temp.at( i - 1 ).GetNominal();
		
		if ( ( (quint8)second - (quint8)first ) <= 2 )
		{
			isOrdered = true;
			break;
		}
	}
	
	return isOrdered;
}

qreal ProbabilityCalculator::CalculatePotOdds(qreal pot, qreal mise)
{
	return mise / ( pot + mise );
}

qreal ProbabilityCalculator::CalculatePreFlopProbability( const QPair<Card, Card> &hand )
{
	std::function<qreal(qreal)> factorial = [&]( qreal value )->qreal
	{
		if ( value == 0 || value == 1 )
			return 1;
		
		return ( value * factorial( value - 1 ) );
	};
	
	auto calculateBernuli = [&]( qreal tacked, qreal all )
	{
		return ( (qreal)factorial( all ) / ( factorial( tacked ) * factorial( all - tacked ) ) );
	};
	
	qreal probability( 0 );
	
//	auto count = CalculateCountCardsForBestCombination( hand, QVector<Card>() );
	const quint8 countCardsInDeck( 52 );
	
	if ( IsOneLead( hand ) )
	{
		const qreal handCount = 2;
		const qreal countInDeckAutoHand = countCardsInDeck - handCount;
		const qreal countLeadCardInDeck = 13;
		const qreal countCardsOnTable = 3;
		
		probability = ( calculateBernuli( handCount, countLeadCardInDeck - handCount ) 
		                * calculateBernuli( 1, countInDeckAutoHand 
		                                    - ( countLeadCardInDeck - handCount ) ) ) 
		        / calculateBernuli( countCardsOnTable, countInDeckAutoHand );
	}
	
	return probability;
}

qreal ProbabilityCalculator::CalculateFlopToRiverProbability(const QPair<Card, Card> &hand, 
                                                             const QVector<Card> &flop)
{
	qreal probability( 0 );
	
	auto count = CalculateCountCardsForBestCombination( hand, flop );
	const quint8 countCardsInDeck( 47 );
	probability = static_cast<qreal>( count ) / countCardsInDeck;
	
	return probability;
}

qreal ProbabilityCalculator::CalculateRiverToTernProbability(const QPair<Card, Card> &hand, 
                                                             const QVector<Card> &river)
{
	qreal probability( 0 );
	
	auto count = CalculateCountCardsForBestCombination( hand, river );
	const quint8 countCardsInDeck( 46 );
	probability = static_cast<qreal>( count ) / countCardsInDeck;
	
	return probability;
}

qreal ProbabilityCalculator::CalculateExpectedValue(const QPair<Card, Card> &hand, 
                                                    const QVector<Card> &table, 
                                                    qreal pot, 
                                                    qreal mise )
{
	qreal ev( 0 );
	
	if ( table.isEmpty() )
		return ev;
	
	const quint8 countCardsOnFlop( 3 );
	const quint8 countCardsOnRiver( 4 );
	
	if ( table.count() == countCardsOnFlop )
	{
		auto prob = CalculateFlopToRiverProbability( hand, table );
		ev = prob * pot - ( mise * ( 1 - prob ) );
	}
	
	if ( table.count() == countCardsOnRiver )
	{
		auto prob = CalculateRiverToTernProbability( hand, table );
		ev = prob * pot - ( mise * ( 1 - prob ) );
	}
	
	return ev;
}

