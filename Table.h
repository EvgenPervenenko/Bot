#ifndef TABLE_H
#define TABLE_H

#include <QVector>

class Card;

enum class Stage : quint8
{
	PreFlop = 0, 
	Flop, 
	River, 
	Tern
};

class Table
{
public:
	Table();
	
	void AddCards(const QVector<Card> & );
	void ClearTable();
	
private:
	void SetStage();
	
private:
	QVector<Card> _cards;
	Stage _stage;
};

#endif // TABLE_H
